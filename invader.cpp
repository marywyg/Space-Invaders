#include "invader.h"

sf::Time invader::shootingIntervalGenerator(sf::Time minInterval, sf::Time maxInterval) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(minInterval.asSeconds(), maxInterval.asSeconds());
	return sf::seconds(distr(gen));
}
bool invader::atLeftBorder() {
	return true;
}
bool invader::atRightBorder() {
	return true;
}
void invader::fireBullet(const sf::Time& time) {

}
void invader::randomisingInvaderType() {
    std::cout << "Randomising invader type for invader " << this << std::endl;
	std::cout << invaderType << std::endl;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, 3);
	invaderType = distr(gen);
	std::cout << invaderType << std::endl;
	switch (invaderType) {
    case 1: {
        if (!texture.loadFromFile("invader1.png")) {
            std::cout << ":(" << std::endl;
        }
        else {
            sprite.setTexture(texture);
            std::cout << ":)" << std::endl;
        }
        health = 40;
        break;
    }
    case 2: {
        if (!texture.loadFromFile("invader2.png")) {
            std::cout << "Nie uda³o siê za³adowaæ tekstury invader2.png" << std::endl;
        }
        else {
            sprite.setTexture(texture);
            std::cout << "Invader typ 2 ustawiony" << std::endl;
        }
        health = 100;
        break;
    }
    case 3: {
        if (!texture.loadFromFile("invader3.png")) {
            std::cout << "Nie uda³o siê za³adowaæ tekstury invader3.png" << std::endl;
        }
        else {
            sprite.setTexture(texture);
            std::cout << "Invader typ 3 ustawiony" << std::endl;
        }
        health = 20;
        break;
    }
	}
	return;
}