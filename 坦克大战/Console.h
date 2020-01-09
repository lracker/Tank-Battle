#pragma once
#include <Windows.h>
#include <io.h>
#include <direct.h>
#include "Data.h"
#include "Draw.h"
#include "Engine.h"

void PrintMenu();													//打印菜单
void Full_Screen();													//全屏以及隐藏光标和切换英文输入法
int ReadyGame();													//准备游戏
int SuspendGame(PTANK pMytk, PTANK BottkList, PBULLET BulletList);  //打印出暂停选项
void CustomMap();													//自定义地图
void ContinueGame();												//继续游戏
bool LoadDeleteMap(int LoadOrDelete);								//加载地图或者删除地图
void Misson(const char *MissionName);								//选择关卡
void SaveMap(const char* c_szFileName);								//保存地图
void ReadMap(const char* c_szFileName);								//读取地图 
int ChoiceMap();													//地图选择菜单
