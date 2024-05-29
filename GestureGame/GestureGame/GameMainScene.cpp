#include "GameMainScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "InputControl.h"
#include <string.h>


/****************************
�}�N����`
****************************/
#define ODAI_FILE		("dat/odai_ansi.csv")
#define ODAI_MAX		(232)
#define ODAI_NAME_LEN	(25)
#define ODAI_LIST_MAX	(50)
#define PI    3.14f
#define HEIGHT			(490)

/****************************
�^��`
****************************/
typedef struct
{
	int num;
	char odai[ODAI_NAME_LEN];
}J_ODAI;

/****************************
�v���g�^�C�v�錾
****************************/
void Odai_Store();


/****************************
�ϐ��錾
****************************/
J_ODAI Odai_Read[ODAI_MAX];
J_ODAI Odai_List[ODAI_LIST_MAX];
int gamemain_background;
int arand;
int countflag;
int count;
int successfulcount;
int passcount;
int signal;
float count_fontsize;
float kaiten;

/****************************
�Q�[�����C����ʁF����������
���@���F�Ȃ�
�߂�l�F�G���[���
****************************/
int GameMainScene_Initialize(void)
{
	int ret = D_NORMAKITY;

	Odai_Store();

	gamemain_background = LoadGraph("texture/back.png");
	arand = 0;
	countflag = 1;
	count = 0;
	signal = 3;
	count_fontsize = 1.0f;
	kaiten = 6.0f;
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
		count++;
		count_fontsize += 0.008f;
		kaiten += 0.05f;
		if (count % 80 == 0)
		{
			signal--;
			count_fontsize = 1.0f;
			kaiten = 6.0f;
		}
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
		if ((GetKeyFlag(KEY_INPUT_RETURN) == TRUE) || (GetMouseFlag(MOUSE_INPUT_1) == TRUE))
		{
			arand += 1;
			successfulcount += 1;
		}
		if ((GetKeyFlag(KEY_INPUT_BACK) == TRUE) || (GetMouseFlag(MOUSE_INPUT_3) == TRUE))
		{
			Change_Scene(E_TITLE);
		}
		if (GetKeyFlag(KEY_INPUT_SPACE) == TRUE)
		{
			arand += 1;
			passcount += 1;
		}
		//if (flag == 0)
		//{
		//	roulette++;
		//	if ((GetKeyFlag(KEY_INPUT_RETURN) == TRUE) || (GetMouseFlag(MOUSE_INPUT_1) == TRUE))
		//	{
		//		flag = 1;
		//		//arand = rand() % 101;
		//		arand = GetRand(100);
		//	}
		//	if ((GetKeyFlag(KEY_INPUT_BACK) == TRUE) || (GetMouseFlag(MOUSE_INPUT_3) == TRUE))
		//	{
		//		Change_Scene(E_TITLE);
		//	}
		//}
		//else
		//{
		//	if ((GetKeyFlag(KEY_INPUT_RETURN) == TRUE) || (GetMouseFlag(MOUSE_INPUT_1) == TRUE))
		//	{
		//		flag = 0;
		//	}
		//	if ((GetKeyFlag(KEY_INPUT_BACK) == TRUE) || (GetMouseFlag(MOUSE_INPUT_3) == TRUE))
		//	{
		//		Change_Scene(E_TITLE);
		//	}
		//}
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

	DrawFormatString(50, 0, 0xED215B, "����:%d �p�X��:%d",successfulcount,passcount);
	//DrawFormatString(0, 180, 0xED215B, "�p�X��:%d", passcount); 

	SetFontSize(180);

	if (countflag == 1)
	{
		switch (signal)
		{
		case 0:
			//DrawFormatString(450, HEIGHT, 0xED215B, "�X�^�[�g");
			break;
		case 1:
			//DrawFormatString(900, HEIGHT, 0xED215B, "1");
			DrawRotaFormatString(1000, 540, count_fontsize, count_fontsize, 50, 90, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "1");
			break;
		case 2:
			//DrawFormatString(900, HEIGHT, 0xED215B, "2");
			DrawRotaFormatString(1000, 540, count_fontsize, count_fontsize, 50, 90, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "2");
			break;
		case 3:
			//DrawFormatString(900, HEIGHT, 0xED215B, "3");
			DrawRotaFormatString(1000, 540, count_fontsize, count_fontsize, 50, 95, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "3");
			break;
		default:
			break;
		}
	}
	else
	{
		if (Odai_List[arand].num == 1)	//�ꕶ��
		{
			DrawRotaFormatString(790, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		}
		else if (Odai_List[arand].num == 2)	//�񕶎�
		{
			DrawRotaFormatString(540, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		}
		else if (Odai_List[arand].num == 3)	//�O����
		{
			DrawRotaFormatString(300, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		}
		else if (Odai_List[arand].num == 4)	//�l����
		{
			DrawRotaFormatString(80, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		}
		else if (Odai_List[arand].num == 5)	//�ܕ���
		{
			DrawRotaFormatString(65, 390, 2.0, 2.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		}
		else if (Odai_List[arand].num == 6)	//�Z����
		{
			DrawRotaFormatString(450, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		}
		else if (Odai_List[arand].num == 7)	//������
		{
			DrawRotaFormatString(350, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		}
		else if (Odai_List[arand].num == 8)	//������
		{
			DrawRotaFormatString(300, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		}
		else if (Odai_List[arand].num == 9)	//�㕶��
		{
			DrawRotaFormatString(200, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		}
		else if (Odai_List[arand].num == 10)	//�\�����ȏ�
		{
			DrawRotaFormatString(150, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		}
		else if (Odai_List[arand].num == 11)	//�\�ꕶ���ȏ�
		{
			DrawRotaFormatString(100, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		}
		
		//�ϐ��ɓ����Ă��邩�m���߂�֐�
		//DrawRotaFormatString(65, 390, 2.0, 2.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_Read[195].odai);
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
	int i;

	OutputDebugString("�t�@�C����ǂݍ��݂܂�");
	fopen_s(&fp, ODAI_FILE, "r");


	if (fp == NULL)
	{
		OutputDebugString("�t�@�C�����ǂݍ��߂܂���");
	}
	else
	{
		for (i = 0; i < ODAI_MAX; i++)
		{
			fscanf_s(fp, "%d, %s,\n", &Odai_Read[i].num, Odai_Read[i].odai, ODAI_NAME_LEN);
		}
		fclose(fp);
	}

	
}

/****************************
�Q�[�����C����ʁF����i�[
���@���F�Ȃ�
�߂�l�F�Ȃ�
****************************/
void Odai_Store()
{

	int a[ODAI_LIST_MAX];

	for (int i = 0; i < ODAI_LIST_MAX; i++)
	{
		a[i] = -1;
	}

	for (int i = 0; i < ODAI_LIST_MAX; i++)
	{
		int b;
		while (1)
		{
			int isexist = FALSE;
			b = GetRand(230);
			for (int k = 0; k < ODAI_LIST_MAX; k++)
			{
				if (a[k] == b)
				{
					isexist = TRUE;
					break;
				}
			}
			if (isexist != TRUE)
			{
				break;
			}
		}
		a[i] = b;
		Odai_List[i].num = Odai_Read[b].num;
		strcpy_s(Odai_List[i].odai, Odai_Read[b].odai);
	}
}