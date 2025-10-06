#ifndef TRITE_H
#define TRITE_H

int umod(int a, int b);

class Trite {
	friend class Cell;
	friend class Machine;

public:
	static const int T1 = 27, T2 = 27 * 27, T3 = 27 * 27 * 27;

	int t1, t2, t3;

	Trite(int value);
	Trite();

	Trite operator=(Trite other);

private:
	int umod(int a, int b);

	int convertToDecimal();
};

#endif