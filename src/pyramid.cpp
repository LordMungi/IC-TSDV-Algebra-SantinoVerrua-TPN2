#include "pyramid.h"

#include <iostream>
#include <ctime>
#include <string>

#include <raymath.h>

Pyramid::Pyramid(int n)
{
	srand(static_cast<unsigned int>(time(0)));

	buildFirstStep(n);
	buildSteps(n);
	originalSteps = steps.size();

	for (int i = 0; i < n; i++)
		invert();

	calculateStats();
}

void Pyramid::buildFirstStep(int n)
{
	const int max = 30;

	Vector3 up = { 0, 1, 0 };

	Line l1;
	l1.end.x = (rand() % (max * 1000) / 1000.0f) - max / 2;
	l1.end.y = (rand() % (max * 1000) / 1000.0f) - max / 2;
	l1.end.z = (rand() % (max * 1000) / 1000.0f) - max / 2;
	l1.color = RED;

	Line l2;
	l2.end = Vector3Scale(Vector3Normalize(Vector3CrossProduct(l1.end, up)), Vector3Length(l1.end));
	l2.color = BLUE;

	Line l3;
	l3.end = Vector3Scale(Vector3Normalize(Vector3CrossProduct(l1.end, l2.end)), Vector3Length(l1.end) / n);
	if (Vector3DotProduct(l3.end, up) < 0)
		l3.end = Vector3Negate(l3.end);
	l3.color = GREEN;

	Step s;
	s.lines[0] = l1;
	s.lines[1] = l2;
	s.lines[2] = l3;
	steps.push_back(s);

	finishStep();
}

void Pyramid::buildSteps(int n)
{
	float x = static_cast<float>(n);

	Step s = steps.back();

	Line l1;
	l1.start = Vector3Subtract(s.lines[0].end, s.lines[0].start);
	l1.start = Vector3Scale(Vector3Normalize(l1.start), x / 2);
	l1.start = Vector3Add(l1.start, Vector3Scale(Vector3Normalize(Vector3Subtract(s.lines[1].end, s.lines[1].start)), x / 2));
	l1.start = Vector3Add(l1.start, s.lines[0].start);
	l1.start = Vector3Add(l1.start, Vector3Subtract(s.lines[2].end, s.lines[2].start));

	l1.end = Vector3Subtract(s.lines[0].end, s.lines[0].start);
	l1.end = Vector3Scale(Vector3Normalize(l1.end), Vector3Length(l1.end) - x);
	l1.end = Vector3Add(l1.start, l1.end);

	Line l2;
	l2.start = l1.start;
	l2.end = Vector3Subtract(s.lines[1].end, s.lines[1].start);
	l2.end = Vector3Scale(Vector3Normalize(l2.end), Vector3Length(l2.end) - x);
	l2.end = Vector3Add(l2.start, l2.end);

	Line l3;
	l3.start = l1.start;
	l3.end = Vector3Add(l3.start, Vector3Subtract(s.lines[2].end, s.lines[2].start));

	s.lines[0] = l1;
	s.lines[1] = l2;
	s.lines[2] = l3;
	steps.push_back(s);

	finishStep();

	if (Vector3Length(Vector3Subtract(s.lines[0].end, s.lines[0].start)) > n)
		buildSteps(n);
}

