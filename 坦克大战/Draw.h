#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "Data.h"
void WriteChar(int x, int y, const char*s, WORD Color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);  //在指定的位置输出字符串
void DrawMap();																								   //打印地图
void DrawTank(PTANK objTank, const char* szOrder);															   //画出坦克或者清除坦克
void DrawBottk(PTANK *pptk);																				   //画出机器人坦克
void DrawBT(PBULLET bt, const char* szOrder);															       //画出子弹或者清除子弹
void DrawHealthAndScore();																					   //打印生命值
void Tips();																								   //打印提示
void ScoreBoard();																							   //画出计分板
void Home();																								   //画出保护的家