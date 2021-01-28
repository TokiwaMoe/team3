#include "DxLib.h"
#include "Player.h"
#include "Key.h"
#include "Door.h"

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
	int title = LoadGraph("title.png");



	//ゲームループで使う変数の宣言
	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報
	Player* player = new Player(64, 544, 64, 732, 64, 732, 16, 0);
	Key* key = new Key(1170, 160, 10, 0);
	Door* door = new Door(1370, 544, 0);

	//マップ変数
	int blocksize = 32;
	int mapcountx;
	int mapcounty;

	enum Map2Info
	{
		NONE,
		BLOCK
	};

	int map1[25][47] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	int map2[25][47] = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	};

	int map3[25][47] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	};

	int map4[25][47] = {

		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	};

	//シーン切り替え変数
	int Scene = 0;


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

		//画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		//更新処理
		switch (Scene) {
		case 0:
			player->update();
			if (player->getMouseInput() == 2) {
				player->setStartPosX(64);
				player->setStartPosY(732);
				player->setEndPosX(64);
				player->setEndPosY(732);
				player->setPlayerPosX(64);
				player->setPlayerPosY(732);
				player->setArrows(0);
				key->setPosX(64);
				key->setPosY(80);
				door->setPosX(1370);
				door->setPosY(704);
				Scene = 1;
			}

			DrawGraph(0, 0, title, true);

			break;

		case 1:
			//背景描画
			DrawGraph(0, 0, background, true);

			//マップの処理
			mapcountx = sizeof(map1[0]) / sizeof(map1[0][0]);
			mapcounty = sizeof(map1) / sizeof(map1[0]);

			for (int y = 0; y < 47; y++)
			{
				for (int x = 0; x < 25; x++)
				{

					//マップの当たり判定//
					//右
					if (map1[static_cast<int>(player->getPlayerPosY() - player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1 &&
						map1[static_cast<int>(player->getPlayerPosY() + player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() - 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//左
					if (map1[static_cast<int>(player->getPlayerPosY() - player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1 &&
						map1[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() + 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//下
					if (map1[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
						map1[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

						player->setPlayerPosY(player->getPlayerPosY() - 1);
						player->setEndPosY(player->getPlayerPosY());

					}

					else {
						if (player->getEndPosY() == player->getPlayerPosY()) {
							player->setPlayerPosY(player->getPlayerPosY() + 0.1);
							player->setEndPosY(player->getPlayerPosY());
						}
					}

					//上
					if (map1[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
						map1[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

						player->setPlayerPosY(player->getPlayerPosY() + 1);
						player->setEndPosY(player->getPlayerPosY());

					}

				}
			}

			//マップ描画
			for (int y = 0; y < 47; y++)
			{
				for (int x = 0; x < 25; x++)
				{
					if (map1[x][y] == BLOCK)
					{
						DrawGraph(y * blocksize, x * blocksize, block, TRUE);

					}
				}
			}

			player->update();
			//プレイヤーと棒の描画
			player->draw();

			key->update(player);
			//鍵描画
			key->draw(player);

			door->update(player, key);
			//扉描画
			door->draw();

			if (door->getIsScene() == 1) {
				player->setStartPosX(64);
				player->setStartPosY(686);
				player->setEndPosX(64);
				player->setEndPosY(686);
				player->setPlayerPosX(64);
				player->setPlayerPosY(686);
				player->setArrows(0);
				key->setPosX(1190);
				key->setPosY(140);
				key->setIsGet(0);
				door->setPosX(1370);
				door->setPosY(640);
				door->setIsScene(0);
				Scene = 2;
			}
			
			break;

		case 2:
			//背景描画
			DrawGraph(0, 0, background, true);

			mapcountx = sizeof(map2[0]) / sizeof(map2[0][0]);
			mapcounty = sizeof(map2) / sizeof(map2[0]);


			for (int y = 0; y < 47; y++)
			{
				for (int x = 0; x < 25; x++)
				{

					//マップの当たり判定//
					//右
					if (map2[static_cast<int>((player->getPlayerPosY() - player->getRadius()) / blocksize)][static_cast<int>((player->getPlayerPosX() + player->getRadius() + 1) / blocksize)] == 1 &&
						map2[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() - 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//左
					if (map2[static_cast<int>((player->getPlayerPosY() - player->getRadius()) / blocksize)][static_cast<int>((player->getPlayerPosX() - player->getRadius() - 1) / blocksize)] == 1 &&
						map2[static_cast<int>((player->getPlayerPosY() + player->getRadius()) / blocksize)][static_cast<int>((player->getPlayerPosX() - player->getRadius() - 1) / blocksize)] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() + 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//下
					if (map2[static_cast<int>((player->getPlayerPosY() + player->getRadius() + 1) / blocksize)][static_cast<int>((player->getPlayerPosX() - player->getRadius()) / blocksize)] == 1 &&
						map2[static_cast<int>((player->getPlayerPosY() + player->getRadius() + 1) / blocksize)][static_cast<int>((player->getPlayerPosX() + player->getRadius()) / blocksize)] == 1) {

						player->setPlayerPosY(player->getPlayerPosY() - 1);
						player->setEndPosY(player->getPlayerPosY());

					}

					else {
						if (player->getEndPosY() == player->getPlayerPosY()) {
							player->setPlayerPosY(player->getPlayerPosY() + 1);
							player->setEndPosY(player->getPlayerPosY());
						}
					}

					//上
					if (map2[static_cast<int>((player->getPlayerPosY() - player->getRadius() - 1) / blocksize)][static_cast<int>((player->getPlayerPosX() - player->getRadius()) / blocksize)] == 1 &&
						map2[static_cast<int>((player->getPlayerPosY() - player->getRadius() - 1) / blocksize)][static_cast<int>((player->getPlayerPosX() + player->getRadius()) / blocksize)] == 1) {

						player->setPlayerPosY(player->getPlayerPosY() + 1);
						player->setEndPosY(player->getPlayerPosY());

					}

				}
			}

			//マップ描画
			for (int y = 0; y < 47; y++)
			{
				for (int x = 0; x < 25; x++)
				{
					if (map2[x][y] == BLOCK)
					{
						DrawGraph(y * blocksize, x * blocksize, block, TRUE);

					}
				}
			}
			
			player->update();

			//プレイヤーと棒の描画
			player->draw();

			key->update(player);
			//鍵描画
			key->draw(player);

			door->update(player, key);
			//扉描画
			door->draw();

			if (door->getIsScene() == 1) {
				player->setStartPosX(30);
				player->setStartPosY(48);
				player->setEndPosX(30);
				player->setEndPosY(48);
				player->setPlayerPosX(30);
				player->setPlayerPosY(48);
				player->setArrows(0);
				key->setPosX(1450);
				key->setPosY(690);
				key->setIsGet(0);
				door->setPosX(750);
				door->setPosY(320);
				door->setIsScene(0);
				Scene = 3;
			}
			
			break;

		case 3:
			//背景描画
			DrawGraph(0, 0, background, true);
			
			player->update();
			key->update(player);
			door->update(player, key);

			mapcountx = sizeof(map3[0]) / sizeof(map3[0][0]);
			mapcounty = sizeof(map3) / sizeof(map3[0]);



			for (int y = 0; y < 47; y++)
			{
				for (int x = 0; x < 25; x++)
				{

					//マップの当たり判定//
					//右
					if (map3[static_cast<int>(player->getPlayerPosY() - player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1 &&
						map3[static_cast<int>(player->getPlayerPosY() + player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() - 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//左
					if (map3[static_cast<int>(player->getPlayerPosY() - player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1 &&
						map3[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() + 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//下
					if (map3[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
						map3[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

						player->setPlayerPosY(player->getPlayerPosY() - 1);
						player->setEndPosY(player->getPlayerPosY());

					}

					else {
						if (player->getEndPosY() == player->getPlayerPosY()) {
							player->setPlayerPosY(player->getPlayerPosY() + 1);
							player->setEndPosY(player->getPlayerPosY());
						}
					}

					//上
					if (map3[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
						map3[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

						player->setPlayerPosY(player->getPlayerPosY() + 1);
						player->setEndPosY(player->getPlayerPosY());

					}

				}
			}

			if (door->getIsScene() == 1) {
				player->setStartPosX(134);
				player->setStartPosY(134);
				player->setEndPosX(134);
				player->setEndPosY(134);
				player->setPlayerPosX(134);
				player->setPlayerPosY(134);
				player->setArrows(0);
				key->setPosX(1404);
				key->setPosY(140);
				key->setIsGet(0);
				door->setPosX(1404);
				door->setPosY(580);
				door->setIsScene(0);
				Scene = 4;
			}

			//マップ描画
			for (int y = 0; y < 47; y++)
			{
				for (int x = 0; x < 25; x++)
				{
					if (map3[x][y] == BLOCK)
					{
						DrawGraph(y * blocksize, x * blocksize, block, TRUE);

					}
				}
			}

			//プレイヤーと棒の描画
			player->draw();

			//鍵描画
			key->draw(player);

			//扉描画
			door->draw();

			break;

		case 4:
			player->update();
			key->update(player);
			door->update(player, key);



			mapcountx = sizeof(map2[0]) / sizeof(map2[0][0]);
			mapcounty = sizeof(map2) / sizeof(map2[0]);



			for (int y = 0; y < 47; y++)
			{
				for (int x = 0; x < 25; x++)
				{

					//マップの当たり判定//
					//右
					if (map4[static_cast<int>(player->getPlayerPosY() - player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1 &&
						map4[static_cast<int>(player->getPlayerPosY() + player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() - 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//左
					if (map4[static_cast<int>(player->getPlayerPosY() - player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1 &&
						map4[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() + 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//下
					if (map4[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
						map4[static_cast<int>(player->getPlayerPosY() + player->getRadius() + 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

						player->setPlayerPosY(player->getPlayerPosY() - 1);
						player->setEndPosY(player->getPlayerPosY());

					}

					else {
						if (player->getEndPosY() == player->getPlayerPosY()) {
							player->setPlayerPosY(player->getPlayerPosY() + 1);
							player->setEndPosY(player->getPlayerPosY());
						}
					}

					//上
					if (map4[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
						map4[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

						player->setPlayerPosY(player->getPlayerPosY() + 1);
						player->setEndPosY(player->getPlayerPosY());

					}

				}
			}

			if (door->getIsScene() == 1) {
				
				Scene = 5;
			}

			//マップ描画
			for (int y = 0; y < 47; y++)
			{
				for (int x = 0; x < 25; x++)
				{
					if (map4[x][y] == BLOCK)
					{
						DrawGraph(y * blocksize, x * blocksize, block, TRUE);

					}
				}
			}

			//プレイヤーと棒の描画
			player->draw();

			//鍵描画
			key->draw(player);

			//扉描画
			door->draw();

			break;

		case 5:

			break;

		case 6:

			break;

		}






		//描画処理




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