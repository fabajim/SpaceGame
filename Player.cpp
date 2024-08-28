#include "Player.h"



//initiates the variabels
void Player::initVariables()
{
	this->movementSpeed = 1.f;
	this->laserCooldownMax = 10.f;
	this->laserCooldown = this->laserCooldownMax;
}

//initieate the player texture
void Player::initTexture()
{
	//load a picture from file
	//if file fails to open display error on console
	if (!this->texture.loadFromFile("Textures/hero.png"))
	{
		std::cout << "Error::PLAYER::INITTEXTURE:: Ccould not load file." << "\n";
	}
}

void Player::initSprite()
{
	//set texture to the sprite
	//sets the sprite on the window
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(100.f, 250.f);
}

//Player Constructor
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{


}

const sf::Vector2f& Player::getPos() const
{
	//Laser appear at player possition
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	//returns the players current location. 
	return this->sprite.getGlobalBounds();
}



//player Methods

void Player::move(const float dirX, const float dirY)
{
	/*
		user input movement
		player moves along x and y axis at movement speed
	*/

	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canFireLaser()
{
	//Keeps laser from being a continues stream
	if (this->laserCooldown >= this->laserCooldownMax)
	{
		//laser only fires at 0
		this->laserCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateLaser()
{
	//when laser fired cool down at 0
	//increase cool down to > than cooldownMax
	if (this->laserCooldown < this->laserCooldownMax)
		this->laserCooldown += 0.5f;
}

void Player::update()
{
	//moves laser to the right
	this->updateLaser();
}


void Player::render(sf::RenderTarget& target)
{
	//draws image to object 
	target.draw(this->sprite);
}
