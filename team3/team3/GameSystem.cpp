#include "DxLib.h"
#include "GameSystem.h"


GameSystem::GameSystem() : WIN_WIDTH(1500), WIN_HEIGHT(800) {
	ChangeWindowMode(TRUE); //�E�B���h�E���[�h�ɐݒ�

	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	
	SetMainWindowText("TITLE"); // �^�C�g����ύX
	
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32); //��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j

	SetWindowSizeExtendRate(1.0); //��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	
	SetBackgroundColor(0x00, 0x00, 0x00); // ��ʂ̔w�i�F��ݒ肷��

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);
}

void GameSystem::init() {
	scene = new Scene(0);
	scene->init();
}

void GameSystem::gameLoopPre() {
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
}

void GameSystem::gameLoop() {
	scene->sceneManager();
}

void GameSystem::gameLoopPost() {

	//---------  �����܂łɃv���O�������L�q  ---------//
	ScreenFlip();//�i�_�u���o�b�t�@�j����
	// 20�~���b�ҋ@�i�^��60FPS�j
	WaitTimer(20);
}


