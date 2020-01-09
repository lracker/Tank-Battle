#include "pch.h"
#include "Console.h"

//*****************************************************************************************
// ��������: CreateFolder
// ����˵��: �����ļ���
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: ���ش����ļ����Ƿ�ɹ�
//*****************************************************************************************
bool CreateFolder()
{
	//�ļ�������
	char folderName[] = "Map";
	// �ļ��в������򴴽��ļ���
	if (_access(folderName, 0) == -1)
	{
		_mkdir(folderName);
	}
	return false;
}

//*****************************************************************************************
// ��������: SaveMap
// ����˵��: �����ͼ
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: const char* c_szFileName ��ͼ��
// �� �� ֵ: void
//*****************************************************************************************
void SaveMap(const char* c_szFileName)
{
	FILE *pFile = NULL;
	fopen_s(&pFile, c_szFileName, "wb+");
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			fprintf(pFile, "%d ", g_aMap[i][j]);
		}
	}
	fclose(pFile);
    pFile = NULL;
}

//*****************************************************************************************
// ��������: ReadMap
// ����˵��: ��ȡ��ͼ
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: const char* c_szFileName
// �� �� ֵ: void
//*****************************************************************************************
void ReadMap(const char* c_szFileName)
{
	FILE *pFile = NULL;
	fopen_s(&pFile, c_szFileName, "rb");
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			fscanf_s(pFile, "%d ", &g_aMap[i][j]);
		}
	}
	fclose(pFile);
    pFile = NULL;
}

//*****************************************************************************************
// ��������: SaveMapName
// ����˵��: �����ͼ������
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: const char* c_szFileName
// �� �� ֵ: void
//*****************************************************************************************
void SaveMapName(const char* c_szFileName)
{
	FILE *pFile = NULL;
	fopen_s(&pFile, "Map\\MapName.txt", "ab+");
	fprintf(pFile, "%s ", c_szFileName);
	fclose(pFile);
    pFile = NULL;
}

