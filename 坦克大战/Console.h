#pragma once
#include <Windows.h>
#include <io.h>
#include <direct.h>
#include "Data.h"
#include "Draw.h"
#include "Engine.h"

void PrintMenu();													//��ӡ�˵�
void Full_Screen();													//ȫ���Լ����ع����л�Ӣ�����뷨
int ReadyGame();													//׼����Ϸ
int SuspendGame(PTANK pMytk, PTANK BottkList, PBULLET BulletList);  //��ӡ����ͣѡ��
void CustomMap();													//�Զ����ͼ
void ContinueGame();												//������Ϸ
bool LoadDeleteMap(int LoadOrDelete);								//���ص�ͼ����ɾ����ͼ
void Misson(const char *MissionName);								//ѡ��ؿ�
void SaveMap(const char* c_szFileName);								//�����ͼ
void ReadMap(const char* c_szFileName);								//��ȡ��ͼ 
int ChoiceMap();													//��ͼѡ��˵�
