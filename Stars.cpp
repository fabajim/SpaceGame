#include "Stars.h"

Stars::Stars(sf::Texture* texture)
{
	this->shape.setTexture(*texture);
	this->shape.setPosition(800.f, rand() % 599);
	this->starSeeed = -5.f;
}

Stars::~Stars()
{
}

void Stars::moveStar()
{
	this->shape.move(starSeeed, 0.f);
}

const sf::FloatRect Stars::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Stars::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
