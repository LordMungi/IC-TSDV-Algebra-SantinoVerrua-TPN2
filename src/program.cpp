#include "program.h"

#include "pyramid.h"

namespace program
{
	static void init();
	static void update();
	static void draw();
	static void close();

	const int n = 3;

	Camera3D camera;
	Pyramid pyramid(n);

	void run()
	{
		init();
		while (!WindowShouldClose())
		{
			update();
			draw();
		}
		close();
	}

	static void init()
	{
		InitWindow(1024, 768, "Pyramids");

		camera.position = { 0, 10, 10 };
		camera.target = { 0, 0, 0 };
		camera.up = { 0, 1, 0 };
		camera.fovy = 45;
		camera.projection = CAMERA_PERSPECTIVE;

		DisableCursor();
	}

	static void update()
	{
		UpdateCamera(&camera, CAMERA_FREE);
	}

	static void draw()
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);
		
		BeginMode3D(camera);

		DrawGrid(10, 1);
		pyramid.draw();

		EndMode3D();

		EndDrawing();
	}

	static void close()
	{
		CloseWindow();
	}
}