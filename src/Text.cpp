#include "Text.hpp"
#include "Game.hpp"

Text::Text(Game& game, std::string text, int fontSize, int x = 0, int y = 0) :
	game_(game) {
	this->text_ = text;
	this->color_ = { 225, 225, 225, 225 }; //white.
	//it's fine i guess to have this such design structure, 
	//since this project isn't that big.
	this->font_ = std::unique_ptr<TTF_Font, My_SDL_Deleter>(
		TTF_OpenFont("src/assets/font/fiery_turk.ttf", fontSize)
	);
	this->updateSurface_();
	this->setPosition(x, y);
}

void Text::setText(std::string text) {
	this->text_ = text;
	this->updateSurface_();
	this->setPosition(this->body.x, this->body.y);
}

void Text::updateSurface_() {
	this->surface_ = std::unique_ptr<SDL_Surface, My_SDL_Deleter>(
		TTF_RenderText_Solid(this->font_.get(), this->text_.c_str(), this->color_)
	);
	this->texture = std::unique_ptr<SDL_Texture, My_SDL_Deleter>(
		SDL_CreateTextureFromSurface(this->game_.renderer().get(), this->surface_.get())
	);
}

void Text::setPosition(int x, int y) {
	this->body = { x, y, this->surface_->w, this->surface_->h };
}