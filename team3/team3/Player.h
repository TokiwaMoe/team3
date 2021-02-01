#pragma once

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

	//プレイヤー変数
	float PlayerPosX;
	float PlayerPosY;
	int Radius;
	int drop;
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
	void update();
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

	void setMousePosX(int mouseposx);
	void setMousePosY(int mouseposy);
	void setStartPosX(int startposx);
	void setStartPosY(int startposy);
	void setEndPosX(int endposx);
	void setEndPosY(int endposy);
	void setPlayerPosX(int playerposx);
	void setPlayerPosY(int playerposy);
	void setRadius(int radius);
	void setArrows(int arrows);
	void setIsArrows(int isArrows);
	void setDrop(int drop);

};
