#include "Title.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "InputControl.h"

/****************************
�}�N����`
****************************/
#define PI    3.14f

/****************************
�ϐ��錾
****************************/
int title_background;			//�^�C�g���w�i
int title_logo;					//�^�C�g�����S
int title_spacelogo;			//�^�C�g�����j���[�ɓ��邽�߂̂���
int title_space_count;			//�J�E���g���v���X�ɂ���ϐ�
int title_space_count_change;	//�X�y�[�X�J�E���g���}�C�i�X�ɂ���ϐ�
double title_logo_change;			//�p�x���}�C�i�X�ɂ���ϐ�
double title_logo_angle;		//�p�x���v���X�ɂ���

/****************************
�^�C�g����ʁF����������
���@���F�Ȃ�
�߂�l�F�G���[���(-1�ُ킠��,-1�ȊO:����I��)
****************************/
int Title_Initialize(void)
{
	int ret = D_NORMAKITY;

	title_background = LoadGraph("texture/back.png");
	title_logo = LoadGraph("texture/title_logo.png");
	title_spacelogo = LoadGraph("texture/menu_space.png");

	if (title_background == D_ERROR)
	{
		ret = D_ERROR;
	}
	if (title_logo == D_ERROR)
	{
		ret = D_ERROR;
	}
	if (title_spacelogo == D_ERROR)
	{
		ret = D_ERROR;
	}
	
	title_logo_angle = -270.0;
	title_logo_change = 2.0;
	title_space_count = 0;
	title_space_count_change = 2;

	return ret;
}

/****************************
�^�C�g����ʁF�X�V����
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void Title_Update(void)
{
	title_space_count += title_space_count_change;
	title_logo_angle += title_logo_change;

	if (title_logo_angle >= 270 || title_logo_angle <= -270)
	{
		title_logo_change *= -1.0;
	}

	if (title_space_count >= 255 || title_space_count <= 0)
	{
		title_space_count_change *= -1;
	}

	if (GetKeyFlag(KEY_INPUT_SPACE) == TRUE)
	{
		Change_Scene(E_GAMEMAIN);
	}
	if (GetMouseFlag(MOUSE_INPUT_1) == TRUE)
	{
		Change_Scene(E_GAMEMAIN);
	}
}

/****************************
�^�C�g����ʁF�`�揈��
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void Title_Draw(void)
{
	DrawGraph(0, 0, title_background, TRUE);

	DrawRotaGraph(640, 150, 1.2, PI / title_logo_angle, title_logo, TRUE);
	DrawFormatString(0, 0, 0xFFFFFF, "Angle:%lf", title_logo_angle);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_space_count);
	DrawGraph(561, 450, title_spacelogo, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}