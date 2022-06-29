#pragma once
#include <Windows.h>
#include <mmsystem.h>

typedef struct sound_ {
	void (*play)(LPCSTR, int);
	void (*stop)(void);
} Sound;

void sound_play(LPCSTR filename, int type) {
	PlaySound(TEXT(filename), NULL, type);
}

void sound_stop(void) {
	PlaySound(NULL, NULL, SND_ASYNC);
}

void InitSound(Sound* sound) {
	sound->play = sound_play;
	sound->stop = sound_stop;
}