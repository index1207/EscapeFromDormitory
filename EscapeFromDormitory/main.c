#include "game.h"

int main() {
	initialization();

	while (TRUE) {
		Sleep(33);
		update();
		render();
	}
	release();
}