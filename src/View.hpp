#pragma once

#include <memory> //unique_ptr.
#include <SDL.h>

#include "Text.hpp"

class Game;

class InGameView {
public:
    SDL_Rect scoreContainer;

    InGameView(Game& game);

    void setScore(int score);
    void render();

private:
    Game& game_; 
    std::unique_ptr<Text> scoreText_;
};

class GameOverView {
public:
    GameOverView(Game& game);

    void render();

private:
    Game& game_;
    std::unique_ptr<Text> gameOverText_;
};