//*****************************************************************************************
// ��������: LoadDeleteMap
// ����˵��: ���ػ���ɾ����ͼ
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: int LoadOrDelete LoadΪ���ص�ͼ��DeleteΪɾ����ͼ
// �� �� ֵ: bool �� �����ɹ� 
//				  �� ����ʧ��
//*****************************************************************************************
bool LoadDeleteMap(int LoadOrDelete)
{
	int nExit = 0;		 //�жϵ�ͼ�Ƿ����
	system("cls");
	FILE *pFile = NULL;
	fopen_s(&pFile, "Map\\MapName.txt", "rb");  //�򿪵�ͼ�������ļ�
	if (!pFile)  //���û������ļ�����ʾ
	{
		WriteChar(Text_LOCX, Text_LOCY, "�����Զ����ͼ");
		Sleep(1000);
		return false;
	}
	if (fgetc(pFile) == EOF)	//�����ͼɾ���˵Ļ��ͻ���ʾ
	{
		WriteChar(Text_LOCX, Text_LOCY, "�����Զ����ͼ");
		Sleep(1000);
		fclose(pFile);
		pFile = NULL;
		return false;
	}
	else
	{
		rewind(pFile);		  //����fgetc��ԭ��ʹ������pFile
		if (LoadOrDelete == Load)
		{
			WriteChar(Text_LOCX - 5, Text_LOCY, "������ʹ�õĵ�ͼ���");
		}
		else if (LoadOrDelete == Delete)
		{
			WriteChar(Text_LOCX - 5, Text_LOCY, "������ɾ����ͼ���");
		}
		PMapName MapnameList = (PMapName)malloc(sizeof(MapName) * 1);
		MapnameList->next = NULL;
		int ret = 0;		   //����Ƿ�����ļ�β
		int i = 1;				//��¼��ͼ���
		char MapNum[10];
		while (true)  //���ļ��ж�ȡ��ͼ��
		{
			PMapName temp = (PMapName)malloc(sizeof(MapName) * 1);
			ret = fscanf_s(pFile, "%s ", temp->m_szMapName, 64);
			temp->m_nChoice = i++;
			if (ret == EOF)
			{
				break;
			}
			temp->next = MapnameList->next;
			MapnameList->next = temp;
		}
		fclose(pFile);
		pFile = NULL;
		PMapName P = MapnameList;	   //����ָ��ָ������ͷ
		while (P->next)  //��ӡ��ͼ���б�
		{
			sprintf_s(MapNum, "%d", P->next->m_nChoice);
			WriteChar(Text_LOCX - 5, Text_LOCY + 2 * P->next->m_nChoice, MapNum);
			WriteChar(Text_LOCX - 3, Text_LOCY + 2 * P->next->m_nChoice, P->next->m_szMapName);
			P = P->next;
			memset(MapNum, 0, 10);
		}
		P = MapnameList;				//����ָ��
		int MapChoice = _getch() - 0x30;  //��ȡ��ͼ���
		char szSeletedMapName[64] = { 0 };			   //�����ļ���
		while (P->next)
		{
			if (MapChoice == P->next->m_nChoice)
			{
				strcpy_s(szSeletedMapName, 64, P->next->m_szMapName);  //������������ȡ��ͼ����
				nExit = 1;
				break;
			}
			P = P->next;
		}
		if (!nExit)
		{
			system("cls");
			WriteChar(Text_LOCX, Text_LOCY, "��������ȷ�����");
			Sleep(1000);
			return false;
		}
		switch (LoadOrDelete)
		{
		case 1:  //1�Ǽ��ص�ͼ
		{
            ReadMap(szSeletedMapName);
			break;
		}
		case 2:  //2��ɾ����ͼ
		{
			FILE *pFile = NULL;
			fopen_s(&pFile, "Map\\MapName.txt", "wb");
			P = MapnameList;
			while (P->next)
			{
				if (MapChoice == P->next->m_nChoice)
				{
					PMapName q = P->next;
					P->next = P->next->next;
					free(q);
					q->next = NULL;
					break;
				}
				P = P->next;
			}
			P = MapnameList;
			while (P->next)  //����д��ȥ
			{
				fprintf(pFile, "%s ", P->next->m_szMapName);
				P = P->next;
			}
			fclose(pFile);
			pFile = NULL;
			break;
		}
		}
		free(P);
		P = NULL;
		return true;
	}
}

//*****************************************************************************************
// ��������: SaveTank
// ����˵��: ������Һͻ����˵�̹��
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK pMytk		���̹��ָ��
//			 PTANK BottkList    ������̹������
//			 char* MyFileName	�������̹�˵��ļ���
//			 char* BotFileName 	���������̹�˵��ļ���
// �� �� ֵ: void
//*****************************************************************************************
void SaveTank(PTANK pMytk, PTANK BottkList, char* MyFileName, char* BotFileName)
{
	/*******���̹��*****************/
	FILE *pFile = NULL;
	fopen_s(&pFile, MyFileName, "wb");
	fwrite(pMytk, sizeof(TANK), 1, pFile);
	fclose(pFile);
	pFile = NULL;
	/**********������̹��**************/
	FILE *pFile1 = NULL;
	fopen_s(&pFile1, BotFileName, "wb");
	while (BottkList->next)
	{
		fwrite(BottkList->next, sizeof(TANK), 1, pFile1);
		BottkList = BottkList->next;
	}
	fclose(pFile1);
	pFile1 = NULL;
}

