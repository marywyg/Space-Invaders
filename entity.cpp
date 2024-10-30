#include "entity.h"
void entity::getPosition() {
	x = sprite.getPosition().x;
	y = sprite.getPosition().y;
}
void entity::fireBullet(const sf::Time& time) {
	return;
}
void entity::death(bool isDead) {
	if (isDead) {
		sprite.setColor(sf::Color::Red);
	}
}