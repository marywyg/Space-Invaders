#ifndef ENTITY_H
#define ENTITY_H
#include "bullet.h"
#include <iostream>
 
class entity {
public:
	int x;
	int y;
	sf::Sprite sprite;
	int health;
	bool isDead;
	bullet entityBullet;
	void getPosition();
	entity() {
		x = 256 - sprite.getGlobalBounds().width;
		y = 512;
		sprite.setPosition(x, y);
		health = 100;
		isDead = false;
	}
	virtual void fireBullet(const sf::Time&);
	virtual void death(bool isDead);
	
};

 
#endif 