//*****************************************************************************************
// ��������: ReadTank
// ����˵��: ��ȡ��Һͻ����˵�̹��
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK pMytk		���̹��ָ��
//			 PTANK BottkList    ������̹������
//			 char* MyFileName	�������̹�˵��ļ���
//			 char* BotFileName 	���������̹�˵��ļ���
// �� �� ֵ: bool �� �����ɹ� 
//				  �� ����ʧ��
//*****************************************************************************************
bool ReadTank(PTANK *FileMyTk, PTANK *FileBotTK, char* MyFileName, char* BotFileName)
{
	/****��ȡ���̹��******/
	FILE *pFile = NULL;
	fopen_s(&pFile, MyFileName, "rb");
	if(!pFile)
	{
		WriteChar(Text_LOCX, Text_LOCY, "���ȱ���һ����Ϸ");
		Sleep(1000);
		return false;
	}
	if(fgetc(pFile) == EOF)
	{
		WriteChar(Text_LOCX, Text_LOCY, "���ȱ���һ����Ϸ");
		Sleep(1000);
		fclose(pFile);
		pFile = NULL;
		return false;
	}
	rewind(pFile);
	fread(*FileMyTk, sizeof(TANK), 1, pFile);
	fclose(pFile);
	/**********��ȡ������̹��**************/
	FILE *pFile1 = NULL;
	fopen_s(&pFile1, BotFileName, "rb");
	int ret = 0;
	while (true)
	{
		PTANK bottemp = (PTANK)malloc(sizeof(TANK) * 1);
		memset(bottemp, 0, sizeof(TANK));
		ret = fread(bottemp, sizeof(TANK), 1, pFile);
		if (ret == 0)
		{
			break;
		}
		bottemp->next = (*FileBotTK)->next;
		(*FileBotTK)->next = bottemp;
	}
	fclose(pFile1);
	return true;
}

//*****************************************************************************************
// ��������: SaveBullet	  
// ����˵��: �����ӵ�����
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PBULLET BulletList �ӵ�����
//			 char* FileName		�����ӵ����ļ���
// �� �� ֵ: void
//*****************************************************************************************
void SaveBullet(PBULLET BulletList, char* BulletFileName)
{
	FILE *pFile = NULL;
	fopen_s(&pFile, BulletFileName, "wb");
	while (BulletList->next)
	{
		fwrite(BulletList->next, sizeof(BULLET), 1, pFile);
		BulletList = BulletList->next;
	}
	fclose(pFile);
	pFile = NULL;
}

//*****************************************************************************************
// ��������: ReadBullet
// ����˵��: ��ȡ�ӵ�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PBULLET *FileBullet �ӵ������ָ��
//			 char* FileName		 �����ӵ����ļ���
// �� �� ֵ: void
//*****************************************************************************************
void ReadBullet(PBULLET *FileBullet, char* FileName)
{
	FILE *pFile = NULL;
	fopen_s(&pFile, FileName, "rb");
	int ret = 0;
	while (true)
	{
		PBULLET temp = (PBULLET)malloc(sizeof(BULLET) * 1);
		memset(temp, 0, sizeof(BULLET));
		ret = fread(temp, sizeof(BULLET), 1, pFile);
		if (ret == 0)
		{
			break;
		}
		temp->next = (*FileBullet)->next;
		(*FileBullet)->next = temp;
	}
	fclose(pFile);
	pFile = NULL;
}

//*****************************************************************************************
// ��������: SaveHealthAndScore
// ����˵��: ��������ֵ�ͳɼ�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: char* FileHealthName  �������ֵ�ͳɼ����ļ���
// �� �� ֵ: void
//*****************************************************************************************
void SaveHealthAndScore(char* FileHealthName)
{
	FILE *pFile = NULL;
	fopen_s(&pFile, FileHealthName, "wb+");
	fprintf(pFile, "%d ", g_nHealth);
	fprintf(pFile, "%d ", g_nScore);
	fclose(pFile);
	pFile = NULL;
}

