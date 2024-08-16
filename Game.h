#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Game
{
private:
	sf::RenderWindow* window;

	void initWindow();
public:
	Game();
	virtual ~Game();

	void run();
	//update and render the window
	void update();
	void render();

};

