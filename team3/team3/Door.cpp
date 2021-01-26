#include "Door.h"
#include "DxLib.h"

Door::Door(int posx, int posy, int isScene) {
	this->PosX = posx;
	this->PosY = posy;
	this->isScene = isScene;
	Timer = 0;
	i = 0;

	LoadDivGraph("door.png", 8, 8, 1, 64, 64, door);
}

Door::~Door() {}

void Door::update(Player* player, Key* key) {
	if (key->getIsGet() == 1) {
		if (player->getPlayerPosX() <= PosX + 64 && PosX <= player->getPlayerPosX() + player->getRadius()) {
			if (player->getPlayerPosY() <= PosY + 64 && PosY <= player->getPlayerPosX() + player->getRadius()) {
				isScene = 1;
			}
		}
	}

	//扉アニメーション
	Timer += 1;

	if (Timer == 6)
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
int Door::getIsScene() { return isScene; }

void Door::setPosX(int posx) { this->PosX = posx; }
void Door::setPosY(int posy) { this->PosY = posy; }
void Door::setIsScene(int isScene) { this->isScene = isScene; }

void Door::draw() {
	DrawGraph(PosX, PosY, door[i], TRUE);

	if (isScene == 1) {
		DrawFormatString(PosX, PosY - 20, GetColor(255, 255, 255), "当たったよ！");
	}
}

