#pragma once
#include "Windows.h"
#define g_MaxX 60		 //围墙最大坐标X
#define g_MaxY 45		 //围墙最大坐标Y
#define Text_LOCX 35     //显示文字位置的X坐标  
#define Text_LOCY 20     //显示文字位置的Y坐标
#define UP 0			 //上
#define DOWN 1			 //下
#define LEFT 2			 //左
#define RIGHT 3			 //右
#define BLANK 0			 //空地
#define TK 1             //玩家坦克在地图上的表示
#define BT 2			 //子弹
#define WALL 3			 //墙
#define WOOD 4			 //木头
#define EnTK1 5			 //机器人1
#define EnTK2 6			 //机器人2
#define EnTK3 7			 //机器人3
#define EnTK4 8			 //机器人4
#define EnTK5 9			 //机器人5
#define IRON 10			 //铁墙
#define GEN 11			 //将军
#define g_ScoreX 60		 //计分板的边框X
#define g_ScoreY 15		 //计分板的边框Y
#define Player 0		 //玩家
#define Enermy 1		 //机器人
#define Health 5		 //生命值
#define Load 1			 //1为加载
#define Delete 2		 //2为删除

//定义坦克结构体
typedef struct _TANK
{
	unsigned int m_uTankX;  //坦克中心点的X坐标
	unsigned int m_uTankY;  //坦克中心点的Y坐标
	int m_nDir;			    //坦克现在的方向
	int m_Camp;			    //阵营 0代表玩家,1代表敌人
	unsigned int m_uColor;  //颜色
	char m_szStyle[10];		//形状
	char m_cKeyboardInfo;   //按键信息
	int m_nTKNumber;		//TK在地图上的数字
	int m_nShootTimeStart;  //射子弹开始时间
	int m_nShootTimeEnd;	//射子弹结束时间
	int m_nHealth;			//坦克的生命值
	struct _TANK *next;		//下一个结构体的指针
}TANK, *PTANK;

//定义子弹结构体
typedef struct _BULLET
{
	unsigned int m_uBulltX;  //子弹X坐标
	unsigned int m_uBulltY;  //子弹Y坐标
	int m_nCamp;		     //阵营
	int m_nDir;				 //方向
	struct _BULLET *next;	 //下一个子弹的地址
}BULLET, *PBULLET;

//定义地图名
typedef struct _MAPNAME
{
	int m_nChoice;				//地图序号
	char m_szMapName[64];		//地图名
	struct _MAPNAME *next;		//下一个地图名的地址
}MapName, *PMapName;

extern char g_aKeyboard[5];
extern const char *g_apStyle[5];
extern int g_aBOTNum[5];
extern int g_nHealth;
extern char g_aTank[4][3][3];
extern int g_aTkColor[5];
extern int g_nScore;
extern int g_aMap[g_MaxX][g_MaxY];