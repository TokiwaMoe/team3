#include "DxLib.h"
#include "Key.h"
Key::Key(int posx, int posy, int radius, int isget) {
	this->PosX = posx;
	this->PosY = posy;
	this->Radius = radius;
	this->isGet = isget;

	key = LoadGraph("key.png");
}

Key::~Key() {}

void Key::update(Player* player) {
	if (player->getPlayerPosX() - player-> getRadius() <= PosX + Radius && PosX <= player->getPlayerPosX() + player->getRadius()) {
		if (player->getPlayerPosY() - player->getRadius() <= PosY + Radius * 2 && PosY <= player->getPlayerPosY() + player->getRadius()) {
			isGet = 1;
		}
	}
}

int Key::getPosX() { return PosX; }
int Key::getPosY() { return PosY; }
int Key::getRadius() { return Radius; }
int Key::getIsGet() { return isGet; }

void Key::setPosX(int posx) { this->PosX = posx; }
void Key::setPosY(int posy) { this->PosY = posy; }
void Key::setRadius(int radius) { this->Radius = radius; }
void Key::setIsGet(int isget) { this->isGet = isget; }

void Key::draw(Player* player) {
	if (isGet == 0) {
		DrawGraph(PosX - Radius, PosY - Radius, key, TRUE);
	}

	if (isGet == 1) {
		PosX = player->getPlayerPosX();
		PosY = player->getPlayerPosY();
		DrawExtendGraph(PosX - 5, PosY - 30, PosX + 5, PosY - 20, key, TRUE);
	}
}




