#include "pch.h"
#include "Engine.h"

//*****************************************************************************************
// 函数名称: InitMap
// 函数说明: 初始化地图为空
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: void
//*****************************************************************************************
void InitMap()
{
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			g_aMap[i][j] = 0;
		}
	}
}

//*****************************************************************************************
// 函数名称: CreateWall
// 函数说明: 创建围墙
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: void
//*****************************************************************************************
void CreateWall()
{
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			if (i == 0 || i == g_MaxX - 1 || j == 0 || j == g_MaxY - 1)
			{
				g_aMap[i][j] = WALL;
			}
		}
	}
}

//*****************************************************************************************
// 函数名称: CreateObj
// 函数说明: 创建木头和铁墙
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: void
//*****************************************************************************************
void CreateObj()
{
	srand((int)time(NULL));
	int woodX = 0;
	int woodY = 0;
	for (int i = 0; i < 60; i++)
	{
		while (true)
		{
			woodX = rand() % (g_MaxX - 2) + 1;
			woodY = rand() % (g_MaxY - 2) + 1;
			if (g_aMap[woodX][woodY] == BLANK)
			{
				if (i % 2)
				{
					g_aMap[woodX][woodY] = IRON;
				}
				else
				{
					g_aMap[woodX][woodY] = WOOD;
				}
				break;
			}
		}
	}
}

//*****************************************************************************************
// 函数名称: InitBulletList
// 函数说明: 初始化子弹链表
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PBULLET *L  子弹链表的指针
// 返 回 值: void
//*****************************************************************************************
void InitBulletList(PBULLET *L)
{
	*L = (PBULLET)malloc(sizeof(BULLET) * 1);
	(*L)->next = NULL;
}

//*****************************************************************************************
// 函数名称: Shoot
// 函数说明: 发射子弹
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK objTank        坦克 
//			 PBULLET* BulletList  子弹链表的指针
//			 PTANK *BottkList     机器人坦克的指针
// 返 回 值: void
//*****************************************************************************************
void Shoot(PTANK objTank, PBULLET* BulletList, PTANK *BottkList)
{
	objTank->m_nShootTimeEnd = clock();
	if (objTank->m_nShootTimeEnd - objTank->m_nShootTimeStart > 500)
	{
		objTank->m_nShootTimeStart = objTank->m_nShootTimeEnd;
		/**********记录子弹方向坐标阵营等信息**********/
		PBULLET bullet = (PBULLET)malloc(sizeof(BULLET) * 1);
		bullet->m_uBulltX = objTank->m_uTankX;
		bullet->m_uBulltY = objTank->m_uTankY;
		bullet->m_nDir = objTank->m_nDir;
		bullet->next = NULL;
		bullet->m_nCamp = objTank->m_Camp;
		switch (bullet->m_nDir)
		{
		case UP:
			bullet->m_uBulltY -= 2;
			break;
		case DOWN:
			bullet->m_uBulltY += 2;
			break;
		case LEFT:
			bullet->m_uBulltX -= 2;
			break;
		case RIGHT:
			bullet->m_uBulltX += 2;
			break;
		default:
			break;
		}
		if (!JudgeBTMove(bullet, BottkList))  //判断是否碰到东西了
		{
			/**********没有碰到东西*******************/
			bullet->next = (*BulletList)->next;
			(*BulletList)->next = bullet;
			WriteChar(bullet->m_uBulltX, bullet->m_uBulltY, "●", FOREGROUND_BLUE);
		}
		else
		{
			free(bullet);
			bullet->next = NULL;
		}
		objTank->m_nShootTimeStart = objTank->m_nShootTimeEnd;
	}
}

//*****************************************************************************************
// 函数名称: BulletPrint
// 函数说明: 遍历所有的子弹，打印出来
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PBULLET *BulletList  子弹链表的指针
//			 PTANK *BottkList	  机器人坦克链表的指针
// 返 回 值: void
//*****************************************************************************************
void BulletPrint(PBULLET *BulletList, PTANK *BottkList)
{
	PBULLET p = *BulletList;
	while (p->next)
	{
		PBULLET pOldBullet = (PBULLET)malloc(sizeof(BULLET) * 1);
		memcpy_s(pOldBullet, sizeof(BULLET), p->next, sizeof(BULLET));
		switch (p->next->m_nDir)  //子弹根据方向移动
		{
		case UP:
			p->next->m_uBulltY -= 1;
			break;
		case DOWN:
			p->next->m_uBulltY += 1;
			break;
		case LEFT:
			p->next->m_uBulltX -= 1;
			break;
		case RIGHT:
			p->next->m_uBulltX += 1;
			break;
		default:
			break;
		}
		DrawBT(pOldBullet, "CLS");
		if (JudgeBTMove(p->next, BottkList))
		{
			
			PBULLET q = p->next;
			p->next = p->next->next;
			free(q);
			q = NULL;
		}
		else
		{
			DrawBT(p->next, "BT");
			p = p->next;
		}
	}
}

