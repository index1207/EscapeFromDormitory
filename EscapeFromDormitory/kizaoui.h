#pragma once
#include "gameData.h"
#include "game.h"

// 따라오는 적
void followEnemy() {
	if (!equalPoint(player.pos, enemy.pos)) {
		// 플레이어로 향하는 벡터
		vec2 diff = { player.pos.x - enemy.pos.x, player.pos.y - enemy.pos.y };

		// 벡터 정규화
		vec2 normalized = vec2_normalize(&diff, vec2_size(diff));

		// 벽에 부딛혔는지
		if (map[stageIdx][(int)(enemy.pos.y + normalized.y * enemy.speed / 2)][(int)(enemy.pos.x + normalized.x * enemy.speed)] != WALL) {
			enemy.pos.x += normalized.x * enemy.speed;
			enemy.pos.y += normalized.y * enemy.speed / 2;
		}
		else { // 부딛혔다면
			vec2 upRay = { enemy.pos.x, enemy.pos.y - 10 };
			vec2 downRay = { enemy.pos.x, enemy.pos.y + 10 };
			vec2 leftRay = { enemy.pos.x - 10, enemy.pos.x };
			vec2 rightRay = { enemy.pos.x + 10, enemy.pos.x };

			vec2 uv, dv, lv, rv;
			set_vec2(&uv, player.pos.x - upRay.x, player.pos.y - upRay.y);
			set_vec2(&dv, player.pos.x - downRay.x, player.pos.y - downRay.y);
			set_vec2(&lv, player.pos.x - leftRay.x, player.pos.y - leftRay.y);
			set_vec2(&rv, player.pos.x - rightRay.x, player.pos.y - rightRay.y);

			BOOL isHorizontal = TRUE; // 수평방향의 벽인가?
			if (map[stageIdx][(int)enemy.pos.y][(int)enemy.pos.x - 1] == WALL || map[stageIdx][(int)enemy.pos.y][(int)enemy.pos.x + 1] == WALL) {
				isHorizontal = FALSE;
			}

			int dir = -1; //방향
			if (isHorizontal) {
				if (vec2_size(lv) < vec2_size(rv)) {
					dir = -1;
				}
				else {
					dir = 1;
				}
				enemy.pos.x += dir * enemy.speed;
			}
			else { // 수직방향(Vertical)
				if (vec2_size(uv) < vec2_size(dv)) {
					dir = -1;
				}
				else {
					dir = 1;
				}
				enemy.pos.y += dir * enemy.speed / 2;
			}
		}
	}
	else {
		//만났다면
		isStart = FALSE;
	}
}