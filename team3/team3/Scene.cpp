#include "Scene.h"


Scene::Scene(int sceneNo) {
	this->sceneNo = sceneNo;
}

void Scene::init() {
	// Load Graph Handle
	LoadDivGraph("title.png", 21, 21, 1, 1500, 800, titleAnimGh);
	LoadDivGraph("Count2.png", 6, 6, 1, 192, 32, arrowsAnimGh);
	int gameclearGh = LoadGraph("gameclear.png");
	int gameoverGh = LoadGraph("gameover.png");

	// Load Sound
	titleSound = LoadSoundMem("title.mp3");
	stageSound = LoadSoundMem("stage.mp3");

	//variable
	titleAnimTimer = 0;
	titleAnimCounter = 0;

	// Game Object 
	player = new Player(176, 650, 176, 654, 176, 654, 16, 0, 0);
	key = new Key(384, 425, 10, 0);
	door = new Door(576, 600, 0);
	stage = new Stage();
	stage->init();
	stage->setMap(0);
}

void Scene::sceneManager() {
	switch (sceneNo) {
	case 0:
		titleTransaction();
	case 98:
		endingTransaction();
	case 99:
		gameOverTransaction();
	default:
		playTransaction();
	}
}

void Scene::titleTransaction() {
	// XVˆ—
	player->update(stage);
	//key->update();
	//door->update();
	
	// •`‰æˆ—
	playSound(titleSound);
	//this->drawTitle();
	stage->draw();
	
	player->draw();
	key->draw(player);
	door->draw();
}


void Scene::endingTransaction() {
	//// XVˆ—

	//// •`‰æˆ—
	//playSound(endingSound);
	//this->drawEnding();
}

void Scene::gameOverTransaction() {
	//// XVˆ—

	//// •`‰æˆ—
	//playSound(gameOverSound);
	//this->drawGameOver();
}

void Scene::playTransaction() {
	//// XVˆ—
	//player->update();
	//key->update();
	//door->update();

	//// •`‰æˆ—
	//playSound(stageSound);
	//this->drawStage();
	//stage->draw();
	//player->draw();
	//key->draw();
	//door->draw();
}

void Scene::playSound(int soundMemory) {
	if (CheckSoundMem(soundMemory) == 0)
	{
		ChangeVolumeSoundMem(125, soundMemory);
		PlaySoundMem(soundMemory, DX_PLAYTYPE_LOOP, TRUE);
	}
}


void Scene::drawTitle() {
	titleAnimTimer++;

	if (titleAnimTimer == 6) {
		titleAnimCounter++;
		if (titleAnimCounter == 21)
		{
			titleAnimCounter = 0;
		}
		titleAnimTimer = 0;
	}

	DrawGraph(0, 0, titleAnimGh[titleAnimCounter], true);
}
