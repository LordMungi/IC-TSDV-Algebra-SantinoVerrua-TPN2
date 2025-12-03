#pragma once
#include <vector>

#include "step.h"

class Pyramid
{
private:

	std::vector<Step> steps;

	void buildFirstStep(int n);
	void buildStep(int n);
	void finishStep();

public:

	Pyramid(int n);

	void draw();
};