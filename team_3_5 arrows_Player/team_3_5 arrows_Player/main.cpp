#include "DxLib.h"
#include "stdio.h"
#include "math.h"

const char TITLE[] = "5 ARROWS";

const int WIN_WIDTH = 1500; //ウィンドウ横幅
const int WIN_HEIGHT = 800;//ウィンドウ縦幅


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0);				//画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0x00, 0x00, 0x00);		// 画面の背景色を設定する

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//画像などのリソースデータの変数宣言と読み込み
	int block = LoadGraph("block.png");
	int background = LoadGraph("background.png");
	int character = LoadGraph("character.png");
	int key = LoadGraph("key.png");
	int door = LoadGraph("door2.png");

	//ゲームループで使う変数の宣言
	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報
	//マウス変数
	int MousePosX;
	int MousePosY;
	int MouseInput = 0;
	int MouseInputOld = 0;
	float startPosX = 64;
	float startPosY = 732;
	float endPosX = 64;
	float endPosY = 732;
	int Drawflag = 0;

	//プレイヤー変数
	float PlayerPosX = 64;
	float PlayerPosY = 732;
	int PlayerRadius = 16;
	int PlayerG = 3;

	//鍵変数
	int KeyPosX = 64;
	int KeyPosY = 64;
	int KeyRadius = 10;
	int getflag = 0;

	//移動変数
	const int maxflame = 50;
	int flame = 0;
	float PI = 3.141592;
	float x = 0;

	//棒変数
	int arrows = 0;

	//マップ変数
	int blocksize = 32;

	// ゲームループ
	while (1)
	{
		//最新のキーボード情報だったものは１フレーム前のキーボード情報として保存

		//最新のキーボード情報を取得
		GetHitKeyStateAll(keys);
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		
		MouseInputOld = MouseInput;
		MouseInput = GetMouseInput();
		
		//画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		//更新処理
		////マウス処理 
		GetMousePoint(&MousePosX, &MousePosY);

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
		
		//マップの処理
		int map[25][47] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		};

		int mapcountx = sizeof(map[0]) / sizeof(map[0][0]);
		int mapcounty = sizeof(map) / sizeof(map[0]);

		enum MapInfo
		{
			NONE,
			BLOCK
		};

		for (int y = 0; y < 47; y++)
		{
			for (int x = 0; x < 25; x++)
			{

				//マップの当たり判定//
				//右
				if (map[static_cast<int>(PlayerPosY - PlayerRadius)/ blocksize][static_cast<int>(PlayerPosX + PlayerRadius + 1)  / blocksize] == 1 &&
					map[static_cast<int>(PlayerPosY + PlayerRadius) / blocksize][static_cast<int>(PlayerPosX + PlayerRadius + 1) / blocksize] == 1) {
					
					PlayerPosX = PlayerPosX - 1;
					endPosX = PlayerPosX;
					
				}

				//左
				if (map[static_cast<int>(PlayerPosY - PlayerRadius) / blocksize][static_cast<int>(PlayerPosX - PlayerRadius - 1) / blocksize] == 1 &&
					map[static_cast<int>(PlayerPosY + PlayerRadius) / blocksize][static_cast<int>(PlayerPosX - PlayerRadius - 1) / blocksize] == 1) {

					PlayerPosX = PlayerPosX + 1;
					endPosX = PlayerPosX;
					
				}

				//下
				if (map[static_cast<int>(PlayerPosY + PlayerRadius + 1) / blocksize][static_cast<int>(PlayerPosX - PlayerRadius) / blocksize] == 1 &&
					map[static_cast<int>(PlayerPosY + PlayerRadius + 1) / blocksize][static_cast<int>(PlayerPosX + PlayerRadius) / blocksize] == 1) {

					PlayerPosY = PlayerPosY - 1;
					endPosY = PlayerPosY;

				}
				

				//上
				if (map[static_cast<int>(PlayerPosY - PlayerRadius - 1) / blocksize][static_cast<int>(PlayerPosX - PlayerRadius) / blocksize] == 1 &&
					map[static_cast<int>(PlayerPosY - PlayerRadius - 1) / blocksize][static_cast<int>(PlayerPosX + PlayerRadius) / blocksize] == 1) {

					PlayerPosY = PlayerPosY + 1;
					endPosY = PlayerPosY;

				}
				
			}
		}

		if (MouseInput == 2) {
			arrows = 0;
		}

		//鍵の処理
		if (PlayerPosX <= KeyPosX + PlayerRadius * 2 && KeyPosX <= PlayerPosX + PlayerRadius) {
			if (PlayerPosY <= KeyPosY + PlayerRadius * 2 && KeyPosY <= PlayerPosY + PlayerRadius) {
				getflag = 1;
			}
		}
		
		//描画処理
		//背景描画
		DrawGraph(0, 0, background, true);

		//マップ描画
		for (int y = 0; y < 47; y++)
		{
			for (int x = 0; x < 25; x++)
			{
				if (map[x][y] == BLOCK)
				{
					DrawGraph(y * blocksize, x * blocksize, block, TRUE);

					DrawFormatString(0,
						200,
						GetColor(255, 255, 255),
						"LeftTop:map[%d][%d]",
						static_cast<int>((PlayerPosY - 10) / blocksize),
						static_cast<int>((PlayerPosX - 10) / blocksize)
					);

					DrawFormatString(0,
						220,
						GetColor(255, 255, 255),
						"LeftBottom:map[%d][%d]",
						static_cast<int>((PlayerPosY + 10) / blocksize),
						static_cast<int>((PlayerPosX - 10) / blocksize)
					);

					DrawFormatString(0,
						240,
						GetColor(255, 255, 255),
						"RightTop:map[%d][%d]",
						static_cast<int>((PlayerPosY - 10) / blocksize),
						static_cast<int>((PlayerPosX + 10) / blocksize)
					);

					DrawFormatString(0,
						260,
						GetColor(255, 255, 255),
						"RightBottom:map[%d][%d]",
						static_cast<int>((PlayerPosY + 10) / blocksize),
						static_cast<int>((PlayerPosX + 10) / blocksize));
				}
			}
		}
		
		//棒描画
		if (Drawflag == 1) {
			DrawLine(startPosX, startPosY, endPosX, endPosY, GetColor(255, 255, 255), 2);
		}

		//プレイヤー描画
		DrawGraph(PlayerPosX - 16, PlayerPosY - 16, character, true);

		//鍵描画
		if (getflag == 0) {
			DrawGraph(KeyPosX, KeyPosY, key, true);
		}

		if (getflag == 1) {
			KeyPosX = PlayerPosX;
			KeyPosY = PlayerPosY;
			DrawExtendGraph(KeyPosX - 5, KeyPosY - 30, KeyPosX + 5, KeyPosY - 20, key, true);
		}

		//扉描画
		DrawGraph(1370, 704, door, true);

		//デバック描画
		DrawFormatString(0, 0, GetColor(255, 255, 255), "X:%d Y:%d", MousePosX, MousePosY);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "マウスの状態%d", MouseInput);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "線の開始位置 X:%f Y:%f", startPosX, startPosY);
		DrawFormatString(0, 60, GetColor(255, 255, 255), "線の終了位置 X:%f Y:%f", endPosX, endPosY);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "プレイヤーの位置 X:%f Y:%f", PlayerPosX, PlayerPosY);

		DrawFormatString(0,
			100,
			GetColor(255, 255, 255),
			"Xの式:%f = %f + (%f - %f) * (sin (%f * %f / 2))",
			PlayerPosX, startPosX, endPosX, startPosX, x, PI);

		DrawFormatString(0,
			120,
			GetColor(255, 255, 255),
			"Yの式:%f = %f + (%f - %f) * (sin (%f * %f / 2))",
			PlayerPosY, startPosY, endPosY, startPosY, x, PI);

		DrawFormatString(0, 140, GetColor(255, 255, 255), "%f", x);
		DrawFormatString(0, 160, GetColor(255, 255, 255), "Flame:%d", flame);
		DrawFormatString(0, 180, GetColor(255, 255, 255), "arrows:%d", arrows);

		//---------  ここまでにプログラムを記述  ---------//
		ScreenFlip();//（ダブルバッファ）裏面
		// 20ミリ秒待機（疑似60FPS）
		WaitTimer(20);
		// Windows システムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}
		// ＥＳＣキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}