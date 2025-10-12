#include "MainConsole.h"
#include "Task.h"

std::random_device rd;
std::mt19937 gen(rd());

int randomNumber(int a, int b) {
	std::uniform_int_distribution<int> dist(a, b - 1);

	return dist(gen);
}

const std::vector<Task> MainConsole::tasks = {
	[](int testNumber) {
		Test test;
		int x = randomNumber(0, Trite::T3);
		test.inputs.push(x);
		test.outputs.push(x);
		return test;
	}
};