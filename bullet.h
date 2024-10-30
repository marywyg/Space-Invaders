#ifndef BULLET_H
#define BULLET_H
#include <iostream>
#include <SFML/Graphics.hpp>
class bullet {
public:
	int x;
	int y;
	sf::Vector2f velocity{ 0.0f, 0.0f };
	sf::Vector2f acceleration{ 0.01f, 0.01f };
	int damage;
	sf::Sprite sprite;
	sf::Texture texture;
	float bulletCooldown = 0.2f;
	float elapsedTime = 0.f;
	float speedMultiplier = 0.1f;
	int frameWidth = 32; 
	int frameHeight = 32;
	int numFrames = 4; 
	int currentFrame = 0; 
	float frameDuration = 0.1f; 
	float frameTimer = 0.0f; 
	float animationTime; 
	void bulletAnimation(float);
	bullet() {
		x = 0;
		y = 0;
		damage = 20;
		texture.loadFromFile("projectile.png");
		sprite.setTexture(texture);
		sprite.setScale(0.15f, 0.15f);
		sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
		
	}
};

#endif

