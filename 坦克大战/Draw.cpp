#include "pch.h"
#include "Draw.h"

//*****************************************************************************************
// ��������: WriteChar
// ����˵��: ��ָ����λ������ַ���
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: int cX				    ����ַ���������X
//			 int cY					����ַ���������Y
//			 const char * szBuffer	Ҫ������ַ���
//			 WORD wColor	        ����ַ�������ɫ
// �� �� ֵ: void
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
// ��������: DrawMap
// ����˵��: ������ͼ��ľͷ��Χǽ����ǽ��������
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: void
//*****************************************************************************************
void DrawMap()
{
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			if (g_aMap[i][j] == WALL)					  //Χǽ
			{

				WriteChar(i, j, "��");
			}
			else if (g_aMap[i][j] == WOOD)				  //ľͷ
			{
				WriteChar(i, j, "��", FOREGROUND_GREEN);
			}
			else if (g_aMap[i][j] == IRON)				  //��ǽ
			{
				WriteChar(i, j, "��", FOREGROUND_RED);	  
			}
			else if (g_aMap[i][j] == GEN)				  //����
			{
				WriteChar(i, j, "��", FOREGROUND_RED | FOREGROUND_GREEN);
			}
		}
	}
}

//*****************************************************************************************
// ��������: DrawTank
// ����˵��: ����̹�˻������̹��
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK objTank		  ̹��ָ��
//			 const char* szOrder  ��̹�˻������̹������
// �� �� ֵ: void
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
// ��������: DrawBottk
// ����˵��: ����������̹��
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK * BottkList  ������̹������
// �� �� ֵ: void
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
// ��������: DrawBT
// ����˵��: �����ӵ���������ӵ�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PBULLET bt			   �ӵ���ָ��
//			 const char * szOrder  �����ӵ���������ӵ�������
// �� �� ֵ: void
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
		strcpy_s(szbuffer, 10, "��");
		t = BT;
	}
	WriteChar(bt->m_uBulltX, bt->m_uBulltY, szbuffer, FOREGROUND_BLUE);
	g_aMap[bt->m_uBulltX][bt->m_uBulltY] = t;
}

//*****************************************************************************************
// ��������: DrawHealthAndScore
// ����˵��: ��������ֵ�ͳɼ�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: void
//*****************************************************************************************
void DrawHealthAndScore()
{
	WriteChar(g_ScoreX + 6, g_ScoreY - 8, "����ֵ");
	WriteChar(g_ScoreX + 7, g_ScoreY - 6, "    ");
	char buffer[10];
	sprintf_s(buffer, "%d", g_nHealth);
	WriteChar(g_ScoreX + 7, g_ScoreY - 6, buffer);
	WriteChar(g_ScoreX + 6, g_ScoreY - 12, "����");
	WriteChar(g_ScoreX + 7, g_ScoreY - 10, "  ");
	char buffer1[10];
	sprintf_s(buffer1, "%d", g_nScore);
	WriteChar(g_ScoreX + 7, g_ScoreY - 10, buffer1);
}

//*****************************************************************************************
// ��������: ScoreBoard
// ����˵��: �����ɼ���
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: void
//*****************************************************************************************
void ScoreBoard()
{
	for (int i = g_ScoreX; i < g_ScoreX + 15; i++)
	{
		for (int j = 0; j < g_ScoreY; j++)
		{
			if (i == g_ScoreX || i == 74 || j == 0 || j == g_ScoreY - 1)
			{
				WriteChar(i, j, "��", FOREGROUND_GREEN | FOREGROUND_RED);
			}
		}
	}
}

//*****************************************************************************************
// ��������: Tips
// ����˵��: ������ʾ��
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: void
//*****************************************************************************************
void Tips()
{
	for (int i = g_ScoreX; i < 75; i++)
	{
		for (int j = 0; j < g_ScoreY; j++)
		{
			if (i == g_ScoreX || i == 74 || j == 0 || j == g_ScoreY - 1)
			{
				WriteChar(i, j, "��", FOREGROUND_GREEN | FOREGROUND_RED);
			}
			if (i == (g_ScoreX + 3) && j == 3)
			{
				WriteChar(i, j, "�س�������");
				WriteChar(i, j + 2, "ESC��������ͼ");
				WriteChar(i, j + 4, "�� ľͷ",FOREGROUND_GREEN);
				WriteChar(i, j + 6, "�� ��ǽ", FOREGROUND_RED);
			}
		}
	}
}

//*****************************************************************************************
// ��������: Home
// ����˵��: ���������ļ�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: void
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