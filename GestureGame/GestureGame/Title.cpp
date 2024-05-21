#include "Title.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "InputControl.h"

/****************************
マクロ定義
****************************/
#define PI    3.14f

/****************************
変数宣言
****************************/
int title_background;			//タイトル背景
int title_logo;					//タイトルロゴ
int title_spacelogo;			//タイトルメニューに入るためのあれ
int title_space_count;			//カウントをプラスにする変数
int title_space_count_change;	//スペースカウントをマイナスにする変数
double title_logo_change;			//角度をマイナスにする変数
double title_logo_angle;		//角度をプラスにする

/****************************
タイトル画面：初期化処理
引　数：なし
戻り値：エラー情報(-1異常あり,-1以外:正常終了)
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
タイトル画面：更新処理
引　数：なし
戻り値：なし
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
タイトル画面：描画処理
引　数：なし
戻り値：なし
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