#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "screen.h"

// 색상표
#define WHITE "\x1b[37m"
#define RED(str) "\x1b[31m"str##WHITE
#define GREEN(str) "\x1b[32m"str##WHITE
#define YELLOW(str) "\x1b[33m"str##WHITE
#define BLUE(str) "\x1b[34m"str##WHITE
#define PURPLE(str) "\x1b[35m"str##WHITE
#define CYAN(str) "\x1b[36m"str##WHITE


typedef struct _point {
	double x;
	double y;
} Point, Map;

// 색깔 바꿔서 출력하기
void print(Point p, const char* str) {
	DWORD dw = 0;
	COORD pos = { p.x, p.y };

	SetConsoleCursorPosition(hScreen[screenIdx], pos);
	WriteFile(hScreen[screenIdx], str, (DWORD)strlen(str), &dw, NULL);
}

void setPoint(Point* p, int x, int y) {
	p->x = x;
	p->y = y;
}

int equalPoint(Point a, Point b) {
	return ((floor(a.x + 0.5) == floor(b.x + 0.5)) && (floor(a.y + 0.5) == floor(b.y + 0.5)));
}

// CMD 크기조절
void setConsoleSize(short width, short height) {
	char cmd[32] = "";
	sprintf_s(cmd, sizeof(cmd), "mode con cols=%d lines=%d", width, height);

	system(cmd);
}


// CMD 좌표 지정
void setPosition(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 깜박이는 커서 안보이게 하기
void showCursor(boolean show) {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = show;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}