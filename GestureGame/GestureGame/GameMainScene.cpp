#include "GameMainScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "InputControl.h"
#include <math.h>


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
J_ODAI Odai_List[ODAI_MAX];
int gamemain_background;
int arand;
int roulette;
int flag;

/****************************
ゲームメイン画面：初期化処理
引　数：なし
戻り値：エラー情報
****************************/
int GameMainScene_Initialize(void)
{
	int ret = 0;

	file_read();
	
	gamemain_background = LoadGraph("texture/back.png");
	arand = 0;
	roulette = 0;
	flag = 0;

	return ret;
}

/****************************
ゲームメイン画面：更新処理
引　数：なし
戻り値：なし
****************************/
void GameMainScene_Update(void)
{	
	if (flag == 0)
	{
		roulette++;
		if ((GetKeyFlag(KEY_INPUT_RETURN) == TRUE) || (GetMouseFlag(MOUSE_INPUT_1) == TRUE))
		{
			flag = 1;
			arand = GetRand(100);
		}
	}
	else
	{
		if ((GetKeyFlag(KEY_INPUT_RETURN) == TRUE) || (GetMouseFlag(MOUSE_INPUT_1) == TRUE))
		{
			flag = 0;
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
	//DrawGraph(0, 0, gamemain_background, TRUE);
	DrawRotaGraph(990, 540, 1.0, 0, gamemain_background, TRUE);

	SetFontSize(180);
	if (flag == 1)
	{
		//if ((arand >= 0) && (arand < 3))	//一文字
		//{
		//	DrawRotaFormatString(900, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
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
		//	DrawRotaFormatString(550, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		//}
		//else if ((arand >= 67) && (arand < 84))//五文字以上
		//{
		//	DrawRotaFormatString(500, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		//}
		//else if((arand >= 84) && (arand < 90))
		//{
		//	DrawRotaFormatString(600, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[arand].odai);
		//}


		DrawRotaFormatString(800, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[67].odai);
	}
	else
	{
		DrawRotaFormatString(800, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[roulette % 10].odai);
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
	int i;

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
			fscanf_s(fp, "%s,\n",Odai_List[i].odai, ODAI_NAME_LEN);
		}
		fclose(fp);
	}

	

}