#include "level.h"

void level::initLevel() {
    invaders.clear();
    switch (levelNumber) {
    case 1: {
        invader1.randomisingInvaderType();
        invader1.sprite.setPosition(160, 20);
        invaders.push_back(invader1);
        invader2.randomisingInvaderType();
        invader2.sprite.setPosition(230, 20);
        invaders.push_back(invader2);
        invader3.randomisingInvaderType();
        invader3.sprite.setPosition(300, 20);
        invaders.push_back(invader3);
        break;
    }
    case 2: {
        
        invader4.randomisingInvaderType();
        invader4.sprite.setPosition(100, 20);
        invaders.push_back(invader4);
        invader5.randomisingInvaderType();
        invader5.sprite.setPosition(190, 20);
        invaders.push_back(invader5);
        invader6.randomisingInvaderType();
        invader6.sprite.setPosition(270, 20);
        invaders.push_back(invader6);
        invader7.randomisingInvaderType();
        invader7.sprite.setPosition(340, 20);
        invaders.push_back(invader7);
        invader8.randomisingInvaderType();
        invader8.sprite.setPosition(410, 20);
        invaders.push_back(invader8);
        break;
    }
    case 3: {
        invader9.randomisingInvaderType();
        invader9.sprite.setPosition(100, 20);
        invaders.push_back(invader9);
        invader10.randomisingInvaderType();
        invader10.sprite.setPosition(190, 20);
        invaders.push_back(invader10);
        invader11.randomisingInvaderType();
        invader11.sprite.setPosition(270, 20);
        invaders.push_back(invader11);
        invader12.randomisingInvaderType();
        invader12.sprite.setPosition(340, 20);
        invaders.push_back(invader12);
        invader13.randomisingInvaderType();
        invader13.sprite.setPosition(410, 20);
        invaders.push_back(invader13);
        /*invader9.randomisingInvaderType();
        invader9.sprite.setPosition(100, 20);
        invaders.push_back(invader9);
        invader10.randomisingInvaderType();
        invader10.sprite.setPosition(190, 20);
        invaders.push_back(invader10);
        invader11.randomisingInvaderType();
        invader11.sprite.setPosition(270, 20);
        invaders.push_back(invader12);
        invader11.randomisingInvaderType();
        invader11.sprite.setPosition(340, 20);
        invaders.push_back(invader11);
        invader12.randomisingInvaderType();
        invader12.sprite.setPosition(410, 20);
        invaders.push_back(invader12);
        invader13.randomisingInvaderType();*/
        /*invader13.sprite.setPosition(270, 20);
        invaders.push_back(invader13);
        invader14.randomisingInvaderType();
        invader14.sprite.setPosition(270, 20);
        invaders.push_back(invader14);*/
        break;
    }
    }
}