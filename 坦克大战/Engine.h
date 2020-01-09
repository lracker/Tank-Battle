#pragma once
#include <stdlib.h>
#include <time.h>
#include "Data.h"
#include "Draw.h"

void Shoot(PTANK objTank, PBULLET* BulletList, PTANK *BottkList);		//����ӵ� 
void InitBulletList(PBULLET *L);										//��ʼ������
void InitMyTK(PTANK ptk);												//��ʼ����ҵ�̹��
void IntkList(PTANK *pptk);												//��ʼ��������̹������
void BulletPrint(PBULLET *BulletList, PTANK *BottkList);				//�ӵ���ӡ
bool JudgeTKMove(PTANK objTank);										//̹���ƶ�ʱ���ж�����ʲô��
void CreateObj();														//����ľͷ����ǽ
void CreateWall();														//����Χǽ
bool JudgeBTMove(PBULLET objBT, PTANK* BottkList);						//�ж��ӵ�����������ʲô��
void CreateBottk(PTANK *pptk);											//����������̹��
void BottkMove(PBULLET *BulletList, PTANK *BottkList);					//������̹���ƶ�
void TKMove(PTANK objTank, PBULLET *BulletList, PTANK *BottkList);		//̹���ǵ��ƶ�
void InitMap();															//��ʼ����ͼ