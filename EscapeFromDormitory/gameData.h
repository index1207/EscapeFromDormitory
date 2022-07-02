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

typedef struct {
	Point pos;
	int nStage;
	const char* sound;
} Npc;

int stamina;

static Character player = { 0, 0, 0.2 };
static Character enemy = { 0, 0, 0.25 };

static Npc daejin;
static Npc taeoh;
static Npc joonseo;
static Npc joonseung;
static Npc jooeun;

Map size = { 105, 35 };

static char map[14][35][105];
static char leftside[4][7][105];

static BOOL isStart;
static BOOL isTitleScreen;

static Point arrow = {44, 0};
static int selection = 0;


static int stageIdx = 5;


#define MAX_STAMINA 200