#pragma once
//#ifndef LASER_H
//#define LASER_H
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>

class Laser
{
private:

	sf::Sprite shape;
	sf::Texture* texture;

	sf::Vector2f direction;
	float movementSpeed;

public:
	Laser(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movement_speed);
	virtual ~Laser();

	//Accessor
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

//#endif // !LASER_H
