#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "Data.h"
void WriteChar(int x, int y, const char*s, WORD Color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);  //��ָ����λ������ַ���
void DrawMap();																								   //��ӡ��ͼ
void DrawTank(PTANK objTank, const char* szOrder);															   //����̹�˻������̹��
void DrawBottk(PTANK *pptk);																				   //����������̹��
void DrawBT(PBULLET bt, const char* szOrder);															       //�����ӵ���������ӵ�
void DrawHealthAndScore();																					   //��ӡ����ֵ
void Tips();																								   //��ӡ��ʾ
void ScoreBoard();																							   //�����Ʒְ�
void Home();																								   //���������ļ