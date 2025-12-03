#pragma once
#include <vector>

#include "step.h"

class Pyramid
{
private:

	std::vector<Step> steps;
	int originalSteps;
	Color color = BLUE;

	void buildFirstStep(int n);
	void buildSteps(int n);
	void finishStep();
	void invert();

public:

	Pyramid(int n);

	void draw();
};