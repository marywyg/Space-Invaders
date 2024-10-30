#include "player.h"
const int& player::getHealth() const {
	return this->health;
}
const int& player::getMaxHealth() const {
	return this->maxHealth;
}
void player::fireBullet(const sf::Time& time) {
	entityBullet.elapsedTime += time.asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && entityBullet.elapsedTime >= entityBullet.bulletCooldown && !isDead) {
		entityBullet.sprite.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - entityBullet.sprite.getGlobalBounds().width / 2, sprite.getPosition().y);
		entityBullet.velocity = sf::Vector2f(0.f, -0.5f);
		entityBullet.currentFrame = 0;
		entityBullet.animationTime = 0.f;
		entityBullet.sprite.setTextureRect(sf::IntRect(0, 0, entityBullet.frameWidth, entityBullet.frameHeight));
		bullets.push_back(entityBullet);
		entityBullet.elapsedTime = 0.f;
	}
	for (auto it = bullets.begin(); it != bullets.end();) {
		it->sprite.move(it->velocity);
		it->bulletAnimation(time.asSeconds());
		if (it->sprite.getPosition().y < 0) {
			it = bullets.erase(it);
		}
		else {
			++it;
		}
	}
}
void player::moveLeft() {
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !isDead)
		{
			velocity.x -= 0.8f;
			noMovementClock.restart();

		}
		return;
	}
}
void player::moveRight() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !isDead)
	{
		velocity.x += 0.8f;
		noMovementClock.restart();

	}
	return;
}
void player::moveUp() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isDead)
	{
		velocity.y -= 0.8f;
		noMovementClock.restart();

	}
	return;
}
void player::moveDown() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isDead)
	{
		velocity.y += 0.8f;
		noMovementClock.restart();

	}
	return;
}