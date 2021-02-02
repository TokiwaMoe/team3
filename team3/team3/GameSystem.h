#pragma once
#include "Scene.h"


class GameSystem
{
protected:
	const char* TITLE;

	const int WIN_WIDTH; //�E�B���h�E����
	const int WIN_HEIGHT;//�E�B���h�E�c��

	char keys[256] = { 0 }; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 };//1���[�v�i�t���[���j�O�̃L�[�{�[�h���

	Scene* scene;
	
	
public:
	GameSystem();

	void init();
	void gameLoopPre();
	void gameLoop();
	void gameLoopPost();
	
};

