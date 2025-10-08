#include "Machine.h"

Machine::Machine() {
	dataRegister = &memory[0];
}

void Machine::input(Cell in) {
	inputs.push(in);
}

Cell Machine::output() {
	if (outputs.empty()) return 0;

	Cell out = outputs.front();
	outputs.pop();
	return out;
}

Cell Machine::getInput() {
	if (inputs.empty()) return 0;
	return inputs.front();
}

Cell Machine::getOutput() {
	if (outputs.empty()) return 0;
	return outputs.front();
}

void Machine::run(Cell startPosition) {
	instructionPointer = startPosition;
	instructionRegister = memory[instructionPointer];
	running = true;

	while (running) advance();
}

void Machine::set(Cell position, Cell data) {
	memory[position] = data;
}

Cell Machine::operator[](Cell position) {
	return memory[position];
}

void Machine::advance() {
	Trite instruction = instructionRegister.T1;
	Cell location = instructionRegister.excFirstTrite();

	addressRegister = location;
	dataRegister = &memory[location];

	(this->*instructions[instruction.convertToDecimal()])();

	++instructionPointer;
	instructionRegister = memory[instructionPointer];
}

void Machine::inst0() {}
void Machine::inst1() {
	if (inputs.empty()) {
		accumulator = 0;
		return;
	}

	accumulator = inputs.front();
	inputs.pop();
}
void Machine::inst2() {
	outputs.push(accumulator);
}
void Machine::inst3() {
	accumulator = *dataRegister;
}
void Machine::inst4() {
	*dataRegister = accumulator;
}
void Machine::inst5() {
	accumulator = accumulator + addressRegister;
	Z = Cell::Z, F = Cell::F;
}
void Machine::inst6() {
	accumulator = accumulator - addressRegister;
	Z = Cell::Z, F = Cell::F;
}
void Machine::inst7() {
	accumulator = accumulator * addressRegister;
	Z = Cell::Z, F = Cell::F;
}
void Machine::inst8() {
	accumulator = accumulator / addressRegister;
	Z = Cell::Z, F = Cell::F;
}
void Machine::inst9() {
	accumulator = memory[dataRegister->excFirstTrite()];
}
void Machine::inst10() {
	memory[dataRegister->excFirstTrite()] = accumulator;
}
void Machine::inst11() {
	accumulator = accumulator + *dataRegister;
	Z = Cell::Z, F = Cell::F;
}
void Machine::inst12() {
	accumulator = accumulator - *dataRegister;
	Z = Cell::Z, F = Cell::F;
}
void Machine::inst13() {
	accumulator = accumulator * *dataRegister;
	Z = Cell::Z, F = Cell::F;
}
void Machine::inst14() {
	accumulator = accumulator / *dataRegister;
	Z = Cell::Z, F = Cell::F;
}
void Machine::inst15() {
	instructionPointer = addressRegister - 1;
}
void Machine::inst16() {
	if (Z == 0) instructionPointer = addressRegister - 1;
}
void Machine::inst17() {
	if (Z == 1) instructionPointer = addressRegister - 1;
}
void Machine::inst18() {
	if (F == 1) instructionPointer = addressRegister - 1;
}
void Machine::inst19() {
	if (F == 2) instructionPointer = addressRegister - 1;
}
void Machine::inst20() {
	accumulator - *dataRegister;
	Z = Cell::Z, F = Cell::F;
}
void Machine::inst21() {
	stack.push(accumulator);
	++stackPointer;
}
void Machine::inst22() {
	accumulator = stack.top();
	stack.pop();
	--stackPointer;
}
void Machine::inst23() {
	stack.push(instructionPointer);
	instructionPointer = addressRegister - 1;
	++stackPointer;
}
void Machine::inst24() {
	instructionPointer = stack.top();
	stack.pop();
	--stackPointer;
}
void Machine::inst25() {
	std::swap(stack.top(), accumulator);
}
void Machine::inst26() {
	running = false;
}

void (Machine::* const Machine::instructions[27])(void) = {
	&Machine::inst0,
	&Machine::inst1,
	&Machine::inst2,
	&Machine::inst3,
	&Machine::inst4,
	&Machine::inst5,
	&Machine::inst6,
	&Machine::inst7,
	&Machine::inst8,
	&Machine::inst9,
	&Machine::inst10,
	&Machine::inst11,
	&Machine::inst12,
	&Machine::inst13,
	&Machine::inst14,
	&Machine::inst15,
	&Machine::inst16,
	&Machine::inst17,
	&Machine::inst18,
	&Machine::inst19,
	&Machine::inst20,
	&Machine::inst21,
	&Machine::inst22,
	&Machine::inst23,
	&Machine::inst24,
	&Machine::inst25,
	&Machine::inst26
};