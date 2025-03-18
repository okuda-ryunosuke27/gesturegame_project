#include "SceneManager.h"
#include "DxLib.h"
#include "Title.h"
#include "GameMainScene.h"

/****************************
�ϐ��錾
****************************/
GAME_MODE game_mode;
GAME_MODE next_mode;
int read_error;

/****************************
�V�[���Ǘ��@�\�F����������
���@���F�Q�[�����[�h���
�߂�l�F�Ȃ�
****************************/
int SceneManager_Initialize(GAME_MODE mode)
{
	//�G���[�̊m�F
	read_error = D_NORMAKITY;
	switch (mode)
	{
		case E_TITLE:
			//�����G���[�Ȃ�-1���A���Ă��܂��B
			read_error = Title_Initialize();
			break;
		case E_GAMEMAIN:
			//�����G���[�Ȃ�-1���A���Ă��܂��B
			read_error = GameMainScene_Initialize();
			break;
		default:
			break;
	}

	//�Q�[�����[�h��؂�ւ��邽�߂ɂ���
	//���̃��[�h�Ǝ��̃��[�h�������ւ����肵�܂��B
	//�A�b�v�f�[�g�őO�t���[���̃��[�h�̂��Ə����Ă܂��B
	game_mode = mode;
	next_mode = game_mode;

	return read_error;
}

/****************************
�V�[���Ǘ��@�\�F�X�V����
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void SceneManager_Update(void)
{
	//�O�t���[���ƃQ�[�����[�h������Ă���V�[����؂�ւ���
	if (game_mode != next_mode)
	{
		SceneManager_Initialize(next_mode);
	}

	switch (game_mode)
	{
		case E_TITLE:
			Title_Update();
			break;
		case E_GAMEMAIN:
			GameMainScene_Update();
			break;
		default:
			break;
	}
}

/****************************
�V�[���Ǘ��@�\�F�`�揈��
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void SceneManager_Draw(void)
{
	switch (game_mode)
	{
		case E_TITLE:
			Title_Draw();
			break;
		case E_GAMEMAIN:
			GameMainScene_Draw();
			break;
	default:
		break;
	}
}

/****************************
�V�[���Ǘ��@�\�F�V�[���ύX����
���@���F�ύX����Q�[�����[�h
�߂�l�F�Ȃ�
****************************/
void Change_Scene(GAME_MODE mode)
{
	next_mode = mode;
}