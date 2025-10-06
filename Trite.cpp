#include "Trite.h"

Trite::Trite(int value) {
	t3 = value % 3;
	value /= 3;
	t2 = value % 3;
	value /= 3;
	t1 = value % 3;
}

Trite::Trite() {
	t1 = t2 = t3 = 0;
}

Trite Trite::operator=(Trite other) {
	t1 = other.t1;
	t2 = other.t2;
	t3 = other.t3;
	return other;
}

int Trite::convertToDecimal() {
	return t1 * 9 + t2 * 3 + t3;
}