#ifndef TEST_CONSOLE_H
#define TEST_CONSOLE_H

#include <cmath>
#include <string>
#include "Console.h"
#include "Machine.h"

class MainConsole : public Console {
private:
	double totalTime = 0.;

	char prev = ' ';
	static const std::string cursor;

	Machine machine;

	Cell testNumber;
	int testProgress = 0;

	int memoryBegin = 0;
	int pointerPosition = 0;
	int pointerType = 0;

	static const std::pair<int, int> positions[];

	void begin();
	void frame(double elapsedTime);

	void compute(double elapsedTime);
	void displayCell(Cell cell);
	void display(double elapsedTime);
};

#endif