//*****************************************************************************************
// 函数名称: JudgeBTMove
// 函数说明: 判断子弹飞行碰到什么
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PBULLET objBT	   单个子弹的指针
//			 PTANK* BottkList  机器人坦克链表的指针
// 返 回 值: bool 真 碰到东西
//				  假 没有碰到东西
//*****************************************************************************************
bool JudgeBTMove(PBULLET objBT, PTANK* BottkList)
{
	int flag = 0;
	PTANK q = *BottkList;
	if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == WALL)  //碰到墙了
	{
		g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] = WALL;
		WriteChar(objBT->m_uBulltX, objBT->m_uBulltY, "▓");
		flag = 1;
	}
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == WOOD)  //碰到木头了
	{
		g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] = BLANK;
		WriteChar(objBT->m_uBulltX, objBT->m_uBulltY, " ");
		flag = 1;
	}
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == IRON)  //碰到铁墙了
	{
		g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] = IRON;
		WriteChar(objBT->m_uBulltX, objBT->m_uBulltY, "¤", FOREGROUND_RED);
		flag = 1;
	}
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] >= EnTK1 && g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] <= EnTK5 && objBT->m_nCamp == Player)  //如果是玩家的子弹碰到敌人了
	{
		while (q->next)
		{
			if ((objBT->m_uBulltX >= q->next->m_uTankX - 1 && objBT->m_uBulltX <= q->next->m_uTankX + 1) && (objBT->m_uBulltY >= q->next->m_uTankY - 1 && objBT->m_uBulltY <= q->next->m_uTankY + 1))
			{
				q->next->m_nHealth--;
				if (!q->next->m_nHealth)
				{
					for (int i = q->next->m_uTankX - 1; i < q->next->m_uTankX + 2; i++)
					{
						for (int j = q->next->m_uTankY - 1; j < q->next->m_uTankY + 2; j++)
						{
							g_aMap[i][j] = BLANK;
							WriteChar(i, j, " ");
						}
					}
					PTANK p = q->next;
					q->next = q->next->next;
					free(p);
					p->next = NULL;
					g_nScore++;
					DrawHealthAndScore();
					break;
				}
				else
				{
					q = q->next;
				}
			}
			else
			{
				q = q->next;
			}
		}
		flag = 1;
	}
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == TK && objBT->m_nCamp == Enermy)  //如果是敌人的坦克碰到玩家了
	{
		g_nHealth--;  //生命值-1
		DrawHealthAndScore();
		flag = 1;
	}
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == GEN)  //如果打到将军了的话
	{
		g_nHealth = 0;
		flag = 1;
	}
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == BT)  //子弹对碰
	{
		g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] = BLANK;
		WriteChar(objBT->m_uBulltX, objBT->m_uBulltY, " ");
		flag = 1;
	}
	if (flag)
	{
		return true;  //如果碰到东西就返回true
	}
	return false;
}

//*****************************************************************************************
// 函数名称: InitMyTK
// 函数说明: 初始化我的坦克
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK ptk  我的坦克的指针
// 返 回 值: void
//*****************************************************************************************
void InitMyTK(PTANK ptk)
{
	ptk->m_uTankX = 10;
	ptk->m_uTankY = g_MaxY-3;
	ptk->m_nDir = UP;
	ptk->m_Camp = 0;  //0代表玩家
	ptk->m_uColor = g_aTkColor[0];
	strcpy_s(ptk->m_szStyle, 10, g_apStyle[0]);
	ptk->next = NULL;
	ptk->m_cKeyboardInfo = 'w';
	ptk->m_nTKNumber = TK;
	ptk->m_nShootTimeStart = clock();
	ptk->m_nHealth = g_nHealth;
}

