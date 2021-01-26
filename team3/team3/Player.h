#pragma once

class Player {
private:
	//�}�E�X�ϐ�
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

	//�v���C���[�ϐ�
	float PlayerPosX;
	float PlayerPosY;
	int Radius;

	//�ړ��ϐ�
	int maxflame;
	int flame;
	float PI;
	float x;

	//�_�ϐ�
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
