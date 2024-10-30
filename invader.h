#ifndef INVADER_H
#define INVADER_H
#include "entity.h"
#include <random>
#include <SFML/Graphics.hpp>

class invader :public entity {
public:
	sf::Texture texture;
	sf::Vector2f velocity{ 0.02f, 0.02f };
	sf::Vector2f acceleration{ 0.001f, 0.001f };
	float friction;
	bool atRightBorder();
	bool atLeftBorder();
	sf::Texture enemyBulletTexture;
	sf::Clock shotClock;
	sf::Time shotInterval;
	sf::Time shootingIntervalGenerator(sf::Time, sf::Time);
	int invaderType;
	void fireBullet(const sf::Time&) override;
	float velocityX;
	bool moveLeft;
	bool moveDown;
	bool moveRight;
	void randomisingInvaderType();
	invader() {
		friction = 0.001f;
		x = 750;
		y = 20;
		sprite.setPosition(x, y);
		enemyBulletTexture.loadFromFile("enemyprojectile1.png");
		entityBullet.sprite.setTexture(enemyBulletTexture);
		entityBullet.sprite.setScale(1.5f, 1.5f);
		shotInterval = sf::seconds(rand());
		velocityX = 30.f;
		sprite.setScale(2.0f, 2.0f);
		entityBullet.velocity = sf::Vector2f(0.f, 0.125f);
	}
};

#endif
