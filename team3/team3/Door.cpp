#include "Door.h"
#include "DxLib.h"

Door::Door(int posx, int posy) {
	this->PosX = posx;
	this->PosY = posy;
	Timer = 0;
	i = 0;
	Scene = 0;

	LoadDivGraph("door.png", 8, 8, 1, 64, 64, door);
}

Door::~Door() {}

void Door::update(Player* player) {
	if (player->getPlayerPosX() <= PosX + player->getRadius() * 2 && PosX <= player->getPlayerPosX() + player->getRadius()) {
		if (player->getPlayerPosY() <= PosY + player->getRadius() * 2 && PosY <= player->getPlayerPosX() + player->getRadius()) {
			Scene = 1;
		}
	}

	//扉アニメーション
	Timer += 1;

	if (Timer == 4)
	{
		i = i + 1;
		if (i == 8)
		{
			i = 0;
		}
		Timer = 0;
	}
}


int Door::getPosX() { return PosX; }
int Door::getPosY() { return PosY; }

void Door::setPosX(int posx) { this->PosX = posx; }
void Door::setPosY(int posy) { this->PosY = posy; }

void Door::draw() {
	DrawGraph(PosX, PosY, door[i], TRUE);

	if (Scene == 1) {
		DrawFormatString(PosX, PosY - 20, GetColor(255, 255, 255), "当たったよ！");
	}
}

