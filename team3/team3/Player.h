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
		int arrows
	);

	~Player();
	void update();
	void draw();

	int geMousetPosX();
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

	void setMousePosX(int mouseposx);
	void setMousesY(int mouseposy);
	void setStartPosX(int startposx);
	void setStartPosY(int startposy);
	void setEndPosX(int endposx);
	void setEndPosY(int endposy);
	void setPlayerPosX(int playerposx);
	void setPlayerPosY(int playerposy);
	void setRadius(int radius);
	void setArrows(int arrows);

};
