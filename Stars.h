#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>

class Stars
{
private:

	sf::Sprite shape;
	sf::Texture* texture;

	float posY;//y position
	float starSeeed;


public:
	Stars(sf::Texture* texture);
	virtual ~Stars();

	float movementSpeed;


	void moveStar();
	const sf::FloatRect getBounds() const;

	void render(sf::RenderTarget* target);

};
