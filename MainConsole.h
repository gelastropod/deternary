#ifndef TEST_CONSOLE_H
#define TEST_CONSOLE_H

#define NOMINMAX

#include <algorithm>
#include <cmath>
#include <format>
#include <fstream>
#include <string>
#include <windows.h>
#include "Console.h"
#include "Machine.h"
#include "Task.h"

class MainConsole : public Console {
private:
	bool options = false;

	double totalTime = 0.;
	double prevIter = 0.;
	static const std::vector<double> iterTimes;
	int iterIndex = 4;

	bool testing = true;
	bool lock = false;
	bool done = false;
	int mode = 0;
	int cachex, cachey;

	char prev = ' ';
	static const std::string cursor;

	std::vector<std::string> fileNames;

	Machine machine;

	Cell testNumber;
	int testProgress = 0;
	static const std::vector<Task> tasks;
	Test test;
	std::queue<int> outputs;

	int memoryBegin = 0;
	int fileBegin = 0;
	int pointerPosition = 0;
	int pointerType = 0;

	bool runHelper = false;
	Cell startAddress;

	Cell input, output;

	static const std::pair<int, int> positions[];

	void begin();
	void frame(double elapsedTime);

	void compute(double elapsedTime);
	void displayCell(Cell cell);
	void display(double elapsedTime);
};

#endif