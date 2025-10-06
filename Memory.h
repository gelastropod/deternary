#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include "Trite.h"

class Cell {
	friend class Machine;

public:
	static const int MAX = Trite::T3;

	Trite T1, T2, T3;

	Cell(Trite T1, Trite T2, Trite T3);
	Cell(int value);
	Cell();

	Cell operator++();
	Cell operator--();

private:
	int convertToDecimal();
};

class Memory {
public:
	std::vector<Cell> data;

	Memory();
};

#endif