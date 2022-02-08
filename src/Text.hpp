#pragma once

#include <string> //string.
#include <memory> //unique_ptr.
#include <SDL.h>
#include <SDL_ttf.h>

#include "Utils.hpp"

class Game;

class Text {
public:
	std::unique_ptr<SDL_Texture, My_SDL_Deleter> texture;
	SDL_Rect body;

	Text(Game& game, std::string text, int fontSize, int x, int y);

	const auto& text() const { return this->text_; }

	void setText(std::string text);
	void setPosition(int x, int y);

private:
	Game& game_;
	std::unique_ptr<SDL_Surface, My_SDL_Deleter> surface_;
	std::unique_ptr<TTF_Font, My_SDL_Deleter> font_;
	SDL_Color color_;
	std::string text_;

	void updateSurface_();
};