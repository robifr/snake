#include "Game.hpp"

InGameView::InGameView(Game& game) :
    game_(game) {
    this->scoreText = std::make_unique<Text>(this->game_, "Score: 0", 16, 5, 5);
    this->scoreContainer = { 0, 0, this->game_.windowSurface->w, this->game_.gridHeight * 2 };
}

GameOverView::GameOverView(Game& game) :
    game_(game) {
    this->gameOverText = std::make_unique<Text>(
        this->game_, "Game Over!", 
        25, 0, 0
    );

    auto& windowSurface = this->game_.windowSurface;
    auto& textBody = this->gameOverText->body;

    this->gameOverText->setPosition(
        static_cast<int>(windowSurface->w / 2) - static_cast<int>(textBody.w / 2),
        static_cast<int>(windowSurface->h / 2) - static_cast<int>(textBody.h / 2)
    );
}