#pragma once
#include "DxLib.h"

class Stage
{
private:
	int map[25][47];

	int blocksize = 32;
	int blockGh;

	enum Map2Info
	{
		NONE,
		BLOCK
	};
	
public:
	Stage();
	~Stage();

	void init();
	void draw();

	void setMap(int sceneNo);
	void mapCopy(int map[25][47], int map_tmp[25][47]);

	int getBlockSize();
	int getMapChip(int y, int x);
};

