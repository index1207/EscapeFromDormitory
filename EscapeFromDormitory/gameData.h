#pragma once
#include "console.h"


HWND hWnd;
HANDLE handle;


Sound sound;
BOOL isGameoverSoundPlayed = FALSE;
BOOL isTalkToJunsungPlayed = FALSE;
BOOL isTalkToJunseoPlayed = FALSE;
BOOL isTalkToDaejinPlayed = FALSE;
BOOL isTalkToJoomyPlayed = FALSE;

typedef struct {
	Point pos;
	double speed;
	char* name;
} Character;

int stamina;

static Character player = { 0, 0, 0.5 };
static Character enemy = { 0, 0, 0.15 };

Map size = { 105, 35 };

static char map[6][35][105];

static BOOL isStart;
static BOOL isTitleScreen;

static Point arrow = {40, 0};
static int selection = 0;


static int stageIdx = 5;


#define MAX_STAMINA 200

#define WALL '#'