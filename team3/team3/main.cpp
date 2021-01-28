#include "DxLib.h"
#include "Player.h"
#include "Key.h"
#include "Door.h"

const char TITLE[] = "5 ARROWS";

const int WIN_WIDTH = 1500; //�E�B���h�E����
const int WIN_HEIGHT = 800;//�E�B���h�E�c��


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0x00, 0x00, 0x00);		// ��ʂ̔w�i�F��ݒ肷��

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//�摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int block = LoadGraph("block.png");
	int background = LoadGraph("background.png");
	int title = LoadGraph("title.png");



	//�Q�[�����[�v�Ŏg���ϐ��̐錾
	char keys[256] = { 0 }; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 };//1���[�v�i�t���[���j�O�̃L�[�{�[�h���
	Player* player = new Player(64, 544, 64, 732, 64, 732, 16, 0);
	Key* key = new Key(1170, 160, 10, 0);
	Door* door = new Door(1370, 544, 0);

	//�}�b�v�ϐ�
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

	//�V�[���؂�ւ��ϐ�
	int Scene = 0;


	// �Q�[�����[�v
	while (1)
	{
		//�ŐV�̃L�[�{�[�h��񂾂������̂͂P�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�

		//�ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}

		//��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		//�X�V����
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
			//�w�i�`��
			DrawGraph(0, 0, background, true);

			//�}�b�v�̏���
			mapcountx = sizeof(map1[0]) / sizeof(map1[0][0]);
			mapcounty = sizeof(map1) / sizeof(map1[0]);

			for (int y = 0; y < 47; y++)
			{
				for (int x = 0; x < 25; x++)
				{

					//�}�b�v�̓����蔻��//
					//�E
					if (map1[static_cast<int>(player->getPlayerPosY() - player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1 &&
						map1[static_cast<int>(player->getPlayerPosY() + player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() - 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//��
					if (map1[static_cast<int>(player->getPlayerPosY() - player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1 &&
						map1[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() + 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//��
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

					//��
					if (map1[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius()) / blocksize] == 1 &&
						map1[static_cast<int>(player->getPlayerPosY() - player->getRadius() - 1) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius()) / blocksize] == 1) {

						player->setPlayerPosY(player->getPlayerPosY() + 1);
						player->setEndPosY(player->getPlayerPosY());

					}

				}
			}

			//�}�b�v�`��
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
			//�v���C���[�Ɩ_�̕`��
			player->draw();

			key->update(player);
			//���`��
			key->draw(player);

			door->update(player, key);
			//���`��
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
			//�w�i�`��
			DrawGraph(0, 0, background, true);

			mapcountx = sizeof(map2[0]) / sizeof(map2[0][0]);
			mapcounty = sizeof(map2) / sizeof(map2[0]);


			for (int y = 0; y < 47; y++)
			{
				for (int x = 0; x < 25; x++)
				{

					//�}�b�v�̓����蔻��//
					//�E
					if (map2[static_cast<int>((player->getPlayerPosY() - player->getRadius()) / blocksize)][static_cast<int>((player->getPlayerPosX() + player->getRadius() + 1) / blocksize)] == 1 &&
						map2[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() - 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//��
					if (map2[static_cast<int>((player->getPlayerPosY() - player->getRadius()) / blocksize)][static_cast<int>((player->getPlayerPosX() - player->getRadius() - 1) / blocksize)] == 1 &&
						map2[static_cast<int>((player->getPlayerPosY() + player->getRadius()) / blocksize)][static_cast<int>((player->getPlayerPosX() - player->getRadius() - 1) / blocksize)] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() + 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//��
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

					//��
					if (map2[static_cast<int>((player->getPlayerPosY() - player->getRadius() - 1) / blocksize)][static_cast<int>((player->getPlayerPosX() - player->getRadius()) / blocksize)] == 1 &&
						map2[static_cast<int>((player->getPlayerPosY() - player->getRadius() - 1) / blocksize)][static_cast<int>((player->getPlayerPosX() + player->getRadius()) / blocksize)] == 1) {

						player->setPlayerPosY(player->getPlayerPosY() + 1);
						player->setEndPosY(player->getPlayerPosY());

					}

				}
			}

			//�}�b�v�`��
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

			//�v���C���[�Ɩ_�̕`��
			player->draw();

			key->update(player);
			//���`��
			key->draw(player);

			door->update(player, key);
			//���`��
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
			//�w�i�`��
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

					//�}�b�v�̓����蔻��//
					//�E
					if (map3[static_cast<int>(player->getPlayerPosY() - player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1 &&
						map3[static_cast<int>(player->getPlayerPosY() + player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() - 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//��
					if (map3[static_cast<int>(player->getPlayerPosY() - player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1 &&
						map3[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() + 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//��
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

					//��
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

			//�}�b�v�`��
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

			//�v���C���[�Ɩ_�̕`��
			player->draw();

			//���`��
			key->draw(player);

			//���`��
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

					//�}�b�v�̓����蔻��//
					//�E
					if (map4[static_cast<int>(player->getPlayerPosY() - player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1 &&
						map4[static_cast<int>(player->getPlayerPosY() + player->getRadius() * 2) / blocksize][static_cast<int>(player->getPlayerPosX() + player->getRadius() + 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() - 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//��
					if (map4[static_cast<int>(player->getPlayerPosY() - player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1 &&
						map4[static_cast<int>(player->getPlayerPosY() + player->getRadius()) / blocksize][static_cast<int>(player->getPlayerPosX() - player->getRadius() - 1) / blocksize] == 1) {

						player->setPlayerPosX(player->getPlayerPosX() + 1);
						player->setEndPosX(player->getPlayerPosX());

					}

					//��
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

					//��
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

			//�}�b�v�`��
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

			//�v���C���[�Ɩ_�̕`��
			player->draw();

			//���`��
			key->draw(player);

			//���`��
			door->draw();

			break;

		case 5:

			break;

		case 6:

			break;

		}






		//�`�揈��




		//---------  �����܂łɃv���O�������L�q  ---------//
		ScreenFlip();//�i�_�u���o�b�t�@�j����
		// 20�~���b�ҋ@�i�^��60FPS�j
		WaitTimer(20);
		// Windows �V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}
		// �d�r�b�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}