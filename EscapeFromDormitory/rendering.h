#pragma once
#include "gameData.h"
#include "game.h"
#include "console.h"

// ½ºÅ×¹Ì³Ê ±×¸®±â
void drawStamina() {
	Point p = { 0, 34 };
	double per = (double)stamina / MAX_STAMINA * 100;
	for (; p.x < (int)per * 105 / 100; ++p.x) {
		print(p, YELLOW"="WHITE);
	}
}

// ±â¼÷»ç ¸Ê ±×¸®±â
void renderMap(int stage) {
	Point m = { 0, 0 };
	for (int i = 0; i < 34; ++i) {
		print(m, map[stage][i]);
		++m.y;
	}
}

// ÇöÀç Ãþ
void drawFloor() {
	Point p = { 100, 32 };
	char buf[16] = ""; sprintf(buf, "%dÃþ", stageIdx);
	print(p, buf);
}