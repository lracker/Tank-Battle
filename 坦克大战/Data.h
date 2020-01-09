#pragma once
#include "Windows.h"
#define g_MaxX 60		 //Χǽ�������X
#define g_MaxY 45		 //Χǽ�������Y
#define Text_LOCX 35     //��ʾ����λ�õ�X����  
#define Text_LOCY 20     //��ʾ����λ�õ�Y����
#define UP 0			 //��
#define DOWN 1			 //��
#define LEFT 2			 //��
#define RIGHT 3			 //��
#define BLANK 0			 //�յ�
#define TK 1             //���̹���ڵ�ͼ�ϵı�ʾ
#define BT 2			 //�ӵ�
#define WALL 3			 //ǽ
#define WOOD 4			 //ľͷ
#define EnTK1 5			 //������1
#define EnTK2 6			 //������2
#define EnTK3 7			 //������3
#define EnTK4 8			 //������4
#define EnTK5 9			 //������5
#define IRON 10			 //��ǽ
#define GEN 11			 //����
#define g_ScoreX 60		 //�Ʒְ�ı߿�X
#define g_ScoreY 15		 //�Ʒְ�ı߿�Y
#define Player 0		 //���
#define Enermy 1		 //������
#define Health 5		 //����ֵ
#define Load 1			 //1Ϊ����
#define Delete 2		 //2Ϊɾ��

//����̹�˽ṹ��
typedef struct _TANK
{
	unsigned int m_uTankX;  //̹�����ĵ��X����
	unsigned int m_uTankY;  //̹�����ĵ��Y����
	int m_nDir;			    //̹�����ڵķ���
	int m_Camp;			    //��Ӫ 0�������,1�������
	unsigned int m_uColor;  //��ɫ
	char m_szStyle[10];		//��״
	char m_cKeyboardInfo;   //������Ϣ
	int m_nTKNumber;		//TK�ڵ�ͼ�ϵ�����
	int m_nShootTimeStart;  //���ӵ���ʼʱ��
	int m_nShootTimeEnd;	//���ӵ�����ʱ��
	int m_nHealth;			//̹�˵�����ֵ
	struct _TANK *next;		//��һ���ṹ���ָ��
}TANK, *PTANK;

//�����ӵ��ṹ��
typedef struct _BULLET
{
	unsigned int m_uBulltX;  //�ӵ�X����
	unsigned int m_uBulltY;  //�ӵ�Y����
	int m_nCamp;		     //��Ӫ
	int m_nDir;				 //����
	struct _BULLET *next;	 //��һ���ӵ��ĵ�ַ
}BULLET, *PBULLET;

//�����ͼ��
typedef struct _MAPNAME
{
	int m_nChoice;				//��ͼ���
	char m_szMapName[64];		//��ͼ��
	struct _MAPNAME *next;		//��һ����ͼ���ĵ�ַ
}MapName, *PMapName;

extern char g_aKeyboard[5];
extern const char *g_apStyle[5];
extern int g_aBOTNum[5];
extern int g_nHealth;
extern char g_aTank[4][3][3];
extern int g_aTkColor[5];
extern int g_nScore;
extern int g_aMap[g_MaxX][g_MaxY];