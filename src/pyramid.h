#pragma once
#include <vector>

#include "step.h"

class Pyramid
{
private:

	std::vector<Step> steps;
	int originalSteps;
	Color color = BLUE;

	float perimeter;
	float area;
	float volume;

	void buildFirstStep(int n);
	void buildSteps(int n);
	void finishStep();
	void invert();
	void calculateStats();

public:

	Pyramid(int n);

	void draw();
	void drawStats();
};