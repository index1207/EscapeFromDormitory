#pragma once
#include <Windows.h>

static HANDLE hScreen[2];
static int screenIdx = 0;

void screenInit() {
	hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
}

void screenFlipping() {
	SetConsoleActiveScreenBuffer(hScreen[screenIdx]);
	screenIdx = !screenIdx;
}

void ScreenClear() {
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(hScreen[screenIdx], ' ', 105 * 35, Coor, &dw);
}

void ScreenRelease()
{
	CloseHandle(hScreen[0]);
	CloseHandle(hScreen[1]);
}