//*****************************************************************************************
// 函数名称: TKMove
// 函数说明: 坦克的移动
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK objTank	 	  //坦克的指针
//			 PBULLET *BulletList  //子弹链表的指针
//			 PTANK *BottkList	  //机器人链表的指针
// 返 回 值: void
//*****************************************************************************************
void TKMove(PTANK objTank, PBULLET *BulletList, PTANK *BottkList)
{
	PTANK pOldtk = (PTANK)malloc(sizeof(TANK) * 1);
	memcpy_s(pOldtk, sizeof(TANK), objTank, sizeof(TANK));
	switch (objTank->m_cKeyboardInfo)
	{
	case 'w':
		objTank->m_nDir = UP;
		objTank->m_uTankY--;
		break;
	case 's':
		objTank->m_nDir = DOWN;
		objTank->m_uTankY++;
		break;
	case 'a':
		objTank->m_nDir = LEFT;
		objTank->m_uTankX--;
		break;
	case 'd':
		objTank->m_nDir = RIGHT;
		objTank->m_uTankX++;
		break;
	case 'j':
	{
		Shoot(objTank, BulletList, BottkList);
		break;
	}
	default:
		break;
	}
	if (!JudgeTKMove(objTank)) //判断碰到什么了
	{
		objTank->m_uTankX = pOldtk->m_uTankX;
		objTank->m_uTankY = pOldtk->m_uTankY;
	}
	DrawTank(pOldtk, "CLS");
	DrawTank(objTank, "TK");
	memcpy_s(pOldtk, sizeof(TANK), objTank, sizeof(TANK));
}

//*****************************************************************************************
// 函数名称: JudgeTKMove
// 函数说明: 判断坦克移动中碰到什么了
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK objTank 坦克的指针
// 返 回 值: bool 真 可以移动
//				  假 不可以移动
//*****************************************************************************************
bool JudgeTKMove(PTANK objTank)  
{
	int flag = 0;
	for (int i = objTank->m_uTankX - 1; i < objTank->m_uTankX + 2; i++)
	{
		for (int j = objTank->m_uTankY - 1; j < objTank->m_uTankY + 2; j++)
		{
			if (g_aMap[i][j] == objTank->m_nTKNumber ||  g_aMap[i][j] == BLANK)
			{
				flag++;
			}
		}
	}
	if (flag == 9)		  //9个格子都为空
	{
		return true;
	}
	else
	{
		return false;
	}
}

//*****************************************************************************************
// 函数名称: IntkList
// 函数说明: 保存地图的名字
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK * pptk  初始化机器人坦克链表
// 返 回 值: void
//*****************************************************************************************
void IntkList(PTANK * pptk)
{
	*pptk = (PTANK)malloc(sizeof(TANK) * 1);
	(*pptk)->next = NULL;
}

//*****************************************************************************************
// 函数名称: CreateBottk
// 函数说明: 创建机器人坦克
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK * pptk  机器人坦克的链表
// 返 回 值: void
//*****************************************************************************************
void CreateBottk(PTANK * BottkList)
{
	srand((int)time(NULL));
	int flag;
	for (int i = 0; i < 4; i++)
	{
		PTANK p = (PTANK)malloc(sizeof(TANK) * 1);
		p->next = NULL;
		p->m_Camp = 1;  //Enermy
		p->m_nDir = rand() % 4;  //随机方向
		strcpy_s(p->m_szStyle, 10, g_apStyle[i+1]);
		p->m_uColor = g_aTkColor[i+1];
		p->m_cKeyboardInfo = g_aKeyboard[rand() % 4];
		p->m_nTKNumber = g_aBOTNum[i];
		p->m_nShootTimeStart = clock();
		p->m_nHealth = i+1;
		while (true)
		{
			flag = 0;
			p->m_uTankX = rand() % (g_MaxX - 4) + 2;
			p->m_uTankY = rand() % (g_MaxY - 4) + 2;
			if (p->m_uTankY < 10)  //限定在上方
			{
				for (int i = p->m_uTankX - 1; i < p->m_uTankX + 2; i++)
				{
					for (int j = p->m_uTankY - 1; j < p->m_uTankY + 2; j++)
					{
						if (g_aMap[i][j] == BLANK)
						{
							flag++;
						}
					}
				}
			}
			if (flag == 9)  //==9说明了这九个格子没东西
			{
				p->next = (*BottkList)->next;
				(*BottkList)->next = p;
				break;
			}
		}
	}	
}

//*****************************************************************************************
// 函数名称: BottkMove
// 函数说明: 机器人坦克的移动
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PBULLET *BulletList  子弹链表的指针
//			 PTANK *BottkList	  机器人坦克的链表
// 返 回 值: void
//*****************************************************************************************
void BottkMove(PBULLET *BulletList, PTANK *BottkList)
{
	srand((int)time(NULL));
	PTANK p = (*BottkList)->next;
	while (p)
	{
		p->m_cKeyboardInfo = g_aKeyboard[rand() % 5];
		TKMove(p, BulletList, BottkList);
		p = p->next;
	}
}

