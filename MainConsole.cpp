#include "MainConsole.h"

#define TESTPROGRAM 1

const std::pair<int, int> MainConsole::positions[] = {
	{3, 6},
	{3, 9},
	{12, 9},
	{21, 9},
	{39, 9},
	{41, 9},
	{43, 9}
};

void MainConsole::begin() {
	moveCursor(5, 2);
	print("Accumulator");

	moveCursor(0, 3, true);
	print("Instruction Pointer");

	moveCursor(0, 3, true);
	print("Instruction Register");

	moveCursor(0, 3, true);
	print("Address Register");

	moveCursor(0, 3, true);
	print("Data Register");

	moveCursor(0, 3, true);
	print("Stack Pointer");

	moveCursor(40, 5);
	print("Z   F");

	moveCursor(0, 3, true);
	print("Input");

	moveCursor(0, 3, true);
	print("Output");

	moveCursor(0, 3, true);
	print("Test");
}

void MainConsole::frame(double elapsedTime) {
	totalTime += elapsedTime;

	compute(elapsedTime);
	display(elapsedTime);
}

void MainConsole::compute(double elapsedTime) {
#if TESTPROGRAM
	if (key == 'a') {
		if (pointerType == 0) {
			if (pointerPosition != 0) {
				pointerPosition--;
			}
			if (pointerPosition < memoryBegin) memoryBegin--;
		}
	}
	if (key == 'd') {
		if (pointerType == 0) {
			if (pointerPosition != Trite::T2 - 1) {
				pointerPosition++;
			}
			if (pointerPosition > memoryBegin + H - 3) memoryBegin++;
		}
	}

	if (key2 == 75) {
		pointerType += 6;
		pointerType %= 7;
	}
	if (key2 == 77) {
		pointerType++;
		pointerType %= 7;
	}
#else
	if (key2 == 72) {
		print(std::string(1, prev));
		moveCursor(0, -1, true);
		prev = grid[y][x];
	}
	if (key2 == 75) {
		print(std::string(1, prev));
		moveCursor(-1, 0, true);
		prev = grid[y][x];
	}
	if (key2 == 77) {
		print(std::string(1, prev));
		moveCursor(1, 0, true);
		prev = grid[y][x];
	}
	if (key2 == 80) {
		print(std::string(1, prev));
		moveCursor(0, 1, true);
		prev = grid[y][x];
	}

	if (key2 == -1 && key != -1) {
		if (key != 8) {
			print(std::string(1, key));
			moveCursor(1, 0, true);
		}
		else {
			print(std::string(1, prev));
			moveCursor(-1, 0, true);
			print(" ");
		}
		prev = grid[y][x];
	}

	if (std::fmod(totalTime, 1.) <= .5) {
		print(cursor);
	}
	else {
		print(std::string(1, prev));
	}
#endif
}

void MainConsole::displayCell(Cell cell) {
	print(std::to_string(cell.T1.t1));
	moveCursor(2, 0, true);
	print(std::to_string(cell.T1.t2));
	moveCursor(2, 0, true);
	print(std::to_string(cell.T1.t3));
	moveCursor(5, 0, true);
	print(std::to_string(cell.T2.t1));
	moveCursor(2, 0, true);
	print(std::to_string(cell.T2.t2));
	moveCursor(2, 0, true);
	print(std::to_string(cell.T2.t3));
	moveCursor(5, 0, true);
	print(std::to_string(cell.T3.t1));
	moveCursor(2, 0, true);
	print(std::to_string(cell.T3.t2));
	moveCursor(2, 0, true);
	print(std::to_string(cell.T3.t3));
}

void MainConsole::display(double elapsedTime) {
#if TESTPROGRAM
	for (Cell i = Cell(memoryBegin); i - memoryBegin + 2 <= Cell(H) - 1; ++i) {
		moveCursor(W - 13, (i - memoryBegin + 2).convertToDecimal());
		print((i == pointerPosition ? ">" : " "));

		moveCursor(2, 0, true);
		print(Cell::convTrite(i.T2));
		moveCursor(2, 0, true);
		print(Cell::convTrite(i.T3));

		moveCursor(4, 0, true);
		print(Cell::convTrite(machine[i].T1));
		moveCursor(2, 0, true);
		print(Cell::convTrite(machine[i].T2));
		moveCursor(2, 0, true);
		print(Cell::convTrite(machine[i].T3));
	}

	moveCursor(5, 3);
	displayCell(machine.accumulator);

	moveCursor(5, 6);
	displayCell(machine.instructionPointer);

	moveCursor(5, 9);
	displayCell(machine.instructionRegister);

	moveCursor(5, 12);
	displayCell(machine.addressRegister);

	moveCursor(5, 15);
	displayCell(*machine.dataRegister);

	moveCursor(5, 18);
	displayCell(machine.stackPointer);

	moveCursor(40, 3);
	print(Cell::convTrite(machine.accumulator.T1));
	moveCursor(42, 3);
	print(Cell::convTrite(machine.accumulator.T2));
	moveCursor(44, 3);
	print(Cell::convTrite(machine.accumulator.T3));

	moveCursor(40, 6);
	print(std::to_string(machine.Z));
	moveCursor(44, 6);
	print(std::to_string(machine.F));

	Cell input = machine.getInput();
	moveCursor(40, 9);
	print(Cell::convTrite(input.T1));
	moveCursor(42, 9);
	print(Cell::convTrite(input.T2));
	moveCursor(44, 9);
	print(Cell::convTrite(input.T3));

	Cell output = machine.getOutput();
	moveCursor(40, 12);
	print(Cell::convTrite(output.T1));
	moveCursor(42, 12);
	print(Cell::convTrite(output.T2));
	moveCursor(44, 12);
	print(Cell::convTrite(output.T3));

	moveCursor(40, 15);
	print(Cell::convTrite(testNumber.T1));
	moveCursor(42, 15);
	print(Cell::convTrite(testNumber.T2));
	moveCursor(44, 15);
	print(Cell::convTrite(testNumber.T3));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			moveCursor(40 + j, 16 + i);
			print((i * 5 + j < testProgress ? "#" : "."));
		}
	}

	for (int i = 0; i < 7; i++) {
		moveCursor(positions[i].first, positions[i].second);
		print(" ");
	}

	moveCursor(positions[pointerType].first, positions[pointerType].second);
	print(">");
#endif
}