#include "pch.h"
#include "Draw.h"

//*****************************************************************************************
// 函数名称: WriteChar
// 函数说明: 在指定的位置输出字符串
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: int cX				    输出字符串的坐标X
//			 int cY					输出字符串的坐标Y
//			 const char * szBuffer	要输出的字符串
//			 WORD wColor	        输出字符串的颜色
// 返 回 值: void
//*****************************************************************************************
void WriteChar(int cX, int cY, const char * szBuffer, WORD wColor)
{
	HANDLE hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOutPut, wColor);
	COORD pos = { 2 * cX,cY };
	SetConsoleCursorPosition(hOutPut, pos);
	printf("%s", szBuffer);
}

//*****************************************************************************************
// 函数名称: DrawMap
// 函数说明: 画出地图（木头、围墙、铁墙、将军）
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: void
//*****************************************************************************************
void DrawMap()
{
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			if (g_aMap[i][j] == WALL)					  //围墙
			{

				WriteChar(i, j, "▓");
			}
			else if (g_aMap[i][j] == WOOD)				  //木头
			{
				WriteChar(i, j, "※", FOREGROUND_GREEN);
			}
			else if (g_aMap[i][j] == IRON)				  //铁墙
			{
				WriteChar(i, j, "¤", FOREGROUND_RED);	  
			}
			else if (g_aMap[i][j] == GEN)				  //将军
			{
				WriteChar(i, j, "囍", FOREGROUND_RED | FOREGROUND_GREEN);
			}
		}
	}
}

//*****************************************************************************************
// 函数名称: DrawTank
// 函数说明: 画出坦克或者清除坦克
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK objTank		  坦克指针
//			 const char* szOrder  画坦克或者清除坦克命令
// 返 回 值: void
//*****************************************************************************************
void DrawTank(PTANK objTank,const char* szOrder)
{
	char szbuffer[10] = { 0 };
	int t = BLANK;
	if (!strcmp("CLS", szOrder))
	{
		strcpy_s(szbuffer, 10, " ");
		t = BLANK;
	}
	else if (!strcmp("TK", szOrder))
	{
		strcpy_s(szbuffer, 10, objTank->m_szStyle);
		t = objTank->m_nTKNumber;
	}
	for (int i = objTank->m_uTankX - 1; i < objTank->m_uTankX + 2; i++)
	{
		for (int j = objTank->m_uTankY - 1; j < objTank->m_uTankY + 2; j++)
		{
			if (g_aTank[objTank->m_nDir][j - objTank->m_uTankY+ 1][i - objTank->m_uTankX + 1])
			{
				WriteChar(i, j, szbuffer,objTank->m_uColor);
			}
			g_aMap[i][j] = t;
		}
	}
}

//*****************************************************************************************
// 函数名称: DrawBottk
// 函数说明: 画出机器人坦克
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK * BottkList  机器人坦克链表
// 返 回 值: void
//*****************************************************************************************
void DrawBottk(PTANK * BottkList)
{
	PTANK q = (*BottkList)->next;
	while (q)
	{
		DrawTank(q, "TK");
		q = q->next;
	}
}

//*****************************************************************************************
// 函数名称: DrawBT
// 函数说明: 画出子弹或者清除子弹
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PBULLET bt			   子弹的指针
//			 const char * szOrder  画出子弹或者清掉子弹的命令
// 返 回 值: void
//*****************************************************************************************
void DrawBT(PBULLET bt, const char * szOrder)
{
	char szbuffer[10] = { 0 };
	int t = BLANK;
	if (!strcmp("CLS", szOrder))
	{
		strcpy_s(szbuffer, 10, " ");
		t = BLANK;
	}
	else if (!strcmp("BT", szOrder))
	{
		strcpy_s(szbuffer, 10, "●");
		t = BT;
	}
	WriteChar(bt->m_uBulltX, bt->m_uBulltY, szbuffer, FOREGROUND_BLUE);
	g_aMap[bt->m_uBulltX][bt->m_uBulltY] = t;
}

//*****************************************************************************************
// 函数名称: DrawHealthAndScore
// 函数说明: 画出生命值和成绩
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: void
//*****************************************************************************************
void DrawHealthAndScore()
{
	WriteChar(g_ScoreX + 6, g_ScoreY - 8, "生命值");
	WriteChar(g_ScoreX + 7, g_ScoreY - 6, "    ");
	char buffer[10];
	sprintf_s(buffer, "%d", g_nHealth);
	WriteChar(g_ScoreX + 7, g_ScoreY - 6, buffer);
	WriteChar(g_ScoreX + 6, g_ScoreY - 12, "分数");
	WriteChar(g_ScoreX + 7, g_ScoreY - 10, "  ");
	char buffer1[10];
	sprintf_s(buffer1, "%d", g_nScore);
	WriteChar(g_ScoreX + 7, g_ScoreY - 10, buffer1);
}

//*****************************************************************************************
// 函数名称: ScoreBoard
// 函数说明: 画出成绩板
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: void
//*****************************************************************************************
void ScoreBoard()
{
	for (int i = g_ScoreX; i < g_ScoreX + 15; i++)
	{
		for (int j = 0; j < g_ScoreY; j++)
		{
			if (i == g_ScoreX || i == 74 || j == 0 || j == g_ScoreY - 1)
			{
				WriteChar(i, j, "※", FOREGROUND_GREEN | FOREGROUND_RED);
			}
		}
	}
}

//*****************************************************************************************
// 函数名称: Tips
// 函数说明: 画出提示板
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: void
//*****************************************************************************************
void Tips()
{
	for (int i = g_ScoreX; i < 75; i++)
	{
		for (int j = 0; j < g_ScoreY; j++)
		{
			if (i == g_ScoreX || i == 74 || j == 0 || j == g_ScoreY - 1)
			{
				WriteChar(i, j, "※", FOREGROUND_GREEN | FOREGROUND_RED);
			}
			if (i == (g_ScoreX + 3) && j == 3)
			{
				WriteChar(i, j, "回车：保存");
				WriteChar(i, j + 2, "ESC：撤销绘图");
				WriteChar(i, j + 4, "※ 木头",FOREGROUND_GREEN);
				WriteChar(i, j + 6, "¤ 铁墙", FOREGROUND_RED);
			}
		}
	}
}

//*****************************************************************************************
// 函数名称: Home
// 函数说明: 画出保护的家
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: void
//*****************************************************************************************
void Home()
{
	for (int i = 25; i < 27; i++)
	{
		for (int j = g_MaxY-2; j > g_MaxY - 6; j--)
		{
			g_aMap[i][j] = WOOD;
		}
	}
	for (int i = 29; i < 31; i++)
	{
		for (int j = g_MaxY - 2; j > g_MaxY - 6; j--)
		{
			g_aMap[i][j] = WOOD;
		}
	}
	for (int i = 25; i < 31; i++)
	{
		g_aMap[i][g_MaxY - 4] = WOOD;
		g_aMap[i][g_MaxY - 5] = WOOD;
	}
	for (int i = 27; i < 29; i++)
	{
		g_aMap[i][g_MaxY - 2] = GEN;
		g_aMap[i][g_MaxY - 3] = GEN;
	}
}