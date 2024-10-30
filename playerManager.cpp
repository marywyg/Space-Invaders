#include "playerManager.h"

void playerManager::initHealthBar() {
	playerHealthBar.setSize(sf::Vector2f(300.f, 25.f));
	playerHealthBar.setFillColor(sf::Color::Magenta);
	playerHealthBar.setPosition(sf::Vector2f(20.f, 20.f));
	playerHealthBarBack = playerHealthBar;
	playerHealthBarBack.setFillColor(sf::Color::Green);
}

