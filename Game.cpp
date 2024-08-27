#include "Game.h"

// Private Functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Earth Defender", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initVars()
{
	this->mouseHeld = false;
}

void Game::initTextures()
{
	this->textures["LASER"] = new sf::Texture();
	this->textures["LASER"]->loadFromFile("Textures/Laser.png");
}

// Public Functions
Game::Game()
{
	this->initVars();
	this->initWindow();
	this->initPlayer();
	this->initTextures();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//delete textrues
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//delets lasers
	for (auto* i : this->laser)
	{
		delete i;
	}
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}

}

void Game::eventUpdate()
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
}

void Game::playerUpdate()
{
	// Player inputs for space ship.
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

	//fire laser
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canFireLaser())
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			this->laser.push_back(new Laser(this->textures["LASER"],
								  this->player->getPos().x, this->player->getPos().y, 1.f, 0.f, 3.f));
		}
		else
		{
			this->mouseHeld = false;
		}
	}
}

void Game::laserUpdate()
{
	unsigned counter = 0;
	for (auto* lasers : this->laser)
	{
		lasers->update();
		if (lasers->getBounds().left + lasers->getBounds().width > window->getSize().x)
		{
			delete this->laser.at(counter);
			this->laser.erase(this->laser.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Game::update()
{
	this->eventUpdate();
	this->playerUpdate();
	this->player->update();
	this->laserUpdate();
}

void Game::render()
{
	this->window->clear();

	//Draw on the window
	this->player->render(*this->window);

	//render lasers
	for (auto* lasers : this->laser)
	{
		lasers->render(this->window);
	}

	this->window->display();
}
