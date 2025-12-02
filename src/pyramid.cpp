#include "pyramid.h"

#include <iostream>
#include <ctime>

#include <raymath.h>

Pyramid::Pyramid(int n)
{
	srand(static_cast<unsigned int>(time(0)));

	buildFirstStep(n);
}

void Pyramid::buildFirstStep(int n)
{
	const int max = 20;
	Color color = MAGENTA;

	Vector3 up = { 0, 1, 0 };

	Step s1;

	Line l1;
	l1.start = { 0,0,0 };
	l1.end.x = (rand() % (max * 1000) / 1000.0f) - max / 2;
	l1.end.y = (rand() % (max * 1000) / 1000.0f) - max / 2;
	l1.end.z = (rand() % (max * 1000) / 1000.0f) - max / 2;
	l1.color = RED;

	Line l2;
	l2.start = { 0,0,0 };
	l2.end = Vector3Scale(Vector3Normalize(Vector3CrossProduct(l1.end, up)), Vector3Length(l1.end));
	l2.color = BLUE;

	Line l3;
	l3.start = { 0,0,0 };
	l3.end = Vector3Scale(Vector3Normalize(Vector3CrossProduct(l1.end, l2.end)), n);
	if (Vector3DotProduct(l3.end, up) < 0)
		l3.end = Vector3Negate(l3.end);
	l3.color = GREEN;

	Line l4;
	l4.start = l1.end;
	l4.end = Vector3Add(l2.end, l4.start);

	Line l5;
	l5.start = l2.end;
	l5.end = Vector3Add(l1.end, l5.start);

	Line l6;
	l6.start = l2.end;
	l6.end = Vector3Add(l3.end, l6.start);

	Line l7;
	l7.start = l4.end;
	l7.end = Vector3Add(l3.end, l7.start);

	Line l8;
	l8.start = l1.end;
	l8.end = Vector3Add(l3.end, l8.start);

	Line l9;
	l9.start = l3.end;
	l9.end = Vector3Add(l2.end, l9.start);

	Line l10;
	l10.start = l3.end;
	l10.end = Vector3Add(l1.end, l10.start);

	Line l11;
	l11.start = l6.end;
	l11.end = Vector3Add(l1.end, l11.start);

	Line l12;
	l12.start = l8.end;
	l12.end = Vector3Add(l2.end, l12.start);

	s1.lines[0] = l1;
	s1.lines[1] = l2;
	s1.lines[2] = l3;
	s1.lines[3] = l4;
	s1.lines[4] = l5;
	s1.lines[5] = l6;
	s1.lines[6] = l7;
	s1.lines[7] = l8;
	s1.lines[8] = l9;
	s1.lines[9] = l10;
	s1.lines[10] = l11;
	s1.lines[11] = l12;

	steps.push_back(s1);
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
