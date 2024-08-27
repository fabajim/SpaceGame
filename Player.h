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

	float laserCooldown;
	float laserCooldownMax;

	//Private Methods
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();

	//Accessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;


	//Player Methods
	void move(const float dirX, const float dirY);
	const bool canFireLaser();

	void updateLaser();
	void update();
	void render(sf::RenderTarget& target);
};

