#include "DxLib.h"
#include "GameMainScene.h"
#include "SceneManager.h"
#include "../Utility/InputControl.h"
#include <string.h>


/****************************
�}�N����`
****************************/
#define ODAI_FILE		("dat/odai_ansi.csv")		//�����csv�ŊǗ����Ă���̂ŏ����Ă܂��B
#define ODAI_MAX		(232)						//csv�ɓ����Ă��邨��̌�
#define ODAI_NAME_LEN	(25)						//�}���`�o�C�g�����̂��Ƃ��l����12������24�݂����Ȋ����ɑ��������Ă���
#define ODAI_LIST_MAX	(50)						//���s�������ɏo������̍ő��
#define PI				(3.14f)						//��]��
#define HEIGHT			(490)						//�����̒��S���W
#define RAND_MAX		(230)						//����������_���œ��ꂽ�����炻��MAX�l

/****************************
�^��`
****************************/
typedef struct
{
	int num;
	char odai[ODAI_NAME_LEN];
}J_ODAI;	
//csv�̒����炱����Ɋi�[���邽�߂ɍ\���̂ō����
//num�͕����̌����i�[����Ƃ���
//odai�͕�������i�[���Ă���B

/****************************
�v���g�^�C�v�錾
****************************/
void Odai_Store();		//����i�[���邽�߂̊֐�


/****************************
�ϐ��錾
****************************/
J_ODAI Odai_Read[ODAI_MAX];			//csv�̂�����i�[���邽�߂ɕK�v
J_ODAI Odai_List[ODAI_LIST_MAX];	//���s���̂�����i�[���邽�߂ɕK�v
int gamemain_background;			//�w�i�̕ϐ�
int around;							//������񂷕ϐ�
int countflag;						//�J�E���g�_�E���̃t���O��������o���̂�����t���O
int count;							//�J�E���g�_�E���ŃJ�E���g����l
int successfulcount;				//�������J�E���g����ϐ�
int passcount;						//�p�X�̐����J�E���g����֐�
int signal;							//������\��������̂ɕϐ��Ɋi�[���Ă���
float count_fontsize;				//�J�E���g�_�E���̃t�H���g�̑傫����ς���

/****************************
�Q�[�����C����ʁF����������
���@���F�Ȃ�
�߂�l�F�G���[���
****************************/
int GameMainScene_Initialize(void)
{
	int ret = D_NORMAKITY;

	//�����csv����ǂݍ���
	file_read();

	//������i�[���鏀������֐�
	Odai_Store();

	//���w�i�摜��ǂݍ���ł���
	gamemain_background = LoadGraph("texture/back.png");

	//�����Ɠǂݍ��܂�Ă���̂��m�F
	if (gamemain_background == D_ERROR)
	{
		ret = D_ERROR;
	}

	//�e��ϐ��̏�����
	around = 0;
	countflag = 1;
	count = 0;
	signal = 3;
	count_fontsize = 1.0f;
	successfulcount = 0;
	passcount = 0;

	return ret;
}

