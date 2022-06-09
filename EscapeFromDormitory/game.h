#pragma once
#include "console.h"
#include "screen.h"

#define X 0
#define Y 1

Point player = {0,0};
int size[2] = { 105, 35 };

void initialization() {
	color.Red = "\x1b[31";
	color.Green = "\x1b[32";
	color.Yellow = "\x1b[33";
	color.Blue = "\x1b[34";
	color.Purple = "\x1b[35";
	color.Cyan = "\x1b[36";
	color.White = "\x1b[37";

	SetConsoleTitle("Escape from Dormitory");
	setConsoleSize(size[X], size[Y]);
	screenInit();
	showCursor(FALSE);
}

//그리기
void render() {
	ScreenClear();
	print(player, "@", color.White);
	screenFlipping();
}

// 값 변화시키기
void update() {
	if ((inputKey(VK_LEFT) || inputKey('A')) && player.x > 0) {
		player.x -= 1;
	}
	else if ((inputKey(VK_UP) || inputKey('W')) && player.y > 0) {
		player.y -= 0.6;
	}
	else if ((inputKey(VK_DOWN) || inputKey('S')) && player.y < size[Y] - 1) {
		player.y += 0.6;
	}
	else if ((inputKey(VK_RIGHT) || inputKey('D')) && player.x < size[X] - 1) {
		player.x += 1;
	}
	showCursor(FALSE);
}

void release() {
	ScreenRelease();
}