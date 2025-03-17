#include "Title.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "InputControl.h"

/****************************
�}�N����`
****************************/
#define PI				(3.14f)
#define HEIGHT			(350)

/****************************
�ϐ��錾
****************************/
int title_background;			//�^�C�g���w�i
int title_logo;					//�^�C�g�����S
int logo_x;						//���S��x��
int logo_y;						//���S��y��
int logo_y_change;				//���S��y���̕�����؂�ւ��邽�߂ɍ����
int logo_flag;					//���S�̓������N�����ƂɈႤ�悤�ɂ����������߂ɍ�����B
double title_logo_change;		//�p�x���}�C�i�X�ɂ���ϐ�
double title_logo_angle;		//�p�x���v���X�ɂ���

/****************************
�^�C�g����ʁF����������
���@���F�Ȃ�
�߂�l�F�G���[���(-1�ُ킠��,-1�ȊO:����I��)
****************************/
int Title_Initialize(void)
{
	int ret = D_NORMAKITY;		//ret�̏�����

	//LoadGraph�ŉ摜��ǂݍ���ł��܂��B
	title_background = LoadGraph("texture/back.png");		//�w�i�摜��ǂݍ���ł��܂��B
	title_logo = LoadGraph("texture/title_logo.png");		//�^�C�g�����S��ǂݍ���ł��܂��B

	//�����ł͂�������ǂݍ���ł���̂��m�F���Ă��܂��B
	//����-1�Ȃ�ret��-1������
	if (title_background == D_ERROR)
	{
		ret = D_ERROR;
	}
	if (title_logo == D_ERROR)
	{
		ret = D_ERROR;
	}

	//�e�ϐ��̏��������s���Ă���܂��B
	title_logo_angle = -270.0;
	title_logo_change = 2.0;
	logo_flag = GetRand(1);
	logo_x = -800;
	logo_y = 980;
	logo_y_change = 4;

	return ret;
}

/****************************
�^�C�g����ʁF�X�V����
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void Title_Update(void)
{
	
	switch (logo_flag)
	{
		//��]����
		case 0:
			title_logo_angle += title_logo_change;

			if (title_logo_angle >= 270 || title_logo_angle <= -270)
			{
				title_logo_change *= -1.0;
			}
			break;
		//�҂��҂����
		case 1:
			logo_x += 5;
			logo_y += logo_y_change;
			if (logo_y < 900 || logo_y > 1000)
			{
				logo_y_change *= -1;
			}
			if (logo_x >= 2880)
			{
				logo_x = -800;
			}
			break;
		default:
			break;
	}
	
	
	//�L�[�{�[�h�ƃ}�E�X����Ή����Ă���܂��B
	//�X�y�[�X�ƍ��N���b�N�ŃQ�[���X�^�[�g
	if ((GetKeyFlag(KEY_INPUT_SPACE) == TRUE) || (GetMouseFlag(MOUSE_INPUT_1) == TRUE))
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
	//�w�i�`��
	DrawRotaGraph(990, 540, 1.0, 0, title_background, TRUE);

	//���S�̕`��
	switch (logo_flag)
	{
		case 0:
			DrawRotaGraph(990, HEIGHT, 2.0, PI / title_logo_angle, title_logo, TRUE);
			break;
		case 1:
			DrawRotaGraph(logo_x, logo_y, 2.0, PI / title_logo_angle, title_logo, TRUE);
			break;
		default:
			break;
	}
}