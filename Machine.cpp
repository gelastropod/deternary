#include "Machine.h"

Machine::Machine() {}

void Machine::input(Cell in) {
	inputs.push(in);
}

Cell Machine::output() {
	Cell out = outputs.front();
	outputs.pop();
	return out;
}

void Machine::advance() {

}