//*****************************************************************************************
// ��������: ReadHealthAndScore
// ����˵��: ��ȡ����ֵ�ͳɼ�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: char* FileHealthName  �������ֵ�ͳɼ����ļ���
// �� �� ֵ: void
//*****************************************************************************************
void ReadHealthAndScore(char* FileHealthName)
{
	FILE *pFile = NULL;
	fopen_s(&pFile, FileHealthName, "rb+");
	fscanf_s(pFile, "%d ", &g_nHealth);
	fscanf_s(pFile, "%d ", &g_nScore);
	fclose(pFile);
	pFile = NULL;
}

//*****************************************************************************************
// ��������: SizeOfWindow&&Full_Screen
// ����˵��: ����ȫ�����޹�ꡢ�޹�������Ӣ�����뷨
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: HANDLE hConsoleOutput	���
//			 void
// �� �� ֵ: SMALL_RECT
//			 void
//*****************************************************************************************
SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &info);
	return info.srWindow;
}
void Full_Screen()
{
	HANDLE hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
	/************����ȫ��************/
	HWND hWnd = GetForegroundWindow();  //��ȡǰ�����ھ��  
	int nCx = GetSystemMetrics(SM_CXSCREEN);  //������Ļ���  
	int nCy = GetSystemMetrics(SM_CYSCREEN);  //������Ļ�߶�  
	LONG l_WinStyle = GetWindowLong(hWnd, GWL_STYLE);  //������ʽ  
	SetWindowLong(hWnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);  // ���ô�����Ϣ ��� ȡ�����������߿�
	SetWindowPos(hWnd, HWND_TOP, 0, 0, nCx, nCy, 0);
	/************�����޹��************/
	CONSOLE_CURSOR_INFO cci;  //���ù����Ϣ�Ľṹ��
	cci.dwSize = 1;  //һ��Ҫ��ֵ��������
	cci.bVisible = FALSE;  //����Ϊ���ɼ�
	SetConsoleCursorInfo(hOutPut, &cci);  //���ù����Ϣ
	/************�����޹�����************/
	CONSOLE_SCREEN_BUFFER_INFO info;  //���û�������Ϣ�Ľṹ��
	GetConsoleScreenBufferInfo(hOutPut, &info);
	SMALL_RECT rect = SizeOfWindow(hOutPut);  //��/��ȡ����size
	COORD size = { rect.Right + 1,rect.Bottom + 1 };	//���建������С 
	SetConsoleScreenBufferSize(hOutPut, size);
	/**************һ��ʼ�������뷨ΪӢ��***************/
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);  //�л�Ӣ��
}

//*****************************************************************************************
// ��������: PrintMenu
// ����˵��: ��ӡ�˵�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: void
//*****************************************************************************************
void PrintMenu()
{
	while (true)
	{
		InitMap();  //��ʼ����ͼΪ��
		system("cls");
		WriteChar(Text_LOCX, Text_LOCY - 4, "1.��ʼ��Ϸ");
		WriteChar(Text_LOCX, Text_LOCY - 2, "2.������Ϸ");
		WriteChar(Text_LOCX, Text_LOCY + 0, "3.�Զ����ͼ");
		WriteChar(Text_LOCX, Text_LOCY + 2, "4.ɾ����ͼ");
		WriteChar(Text_LOCX, Text_LOCY + 4, "5.�˳���Ϸ");
		char MenuChoice = _getch() - 0x30;
		switch (MenuChoice)
		{
		case 1:
			ReadyGame();
			break;
		case 2:
			ContinueGame();
			break;
		case 3:
			CustomMap();
			break;
		case 4:
			LoadDeleteMap(Delete);
			break;
		case 5:
			exit(0);
			break;
		default:
			break;
		}
	}
}

