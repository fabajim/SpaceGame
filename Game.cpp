#include "Game.h"

// Private Functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Defender", sf::Style::Close | sf::Style::Titlebar);
}

// Public Functions
Game::Game()
{
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}

}

void Game::update()
{
}

void Game::render()
{
	this->window->clear();
	//Draw on the window

	this->window->display();
}