void Pyramid::finishStep()
{
	Line l1 = steps.back().lines[0];
	Line l3 = steps.back().lines[2];
	Line l2 = steps.back().lines[1];

	Line l4;
	l4.start = l1.end;
	l4.end = Vector3Add(Vector3Subtract(l2.end, l2.start), l4.start);

	Line l5;
	l5.start = l2.end;
	l5.end = Vector3Add(Vector3Subtract(l1.end, l1.start), l5.start);

	Line l6;
	l6.start = l2.end;
	l6.end = Vector3Add(Vector3Subtract(l3.end, l3.start), l6.start);

	Line l7;
	l7.start = l4.end;
	l7.end = Vector3Add(Vector3Subtract(l3.end, l3.start), l7.start);

	Line l8;
	l8.start = l1.end;
	l8.end = Vector3Add(Vector3Subtract(l3.end, l3.start), l8.start);

	Line l9;
	l9.start = l3.end;
	l9.end = Vector3Add(Vector3Subtract(l2.end, l2.start), l9.start);

	Line l10;
	l10.start = l3.end;
	l10.end = Vector3Add(Vector3Subtract(l1.end, l1.start), l10.start);

	Line l11;
	l11.start = l6.end;
	l11.end = Vector3Add(Vector3Subtract(l1.end, l1.start), l11.start);

	Line l12;
	l12.start = l8.end;
	l12.end = Vector3Add(Vector3Subtract(l2.end, l2.start), l12.start);

	steps.back().lines[3] = l4;
	steps.back().lines[4] = l5;
	steps.back().lines[5] = l6;
	steps.back().lines[6] = l7;
	steps.back().lines[7] = l8;
	steps.back().lines[8] = l9;
	steps.back().lines[9] = l10;
	steps.back().lines[10] = l11;
	steps.back().lines[11] = l12;
}

void Pyramid::invert()
{
	int lastStep = steps.size();
	for (int i = 1; i < originalSteps; i++)
	{
		Step s = steps.at(lastStep - i - 1);

		for (int j = 0; j < i*2; j++)
		{
			s.lines[0].start = Vector3Add(s.lines[0].start, steps.at(0).lines[2].end);
			s.lines[0].end = Vector3Add(s.lines[0].end, steps.at(0).lines[2].end);
			s.lines[1].start = Vector3Add(s.lines[1].start, steps.at(0).lines[2].end);
			s.lines[1].end = Vector3Add(s.lines[1].end, steps.at(0).lines[2].end);
			s.lines[2].start = Vector3Add(s.lines[2].start, steps.at(0).lines[2].end);
			s.lines[2].end = Vector3Add(s.lines[2].end, steps.at(0).lines[2].end);
		}
		steps.push_back(s);
		finishStep();

		for (int j = 0; j < 12; j++)
		{
			steps.back().lines[j].color = color;
		}
	}
	if (color.b == BLUE.b)
		color = MAGENTA;
	else
		color = BLUE;
}

void Pyramid::calculateStats()
{
	for (int i = 0; i < steps.size(); i++)
	{
		Vector3 v1 = Vector3Subtract(steps.at(i).lines[0].end, steps.at(i).lines[0].start);
		Vector3 v2 = Vector3Subtract(steps.at(i).lines[1].end, steps.at(i).lines[1].start);
		Vector3 v3 = Vector3Subtract(steps.at(i).lines[2].end, steps.at(i).lines[2].start);

		perimeter += (Vector3Length(v1) * 2 + Vector3Length(v2) * 2) * 2;
		perimeter += (Vector3Length(v1) * 2 + Vector3Length(v3) * 2) * 4;

		area += (Vector3Length(v1) * Vector3Length(v2)) * 2;
		area += (Vector3Length(v1) * Vector3Length(v3)) * 4;

		volume += Vector3Length(v1) * Vector3Length(v2) * Vector3Length(v3);
	}
}

void Pyramid::draw()
{
	for (int i = 0; i < steps.size(); i++)
	{
		for (int j = 0; j < 12; j++)
		{
			DrawLine3D(steps.at(i).lines[j].start, steps.at(i).lines[j].end, steps.at(i).lines[j].color);
		}
	}
}

void Pyramid::drawStats()
{
	DrawText("Perimeter:", 10, 10, 20, BLACK);
	DrawText("Area:", 10, 30, 20, BLACK);
	DrawText("Volume:", 10, 50, 20, BLACK);

	DrawText(std::to_string(perimeter).c_str(), 150, 10, 20, BLACK);
	DrawText(std::to_string(area).c_str(), 150, 30, 20, BLACK);
	DrawText(std::to_string(volume).c_str(), 150, 50, 20, BLACK);
}