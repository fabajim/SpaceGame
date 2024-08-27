#include "Laser.h"

//Laser constructor
Laser::Laser(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movement_speed)
{
	this->shape.setTexture(*texture);
	this->shape.setPosition(posX, posY);
	this->direction.x = dirX;
	this->direction.y = dirY;
	this->movementSpeed = movement_speed;
}

Laser::~Laser()
{

}

const sf::FloatRect Laser::getBounds() const
{
	//curent location of laser object
	return this->shape.getGlobalBounds();
}

void Laser::update()
{
	//Laser Movement
	this->shape.move(this->movementSpeed * this->direction);
}

void Laser::render(sf::RenderTarget* target)
{
	//places image to object
	target->draw(this->shape);
}
