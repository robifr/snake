#include <iostream> //cerr.
#include <cmath> //floor
#include <cstdlib> //atexit.
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Game.hpp"

int main(int argc, char* argv[]) {
	//initialize SDL components.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << SDL_GetError() << "\n";
		exit(-1);
	}
	if (TTF_Init() < 0) {
		std::cerr << TTF_GetError() << "\n";
		exit(-1);
	}

	//we have to use `atexit` for these two functions below for clean exit,
	//instead of placing them at the end of `main` function.
	//because they HAVE TO be invoked only after smart pointers destruct their object.
	std::atexit(TTF_Quit);
	std::atexit(SDL_Quit);

	const int gridWidth = 15, gridHeight = 15;
	const int windowWidth = std::floor(750 / gridWidth) * gridWidth;
	const int windowHeight = std::floor(500 / gridHeight) * gridHeight;

	Game game(windowWidth, windowHeight, gridWidth, gridHeight);

	const int snakeX = std::floor(windowWidth / 2 / gridWidth) * gridWidth;
	const int snakeY = std::floor(windowHeight / 2 / gridHeight) * gridHeight;

	for (int i = 0; i < 3; i++) {
		game.snake->addBody(snakeX, snakeY + (gridHeight * i));
	}
	game.food->spawnRandom();

	SDL_Event event;
	bool isClosed = false;

	while (!isClosed) {
		while (SDL_PollEvent(&event)) {
			const int keyCode = event.key.keysym.sym;

			if (event.type == SDL_KEYDOWN) {
				if (game.snake->inputQueue.size() == 0
					|| keyCode != game.snake->inputQueue.back()) {
					game.snake->inputQueue.push_back(keyCode);
				}
			
			} else if (event.type == SDL_QUIT
				|| keyCode == SDLK_ESCAPE) {
				isClosed = true;
			}
		}

		game.update();
		game.render();
		SDL_Delay(1000 / 60);
	}

	return 0;
}