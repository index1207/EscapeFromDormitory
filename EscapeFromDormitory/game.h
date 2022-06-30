#pragma once
#include <math.h>
#include "screen.h"
#include "vector.h"
#include "sound.h" 

#include "inputmanager.h"
#include "kizaoui.h"
#include "rendering.h"

// 초기화
void initialization() {
	CONSOLE_FONT_INFOEX fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(handle, 0, &fontex);
	fontex.FontWeight = 800;
	fontex.dwFontSize.X = 22;
	fontex.dwFontSize.Y = 22;
	SetCurrentConsoleFontEx(handle, NULL, &fontex);

	isTitleScreen = TRUE;

	// 사운드
	InitSound(&sound);

	//스테미나와 좌표의 초기값
	stamina = MAX_STAMINA;
	setPoint(&player.pos, 50, 8);
	setPoint(&enemy.pos, 75, 2);

	// 기본적인 콘솔창 세팅
	showCursor(FALSE);
	SetConsoleTitle("기숙사 탈출");
	setConsoleSize(size.x, size.y);

	// 타이틀 화면
	FILE* fp = fopen("resource/title.txt", "r");
	for (int i = 0; fgets(map[0][i], 105, fp) != NULL; ++i);
	fclose(fp);

	// 맵 로드
	for (int i = 2; i <= 5; ++i) {
		fp = fopen("resource/stage/roby.txt", "r");
		for (int j = 0; fgets(map[i][j], 105, fp) != NULL; ++j);
		fclose(fp);
	}

	// 스크린 버퍼 초기화
	screenInit();
}

// 그리기
void render() {
	// 스크린 버퍼 비우기
	ScreenClear();

	if (isTitleScreen) {
		// 타이틀 화면
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
		// 맵 그리기
		renderMap(stageIdx);

		// 층
		drawFloor();

		// 오브젝트 그리기
		print(player.pos, CYAN"†"WHITE);

		if (stageIdx == 3) {
			print(enemy.pos, RED"⊙"WHITE);

			// 기자위에게 잡혔다면
			if (!isStart) {
				Point t = { size.x / 2 - 12, size.y / 2 - 2 };
				print(t, "김준서에게 잡혀버렸다!");

				if (!isGameoverSoundPlayed) {
					sound.play("resource/sound/잡혔을때.wav", SND_FILENAME | SND_SYNC);
					sound.play("resource/sound/게임오버.wav", SND_FILENAME | SND_ASYNC);
					isGameoverSoundPlayed = TRUE;
				}
				if (inputKey(VK_ESCAPE)) exit(0);
			}
		}

		// 스태미너 바
		drawStamina();
	}

	screenFlipping();
}

// 값 변화시키기
void update() {
	if (isTitleScreen) {
		titleInput();
	}
	else if (isTitleScreen ^ isStart) {
		// 키보드 입력 관리
		gameInput();

		if (stageIdx == 3) {
			// 적의 움직임 갱신
			followEnemy();
		}

		if (stageIdx != 1) {
			if ((int)player.pos.x == 0 && ((int)player.pos.y >= 26 && (int)player.pos.y <= 34)) {
				--stageIdx;
				setPoint(&player.pos, 50, 8);
			}
		}
	}
}

void release() {
	ScreenRelease();
}