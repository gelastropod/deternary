#include "Console.h"

const double Console::frameTime = 1 / 60.;

Console::Console() {
	grid.resize(H, std::string(W, ' '));
}

void Console::start() {
	clearScreen();
	hideCursor();
	begin();

	double prev = getTimeSeconds();

	while (key != 27) {
		key = key2 = -1;
		if (_kbhit()) {
			key = _getch();
			if (key == 0 || key == 224) {
				key2 = _getch();
			}
		}

		double frameStart = getTimeSeconds();
		double elapsedTime = frameStart - prev;
		prev = frameStart;

		frame(elapsedTime);
		fps = 1. / elapsedTime;

		resetCursor();
		flush();
	}

	flush(); // this doesnt work idk why
	showCursor();
}

void Console::moveCursor(int x, int y, bool rel) {
	if (rel) {
		x += Console::x;
		y += Console::y;
	}

	if (x < 0 || x >= W || y < 0 || y >= H) return;

	Console::x = x;
	Console::y = y;
}

void Console::print(std::string value) {
	for (int i = 0; i < value.size() && x + i < W; i++) {
		grid[y][x + i] = value[i];
	}
}

void Console::clearScreen() {
	std::cout << "\033[2J\033[H";
}

void Console::resetCursor() {
	std::cout << "\033[H";
}

void Console::hideCursor() {
	std::cout << "\033[?25l";
}

void Console::showCursor() {
	std::cout << "\033[?25h";
}

void Console::flush() {
	for (int i = 0; i < H; i++) {
		std::cout << grid[i];
		if (i != H - 1) {
			std::cout << "\n";
		}
	}
}

double Console::getTimeSeconds() {
	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}