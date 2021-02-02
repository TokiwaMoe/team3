#include "DxLib.h"
#include "GameSystem.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	GameSystem* game_system = new GameSystem();
	if(DxLib_Init() == -1) { return - 1; }
	game_system->init();

	while (1) {
		game_system->gameLoopPre();

		game_system->gameLoop();
		
		game_system->gameLoopPost();
		if (ProcessMessage() == -1) { break; }
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { break; }
	}

	

		////ñ_ïœêî
		//char strNum2[10];






		//// ÉQÅ[ÉÄÉãÅ[Év
		//while (1)
		//{


		//	//çXêVèàóù
		//	switch (Scene) {
		//	//case) 0: Title
		//	case 0:






		//	player->update();


		//		key->update(player);


		//		door->update(player, key);


		//		if (door->getIsScene() == 1) {
		//			player->setStartPosX(64);
		//			player->setStartPosY(732);
		//			player->setEndPosX(64);
		//			player->setEndPosY(732);
		//			player->setPlayerPosX(64);
		//			player->setPlayerPosY(732);
		//			player->setArrows(0);
		//			key->setPosX(64);
		//			key->setPosY(80);
		//			key->setIsGet(0);
		//			door->setPosX(1370);
		//			door->setPosY(704);
		//			door->setIsScene(0);
		//			Scene = 1;
		//		}

		//		break;

		//	case 1:
		//		StopSoundMem(TitleSound);

		//		if (CheckSoundMem(StageSound) == 0)
		//		{
		//			ChangeVolumeSoundMem(110, StageSound);
		//			PlaySoundMem(StageSound, DX_PLAYTYPE_LOOP, TRUE);
		//		}

		//		//îwåiï`âÊ
		//		DrawGraph(0, 0, background, true);

		//		//É}ÉbÉvÇÃèàóù
		//		mapcountx = sizeof(map1[0]) / sizeof(map1[0][0]);
		//		mapcounty = sizeof(map1) / sizeof(map1[0]);

		//		for (int y = 0; y < 47; y++)
		//		{
		//			for (int x = 0; x < 25; x++)
		//			{

		//				//É}ÉbÉvÇÃìñÇΩÇËîªíË//
		//				//âE
		//				if (map1[static_cast<int>(player->getPlayerPosY() - player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1 &&
		//					map1[static_cast<int>(player->getPlayerPosY() + player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

		//					player->setPlayerPosX(player->getPlayerPosX() - 1);
		//					player->setEndPosX(player->getPlayerPosX());

		//				}

		//				//ç∂
		//				if (map1[static_cast<int>(player->getPlayerPosY() - player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1 &&
		//					map1[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1) {

		//					player->setPlayerPosX(player->getPlayerPosX() + 1);
		//					player->setEndPosX(player->getPlayerPosX());

		//				}

		//				//â∫
		//				if (map1[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
		//					map1[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {


		//					player->setPlayerPosY(player->getPlayerPosY() - player->getDrop());
		//					player->setPlayerPosY(player->getPlayerOldPosY() - 1);
		//					player->setEndPosY(player->getPlayerPosY());

		//				}


		//				//è„
		//				if (map1[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
		//					map1[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

		//					player->setPlayerPosY(player->getPlayerPosY() + 1);
		//					player->setEndPosY(player->getPlayerPosY());

		//				}

		//			}
		//		}

		//		//É}ÉbÉvï`âÊ
		//		for (int y = 0; y < 47; y++)
		//		{
		//			for (int x = 0; x < 25; x++)
		//			{
		//				if (map1[x][y] == BLOCK)
		//				{
		//					DrawGraph(y * blocksize, x * blocksize, block, TRUE);

		//				}
		//			}
		//		}

		//		player->update();

		//		//ñ_UI
		//		sprintf_s(strNum2, sizeof(strNum2), "%d", player->getArrows());

		//		for (int t = 0; t < 6; t++)
		//		{
		//			DrawGraph(0, 768, arrowsAnim[strNum2[t] - '0'], TRUE);
		//		}

		//		//ÉvÉåÉCÉÑÅ[Ç∆ñ_ÇÃï`âÊ
		//		player->draw();
		//		DrawFormatString(0, 20, GetColor(255, 255, 255), "PlayerOldPosY:%f", player->getPlayerOldPosY());

		//		key->update(player);
		//		//åÆï`âÊ
		//		key->draw(player);

		//		door->update(player, key);
		//		//î‡ï`âÊ
		//		door->draw();

		//		if (door->getIsScene() == 1) {
		//			player->setStartPosX(64);
		//			player->setStartPosY(686);
		//			player->setEndPosX(64);
		//			player->setEndPosY(686);
		//			player->setPlayerPosX(64);
		//			player->setPlayerPosY(686);
		//			player->setArrows(0);
		//			key->setPosX(1190);
		//			key->setPosY(140);
		//			key->setIsGet(0);
		//			door->setPosX(1370);
		//			door->setPosY(640);
		//			door->setIsScene(0);
		//			Scene = 2;
		//		}

		//		break;

		//	case 2:
		//		//îwåiï`âÊ
		//		DrawGraph(0, 0, background, true);

		//		mapcountx = sizeof(map2[0]) / sizeof(map2[0][0]);
		//		mapcounty = sizeof(map2) / sizeof(map2[0]);


		//		for (int y = 0; y < 47; y++)
		//		{
		//			for (int x = 0; x < 25; x++)
		//			{

		//				//É}ÉbÉvÇÃìñÇΩÇËîªíË//
		//				//âE
		//				if (map2[static_cast<int>((player->getPlayerPosY() - player->getRadius()) / blocksize)][static_cast<int>((player->getPlayerPosX() + player->getRadius() + 1) / blocksize)] == 1 &&
		//					map2[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

		//					player->setPlayerPosX(player->getPlayerPosX() - 1);
		//					player->setEndPosX(player->getPlayerPosX());

		//				}

		//				//ç∂
		//				if (map2[static_cast<int>((player->getPlayerPosY() - player->getRadius()) / blocksize)][static_cast<int>((player->getPlayerPosX() - player->getRadius() - 1) / blocksize)] == 1 &&
		//					map2[static_cast<int>((player->getPlayerPosY() + player->getRadius()) / blocksize)][static_cast<int>((player->getPlayerPosX() - player->getRadius() - 1) / blocksize)] == 1) {

		//					player->setPlayerPosX(player->getPlayerPosX() + 1);
		//					player->setEndPosX(player->getPlayerPosX());

		//				}

		//				//â∫
		//				if (map2[static_cast<int>((player->getPlayerPosY() + player->getRadius() + 1) / blocksize)][static_cast<int>((player->getPlayerPosX() - player->getRadius()) / blocksize)] == 1 &&
		//					map2[static_cast<int>((player->getPlayerPosY() + player->getRadius() + 1) / blocksize)][static_cast<int>((player->getPlayerPosX() + player->getRadius()) / blocksize)] == 1) {

		//					player->setPlayerPosY(player->getPlayerPosY() - 1);
		//					player->setEndPosY(player->getPlayerPosY());

		//				}

		//				else {
		//					if (player->getEndPosY() == player->getPlayerPosY()) {
		//						player->setPlayerPosY(player->getPlayerPosY() + 1);
		//						player->setEndPosY(player->getPlayerPosY());
		//					}
		//				}

		//				//è„
		//				if (map2[static_cast<int>((player->getPlayerPosY() - player->getRadius() - 1) / blocksize)][static_cast<int>((player->getPlayerPosX() - player->getRadius()) / blocksize)] == 1 &&
		//					map2[static_cast<int>((player->getPlayerPosY() - player->getRadius() - 1) / blocksize)][static_cast<int>((player->getPlayerPosX() + player->getRadius()) / blocksize)] == 1) {

		//					player->setPlayerPosY(player->getPlayerPosY() + 1);
		//					player->setEndPosY(player->getPlayerPosY());

		//				}

		//			}
		//		}

		//		//É}ÉbÉvï`âÊ
		//		for (int y = 0; y < 47; y++)
		//		{
		//			for (int x = 0; x < 25; x++)
		//			{
		//				if (map2[x][y] == BLOCK)
		//				{
		//					DrawGraph(y * blocksize, x * blocksize, block, TRUE);

		//				}
		//			}
		//		}

		//		player->update();

		//		/*if (player->getPlayerPosY() > WIN_HEIGHT) {
		//			Scene = 6;
		//		}*/

		//		//ÉvÉåÉCÉÑÅ[Ç∆ñ_ÇÃï`âÊ
		//		player->draw();

		//		key->update(player);
		//		//åÆï`âÊ
		//		key->draw(player);

		//		door->update(player, key);
		//		//î‡ï`âÊ
		//		door->draw();

		//		if (door->getIsScene() == 1) {
		//			player->setStartPosX(30);
		//			player->setStartPosY(48);
		//			player->setEndPosX(30);
		//			player->setEndPosY(48);
		//			player->setPlayerPosX(30);
		//			player->setPlayerPosY(48);
		//			player->setArrows(0);
		//			key->setPosX(1450);
		//			key->setPosY(690);
		//			key->setIsGet(0);
		//			door->setPosX(750);
		//			door->setPosY(320);
		//			door->setIsScene(0);
		//			Scene = 3;
		//		}

		//		break;

		//	case 3:
		//		//îwåiï`âÊ
		//		DrawGraph(0, 0, background, true);

		//		player->update();
		//		key->update(player);
		//		door->update(player, key);

		//		mapcountx = sizeof(map3[0]) / sizeof(map3[0][0]);
		//		mapcounty = sizeof(map3) / sizeof(map3[0]);



		//		for (int y = 0; y < 47; y++)
		//		{
		//			for (int x = 0; x < 25; x++)
		//			{

		//				//É}ÉbÉvÇÃìñÇΩÇËîªíË//
		//				//âE
		//				if (map3[static_cast<int>(player->getPlayerPosY() - player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1 &&
		//					map3[static_cast<int>(player->getPlayerPosY() + player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

		//					player->setPlayerPosX(player->getPlayerPosX() - 1);
		//					player->setEndPosX(player->getPlayerPosX());

		//				}

		//				//ç∂
		//				if (map3[static_cast<int>(player->getPlayerPosY() - player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1 &&
		//					map3[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1) {

		//					player->setPlayerPosX(player->getPlayerPosX() + 1);
		//					player->setEndPosX(player->getPlayerPosX());

		//				}

		//				//â∫
		//				if (map3[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
		//					map3[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

		//					player->setPlayerPosY(player->getPlayerPosY() - 1);
		//					player->setEndPosY(player->getPlayerPosY());

		//				}

		//				else {
		//					if (player->getEndPosY() == player->getPlayerPosY()) {
		//						player->setPlayerPosY(player->getPlayerPosY() + 1);
		//						player->setEndPosY(player->getPlayerPosY());
		//					}
		//				}

		//				//è„
		//				if (map3[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
		//					map3[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

		//					player->setPlayerPosY(player->getPlayerPosY() + 1);
		//					player->setEndPosY(player->getPlayerPosY());

		//				}

		//			}
		//		}

		//		if (door->getIsScene() == 1) {
		//			player->setStartPosX(134);
		//			player->setStartPosY(134);
		//			player->setEndPosX(134);
		//			player->setEndPosY(134);
		//			player->setPlayerPosX(134);
		//			player->setPlayerPosY(134);
		//			player->setArrows(0);
		//			key->setPosX(1404);
		//			key->setPosY(140);
		//			key->setIsGet(0);
		//			door->setPosX(1404);
		//			door->setPosY(580);
		//			door->setIsScene(0);
		//			Scene = 4;
		//		}

		//		//É}ÉbÉvï`âÊ
		//		for (int y = 0; y < 47; y++)
		//		{
		//			for (int x = 0; x < 25; x++)
		//			{
		//				if (map3[x][y] == BLOCK)
		//				{
		//					DrawGraph(y * blocksize, x * blocksize, block, TRUE);

		//				}
		//			}
		//		}

		//		/*if (player->getPlayerPosY() - player->getRadius() > WIN_HEIGHT) {
		//			Scene = 6;
		//		}*/

		//		//ÉvÉåÉCÉÑÅ[Ç∆ñ_ÇÃï`âÊ
		//		player->draw();

		//		//åÆï`âÊ
		//		key->draw(player);

		//		//î‡ï`âÊ
		//		door->draw();

		//		break;

		//	case 4:
		//		player->update();
		//		key->update(player);
		//		door->update(player, key);



		//		mapcountx = sizeof(map2[0]) / sizeof(map2[0][0]);
		//		mapcounty = sizeof(map2) / sizeof(map2[0]);



		//		for (int y = 0; y < 47; y++)
		//		{
		//			for (int x = 0; x < 25; x++)
		//			{

		//				//É}ÉbÉvÇÃìñÇΩÇËîªíË//
		//				//âE
		//				if (map4[static_cast<int>(player->getPlayerPosY() - player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1 &&
		//					map4[static_cast<int>(player->getPlayerPosY() + player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

		//					player->setPlayerPosX(player->getPlayerPosX() - 1);
		//					player->setEndPosX(player->getPlayerPosX());

		//				}

		//				//ç∂
		//				if (map4[static_cast<int>(player->getPlayerPosY() - player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1 &&
		//					map4[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1) {

		//					player->setPlayerPosX(player->getPlayerPosX() + 1);
		//					player->setEndPosX(player->getPlayerPosX());

		//				}

		//				//â∫
		//				if (map4[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
		//					map4[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

		//					player->setPlayerPosY(player->getPlayerPosY() - 1);
		//					player->setEndPosY(player->getPlayerPosY());

		//				}

		//				else {
		//					if (player->getEndPosY() == player->getPlayerPosY()) {
		//						player->setPlayerPosY(player->getPlayerPosY() + 1);
		//						player->setEndPosY(player->getPlayerPosY());
		//					}
		//				}

		//				//è„
		//				if (map4[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
		//					map4[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

		//					player->setPlayerPosY(player->getPlayerPosY() + 1);
		//					player->setEndPosY(player->getPlayerPosY());

		//				}

		//			}
		//		}

		//		if (door->getIsScene() == 1) {

		//			Scene = 5;
		//		}

		//		//É}ÉbÉvï`âÊ
		//		for (int y = 0; y < 47; y++)
		//		{
		//			for (int x = 0; x < 25; x++)
		//			{
		//				if (map4[x][y] == BLOCK)
		//				{
		//					DrawGraph(y * blocksize, x * blocksize, block, TRUE);

		//				}
		//			}
		//		}

		//		/*if (player->getPlayerPosY() - player->getRadius() > WIN_HEIGHT) {
		//			Scene = 6;
		//		}*/

		//		//ÉvÉåÉCÉÑÅ[Ç∆ñ_ÇÃï`âÊ
		//		player->draw();

		//		//åÆï`âÊ
		//		key->draw(player);

		//		//î‡ï`âÊ
		//		door->draw();

		//		break;

		//	case 5:
		//		DrawGraph(0, 0, gameclear, true);
		//		break;

		//	case 6:
		//		DrawGraph(0, 0, gameover, true);
		//		break;

		//	}


		//	//ï`âÊèàóù

	

	//DxÉâÉCÉuÉâÉäèIóπèàóù
	DxLib_End();

	return 0;
}