//*****************************************************************************************
// ��������: BeginGame
// ����˵��: ��Ϸ���в���
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK *pMytk		 ���̹�˵�ָ��
//			 PTANK *BottkList	 ������̹�˵�ָ��
//			 PBULLET *BulletList �ӵ������ָ��
// �� �� ֵ: void
//*****************************************************************************************
void BeginGame(PTANK *pMytk, PTANK *BottkList, PBULLET *BulletList)
{
	/*********ģ����߳�**********/
	clock_t Time1_Start = clock();
	clock_t Time1_End;
	clock_t Time2_Start = clock();
	clock_t Time2_End;
	while (g_nHealth)
	{
		Time1_End = clock();
		Time2_End = clock();
		if (Time1_End - Time1_Start > 60)
		{
			Time1_Start = Time1_End;
			/*********��ȡ����************/
			if (_kbhit())
			{
				(*pMytk)->m_cKeyboardInfo = _getch();
				if ((*pMytk)->m_cKeyboardInfo == 27)  //�������ESC
				{
					int SuspendRet = 0;
					SuspendRet = SuspendGame(*pMytk, *BottkList, *BulletList);
					if (SuspendRet == 1)
					{
						/*******�������ղŵĳ���******/
						DrawMap();
						DrawTank(*pMytk, "TK");
						DrawBottk(BottkList);
						ScoreBoard();
						DrawHealthAndScore();
						BulletPrint(BulletList, BottkList);
						system("pause>null");
					}
					else if (SuspendRet == 3)
					{
						break;  //����ѭ��
					}
				}
				else
				{
					TKMove(*pMytk, BulletList, BottkList);
				}
			}
			BottkMove(BulletList, BottkList);  //������̹���ƶ�
		}
		if (Time2_End - Time2_Start > 50)
		{
			Time2_Start = Time2_End;
			BulletPrint(BulletList, BottkList);  //�ӵ��ɹ�
		}
	}
}

//*****************************************************************************************
// ��������: Misson
// ����˵��: ��ȡ�ؿ���ͼ
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: const char *MissionName  �ؿ���
// �� �� ֵ: void
//*****************************************************************************************
void Misson(const char *MissionName)
{
	FILE *pFile = NULL;
	fopen_s(&pFile, MissionName, "rb");
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			fscanf_s(pFile, "%d ", &g_aMap[i][j]);
		}
	}
	fclose(pFile);
}

//*****************************************************************************************
// ��������: ChoiceMap
// ����˵��: ��ͼѡ��˵�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: int ����1  ʹ�������ͼ
//				 ����2  ʹ���Զ����ͼ
//				 ����3  ʹ��ȫ��1��ͼ
//				 ����4	�ص��˵�
//*****************************************************************************************
int ChoiceMap()
{
	int nChoice = 0;
	while (TRUE)
	{
		system("cls");
		WriteChar(Text_LOCX, Text_LOCY, "1.ʹ�������ͼ");
		WriteChar(Text_LOCX, Text_LOCY + 2, "2.ʹ���Զ����ͼ");
		WriteChar(Text_LOCX, Text_LOCY + 4, "3.ʹ�ùؿ�1��ͼ");
		WriteChar(Text_LOCX, Text_LOCY + 6, "4.�ص��˵�");
		nChoice = _getch() - 0x30;
		switch (nChoice)
		{
		case 1:
			return 1;
		case 2:
			if (LoadDeleteMap(Load)) //ʹ���Զ����ͼ
			{
				return 2;
			}
			break;
		case 3:
			Misson("Mission\\Mission1");
			return 3;
			break;
		case 4:
			return 4;
		default:
			break;
		}
	}
}

