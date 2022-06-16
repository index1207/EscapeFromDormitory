#include "game.h"

int main() {
	initialization();

	while (TRUE) {
		Sleep(14);
		update();
		render();
	}
	release();
}