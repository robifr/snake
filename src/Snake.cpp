#include <cmath> //floor

#include "Snake.hpp"
#include "Game.hpp"
#include "View.hpp"

Snake::Snake(Game& game) :
    game_(game) {
}

void Snake::changeDirection(int keyCode) {
    int deltaX = 0, deltaY = 0;

    switch (keyCode) {
        case SDLK_UP:
        case SDLK_w:
            deltaX = 0;
            deltaY = -this->game_.gridHeight;
            break;
        
        case SDLK_DOWN:
        case SDLK_s:
            deltaX = 0;
            deltaY = this->game_.gridHeight;
            break;
        
        case SDLK_LEFT:
        case SDLK_a:
            deltaX = -this->game_.gridWidth;
            deltaY = 0;
            break;
        
        case SDLK_RIGHT:
        case SDLK_d:
            deltaX = this->game_.gridWidth;
            deltaY = 0;
            break;
        
        default: return;
    } 
    
    const bool isTryingToMoveDownWhileMovingUp = deltaY > this->deltaY_ && this->deltaY_ < 0;
    const bool isTryingToMoveUpWhileMovingDown = deltaY < this->deltaY_ && this->deltaY_ >= 0;
    const bool isTryingToMoveRightWhileMovingLeft = deltaX > this->deltaY_ && this->deltaX_ < 0;
    const bool isTryingToMoveLeftWhileMovingRight = deltaX < this->deltaX_ && this->deltaX_ >= 0;

    //disallow snake to move towards their current opposite direction.
    //e.g. if the snake is currently moving up, user shouldn't be able to move down, and vice versa.
    if (!isTryingToMoveUpWhileMovingDown
        || !isTryingToMoveDownWhileMovingUp
        || !isTryingToMoveLeftWhileMovingRight
        || !isTryingToMoveRightWhileMovingLeft) {
        
        //compute next head position ahead before doing movement.
        //ensuring the head won't eat its own neck, 
        //because of user changing direction way too fast.
        if (this->body_.size() >= 1) {
            std::pair<int, int> nextPosition = this->nextHeadPosition_(deltaX, deltaY);

            if (nextPosition.first == this->body_[1].x 
                && nextPosition.second == this->body_[1].y) {
                return;
            }
        }

        this->deltaX_ = deltaX;
        this->deltaY_ = deltaY;
    }
}

void Snake::move() {
    for (int i = this->body_.size() - 1; i >= 0; i--) {
        //snake head.
    	if (i == 0) {
            std::pair<int, int> position = this->nextHeadPosition_(this->deltaX_, this->deltaY_);
            this->body_[i].x = position.first;
            this->body_[i].y = position.second;

            if (this->isEatingOwnBody_(this->body_[i].x, this->body_[i].y)) this->isAlive = false;
            if (this->isEatingFood_(this->body_[i].x, this->body_[i].y, this->game_.food)) {   
                this->foodEaten_++;
                this->addBody(
                    this->body_.back().x + this->deltaX_, 
                    this->body_.back().y + this->deltaY_
                );
                this->game_.inGameView->setScore(this->foodEaten_);
                this->game_.food->spawnRandom();
                i--;
            }

        //every snake body follow their previous segment position.
        } else if (i > 0) {
            this->body_[i].x = this->body_[i - 1].x;
            this->body_[i].y = this->body_[i - 1].y;
        }
    }
}

void Snake::addBody(int x, int y) {
    SDL_Rect newBody = { x, y, this->game_.gridWidth, this->game_.gridHeight };

    this->body_.push_back(newBody);
}

void Snake::respawn() {
    const int gridWidth = this->game_.gridWidth;
    const int gridHeight = this->game_.gridHeight;
    const int x = std::floor(this->game_.windowSurface->w / 2 / gridWidth) * gridWidth;
    const int y = std::floor(this->game_.windowSurface->h / 2 / gridHeight) * gridHeight;

    this->deltaX_ = 0;
    this->deltaY_ = -15; //move to top as the default position.
    this->foodEaten_ = 0;
    this->body_.clear();

    for (int i = 0; i < 3; i++) {
        this->addBody(x, y + (gridHeight * i));
    }
}

void Snake::render() {
    for (int i = 0; i < this->body_.size(); i++) {
        SDL_SetRenderDrawColor(this->game_.renderer().get(), 220, 20, 60, 225); //red.
        SDL_RenderFillRect(this->game_.renderer().get(), &this->body_[i]);
    }
}

bool Snake::isEatingFood_(int x, int y, const std::unique_ptr<Food>& food) {
    if (x == food->body().x && y == food->body().y) return true;
    return false;
}

bool Snake::isEatingOwnBody_(int x, int y) {
    for (int i = 1; i < this->body_.size(); i++) {
        if (x == this->body_[i].x 
            && y == this->body_[i].y) {
            return true;
        }
    }
    return false;
}

std::pair<int, int> Snake::nextHeadPosition_(int deltaX, int deltaY) {
    const int yMin = this->game_.inGameView->scoreContainer.h;
    const int xMax = this->game_.windowSurface->w - this->game_.gridWidth;
    const int yMax = this->game_.windowSurface->h - this->game_.gridHeight;
    int x = this->body_[0].x + deltaX;
    int y = this->body_[0].y + deltaY;

    if (x > xMax) {
        x = 0;
    } else if (x < 0) {
        x = xMax;
    }

    if (y > yMax) {
        y = yMin;
    } else if (y < yMin) {
        y = yMax;
    }

    return std::make_pair(x, y);
}