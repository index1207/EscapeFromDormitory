#include "game.h"

int main() {
	initialization();

	while (TRUE) {
		update();
		render();
	}
	release();
}