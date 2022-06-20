#pragma once
#include <math.h>
#include <float.h>
#include "console.h"
#include "screen.h"
#include "vector.h"

#define MAX_STAMINA 400

#define WALL 1

typedef struct {
	Point* pos;
	double speed;
	char* name;               
} Character;

int stamina;

Point player_pos;
Character player = { &player_pos, 0.3 };

Point enemy_pos;
Character enemy = { &enemy_pos, 0.4 };

Map size = { 105, 35 };

int map[35][105];
int stage = 5;

// 키 입력
int inputKey(int key) {
	return (GetAsyncKeyState(key) & 0x8000);
}

// 플레이어 입력 관리
void inputManagement(void) {
	if (inputKey(VK_LSHIFT)) {
		if (stamina > 0) {
			player.speed = 0.6;
			stamina -= 1;
		}
		else {
			player.speed = 0.3;
		}
	}
	if ((!inputKey(VK_LSHIFT)) && (stamina < MAX_STAMINA)) {
		player.speed = 0.3;
		stamina += 1;
	}
	if ((inputKey(VK_LEFT) || inputKey('A')) && player_pos.x > 0) {
		if (map[(int)player_pos.y][(int)(player_pos.x - player.speed)] != WALL) {
			player_pos.x -= player.speed;
		}
	}
	if ((inputKey(VK_UP) || inputKey('W')) && player_pos.y > 0) {
		if (map[(int)(player_pos.y - player.speed / 2.25)][(int)player_pos.x] != WALL) {
			player_pos.y -= player.speed / 2.25;
		}
	}
	if ((inputKey(VK_DOWN) || inputKey('S')) && player_pos.y < size.y - 1) {
		if (map[(int)(player_pos.y + player.speed / 2.25)][(int)player_pos.x] != WALL) {
			player_pos.y += player.speed / 2.25;
		}
	}
	if ((inputKey(VK_RIGHT) || inputKey('D')) && player_pos.x < size.x - 1) {
		if (map[(int)player_pos.y][(int)(player_pos.x + player.speed)] != WALL) {
			player_pos.x += player.speed;
		}
	}
}

void drawMap(int stage) {
	FILE* fp;
	switch (stage)
	{
	case 5:
		fp = fopen("stage/fifth.txt", 'r');
		break;
	case 4:
		fp = fopen("stage/fourth.txt", 'r');
		break;
	case 3:
		fp = fopen("stage/third.txt", 'r');
		break;
	case 2:
		fp = fopen("stage/second.txt", 'r');
		break;
	case 1:
		fp = fopen("stage/first.txt", 'r');
		break;
	case 0:
		fp = fopen("stage/room.txt", 'r');
		break;
	case -1:
		fp = fopen("stage/leftside", 'r');
		break;
	case -2:
		fp = fopen("stage/rightside.txt", 'r');
	default:
		break;
	}
}

// 따라오는 적
void followEnemy(void) {
	if (!equalPoint(player_pos, enemy_pos)) {
		vec2 diff = { player_pos.x - enemy_pos.x, player_pos.y - enemy_pos.y };
		vec2 normalized = vec2_normalize(&diff, vec2_size(diff));

		if (map[(int)(enemy_pos.y + normalized.y * enemy.speed / 2)][(int)(enemy_pos.x + normalized.x * enemy.speed)] != WALL) {
			enemy_pos.x += normalized.x * enemy.speed;
			enemy_pos.y += normalized.y * enemy.speed / 2;
		}
		else {
			vec2 upRay = { enemy_pos.x, enemy_pos.y - 5 };
			vec2 downRay = { enemy_pos.x, enemy_pos.x + 5 };
			vec2 leftRay = { enemy_pos.x - 5, enemy_pos.x };
			vec2 rightRay = { enemy_pos.x + 5, enemy_pos.x };

			set_vec2(&upRay, player_pos.x - upRay.x, player_pos.y - upRay.y);
			set_vec2(&downRay, player_pos.x - downRay.x, player_pos.y - downRay.y);
			set_vec2(&leftRay, player_pos.x - leftRay.x, player_pos.y - leftRay.y);
			set_vec2(&rightRay, player_pos.x - rightRay.x, player_pos.y - rightRay.y);

			BOOL isHorizon = TRUE;
			if (map[(int)enemy_pos.y][(int)enemy_pos.x + 1] == WALL || map[(int)enemy_pos.y][(int)enemy_pos.x - 1]) {
				isHorizon = FALSE;
			}

			if (!isHorizon) {
				if (vec2_size(upRay) < vec2_size(downRay)) {
					normalized.y = -1;
				}
				else {
					normalized.y = 1;
				}
				enemy_pos.y += normalized.y * enemy.speed / 2;
			}
			else {
				if (vec2_size(leftRay) < vec2_size(rightRay)) {
					normalized.x = -1;
				}
				else {
					normalized.x = 1;
				}
				enemy_pos.x += normalized.x * enemy.speed;
			}
		}
	}
	else {
		//만났다면
		exit(EXIT_SUCCESS);
	}
}


// 초기화
void initialization() {
	//스테미나와 좌표의 초기값
	stamina = MAX_STAMINA;
	setPoint(&player_pos, 0, 18);
	setPoint(&enemy_pos, 50, 20);

	// 기본적인 콘솔창 세팅
	showCursor(FALSE);
	SetConsoleTitle("Escape from Dormitory");
	setConsoleSize(size.x, size.y);

	// 맵 그리기
	ZeroMemory(map, 35 * 105);
	
	// 스크린 버퍼 초기화
	screenInit();
}

// 그리기
void render() {
	// 스크린 버퍼 비우기
	ScreenClear();

	// 오브젝트 그리기
	print(player_pos, "㉿");
	print(enemy_pos, RED("!"));

	// 스태미너 바
	Point p = {0, 34};
	double per = (double)stamina/MAX_STAMINA * 100;
	for (; p.x < (int)per * 105/100; ++p.x) {
		print(p, "=");
	}
	
	// 맵 그리기
	for (int i = 0; i < size.y; ++i) {
		for (int j = 0; j < size.x; ++j) {
			p.x = j; p.y = i;
			if (map[i][j] == WALL) {
				print(p, "@");
			}
		}
	}

	screenFlipping();
}

// 값 변화시키기
void update() {
	// 키보드 입력 관리
	inputManagement();

	// 적의 움직임 갱신
	followEnemy();
}

void release() {
	ScreenRelease();
}