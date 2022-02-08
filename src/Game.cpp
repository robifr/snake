#include <chrono> //chrono.

#include "Game.hpp"

Game::Game(int width, int height, int gridWidth, int gridHeight) {
	this->gridWidth = gridWidth;
	this->gridHeight = gridHeight;

	this->window_ = std::unique_ptr<SDL_Window, My_SDL_Deleter>(
		SDL_CreateWindow(
			"Snake", 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED,
			width, 
			height,
			SDL_WINDOW_SHOWN
		)
	);
	this->renderer_ = std::unique_ptr<SDL_Renderer, My_SDL_Deleter>(
		SDL_CreateRenderer(this->window_.get(), -1, SDL_RENDERER_ACCELERATED)
	);
	this->windowSurface = SDL_GetWindowSurface(this->window_.get());

	this->snake = std::make_unique<Snake>(*this);
	this->food = std::make_unique<Food>(*this);

	this->inGameView = std::make_unique<InGameView>(*this);
	this->gameOverView = std::make_unique<GameOverView>(*this);
}

void Game::update() {
	const auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
	const double now = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch).count();

	if (this->snake->isAlive
		&& now - this->snake->lastTimeUpdate > this->snake->updateInterval) {
		const int input = this->snake->inputQueue.size() > 0
			? this->snake->inputQueue.front()
			: -1;

		if (input != -1) {
			this->snake->changeDirection(input);
			this->snake->inputQueue.clear();
		}
		this->snake->move();
		this->snake->lastTimeUpdate = now;
	}
}

void Game::render() {
	//render the background firstly.
	SDL_SetRenderDrawColor(this->renderer_.get(), 0, 0, 0, 0); //black.
	SDL_RenderClear(this->renderer_.get());

	//and then render all the stuff on top of it.
	this->food->render();
	this->snake->render();
	this->inGameView->render();

	if (!this->snake->isAlive) this->gameOverView->render();

	SDL_RenderPresent(this->renderer_.get());
}