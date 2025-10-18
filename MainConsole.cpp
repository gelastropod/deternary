#include "MainConsole.h"

const std::string MainConsole::cursor = "_";

const std::vector<double> MainConsole::iterTimes = {
	0.05,
	0.1,
	0.2,
	0.5,
	1.0,
	2.0
};

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

	if (machine.running && (totalTime - prevIter > iterTimes[iterIndex])) {
		if (machine.instructionRegister.T1 == 2) {
			machine.advance();
			output = machine.output();
			outputs.push(output.convertToDecimal());
		}
		else if (machine.instructionRegister.T1 == 1) {
			if (!testing && !done) {
				machine.running = false;
				lock = true;
			}
			else if (testing) {
				input = test.inputs.front();
				test.inputs.pop();

				machine.input(input);
				machine.advance();
			}
		}
		else {
			machine.advance();
		}

		if (machine.instructionRegister.T1 == Trite::T1 - 1 && testing) {
			if (test(outputs)) {
				testProgress++;

				if (testProgress == 16) {
					testProgress = 0;
					++testNumber;
				}

				if (testNumber == tasks.size()) {
					shouldEnd = true;
				}
				else if (runHelper && testProgress != 0) {
					machine.instructionPointer = startAddress;
					machine.instructionRegister = machine[startAddress];

					while (outputs.size()) {
						outputs.pop();
					}

					test = tasks[testNumber.convertToDecimal()](testProgress);
				}
				else {
					machine.running = false;
				}
			}
			else {
				testProgress = 0;
			}
		}

		done = false;
		prevIter = totalTime;
	}

	compute(elapsedTime);
	display(elapsedTime);
}

