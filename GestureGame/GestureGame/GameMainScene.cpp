#include "GameMainScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "InputControl.h"
#include <stdlib.h>
#include <time.h>


/****************************
マクロ定義
****************************/
#define ODAI_FILE		("dat/odai_ansi.csv")
#define ODAI_MAX		(101)
#define ODAI_NAME_LEN	(100)
#define PI    3.14f
#define HEIGHT			(490)

/****************************
型定義
****************************/
typedef struct
{
	char odai[ODAI_NAME_LEN];
}J_ODAI;

/****************************
プロトタイプ宣言
****************************/
void file_read(void);			//ファイル読み込み


/****************************
変数宣言
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
ゲームメイン画面：初期化処理
引　数：なし
戻り値：エラー情報
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
ゲームメイン画面：更新処理
引　数：なし
戻り値：なし
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
ゲームメイン画面：描画処理
引　数：なし
戻り値：なし
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
				//DrawFormatString(450, HEIGHT, 0xED215B, "スタート");
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
			//if ((arand >= 0) && (arand < 3))	//一文字
			//{
			//	DrawRotaFormatString(900, HEIGHT, 2.0, 2.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 3) && (arand < 23))	//二文字
			//{
			//	DrawRotaFormatString(800, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 23) && (arand < 48))	//三文字
			//{
			//	DrawRotaFormatString(700, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 48) && (arand < 67))	//四文字
			//{
			//	DrawRotaFormatString(650, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 67) && (arand < 84))	//五文字
			//{
			//	DrawRotaFormatString(550, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 84) && (arand < 90))	//六文字
			//{
			//	DrawRotaFormatString(450, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 90) && (arand < 93))	//七文字
			//{
			//	DrawRotaFormatString(350, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 93) && (arand < 97))	//八文字
			//{
			//	DrawRotaFormatString(300, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else if ((arand >= 97) && (arand < 100))	//九文字
			//{
			//	DrawRotaFormatString(200, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
			//}
			//else										//十文字以上
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
ゲームメイン画面：ファイル読み込み処理
引　数：なし
戻り値：なし
****************************/
void file_read(void)
{
	FILE* fp = NULL;
	int i, a;

	OutputDebugString("ファイルを読み込みます");
	fopen_s(&fp, ODAI_FILE, "r");


	if (fp == NULL)
	{
		OutputDebugString("ファイルが読み込めません");
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