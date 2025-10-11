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

	if (machine.running && (totalTime - prevIter > iterTime)) {
		if (machine.instructionRegister.T1 == 2) {
			machine.advance();
			output = machine.output();
		}
		else if (machine.instructionRegister.T1 == 1 && !testing && !done) {
			machine.running = false;
			lock = true;
		}
		else {
			machine.advance();
		}

		done = false;
		prevIter = totalTime;
	}

	compute(elapsedTime);
	display(elapsedTime);
}

void MainConsole::compute(double elapsedTime) {
#if TESTPROGRAM
	if (!options) {
		if (key == 'a') {
			if (!machine.running && !lock) {
				if (pointerType == 0) {
					if (machine.instructionPointer != 0) {
						--machine.instructionPointer;
					}
					machine.instructionRegister = machine[machine.instructionPointer];
				}

				if (pointerType == 1) {
					machine.instructionRegister.T1 = machine.instructionRegister.T1 + Trite(Trite::T1 - 1);
					machine[machine.instructionPointer].T1 = machine[machine.instructionPointer].T1 + Trite(Trite::T1 - 1);
				}
				if (pointerType == 2) {
					machine.instructionRegister.T2 = machine.instructionRegister.T2 + Trite(Trite::T1 - 1);
					machine[machine.instructionPointer].T2 = machine[machine.instructionPointer].T2 + Trite(Trite::T1 - 1);
				}
				if (pointerType == 3) {
					machine.instructionRegister.T3 = machine.instructionRegister.T3 + Trite(Trite::T1 - 1);
					machine[machine.instructionPointer].T3 = machine[machine.instructionPointer].T3 + Trite(Trite::T1 - 1);
				}
			}
			if (lock) {
				if (pointerType == 4) {
					input.T1 = input.T1 + Trite(Trite::T1 - 1);
				}
				if (pointerType == 5) {
					input.T2 = input.T2 + Trite(Trite::T1 - 1);
				}
				if (pointerType == 6) {
					input.T3 = input.T3 + Trite(Trite::T1 - 1);
				}
			}
		}

		if (key == 'd') {
			if (!machine.running && !lock) {
				if (pointerType == 0) {
					if (machine.instructionPointer != Trite::T2 - 1) {
						++machine.instructionPointer;
					}
					machine.instructionRegister = machine[machine.instructionPointer];
				}

				if (pointerType == 1) {
					machine.instructionRegister.T1 = machine.instructionRegister.T1 + 1;
					machine[machine.instructionPointer].T1 = machine[machine.instructionPointer].T1 + 1;
				}
				if (pointerType == 2) {
					machine.instructionRegister.T2 = machine.instructionRegister.T2 + 1;
					machine[machine.instructionPointer].T2 = machine[machine.instructionPointer].T2 + 1;
				}
				if (pointerType == 3) {
					machine.instructionRegister.T3 = machine.instructionRegister.T3 + 1;
					machine[machine.instructionPointer].T3 = machine[machine.instructionPointer].T3 + 1;
				}
			}
			if (lock) {
				if (pointerType == 4) {
					input.T1 = input.T1 + 1;
				}
				if (pointerType == 5) {
					input.T2 = input.T2 + 1;
				}
				if (pointerType == 6) {
					input.T3 = input.T3 + 1;
				}
			}
		}

		if (machine.instructionPointer < memoryBegin) memoryBegin--;
		if (machine.instructionPointer > memoryBegin + H - 3) memoryBegin++;

		if (key2 == 75 && !machine.running) {
			pointerType += 6;
			pointerType %= 7;
		}
		if (key2 == 77 && !machine.running) {
			pointerType++;
			pointerType %= 7;
		}

		if (key2 == 72 && pointerType == 0) {
			if (!machine.running) {
				if (lock) {
					machine.input(input);
					lock = false;
					done = true;
				}

				machine.running = true;
				prevIter = totalTime - iterTime;
			}
			else {
				machine.running = false;
				lock = false;
			}
		}

		if (key == 'w') {
			if (machine.running && !lock) {
				iterTime = 0.5 / iterTime;
			}
			else {
				testing = !testing;
			}
		}
	}
	else {
		if ((key2 == 75 || key2 == 77) && !mode) {
			pointerType = 1 - pointerType;
		}

		if (key2 == 72) {
			if (mode == 0) {
				if (pointerType == 0) {
					mode = 1;

					moveCursor(15, 4);
					print("Enter name:");
					moveCursor(27, 4);

					cachex = x, cachey = y;
				}
				else {
					mode = 2;

					WIN32_FIND_DATA fd;
					HANDLE hFind = FindFirstFile("saved/*.den", &fd);
				}
			}
			else if (mode == 1 && cachex != 27) {
				std::string name = grid[4].substr(27, cachex - 27);

				moveCursor(15, 4);
				print(std::string(W - 15, ' '));

				mode = 0;

				std::ofstream savedFile("saved/" + name + ".den");

				savedFile << "A";
			}
			else if (mode == 2) {
				
			}
		}

		if (mode == 1) {
			moveCursor(cachex, cachey);

			if (key2 == -1 && key != -1) {
				if (key != 8 && cachex < W - 5) {
					print(std::string(1, key));
					moveCursor(1, 0, true);
				}
				else if (key == 8 && cachex > 27) {
					print(std::string(1, prev));
					moveCursor(-1, 0, true);
					print(" ");
				}
				else {
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

			cachex = x, cachey = y;
		}
	}

	if (key == 'o' && !machine.running && !lock) {
		options = !options;

		if (!options) {
			clear();
			begin();

			pointerType = 0;
		}
		else {
			clear();
			moveCursor(5, 2);
			print("Options");

			moveCursor(5, 4);
			print("Save");

			moveCursor(5, 6);
			print("Load");

			pointerType = 0;
		}
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
	if (!options) {
		for (Cell i = Cell(memoryBegin); i - memoryBegin + 2 <= Cell(H) - 1; ++i) {
			moveCursor(W - 13, (i - memoryBegin + 2).convertToDecimal());
			print((i == machine.instructionPointer ? ">" : " "));

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

		moveCursor(40, 9);
		print(Cell::convTrite(input.T1));
		moveCursor(42, 9);
		print(Cell::convTrite(input.T2));
		moveCursor(44, 9);
		print(Cell::convTrite(input.T3));

		moveCursor(40, 12);
		print(Cell::convTrite(output.T1));
		moveCursor(42, 12);
		print(Cell::convTrite(output.T2));
		moveCursor(44, 12);
		print(Cell::convTrite(output.T3));

		if (testing) {
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
		}
		else {
			for (int i = 0; i < 6; i++) {
				moveCursor(40, 15 + i);
				print("     ");
			}
		}

		for (int i = 0; i < 7; i++) {
			moveCursor(positions[i].first, positions[i].second);
			print(" ");
		}

		moveCursor(positions[pointerType].first, positions[pointerType].second);
		print(">");
	}
	else {
		if (pointerType == 0) {
			moveCursor(3, 4);
			print(">");
			moveCursor(3, 6);
			print(" ");
		}
		else {
			moveCursor(3, 4);
			print(" ");
			moveCursor(3, 6);
			print(">");
		}
	}
#endif
}