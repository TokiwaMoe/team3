#pragma once
#include "Player.h"

class Key {
private:
	int PosX;
	int PosY;
	int Radius;
	int isGet;
	int key;

public:
	Key(int posx, int posy, int radius, int isget);
	~Key();
	void update(Player* player);
	void draw(Player* player);

	int getPosX();
	int getPosY();
	int getRadius();
	int getIsGet();

	void setPosX(int posx);
	void setPosY(int posy);
	void setRadius(int radius);
	void setIsGet(int isget);
};