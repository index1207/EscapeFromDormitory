#pragma once
#include <math.h>
#include "screen.h"
#include "vector.h"
#include "sound.h" 

#include "inputmanager.h"
#include "kizaoui.h"
#include "rendering.h"

void windowInit() {
	// �⺻���� �ܼ�â ����
	showCursor(FALSE);
	SetConsoleTitle("����� Ż��");
	setConsoleSize(size.x, size.y);

	memset(map, ' ', sizeof(map));

	hWnd = GetConsoleWindow();
	MoveWindow(hWnd, 350, 100, 0, 0, 1);

	CONSOLE_FONT_INFOEX fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(handle, 0, &fontex);
	fontex.FontFamily = TMPF_TRUETYPE;
	wcscpy(fontex.FaceName, "Arial");
	fontex.FontWeight = 200;
	fontex.dwFontSize.Y = 22;
	SetCurrentConsoleFontEx(handle, NULL, &fontex);
}

void loadMap(void) {
	// Ÿ��Ʋ ȭ��
	FILE* fp = fopen("resource/title.txt", "r");
	for (int i = 0; fgets(map[0][i], 105, fp) != NULL; ++i);
	fclose(fp);

	// �� �ε�
	fp = fopen("resource/stage/first.txt", "r");
	for (int i = 0; fgets(map[1][i], 105, fp) != NULL; ++i);

	for (int i = 2; i < 5; ++i) {
		fp = fopen("resource/stage/roby.txt", "r");
		for (int j = 0; fgets(map[i][j], 105, fp) != NULL; ++j);
		fclose(fp);
	}

	fp = fopen("resource/stage/fifth.txt", "r");
	for (int i = 0; fgets(map[5][i], 105, fp) != NULL; ++i);
	fclose(fp);
	
	for (int i = 6; i <= 9; ++i) {
		fp = fopen("resource/stage/leftside.txt", "r");
		for (int j = 0; fgets(map[i][j], 105, fp) != NULL; ++j);
		fclose(fp);
	}
	for (int i = 10; i <= 13; ++i) {
		fp = fopen("resource/stage/rightside.txt", "r");
		for (int j = 0; fgets(map[i][j], 105, fp) != NULL; ++j);
		fclose(fp);
	}
}

// �ʱ�ȭ
void initialization() {
	windowInit(); 
	loadMap();

	isTitleScreen = TRUE;

	// ����
	InitSound(&sound);

	//���׹̳��� ��ǥ�� �ʱⰪ
	stamina = MAX_STAMINA;
	setPoint(&player.pos, 50, 5);
	setPoint(&enemy.pos, 75, 2);

	// ��ũ�� ���� �ʱ�ȭ
	screenInit();
}

// �׸���
void render() {
	// ��ũ�� ���� ����
	ScreenClear();
	if (isTitleScreen) {
		// Ÿ��Ʋ ȭ��
		renderMap(0);
		switch (selection) {
		case 0:
			arrow.y = 25;
			break;
		case 1:
			arrow.y = 27;
			break;
		case 2:
			arrow.y = 29;
			break;
		}
		print(arrow, "��");
	}
	else {
		// �� �׸���
		renderMap(stageIdx);
		drawFloor();

		// ������Ʈ �׸���
		print(player.pos, CYAN"��"WHITE);

		if (stageIdx == 3) {
			print(enemy.pos, RED"��"WHITE);

			// ���������� �����ٸ�
			if (!isStart) {
				Point t = { size.x / 2 - 12, size.y / 2 - 2 };
				print(t, "���ؼ����� �������ȴ�!");

				if (!isGameoverSoundPlayed) {
					sound.play("resource/sound/��������.wav", SND_FILENAME | SND_SYNC);
					sound.play("resource/sound/���ӿ���.wav", SND_FILENAME | SND_ASYNC);
					isGameoverSoundPlayed = TRUE;
				}
				if (inputKey(VK_ESCAPE)) exit(0);
			}
		}

		// ���¹̳� ��
		drawStamina();
	}

	screenFlipping();
}

// �� ��ȭ��Ű��
void update() {
	if (isTitleScreen) {
		titleInput();
	}
	else if (isTitleScreen ^ isStart) {
		// Ű���� �Է� ����
		gameInput();

		if (stageIdx == 3) {
			// ���� ������ ����
			followEnemy();
		}

		if (stageIdx != 1) {
			// �����϶�
			if (stageIdx > 5) {
				// ���� ����
				if (stageIdx >= 6 && stageIdx <= 9) {
					if ((int)player.pos.x == 100 && player.pos.y >= 1 && player.pos.y <= 9) {
						stageIdx -= 4;
						setPoint(&player.pos, 3, 3);
					}
				}
				// ������ ����
				else {
					if ((int)player.pos.x == 0 && player.pos.y >= 1 && player.pos.y <= 9) {
						stageIdx -= 8;
						setPoint(&player.pos, 100, 8);
					}
				}
			}
			// �κ��϶�
			else {
				// ���
				if ((int)player.pos.x == 0 && ((int)player.pos.y >= 26 && (int)player.pos.y <= 34)) {
					--stageIdx;
					setPoint(&player.pos, 50, 10);
				}
				// ���� ����
				else if ((int)player.pos.x == 0 && (int)player.pos.y >= 1 && (int)player.pos.y <= 5) {
					stageIdx += 4;
					setPoint(&player.pos, 100, 5);
				}
				// ������ ����
				else if ((int)player.pos.x == 102 && ((int)player.pos.y >= 7 && (int)player.pos.y <= 11)) {
					stageIdx += 8;
					setPoint(&player.pos, 2, 5);
				}
			}
		}
	}
}

void release() {
	ScreenRelease();
}