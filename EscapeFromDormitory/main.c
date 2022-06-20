#include "game.h"

int main() {
	initialization();

	while (TRUE) {
		Sleep(13);
		update();
		render();
	}
	release();
}