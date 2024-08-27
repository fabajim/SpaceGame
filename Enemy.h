#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>

class Enemy
{
private:

	sf::Sprite shape;
	sf::Texture* texture;

	float posY;//y position


public:
	Enemy(sf::Texture* texture);
	virtual ~Enemy();

	float movementSpeed;

	const sf::FloatRect getBounds() const;

	void move();

	void render(sf::RenderTarget* target);

};