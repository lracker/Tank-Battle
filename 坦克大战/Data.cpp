#include "pch.h"
#include "Data.h"
//坦克在地图上的显示的0和1
char g_aTank[4][3][3] =
{
	{
		{0,1,0},    //上
		{1,1,1},
		{1,0,1}
	},
	{
		{1,0,1},    //下
		{1,1,1},
		{0,1,0}
	},
	{
		{0,1,1},    //左
		{1,1,0},
		{0,1,1}
	},
	{
		{1,1,0},    //右
		{0,1,1},
		{1,1,0}
	}
};
		  
const char *g_apStyle[5] = { "■","□", "○","●", "㊣"};		   //坦克的形状
char g_aKeyboard[5] = { 'w','s','a', 'd', 'j'};					   //坦克的操作			    
int g_aBOTNum[5]{ EnTK1 ,EnTK2,EnTK3,EnTK4,EnTK5 };				   //机器人坦克在地图上的数字表示
int g_nHealth = Health;											   //坦克的生命值
int g_aTkColor[5] = { FOREGROUND_RED,FOREGROUND_BLUE,FOREGROUND_GREEN,FOREGROUND_RED | FOREGROUND_GREEN,FOREGROUND_BLUE | FOREGROUND_GREEN };	 //坦克的颜色
int g_nScore = 0;												   //成绩
int g_aMap[g_MaxX][g_MaxY] = { 0 };								   //地图是由一个二维数组组成的
const char g_cGeneral[] = "囍";									   //将军的形状