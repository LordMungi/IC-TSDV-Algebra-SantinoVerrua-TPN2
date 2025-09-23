#include "raylib.h"
#include <iostream>

//ab =||a ||b sen (theta) n

using namespace std;

float dotProduct(Vector3 a, Vector3 b);
float magnitude(Vector3 vector);
Vector3 normalize(Vector3& vector);
Vector3 crossProduct(Vector3 EofVA, Vector3 EofVB);
float findZ(Vector3 EofVA, Vector3 EofVB);


void main()
{
	const int screenWidth = 1280;
	const int screenHeight = 960;

	InitWindow(screenWidth, screenHeight, "Algebra TP2 - Piramide Escalonada");

	// Define the camera to look into our 3d world
	Camera3D camera = { 0 };
	camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	//Vector A
	Vector3 vectorAInit;
	vectorAInit.x = 0.0f;
	vectorAInit.y = 0.0f;
	vectorAInit.z = 0.0f;

	Vector3 vectorAEnd;
	vectorAEnd.x = GetRandomValue(1, 10);
	vectorAEnd.y = GetRandomValue(1, 10);
	vectorAEnd.z = GetRandomValue(1, 10);

	cout << "magnitude VectorA: " << magnitude(vectorAEnd) << endl;

	//Vector B
	Vector3 vectorBInit = vectorAInit;

	Vector3 vectorBEnd;
	vectorBEnd.x = vectorAEnd.y * -1;
	vectorBEnd.y = vectorAEnd.x;
	vectorBEnd.z = findZ(vectorAEnd, vectorBEnd);
	
	//diff entre magnitudes
	float diff = 0.0f;
	if (magnitude(vectorBEnd) < magnitude(vectorAEnd))
	{
		diff = magnitude(vectorAEnd) / magnitude(vectorBEnd);

		vectorBEnd.x *= diff;
		vectorBEnd.y *= diff;
		vectorBEnd.z *= diff;
	}

	cout << "magnitude VectorB: " << magnitude(vectorBEnd) << endl;

	//dot product
	cout << dotProduct(vectorAEnd, vectorBEnd) << endl;

	//num
	int num = 5;

	//Vector C
	Vector3 vectorCInit = vectorAInit;

	Vector3 vectorCEnd = crossProduct(vectorAEnd, vectorBEnd);
	Vector3 vectorCEndNormalized = normalize(vectorCEnd);

	vectorCEndNormalized.x *= magnitude(vectorAEnd) * 1 / num;
	vectorCEndNormalized.y *= magnitude(vectorAEnd) * 1 / num;
	vectorCEndNormalized.z *= magnitude(vectorAEnd) * 1 / num;

	//dibujado del suelo primer escalon
	Vector3 base;
	base = vectorAInit;

	Vector3 conectorLA;
	conectorLA.x = base.x + vectorAEnd.x;
	conectorLA.y = base.y + vectorAEnd.y;
	conectorLA.z = base.z + vectorAEnd.z;

	Vector3 conectorLB;
	conectorLB.x = base.x + vectorAEnd.x + vectorBEnd.x;
	conectorLB.y = base.y + vectorAEnd.y + vectorBEnd.y;
	conectorLB.z = base.z + vectorAEnd.z + vectorBEnd.z;

	Vector3 conectorLC;
	conectorLC.x = base.x + vectorBEnd.x;
	conectorLC.y = base.y + vectorBEnd.y;
	conectorLC.z = base.z + vectorBEnd.z;

	//dibujado techo
	Vector3 conectorR1;
	conectorR1.x = base.x + vectorCEndNormalized.x;
	conectorR1.y = base.y + vectorCEndNormalized.y;
	conectorR1.z = base.z + vectorCEndNormalized.z;

	Vector3 conectorR2;
	conectorR2.x = conectorLA.x + vectorCEndNormalized.x;
	conectorR2.y = conectorLA.y + vectorCEndNormalized.y;
	conectorR2.z = conectorLA.z + vectorCEndNormalized.z;

	Vector3 conectorR3;
	conectorR3.x = conectorLB.x + vectorCEndNormalized.x;
	conectorR3.y = conectorLB.y + vectorCEndNormalized.y;
	conectorR3.z = conectorLB.z + vectorCEndNormalized.z;

	Vector3 conectorR4;
	conectorR4.x = conectorLC.x + vectorCEndNormalized.x;
	conectorR4.y = conectorLC.y + vectorCEndNormalized.y;
	conectorR4.z = conectorLC.z + vectorCEndNormalized.z;

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	while (!WindowShouldClose())        // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------

		UpdateCamera(&camera, CAMERA_FREE);

		if (IsKeyPressed('Z')) camera.target = { 0.0f, 0.0f, 0.0f };
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		BeginMode3D(camera);
		DrawGrid(1000, 1.0f);

		DrawLine3D(vectorAInit, vectorAEnd, RED); //Vector A
		DrawLine3D(vectorBInit, vectorBEnd, GREEN); // Vector B
		DrawLine3D(vectorCInit, vectorCEndNormalized, SKYBLUE); // Vector C
		DrawLine3D(conectorLA, conectorLB, YELLOW); // Vector C
		DrawLine3D(conectorLB, conectorLC, YELLOW); // Vector C
		DrawLine3D(conectorR1, conectorR2, YELLOW); //Vector Techo 1
		DrawLine3D(conectorR2, conectorR3, YELLOW); //Vector Techo 2
		DrawLine3D(conectorR3, conectorR4, YELLOW); //Vector Techo 3
		DrawLine3D(conectorR4, conectorR1, YELLOW); //Vector Techo 4
		DrawLine3D(conectorLA, conectorR2, YELLOW); //Pilar 2
		DrawLine3D(conectorLB, conectorR3, YELLOW); //Pilar 3
		DrawLine3D(conectorLC, conectorR4, YELLOW); //Pilar 4

		EndMode3D();

		DrawRectangle(10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(10, 10, 320, 93, BLUE);

		DrawText("Free camera default controls:", 20, 20, 10, BLACK);
		DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
		DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
		DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	CloseWindow();        // Close window and OpenGL context
}

float dotProduct(Vector3 a, Vector3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float magnitude(Vector3 vector)
{
	return sqrt((pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2)));
}

Vector3 normalize(Vector3& vector)
{
	float lenght = sqrt((pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2)));

	return
	{
		vector.x / lenght,
		vector.y / lenght,
		vector.z / lenght
	};
}

Vector3 crossProduct(Vector3 EofVA, Vector3 EofVB)
{
	Vector3 c =
	{
	  EofVA.y * EofVB.z - EofVA.z * EofVB.y,
	  EofVA.z * EofVB.x - EofVA.x * EofVB.z,
	  EofVA.x * EofVB.y - EofVA.y * EofVB.x
	};
	return c;
}

float findZ(Vector3 EofVA, Vector3 EofVB)
{
	float result = 0.0f;

	result = (EofVA.x * EofVB.x) + (EofVA.y * EofVB.y) + (EofVA.z * result);

	return result;
}