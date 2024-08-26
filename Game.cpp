#include "Game.h"

// Private Functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Defender", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	this->player = new Player();
}

// Public Functions
Game::Game()
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
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
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		// closing game with x or pressing escape
		if (ev.Event::type == sf::Event::Closed || 
			(ev.Event::KeyPressed && 
			ev.Event::key.code == sf::Keyboard::Escape)) {
			this->window->close();
		}
	}

	// update player
	//Move Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	//Move Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	//Move UP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	//Move Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);
}

void Game::render()
{
	this->window->clear();

	//Draw on the window
	this->player->render(*this->window);

	this->window->display();
}