//*****************************************************************************************
// ��������: ReadyGame
// ����˵��: ��Ϸ�ĳ�ʼ��
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: int 0 ���ز˵�
//*****************************************************************************************
int ReadyGame()
{
	int nChoiceRet = ChoiceMap();
	if (nChoiceRet == 4)
	{
		return 0;  //���ز˵�
	}
	Home();  //�����������ڵ�λ��
	if (nChoiceRet == 1)  //����Ĭ�ϵ�ͼ
	{
		/*******����ǽ���ϰ���******/
		CreateObj();
		CreateWall();
	}
	system("cls");
	DrawMap();
	/*********�ӵ�������*********/
	PBULLET BulletList;
	InitBulletList(&BulletList);
	/******��ʼ��һ����ҵ�̹��*****/
	PTANK pMytk = (PTANK)malloc(sizeof(TANK) * 1);
	InitMyTK(pMytk);
	DrawTank(pMytk, "TK");
	/******��ʼ���з�̹��************/
	PTANK BottkList;
	IntkList(&BottkList);
	CreateBottk(&BottkList);
	DrawBottk(&BottkList);
	/**********�����Ʒְ�***********/
	ScoreBoard();
	/**********��ӡ����ֵ***********/
	g_nHealth = Health;
	g_nScore = 0;
	DrawHealthAndScore();
	/***********��Ϸ��ʼ***********/
	BeginGame(&pMytk, &BottkList, &BulletList);
	delete pMytk;
	delete BottkList;
	delete BulletList;
	if (!g_nHealth)  //�������ֵΪ0�Ļ�
	{
		system("cls");
		WriteChar(Text_LOCX, Text_LOCY, "YOU FAIL");
		Sleep(1500);
	}
	return 0;
}

//*****************************************************************************************
// ��������: ContinueGame
// ����˵��: ������Ϸ
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: void
//*****************************************************************************************
void ContinueGame()
{
	system("cls");
	/************��ȡ��Һͻ�����̹��************/
	PTANK FileMyTk = (PTANK)malloc(sizeof(TANK) * 1);
	PTANK FileBotTKList;
	IntkList(&FileBotTKList);
	if (ReadTank(&FileMyTk, &FileBotTKList, (char*)"SuspendMyTANK", (char*)"SuspendBOTTANK"))  //˳������û�б������Ϸ
	{
		FileMyTk->m_nShootTimeStart = clock();
		DrawTank(FileMyTk, "TK");
		/****************��ȡ�ӵ�*******************/
		PBULLET FileBullet;
		InitBulletList(&FileBullet);
		ReadBullet(&FileBullet, (char*)"SuspendBULLET");
		/**************��ȡ��ͼ**********************/
		ReadMap("Suspend");
		DrawMap();
		/**************��ȡ����ֵ�ͷ���**************/
		ReadHealthAndScore((char*)"SuspendHealthScore");
		DrawHealthAndScore();
		/************�����Ʒְ�**********************/
		ScoreBoard();
		/*************��Ϸ��ʼ************************/
		BeginGame(&FileMyTk, &FileBotTKList, &FileBullet);
		/************��Ϸ����************************/
		if (!g_nHealth)  //�������ֵΪ0�Ļ�
		{
			system("cls");
			WriteChar(Text_LOCX, Text_LOCY, "YOU FAIL");
			Sleep(1500);
		}
		delete FileBullet;
	}
	delete FileMyTk;
	delete FileBotTKList;
}

