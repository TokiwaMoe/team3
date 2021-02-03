#include "DxLib.h"
#include "stdio.h"
#include "Player.h"
#include "math.h"

Player::Player(
	float startPosX,
	float startPosY,
	float endPosX,
	float endPosY,
	float playerPosX,
	float playerPosY,
	int radius,
	int arrows,
	int isArrows,
	int isAlive
) {
	this->startPosX = startPosX;
	this->startPosY = startPosY;
	this->endPosX = endPosX;
	this->endPosY = endPosY;
	this->playerPosX = playerPosX;
	this->playerPosY = playerPosY;
	this->radius = radius;
	this->arrows = arrows;
	this->isArrows = isArrows;
	playerOldPosY = 0;
	PI = 3.141592;
	maxflame = 50;
	flame = 0;
	Drawflag = 0;
	MouseInput = 0;
	MouseInputOld = 0;

	flame++;

	character = LoadGraph("character.png");
}

Player::~Player() {}

void Player::update(Stage* stage) {
	move();
	collide2Stage(stage);
}

void Player::move() {

	playerOldPosX = playerPosX;
	playerOldPosY = playerPosY;
	
	MouseInputOld = MouseInput;
	MouseInput = GetMouseInput();


	GetMousePoint(&MousePosX,
		&MousePosY);

	if (arrows == 0) {
		//trigger
		if (MouseInputOld != 1 && MouseInput == 1) {
			playerPosX = startPosX;
			playerPosY = startPosY;
			arrows++;
			Drawflag = 1;
		}

		//press
		if (MouseInputOld == 1 && MouseInput == 1) {
			endPosX = MousePosX;
			endPosY = MousePosY;
		}

		//release
		if (MouseInputOld == 1 && MouseInput != 1) {
			endPosX = MousePosX;
			endPosY = MousePosY;
		}
	}

	else if (arrows < 6) {
		//trigger
		if (MouseInputOld != 1 && MouseInput == 1) {
			startPosX = endPosX;
			startPosY = endPosY;
			playerPosX = endPosX;
			playerPosY = endPosY;
			arrows++;
			Drawflag = 1;
		}

		//press
		if (MouseInputOld == 1 && MouseInput == 1) {
			endPosX = MousePosX;
			endPosY = MousePosY;
		}

		//release
		if (MouseInputOld == 1 && MouseInput != 1) {
			endPosX = MousePosX;
			endPosY = MousePosY;
		}
	}

	//プレイヤー移動処理
	if (MouseInputOld != 1 && MouseInput == 1) {
		flame = 0;
	}

	if (MouseInputOld == 0 && MouseInput == 0) {
		flame = flame + 1;
		isArrows = 1;
	}

	if (isArrows == 1) {
		if (flame >= 0 && flame <= maxflame) {

			x = static_cast<float>(flame) / static_cast<float>(maxflame);

			playerPosX = startPosX + (endPosX - startPosX) * (sin(x * PI / 2));
			playerPosY = startPosY + (endPosY - startPosY) * (sin(x * PI / 2));

		}

		if (playerPosY >= endPosY) {
			isArrows = 0;
		}
	}

	if (isArrows == 0) {
		drop = 9.8 * (flame / 50.0);
		playerPosY = playerPosY + drop;
	}


	if (arrows > 5) {
		Drawflag = 0;
	}
}

