#pragma once
#include <math.h>
#include <time.h>
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

void changeMap() {
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
				if (stageIdx != 1) {
					setPoint(&player.pos, 50, 10);
				}
				else {
					setPoint(&player.pos, 71, 32);
				}
			}
			else if ((int)player.pos.x == 10 && player.pos.y >= 18 && player.pos.y <= 24 && stageIdx != 1) {
				if (stageIdx < 5 && stageIdx > 1) {
					++stageIdx;
					setPoint(&player.pos, 50, 10);
				}
			}
			else if (stageIdx == 1 && (int)player.pos.x > 11 && (int)player.pos.x < 23 && (int)player.pos.y == 29) {
				++stageIdx;
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
void initNpc() {
	Point pos = { 77, 3 };
	taeoh.nStage = 4;
	taeoh.sound = "resource/sound/��Ʈ����Ʈ.wav";
	taeoh.pos = pos;

	setPoint(&pos, 42, 2);
	daejin.nStage = 12;
	daejin.sound = "resource/sound/��Ʈ1.wav";
	daejin.pos = pos;

	setPoint(&pos, 32, 9);
	joonseo.nStage = 11;
	joonseo.sound = "resource/sound/��Ʈ2.wav";
	joonseo.pos = pos;

	setPoint(&pos, 22, 8);
	joonseung.nStage = 6;
	joonseung.sound = "resource/sound/��Ʈ3.wav";
	joonseung.pos = pos;

	setPoint(&pos, 72, 29);
	jooeun.nStage = 5;
	jooeun.sound = "resource/sound/��Ʈ4.wav";
	jooeun.pos = pos;
}

void renderNPC(int stage) {
	switch (stage) {
	case 12:
	{Point p = daejin.pos;
	p.x -= 1;
	print(p, GREEN"����"WHITE); }
		break;
	case 11:
	{Point p = joonseo.pos;
	p.x -= 1;
	print(p, GREEN"�ؼ�"WHITE); }
		break;
	case 5:
	{Point p = jooeun.pos;
	p.x -= 1;
	print(p, GREEN"����"WHITE); }
		break;
	case 4:
	{Point p = taeoh.pos;
	p.x -= 1;
	print(p, GREEN"�¿�"WHITE); }
		break;
	case 6:
	{Point p = joonseung.pos;
	p.x -= 1;
	print(p, GREEN"�ؼ�"WHITE); }
		break;
	default:
		break;
	}
}

void sayHint(int stage) {
	switch (stage) {
	case 12:
		if (equalPoint(player.pos, daejin.pos)) {
			player.pos.x -= 1;
			sound.play(daejin.sound, SND_SYNC);
		}
		break;
	case 11:
		if (equalPoint(player.pos, joonseo.pos)) {
			player.pos.x -= 1;
			sound.play(joonseo.sound, SND_SYNC);
		}
		break;
	case 5:
		if (equalPoint(player.pos, jooeun.pos)) {
			player.pos.x -= 1;
			sound.play(jooeun.sound, SND_SYNC);
		}
		break;
	case 4:
		if (equalPoint(player.pos, taeoh.pos)) {
			player.pos.x -= 1;
			sound.play(taeoh.sound, SND_SYNC);
		}
		break;
	case 6:
		if (equalPoint(player.pos, joonseung.pos)) {
			player.pos.x -= 1;
			sound.play(joonseung.sound, SND_SYNC);
		}
		break;
	default:
		break;
	}
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
	initNpc();

	FILE* fp = fopen("exit.txt", "w+");
	fprintf(fp, "F");
	fclose(fp);

	isTitleScreen = TRUE;

	// ����W
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
		renderNPC(stageIdx);
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
			if (!isPlayed) {
				sound.play("resource/sound/�Ѿư���.wav", SND_FILENAME | SND_SYNC);
				sound.play("resource/sound/�Ѿư��鼭.wav", SND_FILENAME | SND_ASYNC);
				isPlayed = TRUE;
			}
		}

		// ���¹̳� ��
		drawStamina();
	}

	screenFlipping();
}

// �� ��ȭ��Ű��
void update(int argc, char* argv[]) {
	if (isTitleScreen) {
		titleInput();
	}
	else if (isExit) {
		exit(1);
	}
	else if (isTitleScreen ^ isStart) {
		// Ű���� �Է� ����
		gameInput();

		sayHint(stageIdx);

		if (stageIdx == 3) {
			// ���� ������ ����
			followEnemy();
		}
		else if (stageIdx == 1) { // Ű�е�
			Point keypad = { 17,1 };
			if (equalPoint(player.pos, keypad)) {
				if (!isStop) {
					STARTUPINFO si;
					PROCESS_INFORMATION pi;

					ZeroMemory(&si, sizeof(si));
					si.cb = sizeof(si);
					ZeroMemory(&pi, sizeof(pi));

					CreateProcess(
						NULL,
						argv[1],
						NULL,
						NULL,
						FALSE,
						0,
						NULL,
						NULL,
						&si,
						&pi
					);
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
					isStop = TRUE;
				}
				FILE* fp = fopen("exit.txt", "r");
				char buf[2];
				fgets(buf, 2, fp);
				fclose(fp);
				if (strcmp(buf, "T") == 0) {
					isExit = TRUE;
				}
			}
		}

		changeMap();
	}
}

void release() {
	ScreenRelease();
}