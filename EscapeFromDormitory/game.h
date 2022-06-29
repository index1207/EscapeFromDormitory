#pragma once
#include <math.h>
#include "screen.h"
#include "vector.h"
#include "sound.h" 

#include "inputmanager.h"
#include "kizaoui.h"
#include "rendering.h"

// �ʱ�ȭ
void initialization() {
	isTitleScreen = TRUE;

	// ����
	InitSound(&sound);

	//���׹̳��� ��ǥ�� �ʱⰪ
	stamina = MAX_STAMINA;
	setPoint(&player.pos, 1, 2);
	setPoint(&enemy.pos, 50, 20);

	// �⺻���� �ܼ�â ����
	showCursor(FALSE);
	SetConsoleTitle("����� Ż��");
	setConsoleSize(size.x, size.y);

	// Ÿ��Ʋ ȭ��
	FILE* fp = fopen("resource/title.txt", "r");
	for (int i = 0; fgets(map[0][i], 105, fp) != NULL; ++i);
	fclose(fp);

	// �� �ε�
	for (int i = 2; i <= 5; ++i) {
		fp = fopen("resource/stage/roby.txt", "r");
		for (int j = 0; fgets(map[i][j], 105, fp) != NULL; ++j);
		fclose(fp);
	}

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
			arrow.y = 23;
			break;
		case 1:
			arrow.y = 25;
			break;
		case 2:
			arrow.y = 27;
			break;
		}
		print(arrow, YELLOW">"WHITE);
	}
	else {
		// �� �׸���
		renderMap(5);

		// ������Ʈ �׸���
		print(player.pos, CYAN"P"WHITE);
		print(enemy.pos, RED"D"WHITE);

		// ���¹̳� ��
		drawStamina();

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

		// ���� ������ ����
		followEnemy();

		if ((int)player.pos.x == 0 && ((int)player.pos.y >= 31 && (int)player.pos.y <= 34)) {
			--stageIdx;
		}
	}
}

void release() {
	ScreenRelease();
}