#pragma once

#include <memory> //unique_ptr.
#include <utility> //pair.
#include <vector> //vector.
#include <SDL2/SDL.h>

class Game;
class Food;

class Snake {
public:
	std::vector<SDL_Rect> body;
	double updateInterval = 150.0;
	double lastTimeUpdate = 0.0;
	bool isAlive = true;

	/** 
	 * used to prevent user from changing direction way too fast.
	 * basically we only process single input (which is the oldest one)
	 * everytime snake updates it's own movement.
	 */
	std::vector<int> inputQueue;

	Snake(Game& game, int width, int height);

	/** 
	 * change current snake direction based on keyboard input key-code. 
	 * \param SDL_Event::key.keysym.sym
	 */ 
	void changeDirection(int keyCode);

	void move();
	void addBody(int x, int y);

private:
	Game& game_;
	int width_ = 0;
	int height_ = 0;
	int deltaX_ = 0;
	int deltaY_ = -15; //moving to top when the game just started.
	int foodEaten_ = 0;

	bool isEatingFood_(int x, int y, const std::unique_ptr<Food>& food);
	bool isEatingOwnBody_(int x, int y);

	/**
	 * get position for the snake head. incase when the head is off from screen,
	 * spawn the head on the opposite side of screen from current direction
	 * \return { x, y } position for the head.
	 */
	std::pair<int, int> nextHeadPosition_(int deltaX, int deltaY);
};