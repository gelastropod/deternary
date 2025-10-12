#ifndef CONSOLE_H
#define CONSOLE_H

#include <chrono>
#include <conio.h>
#include <iostream>
#include <queue>
#include <thread>

class Console {
public:
	static const double frameTime;
	double fps = 0.;

	Console();
	virtual ~Console() = default;

	void start();

protected:
	int W = 69, H = 19;
	int key = -1, key2 = -1;
	int x = 0, y = 0;

	bool shouldEnd = false;

	std::vector<std::string> grid;

	void moveCursor(int x, int y, bool rel = false);
	void print(std::string value);

	void clear();

private:
	void clearScreen();
	void resetCursor();
	void hideCursor();
	void showCursor();
	
	void flush();

	virtual void begin() = 0;
	virtual void frame(double elapsedTime) = 0;

	double getTimeSeconds();
};

#endif