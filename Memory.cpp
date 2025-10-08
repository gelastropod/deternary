#include "Memory.h"

int Cell::Z = 0;
int Cell::F = 0;

Cell::Cell(Trite T1, Trite T2, Trite T3) {
	Cell::T1 = T1;
	Cell::T2 = T2;
	Cell::T3 = T3;
}

Cell::Cell(int value) {
	value = umod(value, Trite::T3);

	T3 = Trite(value % Trite::T1);
	value /= Trite::T1;
	T2 = Trite(value % Trite::T1);
	value /= Trite::T1;
	T1 = Trite(value % Trite::T1);
}

int convertChar(char c) {
	if (c == '0') return 0;
	return c - '`';
}

Cell::Cell(std::string value) {
	T1 = convertChar(value[0]);
	T2 = convertChar(value[1]);
	T3 = convertChar(value[2]);
}

Cell::Cell() {}

Cell Cell::operator++() {
	Cell res = Cell(convertToDecimal() + 1);
	T1 = res.T1;
	T2 = res.T2;
	T3 = res.T3;
	return *this;
}

Cell Cell::operator--() {
	Cell res = Cell(convertToDecimal() - 1);
	T1 = res.T1;
	T2 = res.T2;
	T3 = res.T3;
	return *this;
}

Cell Cell::operator+(Cell other) {
	return Cell(convertToDecimal() + other.convertToDecimal());
}

Cell Cell::operator-(Cell other) {
	return Cell(convertToDecimal() - other.convertToDecimal());
}

Cell Cell::operator*(Cell other) {
	return Cell(convertToDecimal() * other.convertToDecimal());
}

Cell Cell::operator/(Cell other) {
	if (other.isNull()) return 0;
	return Cell(convertToDecimal() / other.convertToDecimal());
}

bool Cell::operator<(Cell other) {
	return convertToDecimal() < other.convertToDecimal();
}

bool Cell::operator>(Cell other) {
	return convertToDecimal() > other.convertToDecimal();
}

bool Cell::operator<=(Cell other) {
	return convertToDecimal() <= other.convertToDecimal();
}

bool Cell::operator>=(Cell other) {
	return convertToDecimal() >= other.convertToDecimal();
}

bool Cell::operator==(Cell other) {
	return convertToDecimal() == other.convertToDecimal();
}

bool Cell::operator!=(Cell other) {
	return !operator==(other);
}

bool Cell::isNull() {
	return convertToDecimal() == 0;
}

Cell Cell::excFirstTrite() {
	Cell cell = *this;
	cell.T1 = 0;
	return cell;
}

int Cell::convertToDecimal() {
	return T1.convertToDecimal() * Trite::T2 + T2.convertToDecimal() * Trite::T1 + T3.convertToDecimal();
}

std::string Cell::convTrite(Trite trite) {
	if (trite.convertToDecimal() == 0) return "0";
	return std::string(1, '`' + trite.convertToDecimal());
}

std::string Cell::toString() {
	return convTrite(T1) + convTrite(T2) + convTrite(T3);
}

int Cell::umod(int a, int b) {
	if (a >= b) F = 1;
	else if (a < 0) F = 2;
	else F = 0;
	if (a % b == 0) Z = 0;
	else Z = 1;

	return ((a % b) + b) % b;
}

Memory::Memory() {
	data.resize(Trite::T2, Cell());
}

Cell& Memory::operator[](Cell location) {
	return data[location.convertToDecimal()];
}