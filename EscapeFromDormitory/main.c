#include "game.h"

int main(int argc, char* argv[]) {
	initialization();

	while (TRUE) {
		Sleep(13);
		update(argc, argv);
		render();
	}
	release();
}