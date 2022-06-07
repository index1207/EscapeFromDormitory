#pragma once
#include "console.h"

#define X 0
#define Y 1

float player[2] = {0,};
int size[2] = { 105, 35 };

void initialization() {
	SetConsoleTitle("Escape from Dormitory");
	setConsoleSize(size[X], size[Y]);
	showCursor(FALSE);
}

//그리기
void render() {
	system("cls");
	setPosition(player[X], player[Y]);
	printf("†");
}

// 값 변화시키기
void update() {
	if (inputKey(VK_LEFT) && player[X] > 0) {
		player[X] -= 1;
	}
	else if (inputKey(VK_UP) && player[Y] > 0) {
		player[Y] -= 0.5;
	}
	else if (inputKey(VK_DOWN)&&player[Y] < size[Y]-1) {
		player[Y] += 0.5;
	}
	else if (inputKey(VK_RIGHT)&&player[X] < size[X]-1) {
		player[X] += 1;
	}
}

void release() {

}