#include "Player.h"

void Player::initTexture()
{
	// Load a texture
	if (!this->texture.loadFromFile("Textures/hero.png"))
	{
		std::cout << "Error::Player::initTexture:: could not load file.\n";
	}
}

void Player::initSprite()
{
	// set textrue to sprite
	this->sprite.setTexture(this->texture);

}

void Player::initVariables()
{
	this->movementSpeed = 1.f;
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
}

Player::~Player()
{
}

void Player::move(const float X, const float Y)
{
	this->sprite.move(this->movementSpeed * X, this->movementSpeed * Y);
}

void Player::update()
{
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
