#include "Game.h"

// Private Functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Earth Defender", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initText()
{
	this->gameText.setFont(this->font);
	this->gameText.setCharacterSize(20);
	this->gameText.setFillColor(sf::Color::White);
	this->gameText.setString("NONE");
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initVars()
{
	this->mouseHeld = false;
	this->enemySpawnTimeMax = 700.f;
	this->enemySpawnTime = this->enemySpawnTimeMax;
	this->enemySpeed = -1.5f;
	this->starSpawnMax = 8.f;
	this->starSpawnTimer = this->starSpawnMax;
	this->maxStars = 18;
	this->points = 0;
	this->maxPoints = this->points;
}

void Game::initTextures()
{
	this->textures["STARS"] = new sf::Texture();
	this->textures["STARS"]->loadFromFile("Textures/Stars.png");

	this->textures["LASER"] = new sf::Texture();
	this->textures["LASER"]->loadFromFile("Textures/Laser.png");

	this->textures["ENEMY"] = new sf::Texture();
	this->textures["ENEMY"]->loadFromFile("Textures/Enemy.png");

	if (!this->font.loadFromFile("roman_sd/Roman.ttf"))
		std::cout << "ERROR::GAME::INITTEXTURES::FAILD TO LOAD FONT\n";
}

void Game::initEnemy()
{
	//sf::FloatRect rect = { 80.f,100.f,80.f,80.f };
	this->enemy.push_back(new Enemy(this->textures["ENEMY"], this->enemySpeed));
}

void Game::initStar()
{
	this->stars.push_back(new Stars(this->textures["STARS"]));
}

void Game::subtractPoints()
{
	this->points -= 2;
	if (this->points < 0)
	{
		this->window->close();
		std::cout << "Game over!\n";
	}
}

void Game::updatePoints()
{
	this->points++;
	this->maxPoints = points;
	if (this->points % 2 == 0)
	{
		this->updateEnemySpeed(-0.2f);
	}
	if (this->points % 5 == 0)
	{
		this->updateEnemySpawnTime(-50.f);
	}
}

void Game::updateEnemySpeed(float speed)
{
	this->enemySpeed += speed;
	// std::cout << "Enemy Speed " << enemySpeed << std::endl; debugging
}

void Game::updateEnemySpawnTime(float time)
{
	if (this->enemySpawnTimeMax > 0)
	{
		this->enemySpawnTimeMax += time;

	}
	// std::cout << "Enemy Spawn Time " << enemySpawnTimeMax << std::endl; debugging
}

// Public Functions
Game::Game()
{
	this->initVars();
	this->initWindow();
	this->initTextures();
	this->initText();
	this->initPlayer();
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

	//delete enemy
	for (auto* i : this->enemy)
	{
		delete i;
	}

	//delete star
	for (auto* i : this->stars)
	{
		delete i;
	}
}

int Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
	return this->maxPoints;
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
		else
		{
			// Hitting an enemy
			unsigned enemyCount = 0;
			for (auto *enemies : this->enemy)
			{
				if (lasers->getBounds().intersects(enemies->getBounds()))
				{
					delete this->enemy.at(enemyCount);
					this->enemy.erase(this->enemy.begin() + enemyCount);
					this->updatePoints();

					//delete laser
					delete this->laser.at(counter);
					this->laser.erase(this->laser.begin() + counter);

					--enemyCount;
				}
				++enemyCount;
			}
		}
		++counter;
	}
}

void Game::enemyUpdate()
{
	if (this->enemySpawnTime == this->enemySpawnTimeMax)
	{
		this->initEnemy();
		this->enemySpawnTime = 0.f;
	}
	this->enemySpawnTime += 1.f;

	unsigned counter = 0;//used as an iterator
	for (auto* enemies : this->enemy)
	{	
		enemies->move();

		//enemy deleted if out of bounds
		if (enemies->getBounds().left + enemies->getBounds().width < 0) 
		{
			delete this->enemy.at(counter);
			this->enemy.erase(this->enemy.begin() + counter);
			--counter;
			this->subtractPoints();
		}
		else if (enemies->getBounds().intersects(player->getBounds()))
		{
			this->subtractPoints();
		}
		++counter;
	}
}

void Game::starUpdate()
{
	// spawn stars
	if (this->stars.size() < this->maxStars)
	{
		if (this->starSpawnTimer >= this->starSpawnMax)
		{
			this->initStar();
			this->starSpawnTimer = 0.f;
		} 
		else
		{
			this->starSpawnTimer += 1.f;
		}
	}
	// Move Stars
	unsigned counter = 0;
	for (auto* star : this->stars)
	{
		star->moveStar();
		if (star->getBounds().left + star->getBounds().width < 0)
		{
			delete this->stars.at(counter);
			this->stars.erase(this->stars.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Game::textUpdate()
{
	//display score and enemies escaped
	std::stringstream ss;

	ss << "Points: " << this->points << '\n';

	this->gameText.setString(ss.str());
}

void Game::update()
{
	this->eventUpdate();
	this->textUpdate();
	this->playerUpdate();
	this->player->update();
	this->laserUpdate();
	this->enemyUpdate();
	this->starUpdate();
}

void Game::renderText(sf::RenderTarget &target)
{
	target.draw(this->gameText);
}

void Game::render()
{
	this->window->clear();

	this->renderText(*this->window);

	//Draw on the window
	this->player->render(*this->window);

	//render lasers
	for (auto* lasers : this->laser)
	{
		lasers->render(this->window);
	}

	//render enemy
	for (auto* enemies : this->enemy)
	{
		enemies->render(this->window);
	}

	// rebder stars
	for (auto* star : this->stars)
	{
		star->render(this->window);
	}

	this->window->display();
}
