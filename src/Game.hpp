#pragma once

#include <string> //string.
#include <memory> //unique_ptr.
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Snake.hpp"
#include "Food.hpp"
#include "View.hpp"
#include "Utils.hpp"

class Game {
public:
	SDL_Surface* windowSurface; //window surface shouldn't be freed, based SDL docs.
	std::unique_ptr<Snake> snake;
	std::unique_ptr<Food> food;
	std::unique_ptr<InGameView> inGameView;
	std::unique_ptr<GameOverView> gameOverView;
	int gridWidth = 0;
	int gridHeight = 0;
	
	Game(int width, int height, int gridWidth, int gridHeight);

	const auto& renderer() const { return this->renderer_; }

	void update();
	void render();

private:
	std::unique_ptr<SDL_Window, My_SDL_Deleter> window_;
	std::unique_ptr<SDL_Renderer, My_SDL_Deleter> renderer_;

	void renderRect_(SDL_Rect& rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	void renderText_(const std::unique_ptr<SDL_Texture, My_SDL_Deleter>& texture, SDL_Rect& rect);
};