#pragma once
#include "gameData.h"
#include "game.h"
#include "console.h"

// 스테미너 그리기
void drawStamina() {
	Point p = { 0, 34 };
	double per = (double)stamina / MAX_STAMINA * 100;
	for (; p.x < (int)per * 105 / 100; ++p.x) {
		print(p, YELLOW"="WHITE);
	}
}

void drawTitle() {
	Point p = { 5,0 };
	for (int i = 0; i < 35; ++i) {
		print(p, map[0][i]);
		++p.y;
	}
}

// 기숙사 맵 그리기
void renderMap(int stage) {
	Point m = { 0, 0 };
	for (int i = 0; i < 34; ++i) {
		print(m, map[stage][i]);
		++m.y;
	}
}