#include "SceneManager.h"
#include "DxLib.h"
#include "Title.h"
#include "GameMainScene.h"
#include "Demo.h"

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
	read_error = D_NORMAKITY;
	switch (mode)
	{
		case E_TITLE:
			read_error = Title_Initialize();
			break;
		case E_GAMEMAIN:
			read_error = GameMainScene_Initialize();
			break;
		case E_DEMO:
			read_error = Demo_Initialize();
			break;
		default:
			break;
	}

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
		case E_DEMO:
			Demo_Update();
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
		case E_DEMO:
			Demo_Draw();
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