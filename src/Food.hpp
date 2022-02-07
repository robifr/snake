#pragma once

#include <SDL2/SDL.h>

class Game;

class Food {
public:
    SDL_Rect body;

    Food(Game& game, int x, int y, int width, int height);

    void spawnRandom();

private:
    Game& game_;
};