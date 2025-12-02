#pragma once
#include <vector>

#include "step.h"

class Pyramid
{
private:

	std::vector<Step> steps;

	void buildFirstStep(int max);
	void finishStep(int stepIndex);

public:

	Pyramid(int n);

	void draw();
};