#ifndef TASK_H
#define TASK_H

#include <functional>
#include <queue>
#include <random>

struct Test {
	std::queue<int> inputs, outputs;
};

using Task = std::function<Test(int)>;

int randomNumber(int a, int b);

#endif