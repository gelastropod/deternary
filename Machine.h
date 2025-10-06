#ifndef MACHINE_H
#define MACHINE_H

#include <queue>
#include <stack>
#include "Memory.h"

class Machine {
public:
	Cell accumulator, instructionPointer, instructionRegister, addressRegister, dataRegister, stackPointer;
	Cell input, output;

	Machine();

	void input(Cell in);
	Cell output();

private:
	std::stack<Cell> stack;
	std::queue<Cell> inputs, outputs;

	Memory memory;

	void advance();

	void 
};

#endif