#include "MainConsole.h"
#include "Task.h"

bool Test::operator()(std::queue<int> toTest) {
	if (outputs.size() != toTest.size()) {
		return false;
	}

	std::queue<int> cOutputs = outputs;
	while (cOutputs.size()) {
		if (cOutputs.front() != toTest.front()) {
			return false;
		}

		cOutputs.pop();
		toTest.pop();
	}

	return true;
}

std::random_device rd;
std::mt19937 gen(rd());

int randomNumber(int a, int b) {
	std::uniform_int_distribution<int> dist(a, b - 1);

	return dist(gen);
}

const std::vector<Task> MainConsole::tasks = {
	[](int testNumber) {
		// Task 0: Cat
		Test test;
		int x = randomNumber(0, Trite::T3);
		test.inputs.push(x);
		test.outputs.push(x);
		return test;
	},
	[](int testNumber) {
		// Task 1: Addition
		Test test;
		int x = randomNumber(0, Trite::T3);
		int y = randomNumber(0, Trite::T3);
		test.inputs.push(x);
		test.inputs.push(y);
		test.outputs.push((x + y) % Trite::T3);
		return test;
	},
	[](int testNumber) {
		// Task 2: Maximum
		Test test;
		int x = randomNumber(0, Trite::T3);
		int y = randomNumber(0, Trite::T3);
		test.inputs.push(x);
		test.inputs.push(y);
		test.outputs.push(std::max(x, y));
		return test;
	},
	[](int testNumber) {
		// Task 3: Arithmetic
		Test test;
		int n = randomNumber(0, 4);
		int x = randomNumber(0, Trite::T3);
		int y = randomNumber(0, Trite::T3);
		test.inputs.push(n);
		test.inputs.push(x);
		test.inputs.push(y);
		if (n == 0) {
			test.outputs.push((x + y) % Trite::T3);
		}
		else if (n == 1) {
			test.outputs.push((x - y + Trite::T3) % Trite::T3);
		}
		else if (n == 2) {
			test.outputs.push((x* y) % Trite::T3);
		}
		else if (n == 3) {
			test.outputs.push(x / y);
		}
		return test;
	},
	[](int testNumber) {
		// Task 4: Choice
		Test test;
		int x = randomNumber(0, Trite::T3);
		int y = randomNumber(0, Trite::T3);
		int z = randomNumber(0, Trite::T3);
		test.inputs.push(x);
		test.inputs.push(y);
		test.inputs.push(z);
		test.outputs.push(z % 2 ? y : x);
		return test;
	}
};