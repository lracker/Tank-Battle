#include "pch.h"
#include "Engine.h"

//*****************************************************************************************
// ��������: InitMap
// ����˵��: ��ʼ����ͼΪ��
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: void
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
// ��������: CreateWall
// ����˵��: ����Χǽ
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: void
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
// ��������: CreateObj
// ����˵��: ����ľͷ����ǽ
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: void
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
// ��������: InitBulletList
// ����˵��: ��ʼ���ӵ�����
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PBULLET *L  �ӵ������ָ��
// �� �� ֵ: void
//*****************************************************************************************
void InitBulletList(PBULLET *L)
{
	*L = (PBULLET)malloc(sizeof(BULLET) * 1);
	(*L)->next = NULL;
}

//*****************************************************************************************
// ��������: Shoot
// ����˵��: �����ӵ�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK objTank        ̹�� 
//			 PBULLET* BulletList  �ӵ������ָ��
//			 PTANK *BottkList     ������̹�˵�ָ��
// �� �� ֵ: void
//*****************************************************************************************
void Shoot(PTANK objTank, PBULLET* BulletList, PTANK *BottkList)
{
	objTank->m_nShootTimeEnd = clock();
	if (objTank->m_nShootTimeEnd - objTank->m_nShootTimeStart > 500)
	{
		objTank->m_nShootTimeStart = objTank->m_nShootTimeEnd;
		/**********��¼�ӵ�����������Ӫ����Ϣ**********/
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
		if (!JudgeBTMove(bullet, BottkList))  //�ж��Ƿ�����������
		{
			/**********û����������*******************/
			bullet->next = (*BulletList)->next;
			(*BulletList)->next = bullet;
			WriteChar(bullet->m_uBulltX, bullet->m_uBulltY, "��", FOREGROUND_BLUE);
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
// ��������: BulletPrint
// ����˵��: �������е��ӵ�����ӡ����
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PBULLET *BulletList  �ӵ������ָ��
//			 PTANK *BottkList	  ������̹�������ָ��
// �� �� ֵ: void
//*****************************************************************************************
void BulletPrint(PBULLET *BulletList, PTANK *BottkList)
{
	PBULLET p = *BulletList;
	while (p->next)
	{
		PBULLET pOldBullet = (PBULLET)malloc(sizeof(BULLET) * 1);
		memcpy_s(pOldBullet, sizeof(BULLET), p->next, sizeof(BULLET));
		switch (p->next->m_nDir)  //�ӵ����ݷ����ƶ�
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
// ��������: JudgeBTMove
// ����˵��: �ж��ӵ���������ʲô
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PBULLET objBT	   �����ӵ���ָ��
//			 PTANK* BottkList  ������̹�������ָ��
// �� �� ֵ: bool �� ��������
//				  �� û����������
//*****************************************************************************************
bool JudgeBTMove(PBULLET objBT, PTANK* BottkList)
{
	int flag = 0;
	PTANK q = *BottkList;
	if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == WALL)  //����ǽ��
	{
		g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] = WALL;
		WriteChar(objBT->m_uBulltX, objBT->m_uBulltY, "��");
		flag = 1;
	}
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == WOOD)  //����ľͷ��
	{
		g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] = BLANK;
		WriteChar(objBT->m_uBulltX, objBT->m_uBulltY, " ");
		flag = 1;
	}
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == IRON)  //������ǽ��
	{
		g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] = IRON;
		WriteChar(objBT->m_uBulltX, objBT->m_uBulltY, "��", FOREGROUND_RED);
		flag = 1;
	}
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] >= EnTK1 && g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] <= EnTK5 && objBT->m_nCamp == Player)  //�������ҵ��ӵ�����������
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
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == TK && objBT->m_nCamp == Enermy)  //����ǵ��˵�̹�����������
	{
		g_nHealth--;  //����ֵ-1
		DrawHealthAndScore();
		flag = 1;
	}
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == GEN)  //����򵽽����˵Ļ�
	{
		g_nHealth = 0;
		flag = 1;
	}
	else if (g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] == BT)  //�ӵ�����
	{
		g_aMap[objBT->m_uBulltX][objBT->m_uBulltY] = BLANK;
		WriteChar(objBT->m_uBulltX, objBT->m_uBulltY, " ");
		flag = 1;
	}
	if (flag)
	{
		return true;  //������������ͷ���true
	}
	return false;
}

//*****************************************************************************************
// ��������: InitMyTK
// ����˵��: ��ʼ���ҵ�̹��
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK ptk  �ҵ�̹�˵�ָ��
// �� �� ֵ: void
//*****************************************************************************************
void InitMyTK(PTANK ptk)
{
	ptk->m_uTankX = 10;
	ptk->m_uTankY = g_MaxY-3;
	ptk->m_nDir = UP;
	ptk->m_Camp = 0;  //0�������
	ptk->m_uColor = g_aTkColor[0];
	strcpy_s(ptk->m_szStyle, 10, g_apStyle[0]);
	ptk->next = NULL;
	ptk->m_cKeyboardInfo = 'w';
	ptk->m_nTKNumber = TK;
	ptk->m_nShootTimeStart = clock();
	ptk->m_nHealth = g_nHealth;
}

//*****************************************************************************************
// ��������: TKMove
// ����˵��: ̹�˵��ƶ�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK objTank	 	  //̹�˵�ָ��
//			 PBULLET *BulletList  //�ӵ������ָ��
//			 PTANK *BottkList	  //�����������ָ��
// �� �� ֵ: void
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
	if (!JudgeTKMove(objTank)) //�ж�����ʲô��
	{
		objTank->m_uTankX = pOldtk->m_uTankX;
		objTank->m_uTankY = pOldtk->m_uTankY;
	}
	DrawTank(pOldtk, "CLS");
	DrawTank(objTank, "TK");
	memcpy_s(pOldtk, sizeof(TANK), objTank, sizeof(TANK));
}

//*****************************************************************************************
// ��������: JudgeTKMove
// ����˵��: �ж�̹���ƶ�������ʲô��
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK objTank ̹�˵�ָ��
// �� �� ֵ: bool �� �����ƶ�
//				  �� �������ƶ�
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
	if (flag == 9)		  //9�����Ӷ�Ϊ��
	{
		return true;
	}
	else
	{
		return false;
	}
}

//*****************************************************************************************
// ��������: IntkList
// ����˵��: �����ͼ������
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK * pptk  ��ʼ��������̹������
// �� �� ֵ: void
//*****************************************************************************************
void IntkList(PTANK * pptk)
{
	*pptk = (PTANK)malloc(sizeof(TANK) * 1);
	(*pptk)->next = NULL;
}

//*****************************************************************************************
// ��������: CreateBottk
// ����˵��: ����������̹��
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK * pptk  ������̹�˵�����
// �� �� ֵ: void
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
		p->m_nDir = rand() % 4;  //�������
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
			if (p->m_uTankY < 10)  //�޶����Ϸ�
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
			if (flag == 9)  //==9˵������Ÿ�����û����
			{
				p->next = (*BottkList)->next;
				(*BottkList)->next = p;
				break;
			}
		}
	}	
}

//*****************************************************************************************
// ��������: BottkMove
// ����˵��: ������̹�˵��ƶ�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PBULLET *BulletList  �ӵ������ָ��
//			 PTANK *BottkList	  ������̹�˵�����
// �� �� ֵ: void
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

