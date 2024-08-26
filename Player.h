#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>


class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	void initTexture();
	void initSprite();
	void initVariables();

public:
	Player();
	virtual ~Player();

	void move(const float X, const float Y);

	void update();
	void render(sf::RenderTarget& target);
};

