#pragma once

#include <SDL.h>

class Game;

class Food {
public:
    Food(Game& game);

    const auto& body() const { return this->body_; }

    void spawnRandom();
    void render();

private:
    Game& game_;
    SDL_Rect body_;

};