#pragma once
#include "player.h"

class Game
{
private:
	sf::RenderWindow* window;

	//player
	Player* player;

	void initWindow();
	void initPlayer();

public:
	Game();
	virtual ~Game();

	void run();
	//update and render the window
	void update();
	void render();

};

