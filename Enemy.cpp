#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, float speed)
{
	//sets position y at a random location when object is crated
	this->posY = static_cast<float>(rand() % 500);
	this->shape.setTexture(*texture);
	this->shape.setPosition(799.f, posY);
	this->movementSpeed = speed;
}

Enemy::~Enemy()
{

}

void Enemy::move()
{
	/*
		movement of the enemy
		moves at negative sped * 1 x postion
	*/
	this->shape.move(this->movementSpeed * 1, this->movementSpeed * 0.f);
}

const sf::FloatRect Enemy::getBounds() const
{
	/*
		returns current location
		of enemy
	*/
	return this->shape.getGlobalBounds();
}

void Enemy::render(sf::RenderTarget* target)
{
	//drawing of the enemy
	target->draw(this->shape);
}
