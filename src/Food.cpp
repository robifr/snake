#include <cmath>
#include <random> //random_device, mt19937, uniform_int_distribution.

#include "Food.hpp"
#include "Game.hpp"

Food::Food(Game& game) :
    game_(game) {
    this->body_ = { 0, 0, this->game_.gridWidth, this->game_.gridHeight };
}

void Food::spawnRandom() {
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<int> randomX(
        0, this->game_.windowSurface->w - this->game_.gridWidth
    );
    std::uniform_int_distribution<int> randomY(
        this->game_.inGameView->scoreContainer.h,
        this->game_.windowSurface->h - this->game_.gridHeight
    );

    bool collideWithSnake = true;

    //searching position for the food, those are not located on top of snake bodies.
    while (collideWithSnake) {
        collideWithSnake = false;
        int x = std::floor(randomX(generator) / this->game_.gridWidth) * this->game_.gridWidth;
        int y = std::floor(randomY(generator) / this->game_.gridHeight) * this->game_.gridHeight;
        auto snakeBody = this->game_.snake->body();

        for (int i = 0; i < snakeBody.size(); i++) {
            if (x == snakeBody[i].x && y == snakeBody[i].y) {
                collideWithSnake = true;
                break;
            }
        }

        this->body_.x = x;
        this->body_.y = y;
    }
}

void Food::render() {
    SDL_SetRenderDrawColor(this->game_.renderer().get(), 250, 180, 30, 255);
    SDL_RenderFillRect(this->game_.renderer().get(), &this->body_);
}