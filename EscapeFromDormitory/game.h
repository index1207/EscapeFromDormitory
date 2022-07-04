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
	// 기본적인 콘솔창 세팅
	showCursor(FALSE);
	SetConsoleTitle("기숙사 탈출");
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
		// 복도일때
		if (stageIdx > 5) {
			// 왼쪽 복도
			if (stageIdx >= 6 && stageIdx <= 9) {
				if ((int)player.pos.x == 100 && player.pos.y >= 1 && player.pos.y <= 9) {
					stageIdx -= 4;
					setPoint(&player.pos, 3, 3);
				}
			}
			// 오른쪽 복도
			else {
				if ((int)player.pos.x == 0 && player.pos.y >= 1 && player.pos.y <= 9) {
					stageIdx -= 8;
					setPoint(&player.pos, 100, 8);
				}
			}
		}
		// 로비일때
		else {
			// 계단
			if ((int)player.pos.x == 0 && ((int)player.pos.y >= 26 && (int)player.pos.y <= 34)) {
				--stageIdx;
				if (stageIdx != 1) {
					setPoint(&player.pos, 50, 10);
				}
				else {
					setPoint(&player.pos, 71, 32);
				}
			}
			// 왼쪽 복도
			else if ((int)player.pos.x == 0 && (int)player.pos.y >= 1 && (int)player.pos.y <= 5) {
				stageIdx += 4;
				setPoint(&player.pos, 100, 5);
			}
			// 오른쪽 복도
			else if ((int)player.pos.x == 102 && ((int)player.pos.y >= 7 && (int)player.pos.y <= 11)) {
				stageIdx += 8;
				setPoint(&player.pos, 2, 5);
			}
		}
	}
}

void setNPC() {
	Point pos = { 77, 3 };
	taeoh.nStage = 4;
	taeoh.sound = "resource/sound/힌트의힌트.wav";
	taeoh.pos = pos;

	setPoint(&pos, 42, 2);
	daejin.nStage = 12;
	daejin.sound = "resource/sound/힌트1.wav";
	daejin.pos = pos;

	setPoint(&pos, 32, 9);
	joonseo.nStage = 11;
	joonseo.sound = "resource/sound/힌트2.wav";
	joonseo.pos = pos;

	setPoint(&pos, 22, 8);
	joonseung.nStage = 6;
	joonseung.sound = "resource/sound/힌트3.wav";
	joonseung.pos = pos;

	setPoint(&pos, 72, 29);
	jooeun.nStage = 5;
	jooeun.sound = "resource/sound/힌트4.wav";
	jooeun.pos = pos;
}

void renderNPC(int stage) {
	switch (stage) {
	case 12:
	{Point p = daejin.pos;
	p.x -= 1;
	print(p, GREEN"대진"WHITE); }
		break;
	case 11:
	{Point p = joonseo.pos;
	p.x -= 1;
	print(p, GREEN"준서"WHITE); }
		break;
	case 5:
	{Point p = jooeun.pos;
	p.x -= 1;
	print(p, GREEN"주은"WHITE); }
		break;
	case 4:
	{Point p = taeoh.pos;
	p.x -= 1;
	print(p, GREEN"태오"WHITE); }
		break;
	case 6:
	{Point p = joonseung.pos;
	p.x -= 1;
	print(p, GREEN"준성"WHITE); }
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
	// 타이틀 화면
	FILE* fp = fopen("resource/title.txt", "r");
	for (int i = 0; fgets(map[0][i], 105, fp) != NULL; ++i);
	fclose(fp);

	// 맵 로드
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

// 초기화
void initialization() {
	windowInit(); 
	loadMap();
	setNPC();

	isTitleScreen = TRUE;

	// 사운드
	InitSound(&sound);

	//스테미나와 좌표의 초기값
	stamina = MAX_STAMINA;
	setPoint(&player.pos, 50, 5);
	setPoint(&enemy.pos, 75, 2);

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
			arrow.y = 25;
			break;
		case 1:
			arrow.y = 27;
			break;
		case 2:
			arrow.y = 29;
			break;
		}
		print(arrow, "▷");
	}
	else {
		// 맵 그리기
		renderMap(stageIdx);
		drawFloor();
		renderNPC(stageIdx);
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
			if (!isPlayed) {
				sound.play("resource/sound/쫓아갈때.wav", SND_FILENAME | SND_SYNC);
				sound.play("resource/sound/쫓아가면서.wav", SND_FILENAME | SND_ASYNC);
				isPlayed = TRUE;
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

		sayHint(stageIdx);

		if (stageIdx == 3) {
			// 적의 움직임 갱신
			followEnemy();
		}
		else if (stageIdx == 1) { // 키패드
			Point keypad = { 17,1 };
			if (equalPoint(player.pos, keypad)) {
				char pwd[5] = "";
				int i = 0;
			}
		}

		changeMap();
	}
}

void release() {
	ScreenRelease();
}