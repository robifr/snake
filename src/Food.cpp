#include <vector> //vector.
#include <random> //random_device, mt19937, uniform_int_distribution.

#include "Food.hpp"
#include "Game.hpp"

Food::Food(Game& game, int x, int y, int width, int height) :
    game_(game) {
    this->body = { x, y, width, height };
}

void Food::spawnRandom() {
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<int> randomX(
        0, this->game_.windowSurface->w - this->body.w
    );
    std::uniform_int_distribution<int> randomY(
        this->game_.inGameView->scoreContainer.h,
        this->game_.windowSurface->h - this->body.h
    );

    bool collideWithSnake = true;

    //searching position for the food, those are not located on top of snake bodies.
    while (collideWithSnake) {
        collideWithSnake = false;
        int x = static_cast<int>(randomX(generator) / this->body.w) * this->body.w;
        int y = static_cast<int>(randomY(generator) / this->body.h) * this->body.h;
        std::vector<SDL_Rect> snakeBody = this->game_.snake->body;

        for (int i = 0; i < snakeBody.size(); i++) {
            if (x == snakeBody[i].x && y == snakeBody[i].y) {
                collideWithSnake = true;
                break;
            }
        }

        this->body.x = x;
        this->body.y = y;
    }
}