void MainConsole::compute(double elapsedTime) {
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

				while (outputs.size()) {
					outputs.pop();
				}

				machine.running = true;
				prevIter = totalTime - iterTimes[iterIndex];
			}
			else {
				if (testing) {
					testProgress = 0;
				}

				machine.running = false;
				lock = false;
			}

			if (testing) {
				test = tasks[testNumber.convertToDecimal()](testProgress);
			}
		}

		if (key == 'w' && !machine.running) {
			testing = !testing;
		}
	}
	else {
		if (key2 == 75) {
			if (mode == 0) {
				pointerType += 4;
				pointerType %= 5;
			}
			else if (mode == 2) {
				pointerPosition += fileNames.size() - 1;
				pointerPosition %= fileNames.size();

				if (pointerPosition < fileBegin) fileBegin--;
			}
			else if (mode == 3) {
				iterIndex += iterTimes.size() - 1;
				iterIndex %= iterTimes.size();
			}
			else if (mode == 4) {
				runHelper = !runHelper;
			}
			else if (mode == 5) {
				pointerPosition += 2;
				pointerPosition %= 3;
			}
		}
		if (key2 == 77) {
			if (mode == 0) {
				pointerType++;
				pointerType %= 5;
			}
			else if (mode == 2) {
				pointerPosition++;
				pointerPosition %= fileNames.size();

				if (pointerPosition >= fileBegin + 6) fileBegin++;
			}
			else if (mode == 3) {
				iterIndex++;
				iterIndex %= iterTimes.size();
			}
			else if (mode == 4) {
				runHelper = !runHelper;
			}
			else if (mode == 5) {
				pointerPosition++;
				pointerPosition %= 3;
			}
		}

		if (key2 == 72) {
			if (mode == 0) {
				if (pointerType == 0) {
					mode = 1;

					moveCursor(18, 4);
					print("Enter name:");
					moveCursor(30, 4);

					cachex = x, cachey = y;
				}
				else if (pointerType == 1) {
					mode = 2;

					fileNames.clear();
					fileNames.push_back("Cancel");

					WIN32_FIND_DATA fd;
					HANDLE hFind = FindFirstFile("saved/*.den", &fd);

					if (hFind == INVALID_HANDLE_VALUE) {
						mode = 0;
						return;
					}

					do {
						if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0) {
							continue;
						}

						std::string fileName = std::string(fd.cFileName);
						fileName = fileName.substr(0, fileName.size() - 4);
						fileNames.push_back(fileName);
					} while (FindNextFile(hFind, &fd));
				}
				else if (pointerType == 2) {
					mode = 3;
				}
				else if (pointerType == 3) {
					mode = 4;
				}
				else if (pointerType == 4) {
					mode = 5;
				}
			}
			else if (mode == 1) {
				if (cachex != 30) {
					std::string name = grid[4].substr(30, cachex - 30);

					std::ofstream savedFile("saved/" + name + ".den");

					savedFile << testNumber.toString() << ' ' << testProgress << ' ' << testing << '\n';
					savedFile << machine.accumulator.toString() << ' ' << machine.instructionPointer.toString() << ' '
						<< machine.instructionRegister.toString() << ' ' << machine.addressRegister.toString() << ' '
						<< machine.stackPointer.toString() << '\n';
					savedFile << input.toString() << ' ' << output.toString() << '\n';
					savedFile << iterIndex << ' ' << runHelper << ' ' << startAddress.toString() << '\n';

					for (Cell i = 0; i <= Trite::T2 - 1; ++i) {
						savedFile << machine[i].toString() << '\n';
					}
				}

				moveCursor(15, 4);
				print(std::string(W - 15, ' '));

				mode = 0;
			}
			else if (mode == 2) {
				mode = 0;

				if (pointerPosition == 0) return;

				std::ifstream savedFile("saved/" + fileNames[pointerPosition] + ".den");

				savedFile >> testNumber >> testProgress >> testing;
				savedFile >> machine.accumulator >> machine.instructionPointer
					>> machine.instructionRegister >> machine.addressRegister
					>> machine.stackPointer;
				savedFile >> input >> output;
				savedFile >> iterIndex >> runHelper >> startAddress;

				for (Cell i = 0; i <= Trite::T2 - 1; ++i) {
					savedFile >> machine[i];
				}

				options = false;
				pointerType = 0;

				clear();
				begin();
			}
			else if (mode >= 3) {
				mode = 0;
			}
		}

		if (mode == 1) {
			moveCursor(cachex, cachey);

			if (key2 == -1 && key != -1) {
				if (key != 8 && cachex < W - 5) {
					print(std::string(1, key));
					moveCursor(1, 0, true);
				}
				else if (key == 8 && cachex > 30) {
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

		if (mode == 5) {
			if (key == 'a') {
				if (pointerPosition == 0) {
					startAddress.T1 = startAddress.T1 + Trite(Trite::T1 - 1);
				}
				else if (pointerPosition == 1) {
					startAddress.T2 = startAddress.T2 + Trite(Trite::T1 - 1);
				}
				else if (pointerPosition == 2) {
					startAddress.T3 = startAddress.T3 + Trite(Trite::T1 - 1);
				}
			}

			if (key == 'd') {
				if (pointerPosition == 0) {
					startAddress.T1 = startAddress.T1 + 1;
				}
				else if (pointerPosition == 1) {
					startAddress.T2 = startAddress.T2 + 1;
				}
				else if (pointerPosition == 2) {
					startAddress.T3 = startAddress.T3 + 1;
				}
			}
		}
	}

	if (key == 'o' && !machine.running && !lock && mode == 0) {
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

			moveCursor(5, 8);
			print("Process Speed");

			moveCursor(5, 10);
			print("Run Helper");

			moveCursor(5, 12);
			print("Start Address");

			pointerType = 0;
		}
	}
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
	if (shouldEnd) {
		clear();

		moveCursor(3, 2);
		print("gg");

		return;
	}

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
			for (int i = 0; i < 4; i++) {
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
		moveCursor(3, 4);
		for (int i = 0; i < 5; i++) {
			print((i == pointerType ? ">" : " "));
			moveCursor(0, 2, true);
		}
		
		if (mode == 2) {
			moveCursor(28, 6);

			for (int i = fileBegin; i < std::min(fileBegin + 6, (int)fileNames.size()); i++) {
				print(i == pointerPosition ? ">" : " ");

				moveCursor(2, 0, true);
				std::string currentFileName = fileNames[i];
				currentFileName += std::string(W - 30 - currentFileName.size(), ' ');
				print(currentFileName);

				moveCursor(-2, 2, true);
			}
		}
		else {
			moveCursor(25, 6);

			for (int i = 0; i < 6; i++) {
				print(std::string(W - 28, ' '));
				moveCursor(0, 2, true);
			}
		}

		if (mode == 3) {
			moveCursor(28, 8);
			print("<");
			moveCursor(34, 8);
			print("s >");

			moveCursor(30, 8);
			print(std::format("{:.2f}", iterTimes[iterIndex]));
		}

		if (mode == 4) {
			moveCursor(28, 10);
			print("<");
			moveCursor(36, 10);
			print(">");

			moveCursor(31, 10);
			print(runHelper ? "ON" : "OFF");
		}

		if (mode == 5) {
			moveCursor(30, 12);
			print(Cell::convTrite(startAddress.T1));
			moveCursor(32, 12);
			print(Cell::convTrite(startAddress.T2));
			moveCursor(34, 12);
			print(Cell::convTrite(startAddress.T3));

			moveCursor(30, 13);
			for (int i = 0; i < 3; i++) {
				print(i == pointerPosition ? "^" : " ");
				moveCursor(2, 0, true);
			}
		}
		else {
			moveCursor(30, 13);
			print(std::string(5, ' '));
		}
	}
}