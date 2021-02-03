#pragma once
#include "Stage.h"

class Player {
private:
	//マウス変数
	int MousePosX;
	int MousePosY;
	int MouseInput;
	int MouseInputOld;
	float startPosX;
	float startPosY;
	float endPosX;
	float endPosY;
	int Drawflag;
	int character;
	int canDrop;

	//プレイヤー変数
	float playerPosX;
	float playerPosY;
	float playerOldPosX;
	float playerOldPosY;
	int radius;
	float drop;
	int isArrows;
	
	//移動変数
	int maxflame;
	int flame;
	float PI;
	float x;

	//棒変数
	int arrows;
public:
	Player(
		float startPosX,
		float startPosY,
		float endPosX,
		float endPosY,
		float playerPosX,
		float playerPosY,
		int radius,
		int arrows,
		int isArrows
	);

	~Player();
	void update(Stage* stage);
	void move(Stage* stage);
	void collide2Stage(Stage* stage);
	void draw();

	int getMousePosX();
	int getMousePosY();
	int getStartPosX();
	int getStartPosY();
	int getEndPosX();
	int getEndPosY();
	int getPlayerPosX();
	int getPlayerPosY();
	int getRadius();
	int getArrows();
	int getMouseInput();
	int getMouseInputOld();
	int getIsArrows();
	int getDrop();
	int getPlayerOldPosY();

	void setMousePosX(float mouseposx);
	void setMousePosY(float mouseposy);
	void setStartPosX(float startposx);
	void setStartPosY(float startposy);
	void setEndPosX(float endposx);
	void setEndPosY(float endposy);
	void setPlayerPosX(float playerposx);
	void setPlayerPosY(float playerposy);
	void setRadius(int radius);
	void setArrows(int arrows);
	void setIsArrows(int isArrows);

};
