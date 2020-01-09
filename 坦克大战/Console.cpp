#include "pch.h"
#include "Console.h"

//*****************************************************************************************
// 函数名称: CreateFolder
// 函数说明: 创建文件夹
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: 返回创建文件夹是否成功
//*****************************************************************************************
bool CreateFolder()
{
	//文件夹名称
	char folderName[] = "Map";
	// 文件夹不存在则创建文件夹
	if (_access(folderName, 0) == -1)
	{
		_mkdir(folderName);
	}
	return false;
}

//*****************************************************************************************
// 函数名称: SaveMap
// 函数说明: 保存地图
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: const char* c_szFileName 地图名
// 返 回 值: void
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
// 函数名称: ReadMap
// 函数说明: 读取地图
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: const char* c_szFileName
// 返 回 值: void
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
// 函数名称: SaveMapName
// 函数说明: 保存地图的名字
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: const char* c_szFileName
// 返 回 值: void
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
// 函数名称: LoadDeleteMap
// 函数说明: 加载或者删除地图
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: int LoadOrDelete Load为加载地图，Delete为删除地图
// 返 回 值: bool 真 操作成功 
//				  假 操作失败
//*****************************************************************************************
bool LoadDeleteMap(int LoadOrDelete)
{
	int nExit = 0;		 //判断地图是否存在
	system("cls");
	FILE *pFile = NULL;
	fopen_s(&pFile, "Map\\MapName.txt", "rb");  //打开地图名索引文件
	if (!pFile)  //如果没有这个文件会提示
	{
		WriteChar(Text_LOCX, Text_LOCY, "请先自定义地图");
		Sleep(1000);
		return false;
	}
	if (fgetc(pFile) == EOF)	//如果地图删完了的话就会提示
	{
		WriteChar(Text_LOCX, Text_LOCY, "请先自定义地图");
		Sleep(1000);
		fclose(pFile);
		pFile = NULL;
		return false;
	}
	else
	{
		rewind(pFile);		  //由于fgetc的原因，使用重置pFile
		if (LoadOrDelete == Load)
		{
			WriteChar(Text_LOCX - 5, Text_LOCY, "请输入使用的地图序号");
		}
		else if (LoadOrDelete == Delete)
		{
			WriteChar(Text_LOCX - 5, Text_LOCY, "请输入删除地图序号");
		}
		PMapName MapnameList = (PMapName)malloc(sizeof(MapName) * 1);
		MapnameList->next = NULL;
		int ret = 0;		   //检测是否读到文件尾
		int i = 1;				//记录地图序号
		char MapNum[10];
		while (true)  //从文件中读取地图名
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
		PMapName P = MapnameList;	   //定义指针指向链表头
		while (P->next)  //打印地图名列表
		{
			sprintf_s(MapNum, "%d", P->next->m_nChoice);
			WriteChar(Text_LOCX - 5, Text_LOCY + 2 * P->next->m_nChoice, MapNum);
			WriteChar(Text_LOCX - 3, Text_LOCY + 2 * P->next->m_nChoice, P->next->m_szMapName);
			P = P->next;
			memset(MapNum, 0, 10);
		}
		P = MapnameList;				//重置指针
		int MapChoice = _getch() - 0x30;  //获取地图序号
		char szSeletedMapName[64] = { 0 };			   //保存文件名
		while (P->next)
		{
			if (MapChoice == P->next->m_nChoice)
			{
				strcpy_s(szSeletedMapName, 64, P->next->m_szMapName);  //根据输入来获取地图名字
				nExit = 1;
				break;
			}
			P = P->next;
		}
		if (!nExit)
		{
			system("cls");
			WriteChar(Text_LOCX, Text_LOCY, "请输入正确的序号");
			Sleep(1000);
			return false;
		}
		switch (LoadOrDelete)
		{
		case 1:  //1是加载地图
		{
            ReadMap(szSeletedMapName);
			break;
		}
		case 2:  //2是删除地图
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
			while (P->next)  //重新写进去
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
// 函数名称: SaveTank
// 函数说明: 保存玩家和机器人的坦克
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK pMytk		玩家坦克指针
//			 PTANK BottkList    机器人坦克链表
//			 char* MyFileName	保存玩家坦克的文件名
//			 char* BotFileName 	保存机器人坦克的文件名
// 返 回 值: void
//*****************************************************************************************
void SaveTank(PTANK pMytk, PTANK BottkList, char* MyFileName, char* BotFileName)
{
	/*******玩家坦克*****************/
	FILE *pFile = NULL;
	fopen_s(&pFile, MyFileName, "wb");
	fwrite(pMytk, sizeof(TANK), 1, pFile);
	fclose(pFile);
	pFile = NULL;
	/**********机器人坦克**************/
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
// 函数名称: ReadTank
// 函数说明: 读取玩家和机器人的坦克
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK pMytk		玩家坦克指针
//			 PTANK BottkList    机器人坦克链表
//			 char* MyFileName	保存玩家坦克的文件名
//			 char* BotFileName 	保存机器人坦克的文件名
// 返 回 值: bool 真 操作成功 
//				  假 操作失败
//*****************************************************************************************
bool ReadTank(PTANK *FileMyTk, PTANK *FileBotTK, char* MyFileName, char* BotFileName)
{
	/****读取玩家坦克******/
	FILE *pFile = NULL;
	fopen_s(&pFile, MyFileName, "rb");
	if(!pFile)
	{
		WriteChar(Text_LOCX, Text_LOCY, "请先保存一次游戏");
		Sleep(1000);
		return false;
	}
	if(fgetc(pFile) == EOF)
	{
		WriteChar(Text_LOCX, Text_LOCY, "请先保存一次游戏");
		Sleep(1000);
		fclose(pFile);
		pFile = NULL;
		return false;
	}
	rewind(pFile);
	fread(*FileMyTk, sizeof(TANK), 1, pFile);
	fclose(pFile);
	/**********读取机器人坦克**************/
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
// 函数名称: SaveBullet	  
// 函数说明: 保存子弹链表
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PBULLET BulletList 子弹链表
//			 char* FileName		保存子弹的文件名
// 返 回 值: void
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
// 函数名称: ReadBullet
// 函数说明: 读取子弹
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PBULLET *FileBullet 子弹链表的指针
//			 char* FileName		 保存子弹的文件名
// 返 回 值: void
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
// 函数名称: SaveHealthAndScore
// 函数说明: 保存生命值和成绩
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: char* FileHealthName  存放生命值和成绩的文件名
// 返 回 值: void
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
// 函数名称: ReadHealthAndScore
// 函数说明: 读取生命值和成绩
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: char* FileHealthName  存放生命值和成绩的文件名
// 返 回 值: void
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
// 函数名称: SizeOfWindow&&Full_Screen
// 函数说明: 设置全屏、无光标、无滚动条、英文输入法
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: HANDLE hConsoleOutput	句柄
//			 void
// 返 回 值: SMALL_RECT
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
	/************设置全屏************/
	HWND hWnd = GetForegroundWindow();  //获取前景窗口句柄  
	int nCx = GetSystemMetrics(SM_CXSCREEN);  //检索屏幕宽度  
	int nCy = GetSystemMetrics(SM_CYSCREEN);  //检索屏幕高度  
	LONG l_WinStyle = GetWindowLong(hWnd, GWL_STYLE);  //窗口样式  
	SetWindowLong(hWnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);  // 设置窗口信息 最大化 取消标题栏及边框
	SetWindowPos(hWnd, HWND_TOP, 0, 0, nCx, nCy, 0);
	/************设置无光标************/
	CONSOLE_CURSOR_INFO cci;  //设置光标信息的结构体
	cci.dwSize = 1;  //一定要赋值才嫩隐藏
	cci.bVisible = FALSE;  //设置为不可见
	SetConsoleCursorInfo(hOutPut, &cci);  //设置光标信息
	/************设置无滚动条************/
	CONSOLE_SCREEN_BUFFER_INFO info;  //设置缓冲区信息的结构体
	GetConsoleScreenBufferInfo(hOutPut, &info);
	SMALL_RECT rect = SizeOfWindow(hOutPut);  //、/获取窗口size
	COORD size = { rect.Right + 1,rect.Bottom + 1 };	//定义缓冲区大小 
	SetConsoleScreenBufferSize(hOutPut, size);
	/**************一开始设置输入法为英文***************/
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);  //切换英文
}

//*****************************************************************************************
// 函数名称: PrintMenu
// 函数说明: 打印菜单
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: void
//*****************************************************************************************
void PrintMenu()
{
	while (true)
	{
		InitMap();  //初始化地图为空
		system("cls");
		WriteChar(Text_LOCX, Text_LOCY - 4, "1.开始游戏");
		WriteChar(Text_LOCX, Text_LOCY - 2, "2.继续游戏");
		WriteChar(Text_LOCX, Text_LOCY + 0, "3.自定义地图");
		WriteChar(Text_LOCX, Text_LOCY + 2, "4.删除地图");
		WriteChar(Text_LOCX, Text_LOCY + 4, "5.退出游戏");
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
// 函数名称: BeginGame
// 函数说明: 游戏运行部分
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK *pMytk		 玩家坦克的指针
//			 PTANK *BottkList	 机器人坦克的指针
//			 PBULLET *BulletList 子弹链表的指针
// 返 回 值: void
//*****************************************************************************************
void BeginGame(PTANK *pMytk, PTANK *BottkList, PBULLET *BulletList)
{
	/*********模拟多线程**********/
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
			/*********获取输入************/
			if (_kbhit())
			{
				(*pMytk)->m_cKeyboardInfo = _getch();
				if ((*pMytk)->m_cKeyboardInfo == 27)  //如果输入ESC
				{
					int SuspendRet = 0;
					SuspendRet = SuspendGame(*pMytk, *BottkList, *BulletList);
					if (SuspendRet == 1)
					{
						/*******重新描绘刚才的场面******/
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
						break;  //跳出循环
					}
				}
				else
				{
					TKMove(*pMytk, BulletList, BottkList);
				}
			}
			BottkMove(BulletList, BottkList);  //机器人坦克移动
		}
		if (Time2_End - Time2_Start > 50)
		{
			Time2_Start = Time2_End;
			BulletPrint(BulletList, BottkList);  //子弹飞过
		}
	}
}

//*****************************************************************************************
// 函数名称: Misson
// 函数说明: 读取关卡地图
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: const char *MissionName  关卡名
// 返 回 值: void
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
// 函数名称: ChoiceMap
// 函数说明: 地图选择菜单
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: int 返回1  使用随机地图
//				 返回2  使用自定义地图
//				 返回3  使用全卡1地图
//				 返回4	回到菜单
//*****************************************************************************************
int ChoiceMap()
{
	int nChoice = 0;
	while (TRUE)
	{
		system("cls");
		WriteChar(Text_LOCX, Text_LOCY, "1.使用随机地图");
		WriteChar(Text_LOCX, Text_LOCY + 2, "2.使用自定义地图");
		WriteChar(Text_LOCX, Text_LOCY + 4, "3.使用关卡1地图");
		WriteChar(Text_LOCX, Text_LOCY + 6, "4.回到菜单");
		nChoice = _getch() - 0x30;
		switch (nChoice)
		{
		case 1:
			return 1;
		case 2:
			if (LoadDeleteMap(Load)) //使用自定义地图
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
// 函数名称: ReadyGame
// 函数说明: 游戏的初始化
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: int 0 返回菜单
//*****************************************************************************************
int ReadyGame()
{
	int nChoiceRet = ChoiceMap();
	if (nChoiceRet == 4)
	{
		return 0;  //返回菜单
	}
	Home();  //画出将军所在的位置
	if (nChoiceRet == 1)  //按照默认地图
	{
		/*******画出墙和障碍物******/
		CreateObj();
		CreateWall();
	}
	system("cls");
	DrawMap();
	/*********子弹的链表*********/
	PBULLET BulletList;
	InitBulletList(&BulletList);
	/******初始化一辆玩家的坦克*****/
	PTANK pMytk = (PTANK)malloc(sizeof(TANK) * 1);
	InitMyTK(pMytk);
	DrawTank(pMytk, "TK");
	/******初始化敌方坦克************/
	PTANK BottkList;
	IntkList(&BottkList);
	CreateBottk(&BottkList);
	DrawBottk(&BottkList);
	/**********画出计分板***********/
	ScoreBoard();
	/**********打印生命值***********/
	g_nHealth = Health;
	g_nScore = 0;
	DrawHealthAndScore();
	/***********游戏开始***********/
	BeginGame(&pMytk, &BottkList, &BulletList);
	delete pMytk;
	delete BottkList;
	delete BulletList;
	if (!g_nHealth)  //如果生命值为0的话
	{
		system("cls");
		WriteChar(Text_LOCX, Text_LOCY, "YOU FAIL");
		Sleep(1500);
	}
	return 0;
}

//*****************************************************************************************
// 函数名称: ContinueGame
// 函数说明: 继续游戏
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: void
//*****************************************************************************************
void ContinueGame()
{
	system("cls");
	/************读取玩家和机器人坦克************/
	PTANK FileMyTk = (PTANK)malloc(sizeof(TANK) * 1);
	PTANK FileBotTKList;
	IntkList(&FileBotTKList);
	if (ReadTank(&FileMyTk, &FileBotTKList, (char*)"SuspendMyTANK", (char*)"SuspendBOTTANK"))  //顺便检查有没有保存过游戏
	{
		FileMyTk->m_nShootTimeStart = clock();
		DrawTank(FileMyTk, "TK");
		/****************读取子弹*******************/
		PBULLET FileBullet;
		InitBulletList(&FileBullet);
		ReadBullet(&FileBullet, (char*)"SuspendBULLET");
		/**************读取地图**********************/
		ReadMap("Suspend");
		DrawMap();
		/**************读取生命值和分数**************/
		ReadHealthAndScore((char*)"SuspendHealthScore");
		DrawHealthAndScore();
		/************画出计分板**********************/
		ScoreBoard();
		/*************游戏开始************************/
		BeginGame(&FileMyTk, &FileBotTKList, &FileBullet);
		/************游戏结束************************/
		if (!g_nHealth)  //如果生命值为0的话
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
// 函数名称: CustomMap
// 函数说明: 保存自定义地图
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: void
// 返 回 值: void
//*****************************************************************************************
void CustomMap()
{
	CreateFolder();
	system("cls");
	/********画出墙*********/
	CreateWall();
	/********画出将军********/
	Home();
	DrawMap();
	Tips();
	/**********获取鼠标事件和键盘事件****************/
	HANDLE hInPut = GetStdHandle(STD_INPUT_HANDLE);  //获取句柄
	INPUT_RECORD ir = {};  //设置结构体
	DWORD dwCount = 0;
	SetConsoleMode(hInPut, ENABLE_MOUSE_INPUT);
	char szStyle[4] = { 0 };
	int nColor = 0;
	int MapNum = 0;
	while (true)
	{
		ReadConsoleInput(hInPut, &ir, 1, &dwCount);
		if (ir.EventType == MOUSE_EVENT)  //获取鼠标事件
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X / 2 >= g_ScoreX + 3 && pos.X / 2 <= g_ScoreX + 7 && pos.Y == 7)	   //判断是否按了木头
				{
					strcpy_s(szStyle, 4, "※");
					nColor = FOREGROUND_GREEN;
					MapNum = WOOD;
				}
				else if (pos.X / 2 >= g_ScoreX + 3 && pos.X / 2 <= g_ScoreX + 7 && pos.Y == 9)		//判断是否按了铁墙
				{
					strcpy_s(szStyle, 4, "¤");
					nColor = FOREGROUND_RED;
					MapNum = IRON;
				}
				if (pos.X / 2 > g_MaxX - 2 || pos.X / 2 < 1 || pos.Y > g_MaxY - 2 || pos.Y < 1)		  //判断是否超过围墙了
				{
					continue;
				}
				if (g_aMap[pos.X / 2][pos.Y] == GEN)										//判断是否碰到将军了
				{
					continue;
				}
				WriteChar(pos.X / 2, pos.Y, szStyle, nColor);
				g_aMap[pos.X / 2][pos.Y] = MapNum;
			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)  //设置空地，撤销障碍物
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X / 2 > g_MaxX - 2 || pos.X / 2 < 1 || pos.Y > g_MaxY - 2 || pos.Y < 1)				//判断是否超过围墙了
				{
					continue;
				}
				if (g_aMap[pos.X / 2][pos.Y] == GEN)							   //判断是否碰到将军了
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
				struct tm t;   //tm结构指针
				time_t now;  //声明time_t类型指针
				time(&now);
				localtime_s(&t, &now);
				char tmp[64];
				char tmp2[64];
				strftime(tmp, sizeof(tmp), "Map\\%Y年%m月%d日%H点%M分%S秒", &t);  //用时间来做文件名
				strftime(tmp2, sizeof(tmp2), "Map\\%Y年%m月%d日%H点%M分%S秒", &t);
				SaveMap(tmp);  //保存地图
				SaveMapName(tmp2);  //保存地图名
				system("cls");
				break;
			}
			else if (ir.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)  //不保存
			{
				system("cls");
				break;
			}
		}
	}
}

//*****************************************************************************************
// 函数名称: SuspendGame
// 函数说明: 暂停游戏菜单
// 作    者: lracker
// 时    间: 2019/8/8
// 参    数: PTANK pMytk		  //玩家坦克指针
//			 PTANK BottkList	  //机器人坦克链表
//			 PBULLET BulletList	  //子弹链表
// 返 回 值: int  返回1  继续游戏
//				  返回2  保存游戏
//				  返回3  回到菜单
//*****************************************************************************************
int SuspendGame(PTANK pMytk, PTANK BottkList, PBULLET BulletList)
{
	system("cls");
	while (true)
	{
		WriteChar(Text_LOCX, Text_LOCY, "1.继续游戏");
		WriteChar(Text_LOCX, Text_LOCY + 2, "2.保存游戏");
		WriteChar(Text_LOCX, Text_LOCY + 4, "3.回到菜单");
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











