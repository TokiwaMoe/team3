#pragma once
#include "Player.h"

class Door {
private:
	int PosX;
	int PosY;
	int door[8];
	int Timer;
	int i;
	int Scene;
	
public:
	Door(int posx, int posy);
	~Door();

	void update(Player* player);
	void draw();

	int getPosX();
	int getPosY();

	void setPosX(int posx);
	void setPosY(int posy);
};