//*****************************************************************************************
// ��������: CustomMap
// ����˵��: �����Զ����ͼ
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: void
// �� �� ֵ: void
//*****************************************************************************************
void CustomMap()
{
	CreateFolder();
	system("cls");
	/********����ǽ*********/
	CreateWall();
	/********��������********/
	Home();
	DrawMap();
	Tips();
	/**********��ȡ����¼��ͼ����¼�****************/
	HANDLE hInPut = GetStdHandle(STD_INPUT_HANDLE);  //��ȡ���
	INPUT_RECORD ir = {};  //���ýṹ��
	DWORD dwCount = 0;
	SetConsoleMode(hInPut, ENABLE_MOUSE_INPUT);
	char szStyle[4] = { 0 };
	int nColor = 0;
	int MapNum = 0;
	while (true)
	{
		ReadConsoleInput(hInPut, &ir, 1, &dwCount);
		if (ir.EventType == MOUSE_EVENT)  //��ȡ����¼�
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X / 2 >= g_ScoreX + 3 && pos.X / 2 <= g_ScoreX + 7 && pos.Y == 7)	   //�ж��Ƿ���ľͷ
				{
					strcpy_s(szStyle, 4, "��");
					nColor = FOREGROUND_GREEN;
					MapNum = WOOD;
				}
				else if (pos.X / 2 >= g_ScoreX + 3 && pos.X / 2 <= g_ScoreX + 7 && pos.Y == 9)		//�ж��Ƿ�����ǽ
				{
					strcpy_s(szStyle, 4, "��");
					nColor = FOREGROUND_RED;
					MapNum = IRON;
				}
				if (pos.X / 2 > g_MaxX - 2 || pos.X / 2 < 1 || pos.Y > g_MaxY - 2 || pos.Y < 1)		  //�ж��Ƿ񳬹�Χǽ��
				{
					continue;
				}
				if (g_aMap[pos.X / 2][pos.Y] == GEN)										//�ж��Ƿ�����������
				{
					continue;
				}
				WriteChar(pos.X / 2, pos.Y, szStyle, nColor);
				g_aMap[pos.X / 2][pos.Y] = MapNum;
			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)  //���ÿյأ������ϰ���
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X / 2 > g_MaxX - 2 || pos.X / 2 < 1 || pos.Y > g_MaxY - 2 || pos.Y < 1)				//�ж��Ƿ񳬹�Χǽ��
				{
					continue;
				}
				if (g_aMap[pos.X / 2][pos.Y] == GEN)							   //�ж��Ƿ�����������
				{
					continue;
				}
				WriteChar(pos.X / 2, pos.Y, " ");
				g_aMap[pos.X / 2][pos.Y] = BLANK;
			}
		}
		if (ir.EventType == KEY_EVENT)
		{
			if (ir.Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
			{
				struct tm t;   //tm�ṹָ��
				time_t now;  //����time_t����ָ��
				time(&now);
				localtime_s(&t, &now);
				char tmp[64];
				char tmp2[64];
				strftime(tmp, sizeof(tmp), "Map\\%Y��%m��%d��%H��%M��%S��", &t);  //��ʱ�������ļ���
				strftime(tmp2, sizeof(tmp2), "Map\\%Y��%m��%d��%H��%M��%S��", &t);
				SaveMap(tmp);  //�����ͼ
				SaveMapName(tmp2);  //�����ͼ��
				system("cls");
				break;
			}
			else if (ir.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)  //������
			{
				system("cls");
				break;
			}
		}
	}
}

//*****************************************************************************************
// ��������: SuspendGame
// ����˵��: ��ͣ��Ϸ�˵�
// ��    ��: lracker
// ʱ    ��: 2019/8/8
// ��    ��: PTANK pMytk		  //���̹��ָ��
//			 PTANK BottkList	  //������̹������
//			 PBULLET BulletList	  //�ӵ�����
// �� �� ֵ: int  ����1  ������Ϸ
//				  ����2  ������Ϸ
//				  ����3  �ص��˵�
//*****************************************************************************************
int SuspendGame(PTANK pMytk, PTANK BottkList, PBULLET BulletList)
{
	system("cls");
	while (true)
	{
		WriteChar(Text_LOCX, Text_LOCY, "1.������Ϸ");
		WriteChar(Text_LOCX, Text_LOCY + 2, "2.������Ϸ");
		WriteChar(Text_LOCX, Text_LOCY + 4, "3.�ص��˵�");
		char cSuspendChoice = _getch()-0x30;
		system("cls");
		switch (cSuspendChoice)
		{
		case 1:
			return 1;
			break;
		case 2:
			SaveMap((char*)"Suspend");
			SaveTank(pMytk, BottkList, (char*)"SuspendMYTANK", (char*)"SuspendBOTTANK");
			SaveBullet(BulletList, (char*)"SuspendBULLET");
			SaveHealthAndScore((char*)"SuspendHealthScore");
			break;
		case 3:
			return 3;
			break;
		default:
			break;
		}
	}
}











