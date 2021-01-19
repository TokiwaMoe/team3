#include "DxLib.h"
#include "stdio.h"
#include "math.h"

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
	int character = LoadGraph("character.png");
	int key = LoadGraph("key.png");
	int door = LoadGraph("door2.png");

	//�Q�[�����[�v�Ŏg���ϐ��̐錾
	char keys[256] = { 0 }; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 };//1���[�v�i�t���[���j�O�̃L�[�{�[�h���
	//�}�E�X�ϐ�
	int MousePosX;
	int MousePosY;
	int MouseInput = 0;
	int MouseInputOld = 0;
	float startPosX = 64;
	float startPosY = 732;
	float endPosX = 64;
	float endPosY = 732;
	int Drawflag = 0;

	//�v���C���[�ϐ�
	float PlayerPosX = 64;
	float PlayerPosY = 732;
	int PlayerRadius = 16;
	int PlayerG = 3;

	//���ϐ�
	int KeyPosX = 64;
	int KeyPosY = 64;
	int KeyRadius = 10;
	int getflag = 0;

	//�ړ��ϐ�
	const int maxflame = 50;
	int flame = 0;
	float PI = 3.141592;
	float x = 0;

	//�_�ϐ�
	int arrows = 0;

	//�}�b�v�ϐ�
	int blocksize = 32;

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
		
		MouseInputOld = MouseInput;
		MouseInput = GetMouseInput();
		
		//��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		//�X�V����
		////�}�E�X���� 
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

		//�v���C���[�ړ�����
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
		
		//�}�b�v�̏���
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

				//�}�b�v�̓����蔻��//
				//�E
				if (map[static_cast<int>(PlayerPosY - PlayerRadius)/ blocksize][static_cast<int>(PlayerPosX + PlayerRadius + 1)  / blocksize] == 1 &&
					map[static_cast<int>(PlayerPosY + PlayerRadius) / blocksize][static_cast<int>(PlayerPosX + PlayerRadius + 1) / blocksize] == 1) {
					
					PlayerPosX = PlayerPosX - 1;
					endPosX = PlayerPosX;
					
				}

				//��
				if (map[static_cast<int>(PlayerPosY - PlayerRadius) / blocksize][static_cast<int>(PlayerPosX - PlayerRadius - 1) / blocksize] == 1 &&
					map[static_cast<int>(PlayerPosY + PlayerRadius) / blocksize][static_cast<int>(PlayerPosX - PlayerRadius - 1) / blocksize] == 1) {

					PlayerPosX = PlayerPosX + 1;
					endPosX = PlayerPosX;
					
				}

				//��
				if (map[static_cast<int>(PlayerPosY + PlayerRadius + 1) / blocksize][static_cast<int>(PlayerPosX - PlayerRadius) / blocksize] == 1 &&
					map[static_cast<int>(PlayerPosY + PlayerRadius + 1) / blocksize][static_cast<int>(PlayerPosX + PlayerRadius) / blocksize] == 1) {

					PlayerPosY = PlayerPosY - 1;
					endPosY = PlayerPosY;

				}
				

				//��
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

		//���̏���
		if (PlayerPosX <= KeyPosX + PlayerRadius * 2 && KeyPosX <= PlayerPosX + PlayerRadius) {
			if (PlayerPosY <= KeyPosY + PlayerRadius * 2 && KeyPosY <= PlayerPosY + PlayerRadius) {
				getflag = 1;
			}
		}
		
		//�`�揈��
		//�w�i�`��
		DrawGraph(0, 0, background, true);

		//�}�b�v�`��
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
		
		//�_�`��
		if (Drawflag == 1) {
			DrawLine(startPosX, startPosY, endPosX, endPosY, GetColor(255, 255, 255), 2);
		}

		//�v���C���[�`��
		DrawGraph(PlayerPosX - 16, PlayerPosY - 16, character, true);

		//���`��
		if (getflag == 0) {
			DrawGraph(KeyPosX, KeyPosY, key, true);
		}

		if (getflag == 1) {
			KeyPosX = PlayerPosX;
			KeyPosY = PlayerPosY;
			DrawExtendGraph(KeyPosX - 5, KeyPosY - 30, KeyPosX + 5, KeyPosY - 20, key, true);
		}

		//���`��
		DrawGraph(1370, 704, door, true);

		//�f�o�b�N�`��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "X:%d Y:%d", MousePosX, MousePosY);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "�}�E�X�̏��%d", MouseInput);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "���̊J�n�ʒu X:%f Y:%f", startPosX, startPosY);
		DrawFormatString(0, 60, GetColor(255, 255, 255), "���̏I���ʒu X:%f Y:%f", endPosX, endPosY);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "�v���C���[�̈ʒu X:%f Y:%f", PlayerPosX, PlayerPosY);

		DrawFormatString(0,
			100,
			GetColor(255, 255, 255),
			"X�̎�:%f = %f + (%f - %f) * (sin (%f * %f / 2))",
			PlayerPosX, startPosX, endPosX, startPosX, x, PI);

		DrawFormatString(0,
			120,
			GetColor(255, 255, 255),
			"Y�̎�:%f = %f + (%f - %f) * (sin (%f * %f / 2))",
			PlayerPosY, startPosY, endPosY, startPosY, x, PI);

		DrawFormatString(0, 140, GetColor(255, 255, 255), "%f", x);
		DrawFormatString(0, 160, GetColor(255, 255, 255), "Flame:%d", flame);
		DrawFormatString(0, 180, GetColor(255, 255, 255), "arrows:%d", arrows);

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