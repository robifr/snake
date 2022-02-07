#pragma once

#include <memory> //unique_ptr.
#include <SDL2/SDL.h>

#include "Text.hpp"

class Game;

class InGameView {
public:
    std::unique_ptr<Text> scoreText;
    SDL_Rect scoreContainer;

    InGameView(Game& game);

private:
    Game& game_;
};

class GameOverView {
public:
    std::unique_ptr<Text> gameOverText;
    
    GameOverView(Game& game);

private:
    Game& game_;
};