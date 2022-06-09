#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "screen.h"

// 색상표
typedef struct _colors {
	char* Red;
	char* Green;
	char* Yellow;
	char* Blue;
	char* Purple;
	char* Cyan;
	char* White;
} Colors;

Colors color;

typedef struct _point {
	double x;
	double y;
} Point;

// 색깔 바꿔서 출력하기
void print(Point p, const char* str, const char* color) {
	size_t dw;
	COORD pos = { p.x, p.y };

	SetConsoleCursorPosition(hScreen[screenIdx], pos);
	WriteFile(hScreen[screenIdx], str, strlen(str), &dw, NULL);
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

// 키 입력
int inputKey(int key) {
	return (GetAsyncKeyState(key) & 0x8000);
}