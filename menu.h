
#ifndef MENU_H
#define MENU_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "highScores.h"
#include <regex>
import gameState;
class game;
class menu {
public:
    menu() = default;
    menu(float, float);
    void draw(sf::RenderWindow&);
    void moveUp();
    void moveDown();
    int getSelectedItem() const;
    void options(game&);
    void manageMenus(game&);
    highScores highScoresInMenu;
    void changeDifficulty(game&);
    void mainMenu(game&);
    void optionsMenu(game&);
    void changeNickname(game&);
    sf::Texture backgroundTexture;
    void displayHighScores(game& SpaceInvaders) const;
    void gameOver(game&, bool);
private:
    std::vector<sf::Text> menuItems;
    sf::Font font;
    int selectedItemIndex;
    std::vector<std::string> items;
    void initMenuItems(int, int);
};


#endif
