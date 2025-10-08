#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <vector>
#include "Trite.h"

class Cell {
public:
	static int Z, F;

	Trite T1, T2, T3;

	Cell(Trite T1, Trite T2, Trite T3);
	Cell(int value);
	Cell(std::string value);
	Cell();

	Cell operator++();
	Cell operator--();
	Cell operator+(Cell other);
	Cell operator-(Cell other);
	Cell operator*(Cell other);
	Cell operator/(Cell other);

	bool operator<(Cell other);
	bool operator>(Cell other);
	bool operator<=(Cell other);
	bool operator>=(Cell other);
	bool operator==(Cell other);
	bool operator!=(Cell other);

	bool isNull();

	Cell excFirstTrite();

	int convertToDecimal();

	static std::string convTrite(Trite trite);
	std::string toString();

private:
	static int umod(int a, int b);
};

class Memory {
	friend class Machine;

public:
	std::vector<Cell> data;

	Memory();

private:
	Cell& operator[](Cell location);
};

#endif