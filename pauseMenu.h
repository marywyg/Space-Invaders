#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "menu.h"
#include "invader.h"
class pauseMenu : private menu {
public:
	pauseMenu()=default;
	pauseMenu(float, float);
};

pauseMenu::pauseMenu(float width, float height) {
    /*if (!font.loadFromFile("NovaSlim-Regular.ttf")) {
        std::cout << "Cannot load font file :(" << std::endl;
    }
    else {
        std::cout << "Font file loaded :)" << std::endl;
    }
    items = { "Start Game", "High Scores", "Options", "Exit" };
    initMenuItems(width, height);*/
}
#endif

