#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "player.h"
#include "invader.h"
class level {
private:
	invader invader1;
	invader invader2;
	invader invader3;
	invader invader4;
	invader invader5;
	invader invader6;
	invader invader7;
	invader invader8;
	invader invader9;
	invader invader10;
	invader invader11;
	invader invader12;
	invader invader13;
	invader invader14;
public:
	std::vector<invader> invaders;
	int levelNumber;
	bool levelFinished;
	void initLevel();
	int distanceBetweenInvaders;
	level() {
		levelNumber = 1;
		distanceBetweenInvaders = 20;
		initLevel();
	}

};


#endif
