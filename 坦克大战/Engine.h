#pragma once
#include <stdlib.h>
#include <time.h>
#include "Data.h"
#include "Draw.h"

void Shoot(PTANK objTank, PBULLET* BulletList, PTANK *BottkList);		//射出子弹 
void InitBulletList(PBULLET *L);										//初始化链表
void InitMyTK(PTANK ptk);												//初始化玩家的坦克
void IntkList(PTANK *pptk);												//初始化机器人坦克链表
void BulletPrint(PBULLET *BulletList, PTANK *BottkList);				//子弹打印
bool JudgeTKMove(PTANK objTank);										//坦克移动时候判断碰到什么了
void CreateObj();														//创建木头和铁墙
void CreateWall();														//创建围墙
bool JudgeBTMove(PBULLET objBT, PTANK* BottkList);						//判断子弹飞行中碰到什么了
void CreateBottk(PTANK *pptk);											//创建机器人坦克
void BottkMove(PBULLET *BulletList, PTANK *BottkList);					//机器人坦克移动
void TKMove(PTANK objTank, PBULLET *BulletList, PTANK *BottkList);		//坦克们的移动
void InitMap();															//初始化地图