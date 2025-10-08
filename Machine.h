#ifndef MACHINE_H
#define MACHINE_H

#include <queue>
#include <stack>
#include "Memory.h"

class Machine {
public:
	Cell accumulator, instructionPointer, instructionRegister, addressRegister, stackPointer;
	Cell* dataRegister;
	std::queue<Cell> inputs, outputs;
	int Z = 0, F = 0;
	bool running = false;

	Machine();

	void input(Cell in);
	Cell output();

	Cell getInput();
	Cell getOutput();

	void run(Cell startPosition);

	void set(Cell position, Cell data);

	Cell& operator[](Cell position);

private:
	std::stack<Cell> stack;

	Memory memory;

	void advance();

	void inst0();
	void inst1();
	void inst2();
	void inst3();
	void inst4();
	void inst5();
	void inst6();
	void inst7();
	void inst8();
	void inst9();
	void inst10();
	void inst11();
	void inst12();
	void inst13();
	void inst14();
	void inst15();
	void inst16();
	void inst17();
	void inst18();
	void inst19();
	void inst20();
	void inst21();
	void inst22();
	void inst23();
	void inst24();
	void inst25();
	void inst26();

	static void (Machine::*const instructions[Trite::T1])(void);
};

#endif