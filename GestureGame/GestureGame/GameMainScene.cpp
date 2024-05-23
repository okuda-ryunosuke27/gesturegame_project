#include "GameMainScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "InputControl.h"
#include <stdlib.h>
#include <time.h>


/****************************
�}�N����`
****************************/
#define ODAI_FILE		("dat/odai_ansi.csv")
#define ODAI_MAX		(101)
#define ODAI_NAME_LEN	(100)
#define PI    3.14f
#define HEIGHT			(490)

/****************************
�^��`
****************************/
typedef struct
{
	char odai[ODAI_NAME_LEN];
}J_ODAI;

/****************************
�v���g�^�C�v�錾
****************************/
void file_read(void);			//�t�@�C���ǂݍ���


/****************************
�ϐ��錾
****************************/
J_ODAI Odai_Read[ODAI_MAX];
J_ODAI Odai_List[ODAI_MAX];
int gamemain_background;
int arand;
int roulette;
int flag;
int countflag;
int count;
int signal;
int count_fontsize;

/****************************
�Q�[�����C����ʁF����������
���@���F�Ȃ�
�߂�l�F�G���[���
****************************/
int GameMainScene_Initialize(void)
{
	int ret = D_NORMAKITY;

	file_read();
	
	gamemain_background = LoadGraph("texture/back.png");
	arand = 0;
	roulette = 0;
	flag = 0;
	countflag = 1;
	count = 0;
	signal = 3;
	count_fontsize = 180;
	srand((unsigned int)time(NULL));

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
		count++;
		count_fontsize++;
		if (count % 80 == 0)
		{
			signal--;
			count_fontsize = 180;
		}
		if (signal == 0)
		{
			countflag = 0;
			count = 0;
			signal = 3;
		}
	}
	else
	{
		if (flag == 0)
		{
			roulette++;
			if ((GetKeyFlag(KEY_INPUT_RETURN) == TRUE) || (GetMouseFlag(MOUSE_INPUT_1) == TRUE))
			{
				flag = 1;
				//arand = rand() % 101;
				arand = GetRand(100);
			}
			if ((GetKeyFlag(KEY_INPUT_BACK) == TRUE) || (GetMouseFlag(MOUSE_INPUT_3) == TRUE))
			{
				Change_Scene(E_TITLE);
			}
		}
		else
		{
			if ((GetKeyFlag(KEY_INPUT_RETURN) == TRUE) || (GetMouseFlag(MOUSE_INPUT_1) == TRUE))
			{
				flag = 0;
			}
			if ((GetKeyFlag(KEY_INPUT_BACK) == TRUE) || (GetMouseFlag(MOUSE_INPUT_3) == TRUE))
			{
				Change_Scene(E_TITLE);
			}
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
	DrawRotaGraph(990, 540, 1.0, 0, gamemain_background, TRUE);

	//DrawFormatString(0, 0, 0xED215B, "arand:%d",arand);
	/*DrawFormatString(0, 180, 0xED215B, "signal:%d", signal); */

	SetFontSize(180);

	if (countflag == 1)
	{
		SetFontSize(count_fontsize);
		switch (signal)
		{
			case 0:
				//DrawFormatString(450, HEIGHT, 0xED215B, "�X�^�[�g");
				break;
			case 1:
				//DrawFormatString(900, HEIGHT, 0xED215B, "1");
				DrawRotaFormatString(900, HEIGHT, 1.0, 1.0, 0, 0, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "1");
				break;
			case 2:
				//DrawFormatString(900, HEIGHT, 0xED215B, "2");
				DrawRotaFormatString(900, HEIGHT, 1.0, 1.0, 0, 0, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "2");
				break;
			case 3:
				//DrawFormatString(900, HEIGHT, 0xED215B, "3");
				DrawRotaFormatString(900, HEIGHT, 1.0, 1.0, 0, 0, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "3");
				break;
			default:
				break;
		}
	}
	else
	{
		
		if (flag == 1)
		{
			//if ((arand >= 0) && (arand < 3))	//�ꕶ��
			//{
			//	DrawRotaFormatString(900, HEIGHT, 2.0, 2.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 3) && (arand < 23))	//�񕶎�
			//{
			//	DrawRotaFormatString(800, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 23) && (arand < 48))	//�O����
			//{
			//	DrawRotaFormatString(700, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 48) && (arand < 67))	//�l����
			//{
			//	DrawRotaFormatString(650, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 67) && (arand < 84))	//�ܕ���
			//{
			//	DrawRotaFormatString(550, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 84) && (arand < 90))	//�Z����
			//{
			//	DrawRotaFormatString(450, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 90) && (arand < 93))	//������
			//{
			//	DrawRotaFormatString(350, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 93) && (arand < 97))	//������
			//{
			//	DrawRotaFormatString(300, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 97) && (arand < 100))	//�㕶��
			//{
			//	DrawRotaFormatString(200, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else										//�\�����ȏ�
			//{
			//	DrawRotaFormatString(100, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}


			//DrawRotaFormatString(200, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[97].odai);
		}
		else
		{
			DrawRotaFormatString(800, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[roulette % 10].odai);
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
	FILE* fp = NULL;
	int i, a;

	OutputDebugString("�t�@�C����ǂݍ��݂܂�");
	fopen_s(&fp, ODAI_FILE, "r");


	if (fp == NULL)
	{
		OutputDebugString("�t�@�C�����ǂݍ��߂܂���");
	}
	else
	{
		for ( i = 0; i < ODAI_MAX; i++)
		{
			fscanf_s(fp, "%s,\n", Odai_Read[i].odai, ODAI_NAME_LEN);
		}
		fclose(fp);

		for ( i = 0; i < ODAI_MAX; i++)
		{


		}
	}

	

}