/****************************
�Q�[�����C����ʁF�X�V����
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void GameMainScene_Update(void)
{
	if (countflag == 1)
	{
		//�J�E���g�_�E���̐�������Ă��邪�A
		//������{�l���Y��Ă���
		
		//�J�E���g�𑝂₵�Ă���
		count++;

		//�J�E���g�̃t�H���g��傫������
		count_fontsize += 0.008f;

		//�������Y��Ă���|�C���g�Ȃ��80�J�E���g�Ŋ�����0��������ɂ����̂����s������
		//�C�C�����ɂȂ��Ă邩��80�ɂ����͂�
		if (count % 80 == 0)
		{
			//�J�E���g�̐���������炵�Ă���
			signal--;

			//�J�E���g�̃t�H���g�������l�ɖ߂�
			count_fontsize = 1.0f;
		}

		//�J�E���g���I�������Q�[���I�����Ȃ��Ă������悤�ɏ��������Ă���
		if (signal == 0)
		{
			countflag = 0;
			count = 0;
			signal = 3;
			count_fontsize = 1.0f;
			
		}
	}
	else
	{
		//�����`�撆�̎��̑���
		//Enter�L�[�ƃ}�E�X�̍��N���b�N�ł���A������
		//���̂�����o���B
		if ((GetKeyFlag(KEY_INPUT_RETURN) == TRUE) || (GetMouseFlag(MOUSE_INPUT_1) == TRUE))
		{
			around += 1;
			successfulcount += 1;
		}

		//�o�b�N�X�y�[�X�L�[�ƃ}�E�X�̃z�C�[�����N���b�N����ƃ^�C�g���ɖ߂�
		if ((GetKeyFlag(KEY_INPUT_BACK) == TRUE) || (GetMouseFlag(MOUSE_INPUT_3) == TRUE))
		{
			Change_Scene(E_TITLE);
		}

		//�X�y�[�X�L�[�ƃ}�E�X�̉E�N���b�N�ł���A�p�X��
		//���̂�����o���B
		if ((GetKeyFlag(KEY_INPUT_SPACE) == TRUE) || (GetMouseFlag(MOUSE_INPUT_2) == TRUE))
		{
			around += 1;
			passcount += 1;
		}
	}
}

/****************************
�Q�[�����C����ʁF�`�揈��
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void GameMainScene_Draw(void)
{
	//�w�i��`��
	DrawRotaGraph(990, 540, 1.0, 0, gamemain_background, TRUE);

	//�����ƃp�X�̐���`��
	DrawFormatString(50, 0, 0xED215B, "����:%d �p�X��:%d",successfulcount,passcount);
	
	SetFontSize(180);
	
	//�t���O�ŊǗ����Ă���1�Ȃ�J�E���g�_�E��
	//2�Ȃ炨���`��Ƃ��������ł��B
	if (countflag == 1)
	{
		//�J�E���g�_�E���̕`������Ă��܂��B
		switch (signal)
		{
		case 0:
			break;
		case 1:
			DrawRotaFormatString(1000, 540, count_fontsize, count_fontsize, 50, 90, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "1");
			break;
		case 2:
			DrawRotaFormatString(1000, 540, count_fontsize, count_fontsize, 50, 90, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "2");
			break;
		case 3:
			DrawRotaFormatString(1000, 540, count_fontsize, count_fontsize, 50, 95, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "3");
			break;
		default:
			break;
		}
	}
	else
	{
		//���̒��͕��������ꂢ�Ɍ�����悤�ɋϓ��ɕ����Ă���܂��B
		if (Odai_List[around].num == 1)			//�ꕶ��
		{
			DrawRotaFormatString(790, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 2)	//�񕶎�
		{
			DrawRotaFormatString(540, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 3)	//�O����
		{
			DrawRotaFormatString(300, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 4)	//�l����
		{
			DrawRotaFormatString(80, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 5)	//�ܕ���
		{
			DrawRotaFormatString(65, 390, 2.0, 2.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 6)	//�Z����
		{
			DrawRotaFormatString(450, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 7)	//������
		{
			DrawRotaFormatString(350, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 8)	//������
		{
			DrawRotaFormatString(300, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 9)	//�㕶��
		{
			DrawRotaFormatString(200, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 10)	//�\�����ȏ�
		{
			DrawRotaFormatString(150, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 11)	//�\�ꕶ���ȏ�
		{
			DrawRotaFormatString(100, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		
		
	}

}

/****************************
�Q�[�����C����ʁF�t�@�C���ǂݍ��ݏ���
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void file_read(void)
{
	//�t�@�C���̓ǂݍ��݂Ɏg��
	FILE* fp = NULL;
	int i;


	OutputDebugString("========�t�@�C����ǂݍ��݂܂�========\n");

	//�����Ńt�@�C����ǂݍ���ł���
	fopen_s(&fp, ODAI_FILE, "r");

	//�t�@�C�������܂��ǂݍ��߂Ȃ�������f�o�b�N�ɕ�����\��
	//���܂��s������Odai_Read�̔z��Ɋi�[�����B
	if (fp == NULL)
	{
		OutputDebugString("========�t�@�C�����ǂݍ��߂܂���========\n");
	}
	else
	{
		//�ЂƂЂƂz��Ɋi�[���Ă���B
		for (i = 0; i < ODAI_MAX; i++)
		{
			fscanf_s(fp, "%d, %s,\n", &Odai_Read[i].num, Odai_Read[i].odai, ODAI_NAME_LEN);
		}

		//�K���t�@�C�����N���[�Y�����Ȃ��ƃv���O���������̊����̂ŏ����Ȃ���
		fclose(fp);

		OutputDebugString("========�t�@�C����ǂݍ��݂܂���========\n");
	}

	
}

/****************************
�Q�[�����C����ʁF����i�[
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void Odai_Store()
{

	int odai[ODAI_LIST_MAX];

	//0����0�Ԗڂ����Ă��܂��̂�-1�����Ă���B
	for (int i = 0; i < ODAI_LIST_MAX; i++)
	{
		odai[i] = -1;
	}

	//���̒���231�̂����50�܂ōi���ăQ�[���̂���Ɋi�[���Ă���B
	for (int i = 0; i < ODAI_LIST_MAX; i++)
	{
		int randint;		//�����_���̒l���~�����̂Ń����_��int�ɂ��Ă���B
		while (1)
		{

			int isexist = FALSE;	//���������݂��Ă���̂��ǂ����m�F����t���O
			randint = GetRand(RAND_MAX);	//�����_���Œl�����Ă��܂��B
			
			//odai�z��̒��ɓ����l�������Ă��Ȃ��̂��m�F���郋�[�v��
			for (int k = 0; k < ODAI_LIST_MAX; k++)
			{
				//�����l�����������΂��B
				if (odai[k] == randint)
				{
					isexist = TRUE;
					break;
				}
			}
			//�����l������������u���C�N����while���𔲂���
			if (isexist != TRUE)
			{
				break;
			}
		}
		//�����_���̒l������̔z��Ɋi�[���Ă���
		odai[i] = randint;

		//csv����ǂݍ���l���Q�[���Ŏg�����X�g�Ɋi�[���Ă���
		Odai_List[i].num = Odai_Read[randint].num;

		//��������csv����ǂݍ��񂾕�������Q�[���Ŏg�����X�g�Ɋi�[���Ă���
		strcpy_s(Odai_List[i].odai, Odai_Read[randint].odai);		
	}
}