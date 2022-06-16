#pragma once
#include "console.h"
#include "screen.h"

#define X 0
#define Y 1

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define PURPLE "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"



Point player = {0,0};
int size[2] = { 105, 35 };

void initialization() {
	SetConsoleTitle("Escape from Dormitory");
	setConsoleSize(size[X], size[Y]);
	screenInit();
	showCursor(FALSE);
}

//그리기
void render() {
	ScreenClear();
	print(player, CYAN"@");
	screenFlipping();
}

// 값 변화시키기
void update() {
	if ((inputKey(VK_LEFT) || inputKey('A')) && player.x > 0) {
		player.x -= 0.5;
	}
	else if ((inputKey(VK_UP) || inputKey('W')) && player.y > 0) {
		player.y -= 0.25;
	}
	else if ((inputKey(VK_DOWN) || inputKey('S')) && player.y < size[Y] - 1) {
		player.y += 0.25;
	}
	else if ((inputKey(VK_RIGHT) || inputKey('D')) && player.x < size[X] - 1) {
		player.x += 0.5;
	}
	showCursor(FALSE);
}

void release() {
	ScreenRelease();
}