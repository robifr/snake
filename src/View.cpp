#include <string> //to_string.
#include <cmath> //floor.

#include "Game.hpp"

InGameView::InGameView(Game& game) :
    game_(game) {
    this->scoreText_ = std::make_unique<Text>(this->game_, "Score: 0", 16, 5, 5);
    this->scoreContainer = { 0, 0, this->game_.windowSurface->w, this->game_.gridHeight * 2 };
}

void InGameView::setScore(int score) {
    this->scoreText_->setText("Score: " + std::to_string(score));
}

void InGameView::render() {
    SDL_SetRenderDrawColor(this->game_.renderer().get(), 50, 50, 50, 225); //grey.
    SDL_RenderFillRect(this->game_.renderer().get(), &this->scoreContainer);

    SDL_RenderCopy(
        this->game_.renderer().get(), 
        this->scoreText_->texture.get(), 
        NULL, 
        &this->scoreText_->body
    );
}

GameOverView::GameOverView(Game& game) :
    game_(game) {
    this->gameOverText_ = std::make_unique<Text>(
        this->game_, "Game Over!", 
        25, 0, 0
    );

    //aligning to the center of screen.
    auto& windowSurface = this->game_.windowSurface;
    auto& textBody = this->gameOverText_->body;
    
    this->gameOverText_->setPosition(
        std::floor(windowSurface->w / 2) - std::floor(textBody.w / 2),
        std::floor(windowSurface->h / 2) - std::floor(textBody.h / 2)
    );
}

void GameOverView::render() {
    SDL_RenderCopy(
        this->game_.renderer().get(), 
        this->gameOverText_->texture.get(), 
        NULL, 
        &this->gameOverText_->body
    );
}