#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include "Trite.h"

class Cell {
	friend class Machine;
	friend class Memory;

public:
	static int Z, F;

	Trite T1, T2, T3;

	Cell(Trite T1, Trite T2, Trite T3);
	Cell(int value);
	Cell();

	Cell operator++();
	Cell operator--();
	Cell operator+(Cell other);
	Cell operator-(Cell other);
	Cell operator*(Cell other);
	Cell operator/(Cell other);

	bool isNull();

	Cell excFirstTrite();

private:
	static int umod(int a, int b);

	int convertToDecimal();
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