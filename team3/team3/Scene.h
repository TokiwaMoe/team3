#pragma once
#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
#include "Key.h"
#include "Door.h"

class Scene 
{
private:
	int sceneNo;

	// Game object Instance
	Player* player;
	Key* key;
	Door* door;
	Stage* stage;

	//Sound
	int titleSound;
	int stageSound;
	
	//GraphHandle
	int titleAnimGh[21];
	int gameClearGh;
	int gameOverGh;
	int arrowsAnimGh[6];

	// Animation Variable
	int titleAnimTimer;
	int titleAnimCounter;

public:
	Scene(int sceneNo);
	~Scene();

	void init();
	void sceneManager();

	void titleTransaction();
	void endingTransaction();
	void gameOverTransaction();
	void playTransaction();

	void playSound(int soundMemory);
	void drawTitle();

};

