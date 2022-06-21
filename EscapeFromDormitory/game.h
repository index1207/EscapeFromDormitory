#pragma once
#include <process.h>
#include <math.h>
#include <float.h>
#include "console.h"
#include "screen.h"
#include "vector.h"

#define MAX_STAMINA 100

#define WALL '1'

typedef struct {
	Point* pos;
	double speed;
	char* name;               
} Character;

int stamina;

Point player_pos;
Character player = { &player_pos, 0.6 };

Point enemy_pos;
Character enemy = { &enemy_pos, 0.6 };

Map size = { 105, 35 };

char map[35][105];

BOOL isStart;

// Ű �Է�
int inputKey(int key) {
	return (GetAsyncKeyState(key) & 0x8000);
}

// �÷��̾� �Է� ����
void inputManagement(BOOL isMove) {
	if (isMove) {
		if (inputKey(VK_LSHIFT)) {
			if (stamina > 0) {
				player.speed = 0.8;
				stamina -= 1;
			}
			else {
				player.speed = 0.6;
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
		if ((inputKey(VK_DOWN) || inputKey('S')) && player_pos.y < size.y - 2) {
			if (map[(int)(player_pos.y + player.speed / 2.25)][(int)player_pos.x] != WALL) {
				player_pos.y += player.speed / 2.25;
			}
		}
		if ((inputKey(VK_RIGHT) || inputKey('D')) && player_pos.x < size.x - 3) {
			if (map[(int)player_pos.y][(int)(player_pos.x + player.speed)] != WALL) {
				player_pos.x += player.speed;
			}
		}
	}
}

void renderMap() {
	Point m = { 0, 0 };
	for (int i = 0; i < 34; ++i) {
		m.x = 0;
		for (int j = 0; j < 103; ++j) {
			if (map[i][j] == '1') {
				print(m, "#");
			}
			else {
				print(m, " ");
			}
			++m.x;
		}
		++m.y;
	}
}

// ������� ��
void followEnemy(BOOL isFollow) {
	if (isFollow) {
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

				if (isHorizon) {
					if (vec2_size(leftRay) < vec2_size(rightRay)) {
						normalized.x = -1;
					}
					else {
						normalized.x = 1;
					}
					enemy_pos.x += normalized.x * enemy.speed;
				}
				else {
					if (vec2_size(upRay) < vec2_size(downRay)) {
						normalized.y = -1;
					}
					else {
						normalized.y = 1;
					}
					enemy_pos.y += normalized.y * enemy.speed / 2;
				}
			}
		}
		else {
			//�����ٸ�
			isStart = FALSE;
		}
	}
}


// �ʱ�ȭ
void initialization() {
	isStart = TRUE;

	//���׹̳��� ��ǥ�� �ʱⰪ
	stamina = MAX_STAMINA;
	setPoint(&player_pos, 1, 2);
	setPoint(&enemy_pos, 50, 20);

	// �⺻���� �ܼ�â ����
	showCursor(FALSE);
	SetConsoleTitle("����� Ż��");
	setConsoleSize(size.x, size.y);

	// �� �׸���
	ZeroMemory(map, 35 * 105);
	FILE* fp = fopen("fourth.txt", "r");
	char buf[105];
	for (int i = 0; fgets(buf, 105, fp) != NULL; ++i) {
		strcpy(map[i], buf);
	}
	fclose(fp);
	// ��ũ�� ���� �ʱ�ȭ
	screenInit();
}

// �׸���
void render() {
	// ��ũ�� ���� ����
	ScreenClear();

	// �� �׸���
	renderMap();

	// ������Ʈ �׸���
	print(player_pos, CYAN("P"));
	print(enemy_pos, RED("D"));

	// ���¹̳� ��
	Point p = { 0, 34 };
	double per = (double)stamina / MAX_STAMINA * 100;
	for (; p.x < (int)per * 105 / 100; ++p.x) {
		print(p, YELLOW("="));
	}

	if (!isStart) {
		Point t = {size.x/2-12, size.y/2-2};
		print(t, "�ؼ����� �������ȴ�!");

		if(inputKey(VK_ESCAPE)) exit(0);
	}

	screenFlipping();
}

// �� ��ȭ��Ű��
void update() {
	// Ű���� �Է� ����
	inputManagement(isStart);

	// ���� ������ ����
	followEnemy(isStart);
}

void release() {
	ScreenRelease();
}