void Player::collide2Stage(Stage* stage) {
	DrawFormatString(100, 100, GetColor(255, 255, 255), "playerPosX: %f", playerPosX);
	DrawFormatString(100, 120, GetColor(255, 255, 255), "playerPosY: %f", playerPosY);
	DrawFormatString(100, 140, GetColor(255, 255, 255), "playerOldPosX: %f", playerOldPosX);
	DrawFormatString(100, 160, GetColor(255, 255, 255), "playerOldPosY: %f", playerOldPosY);
	
	// 四隅の座標のマップチップ番号
	int leftTopX = (static_cast<int>(playerPosX) - radius)/stage->getBlockSize();
	int leftTopY = (static_cast<int>(playerPosY) - radius)/stage->getBlockSize();
	
	int rightTopX = (static_cast<int>(playerPosX) + radius) / stage->getBlockSize();
	int rightTopY = (static_cast<int>(playerPosY) - radius) / stage->getBlockSize();
	
	int rightBottomX = (static_cast<int>(playerPosX) + radius) / stage->getBlockSize();
	int rightBottomY = (static_cast<int>(playerPosY) + radius) / stage->getBlockSize();
	
	int leftBottomX = (static_cast<int>(playerPosX) - radius) / stage->getBlockSize();
	int leftBottomY = (static_cast<int>(playerPosY) + radius) / stage->getBlockSize();

	// leftTop
	if (stage->getMapChip(leftTopY, leftTopX) == 1 ) {
		playerPosX = playerOldPosX + 1;
		playerPosY = playerPosY + 1;
		/*endPosX = playerOldPosX;
		endPosY = playerOldPosY;*/
	}

	// righttop
	if (stage->getMapChip(rightTopY, rightTopX) == 1) {
		playerPosX = playerPosX - 1;
		playerPosY = playerPosY + 1;
		//endPosY = playerOldPosY;
	}

	//// 下
	//if (stage->getMapChip(rightBottomY, rightBottomX) == 1 && stage->getMapChip(leftBottomY, leftBottomX) == 1) {
	//	playerPosY = playerOldPosY;
	//	endPosY = playerOldPosY;
	//}
	//
	//// 左
	//if (stage->getMapChip(leftTopY , leftTopX) == 1 && stage->getMapChip(leftBottomY, leftBottomX)) {
	//	playerPosX = playerOldPosX;
	//	endPosX = playerOldPosX;
	//}


	//// 右
	//if (stage->getMapChip(rightBottomY, rightBottomX) == 1 && stage->getMapChip(rightTopY, rightTopX) == 1) {
	//	playerPosX = playerOldPosX ;
	//	endPosX = playerOldPosX;
	//}



////マップの当たり判定//
////右
//if (stage->getMap
//	[static_cast<int>(player->getPlayerPosY() - player->getRadius() * 2) / blocksize]
//[static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1
	 
//	&&
//	map[static_cast<int>(player->getPlayerPosY() + player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

//	player->setPlayerPosX(player->getPlayerPosX() - 1);
//	player->setEndPosX(player->getPlayerPosX());

//}

////左
//if (map[static_cast<int>(player->getPlayerPosY() - player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1 &&
//	map[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1) {

//	player->setPlayerPosX(player->getPlayerPosX() + 1);
//	player->setEndPosX(player->getPlayerPosX());

//}

////下
//if (map[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
//	map[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

//	player->setPlayerPosY(player->getPlayerPosY() - player->getDrop());
//	player->setPlayerPosY(player->getPlayerOldPosY());
//	player->setEndPosY(player->getPlayerPosY());

//}

////上
//if (map[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
//	map[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

//	player->setPlayerPosY(player->getPlayerPosY() + 1);
//	player->setEndPosY(player->getPlayerPosY());

//}
//
//}
//	}

}

void Player::isAlive()
{
	if (playerPosY - radius >= 800) {
		alive = 0;
	}
}

int Player::getMousePosX() { return MousePosX; }
int Player::getMousePosY() { return  MousePosY; }
int Player::getStartPosX() { return  startPosX; }
int Player::getStartPosY() { return startPosY; }
int Player::getEndPosX() { return endPosX; }
int Player::getEndPosY() { return endPosY; }
int Player::getPlayerPosX() { return playerPosX; }
int Player::getPlayerPosY() { return playerPosY; }
int Player::getRadius() { return radius; }
int Player::getArrows() { return arrows; }
int Player::getMouseInput() { return MouseInput; }
int Player::getMouseInputOld() { return  MouseInputOld; }
int Player::getIsArrows() { return isArrows; }
int Player::getDrop() { return drop; }
int Player::getPlayerOldPosY() { return playerOldPosY; }
int Player::getisAlive() { return alive; }

void Player::setMousePosX(float mouseposx) { this->MousePosX = mouseposx; }
void Player::setMousePosY(float mouseposy) { this->MousePosY = mouseposy; }
void Player::setStartPosX(float startposx) { this->startPosX = startposx; }
void Player::setStartPosY(float startposy) { this->startPosY = startposy; }
void Player::setEndPosX(float endposx) { this->endPosX = endposx; }
void Player::setEndPosY(float endposy) { this->endPosY = endposy; }
void Player::setPlayerPosX(float playerposx) { this->playerPosX = playerposx; }
void Player::setPlayerPosY(float playerposy) { this->playerPosY = playerposy; }
void Player::setRadius(int radius) { this->radius = radius; }
void Player::setArrows(int arrows) { this->arrows = arrows; }
void Player::setIsArrows(int isArrows) { this->isArrows = isArrows; }
void Player::setIsAlive(int isAlive) { this->alive = isAlive; }

void Player::draw() {
	if (Drawflag == 1) {
		DrawLine(startPosX, startPosY, endPosX, endPosY, GetColor(255, 255, 255), 2);
	}

	DrawGraph(playerPosX - radius, playerPosY - radius, character, TRUE);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "drop:%f", drop);
}
