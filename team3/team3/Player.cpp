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
    int radius
) {
	this->startPosX = startPosX;
	this->startPosY = startPosY;
	this->endPosX = endPosX;
	this->endPosY = endPosY;
	this->PlayerPosX = playerPosX;
	this->PlayerPosY = playerPosY;
	this->Radius = radius;
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

void Player::update() {
	MouseInputOld = MouseInput;
	MouseInput = GetMouseInput();
	
	GetMousePoint(&MousePosX,
   &MousePosY);

	if (arrows == 0) {
		//trigger
		if (MouseInputOld != 1 && MouseInput == 1) {
			PlayerPosX = startPosX;
			PlayerPosY = startPosY;
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
			PlayerPosX = endPosX;
			PlayerPosY = endPosY;
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

		if (flame >= 0 && flame <= maxflame) {

			x = static_cast<float>(flame) / static_cast<float>(maxflame);

			PlayerPosX = startPosX + (endPosX - startPosX) * (sin(x * PI / 2));
			PlayerPosY = startPosY + (endPosY - startPosY) * (sin(x * PI / 2));

		}

	}


	if (arrows > 5) {

		Drawflag = 0;
	}

	if (MouseInput == 2) {
		arrows = 0;
	}
}

int Player::geMousetPosX() { return MousePosX; }
int Player::getMousePosY() { return  MousePosY; }
int Player::getStartPosX() { return  startPosX; }
int Player::getStartPosY() { return startPosY; }
int Player::getEndPosX() { return endPosX; }
int Player::getEndPosY() { return endPosY; }
int Player::getPlayerPosX() { return PlayerPosX; }
int Player::getPlayerPosY() { return PlayerPosY; }
int Player::getRadius() { return Radius; }

void Player::setMousePosX(int mouseposx) { this->MousePosX = mouseposx; }
void Player::setMousesY(int mouseposy) { this->MousePosY = mouseposy; }
void Player::setStartPosX(int startposx) { this->startPosX = startposx; }
void Player::setStartPosY(int startposy) { this->startPosY = startposy; }
void Player::setEndPosX(int endposx) { this->endPosX = endposx; }
void Player::setEndPosY(int endposy) { this->endPosY = endposy; }
void Player::setPlayerPosX(int playerposx) { this->PlayerPosX = playerposx; }
void Player::setPlayerPosY(int playerposy) { this->PlayerPosY = playerposy; }
void Player::setRadius(int radius) { this->Radius = radius; }

void Player::draw() {
	if (Drawflag == 1) {
		DrawLine(startPosX, startPosY, endPosX, endPosY, GetColor(255, 255, 255), 2);
	}

	DrawGraph(PlayerPosX - Radius, PlayerPosY - Radius, character, TRUE);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "マウスの状態 : %d", MouseInput);
	DrawFormatString(0,
		20,
		GetColor(255, 255, 255),
		"スタートの位置X : %f  スタートの位置 : %f",
		startPosX,
		startPosY);

	DrawFormatString(0,
		40,
		GetColor(255, 255, 255),
		"エンドの位置X : %f  エンドの位置 : %f",
		endPosX,
		endPosY);
	
	DrawFormatString(0,
		60,
		GetColor(255, 255, 255),
		"プレイヤーの位置X : %f  プレイヤーの位置 : %f",
		PlayerPosX,
		PlayerPosY);

	DrawFormatString(0,
		80,
		GetColor(255, 255, 255),
		"Xの式: %f = %f + (%f - %f) * (sin(%f * %f / 2));",
		PlayerPosX, startPosX, endPosX, startPosX, x, PI
	);

	DrawFormatString(0,
		100,
		GetColor(255, 255, 255),
		"Yの式: %f = %f + (%f - %f) * (sin(%f * %f / 2));",
		PlayerPosY, startPosY, endPosY, startPosY, x, PI
	);

	DrawFormatString(0, 120, GetColor(255, 255, 255), "X : %f", x);

	DrawFormatString(0, 140, GetColor(255, 255, 255), "flame : %d", flame);
}