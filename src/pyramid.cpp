#include "pyramid.h"

#include <iostream>
#include <ctime>

#include <raymath.h>

Pyramid::Pyramid(int n)
{
	srand(static_cast<unsigned int>(time(0)));
	Vector3 up = { 0, 1, 0 };

	Line l1;
	Line l2;
	Line l3;
	
	l1.start = { 0,0,0 };	
	l1.end = { (rand() % 10000 / 1000.0f) - 5.0f, (rand() % 10000 / 1000.0f) - 5.0f, (rand() % 10000 / 1000.0f) - 5.0f };
	l1.color = RED;
	l2.start = { 0,0,0 };
	l2.end = Vector3Scale(Vector3Normalize(Vector3CrossProduct(l1.end, up)), Vector3Length(l1.end));
	l2.color = BLUE;
	l3.start = { 0,0,0 };
	l3.end = Vector3Scale(Vector3Normalize(Vector3CrossProduct(l1.end, l2.end)), n);
	if (Vector3DotProduct(l3.end, up) < 0)
		l3.end = Vector3Negate(l3.end);
	l3.color = GREEN;

	lines.push_back(l1);
	lines.push_back(l2);
	lines.push_back(l3);
}

void Pyramid::draw()
{

	for (int i = 0; i < lines.size(); i++)
	{
		DrawLine3D(lines.at(i).start, lines.at(i).end, lines.at(i).color);
	}
}
