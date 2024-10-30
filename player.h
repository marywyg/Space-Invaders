#ifndef PLAYER_H
#define PLAYER_H
#include "playerManager.h"
#include "entity.h"
#include "bullet.h"
class player :public entity {
public:
	sf::Texture texture;
	sf::Vector2f velocity{ 0.0f, 0.0f };
	sf::Vector2f minvelocity{ 0.0f, 0.0f };
	sf::Vector2f acceleration{ 0.001f, 0.001f };
	float friction;
	std::vector<bullet> bullets;
	float speedMultiplier;
	sf::Clock noMovementClock;
	sf::Time noMovementThreshold;
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void fireBullet(const sf::Time&) override;
	playerManager manager;
	const int maxHealth = 150.f;
	const int& getHealth() const;
	const int& getMaxHealth() const;

	player() {
		health = 150;
		texture.loadFromFile("Main Ship - Base - Full health.png");
		sprite.setTexture(texture);
		sprite.setScale(2.f, 2.f);
		friction = 0.01f;
		speedMultiplier = 0.001f;
		noMovementThreshold = sf::seconds(0.1f);
		noMovementClock.restart();
		if (!entityBullet.texture.loadFromFile("projectile.png")) {
			std::cerr << "Error loading bullet texture from file 'projectile.png'" << std::endl;
		}
		entityBullet.sprite.setTexture(entityBullet.texture);
		entityBullet.sprite.setScale(2.f, 2.f);
		manager.initHealthBar();
	}
	
};

#endif
