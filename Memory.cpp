#include "Memory.h"

Cell::Cell(Trite T1, Trite T2, Trite T3) {
	Cell::T1 = T1;
	Cell::T2 = T2;
	Cell::T3 = T3;
}

Cell::Cell(int value) {
	T3 = Trite(value % 27);
	value /= 27;
	T2 = Trite(value % 27);
	value /= 27;
	T1 = Trite(value % 27);
}

Cell::Cell() {}

Cell Cell::operator++() {
	return Cell(convertToDecimal() + 1);
}

Cell Cell::operator--() {
	return Cell(convertToDecimal() - 1);
}

int Cell::convertToDecimal() {
	return T1.convertToDecimal() * Trite::T2 + T2.convertToDecimal() * Trite::T1 + T3.convertToDecimal();
}

Memory::Memory() {
	data.resize(Trite::T2, Cell());
}