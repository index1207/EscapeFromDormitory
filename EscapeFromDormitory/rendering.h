#pragma once
#include "gameData.h"
#include "game.h"
#include "console.h"

// ???׹̳? ?׸???
void drawStamina() {
	Point p = { 0, 34 };
	double per = (double)stamina / MAX_STAMINA * 100;
	for (; p.x < (int)per * 105 / 100; ++p.x) {
		print(p, YELLOW"="WHITE);
	}
}

// ?????? ?? ?׸???
void renderMap(int stage) {
	Point m = { 0, 0 };
	for (int i = 0; i < 34; ++i) {
		print(m, map[stage][i]);
		++m.y;
	}
}

// ???? ??
void drawFloor() {
	Point p = { 100, 32 };
	char buf[16] = "";
	if (stageIdx > 5) {
		if (stageIdx > 9) {
			sprintf(buf, "%d??", stageIdx - 8);
		}
		else {
			sprintf(buf, "%d??", stageIdx - 4);
		}
	}
	else sprintf(buf, "%d??", stageIdx);
	print(p, buf);
}