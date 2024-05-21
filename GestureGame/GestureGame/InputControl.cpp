#include "DxLib.h"
#include "InputControl.h"

/****************************
�}�N����`
****************************/
#define KEY_INPUT_MAX		(255)

/****************************
�ϐ��錾
****************************/
char old_key[KEY_INPUT_MAX];
char now_key[KEY_INPUT_MAX];

/****************************
���͐���@�\�F����������
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void Input_Initialize(void)
{
	for (int i = 0; i < KEY_INPUT_MAX; i++)
	{
		old_key[i] = NULL;
		now_key[i] = NULL;
	}
}

/****************************
���͐���@�\�F�X�V����
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void Input_Update(void)
{
	//�L�[�{�[�h���͏��̎擾
	for (int i = 0; i < KEY_INPUT_MAX; i++)
	{
		old_key[i] = now_key[i];
	}

	GetHitKeyStateAll(now_key);
}

/****************************
���͐���@�\�FESC�L�[���̓`�F�b�N
���@���F�Ȃ�
�߂�l�FTRUE(���͂��ꂽ)�AFALSE(������)
****************************/
int Input_Escape(void)
{
	int ret = FALSE;

	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ret = TRUE;
	}
	return ret;
}

/*********************************
���͐���@�\�F���͏��擾����(�������u��)
���@���F�w�肷��}�E�X�̃{�^��
�߂�l�FTRUE(���͂��ꂽ)�AFALSE(������)
*********************************/
int GetOldKey(int key)
{
	int ret = FALSE;
	for (int i = 0; i < KEY_INPUT_MAX; i++)
	{
		if ((key & old_key[i]) != FALSE)
		{
			ret = TRUE;
		}
	}
	return ret;
}

/*********************************
���͐���@�\�F���͏��擾����(�����Ă���)
���@���F�w�肷��}�E�X�̃{�^��
�߂�l�FTRUE(���͂��ꂽ)�AFALSE(������)
*********************************/
int GetNowKey(int key)
{
	int ret = FALSE;
	for (int i = 0; i < KEY_INPUT_MAX; i++)
	{
		if ((key & now_key[i]) != FALSE)
		{
			ret = TRUE;
		}
	}
	return ret;
}

/*********************************
���͐���@�\�F���͏��擾����(�������u��)
���@���F�w�肷��}�E�X�̃{�^��
�߂�l�FTRUE(���͂��ꂽ)�AFALSE(������)
*********************************/
int GetKeyFlag(int key)
{
	int ret = FALSE;

	if ((now_key[key] & ~old_key[key]) != FALSE)
	{
		ret = TRUE;
	}

	return ret;
}