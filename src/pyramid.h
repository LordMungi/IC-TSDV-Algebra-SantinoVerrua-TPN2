#pragma once
#include <vector>

#include "line.h"

class Pyramid
{
private:

	std::vector<Line> lines;

public:

	Pyramid(int n);

	void draw();
};