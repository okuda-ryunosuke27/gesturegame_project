#include "Demo.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "InputControl.h"



/****************************
�ϐ��錾
****************************/
int demo_background;			//�f���̔w�i�摜




/****************************
�f����ʁF����������
���@���F�Ȃ�
�߂�l�F�G���[���
****************************/
int Demo_Initialize(void)
{
	int ret = D_NORMAKITY;

	demo_background = LoadGraph("texture/back.png");

	if (demo_background == D_ERROR)
	{
		ret = D_ERROR;
	}

	return ret;
}

/****************************
�f����ʁF�X�V����
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void Demo_Update(void)
{
	if ((GetKeyFlag(KEY_INPUT_BACK) == TRUE) || (GetMouseFlag(MOUSE_INPUT_3) == TRUE))
	{
		Change_Scene(E_TITLE);
	}
}

/****************************
�f����ʁF�`�揈��
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void Demo_Draw(void)
{
	DrawFormatString(650, 490, 0XED215B, "�f������");
}