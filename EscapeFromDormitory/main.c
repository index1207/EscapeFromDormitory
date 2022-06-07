#include "game.h"

int main() {
	initialization();

	while (TRUE) {
		Sleep(17);
		update();
		render();
	}
	release();
}