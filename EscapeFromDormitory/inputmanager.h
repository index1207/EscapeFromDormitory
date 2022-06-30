#pragma once
#include "gameData.h"
#include "game.h"

// 키 입력
#define inputKey(key) (GetAsyncKeyState(key) & 0x8000)

void titleInput() {
	if (inputKey(VK_UP) && selection > 0) {
		--selection;
		Sleep(100);
	}
	if (inputKey(VK_DOWN) && selection < 2) {
		++selection;
		Sleep(100);
	}
	if (inputKey(VK_RIGHT)) {
		isTitleScreen = FALSE;
		isStart = TRUE;
	}
}

// 플레이어 입력 관리
void gameInput() {
	if (inputKey(VK_LSHIFT)) {
		if (stamina > 0) {
			player.speed = 0.3;
			stamina -= 1;
		}
		else {
			player.speed = 0.1;
		}
	}
	if ((!inputKey(VK_LSHIFT)) && (stamina < MAX_STAMINA)) {
		player.speed = 0.2;
		stamina += 1;
	}
	if (inputKey('A') && player.pos.x > 0) {
		if (map[stageIdx][(int)player.pos.y][(int)(player.pos.x - player.speed)] != WALL) {
			player.pos.x -= player.speed;
		}
	}
	if (inputKey('W') && player.pos.y > 0) {
		if (map[stageIdx][(int)(player.pos.y - player.speed / 2.25)][(int)player.pos.x] != WALL) {
			player.pos.y -= player.speed / 2.25;
		}
	}
	if (inputKey('S') && player.pos.y < size.y - 2) {
		if (map[stageIdx][(int)(player.pos.y + player.speed / 2.25)][(int)player.pos.x] != WALL) {
			player.pos.y += player.speed / 2.25;
		}
	}
	if (inputKey('D') && player.pos.x < size.x - 3) {
		if (map[stageIdx][(int)player.pos.y][(int)(player.pos.x + player.speed)+1] != WALL) {
			player.pos.x += player.speed;
		}
	}
}