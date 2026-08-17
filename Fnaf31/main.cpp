#include "raylib.h"
#include "Game.h"


int main() {

	Game game;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	// Initialization
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Game");
	SetTargetFPS(60);
	game.init();

	// Main game loop
	while (!WindowShouldClose()) {
		//update
		game.update();

		// Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);



		game.draw();
		//DrawText("Hello World", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}
	// De-Initialization
	game.shutdown();
	CloseWindow();
	return 0;
}