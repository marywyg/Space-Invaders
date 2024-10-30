#ifndef MANAGER_H
#define MANAGER_H
#include <SFML/Graphics.hpp>
class playerManager{
public:
	sf::RectangleShape playerHealthBar;
	sf::RectangleShape playerHealthBarBack;

	void initHealthBar();
};


#endif
