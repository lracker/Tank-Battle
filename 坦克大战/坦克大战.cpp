// 坦克大战.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "Draw.h"
#include "Engine.h"
#include "Console.h"
#pragma comment(lib, "Winmm.lib")
using std::cout;
using std::endl;
int main()
{
	Full_Screen();  //全屏
	PlaySoundA("Sound\\begin.wav", NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP); // 播放音乐
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {};
	SetConsoleCursorPosition(hOutput, position);
	SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "■■■■■■     ■         ■       ■ ■    ■      " << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "    ■■       ■  ■       ■ ■    ■ ■   ■       " << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "    ■■      ■    ■      ■  ■   ■ ■  ■     " << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "    ■■     ■■■■■     ■   ■  ■ ■■" << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "    ■■    ■        ■    ■    ■ ■ ■  ■              " << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "    ■■   ■          ■   ■     ■■ ■    ■            " << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "    ■■ ■              ■ ■       ■ ■      ■          " << endl;

	Sleep(1000);
	PrintMenu();
}