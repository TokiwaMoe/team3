#pragma once
#include "Player.h"
#include "Key.h"

class Door {
private:
	int PosX;
	int PosY;
	int door[8];
	int Timer;
	int i;
	int isScene;

public:
	Door(int posx, int posy, int isScene);
	~Door();

	void update(Player* player, Key* key);
	void draw();

	int getPosX();
	int getPosY();
	int getIsScene();

	void setPosX(int posx);
	void setPosY(int posy);
	void setIsScene(int isScene);
};
