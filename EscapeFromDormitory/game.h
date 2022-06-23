#pragma once
#include <process.h>
#include <math.h>
#include <float.h>
#include "console.h"
#include "screen.h"
#include "vector.h"

#define MAX_STAMINA 200

#define WALL '#'

typedef struct {
	Point* pos;
	double speed;
	char* name;               
} Character;

int stamina;

Point player_pos;
static Character player = { &player_pos, 0.2 };

Point enemy_pos;
static Character enemy = { &enemy_pos, 0.3 };

Map size = { 105, 35 };

static char map[35][105];
static char titlemap[35][105];

static BOOL isStart;
static BOOL isTitleScreen;

// Ű �Է�
int inputKey(int key) {
	return (GetAsyncKeyState(key) & 0x8000);
}

// �÷��̾� �Է� ����
void inputManagement(BOOL isMove) {
	if (isMove) {
		if (inputKey(VK_LSHIFT)) {
			if (stamina > 0) {
				player.speed = 0.4;
				stamina -= 1;
			}
			else {
				player.speed = 0.2;
			}
		}
		if ((!inputKey(VK_LSHIFT)) && (stamina < MAX_STAMINA)) {
			player.speed = 0.2;
			stamina += 1;
		}
		if (inputKey('A') && player_pos.x > 0) {
			if (map[(int)player_pos.y][(int)(player_pos.x - player.speed)] != WALL) {
				player_pos.x -= player.speed;
			}
		}
		if (inputKey('W') && player_pos.y > 0) {
			if (map[(int)(player_pos.y - player.speed / 2.25)][(int)player_pos.x] != WALL) {
				player_pos.y -= player.speed / 2.25;
			}
		}
		if (inputKey('S') && player_pos.y < size.y - 2) {
			if (map[(int)(player_pos.y + player.speed / 2.25)][(int)player_pos.x] != WALL) {
				player_pos.y += player.speed / 2.25;
			}
		}
		if (inputKey('D') && player_pos.x < size.x - 3) {
			if (map[(int)player_pos.y][(int)(player_pos.x + player.speed)] != WALL) {
				player_pos.x += player.speed;
			}
		}
	}
}


// ���׹̳� �׸���
void drawStamina() {
	Point p = { 0, 34 };
	double per = (double)stamina / MAX_STAMINA * 100;
	for (; p.x < (int)per * 105 / 100; ++p.x) {
		print(p, YELLOW("="));
	}
}

// ������Ʈ ��ǥ Ȯ�ο�
void debuging() {
	Point p = { 0,0 };
	char buf[16];
	sprintf(buf, "(%.1lf, %.1lf)", player_pos.x, player_pos.y);
	print(p, buf);
}

// ����� �� �׸���
void renderMap() {
	Point m = { 0, 0 };
	for (int i = 0; i < 34; ++i) {
		print(m, map[i]);
		++m.y;
	}
}

// ������� ��
void followEnemy(BOOL isFollow) {
	if (isFollow) {
		if (!equalPoint(player_pos, enemy_pos)) {
			// �÷��̾�� ���ϴ� ����
			vec2 diff = { player_pos.x - enemy_pos.x, player_pos.y - enemy_pos.y };

			// ���� ����ȭ
			vec2 normalized = vec2_normalize(&diff, vec2_size(diff));
			
			// ���� �ε�������
			if (map[(int)(enemy_pos.y + normalized.y * enemy.speed / 2)][(int)(enemy_pos.x + normalized.x * enemy.speed)] != WALL) {
				enemy_pos.x += normalized.x * enemy.speed;
				enemy_pos.y += normalized.y * enemy.speed / 2;
			}
			else { // �ε����ٸ�
				vec2 upRay = { enemy_pos.x, enemy_pos.y - 10 };
				vec2 downRay = { enemy_pos.x, enemy_pos.y + 10 };
				vec2 leftRay = { enemy_pos.x - 10, enemy_pos.x };
				vec2 rightRay = { enemy_pos.x + 10, enemy_pos.x };

				vec2 uv, dv, lv, rv;
				set_vec2(&uv, player_pos.x - upRay.x, player_pos.y - upRay.y);
				set_vec2(&dv, player_pos.x - downRay.x, player_pos.y - downRay.y);
				set_vec2(&lv, player_pos.x - leftRay.x, player_pos.y - leftRay.y);
				set_vec2(&rv, player_pos.x - rightRay.x, player_pos.y - rightRay.y);

				BOOL isHorizon = TRUE; // ��������� ���ΰ�?
				if (map[(int)enemy_pos.y][(int)enemy_pos.x + 1] == WALL || map[(int)enemy_pos.y][(int)enemy_pos.x - 1] == WALL) {
					isHorizon = FALSE;
				}

				int dir = -1; //����
				if (isHorizon) {
					if (vec2_size(lv) < vec2_size(rv)) {
						dir = -1;
					}
					else {
						dir = 1;
					}
					enemy_pos.x += dir * enemy.speed;
				}
				else { // ��������(Vertical)
					if (vec2_size(uv) < vec2_size(dv)) {
						dir = -1;
					}
					else {
						dir = 1;
					}
					enemy_pos.y += dir * enemy.speed / 2;
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
	FILE* fp = fopen("third.txt", "r");
	for (int i = 0; fgets(map[i], 105, fp) != NULL; ++i);
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
	drawStamina();


	// ���������� �����ٸ�
	if (!isStart) {
		Point t = { size.x / 2 - 12, size.y / 2 - 2 };
		print(t, "���ؼ����� �������ȴ�!");

		if (inputKey(VK_ESCAPE)) exit(0);
	}
	//debuging(); // ��ǥ Ȯ��

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