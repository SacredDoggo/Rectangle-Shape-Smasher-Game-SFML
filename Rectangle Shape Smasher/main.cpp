#include "Game.h"

int main() {

	// init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	// Initialize Game Engine
	Game game;


	//Game loop
	while (game.running())
	{
		// Event Polling

		// Update


		// Render
			// clear old frame

			// Draw your game

		 // tell app that window is done drawing

		game.update();

		game.render();
	}


	// End of application
	return 0;
}