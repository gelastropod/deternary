#include <fstream>
#include <iostream>
#include "Machine.h"

#define TESTING 1

#if TESTING
int main(int argc, char* argV[]) {
	const char* argv[] = { "", "program.den", "sample.in", "sample.out" };
#else
int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cerr << "Invalid format: deternary [program] [input] [output]" << std::endl;
		return -1;
	}
#endif

	std::ifstream programFile(argv[1]);
	std::ifstream inFile(argv[2]);
	std::ofstream outFile(argv[3]);

	if (!programFile.is_open()) {
		std::cerr << "Error opening " << argv[1] << std::endl;
		return -1;
	}
	if (!inFile.is_open()) {
		std::cerr << "Error opening " << argv[2] << std::endl;
		return -1;
	}

	Machine machine;

	int index = 0, data, startPosition;
	programFile >> startPosition;
	while (index < Trite::T2 && !programFile.eof()) {
		programFile >> data;
		machine.set(Cell(index), Cell(data));
		index++;
	}

	while (!inFile.eof()) {
		inFile >> data;
		machine.input(Cell(data));
	}

	machine.run(Cell(startPosition));

	while (!machine.outputs.empty()) {
		outFile << machine.output().convertToDecimal() << std::endl;
	}

	outFile.close();
}