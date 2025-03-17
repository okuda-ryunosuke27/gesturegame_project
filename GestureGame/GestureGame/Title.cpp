#include "Title.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "InputControl.h"

/****************************
マクロ定義
****************************/
#define PI				(3.14f)
#define HEIGHT			(350)

/****************************
変数宣言
****************************/
int title_background;			//タイトル背景
int title_logo;					//タイトルロゴ
int logo_x;						//ロゴのx軸
int logo_y;						//ロゴのy軸
int logo_y_change;				//ロゴのy軸の方向を切り替えるために作った
int logo_flag;					//ロゴの動くが起動ごとに違うようにしたいがために作った。
double title_logo_change;		//角度をマイナスにする変数
double title_logo_angle;		//角度をプラスにする

/****************************
タイトル画面：初期化処理
引　数：なし
戻り値：エラー情報(-1異常あり,-1以外:正常終了)
****************************/
int Title_Initialize(void)
{
	int ret = D_NORMAKITY;		//retの初期化

	//LoadGraphで画像を読み込んでいます。
	title_background = LoadGraph("texture/back.png");		//背景画像を読み込んでいます。
	title_logo = LoadGraph("texture/title_logo.png");		//タイトルロゴを読み込んでいます。

	//ここではしっかり読み込んでいるのか確認しています。
	//もし-1ならretに-1を入れる
	if (title_background == D_ERROR)
	{
		ret = D_ERROR;
	}
	if (title_logo == D_ERROR)
	{
		ret = D_ERROR;
	}

	//各変数の初期化を行っております。
	title_logo_angle = -270.0;
	title_logo_change = 2.0;
	logo_flag = GetRand(1);
	logo_x = -800;
	logo_y = 980;
	logo_y_change = 4;

	return ret;
}

/****************************
タイトル画面：更新処理
引　数：なし
戻り値：なし
****************************/
void Title_Update(void)
{
	
	switch (logo_flag)
	{
		//回転する
		case 0:
			title_logo_angle += title_logo_change;

			if (title_logo_angle >= 270 || title_logo_angle <= -270)
			{
				title_logo_change *= -1.0;
			}
			break;
		//ぴょんぴょん飛ぶ
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
	
	
	//キーボードとマウス操作対応しております。
	//スペースと左クリックでゲームスタート
	if ((GetKeyFlag(KEY_INPUT_SPACE) == TRUE) || (GetMouseFlag(MOUSE_INPUT_1) == TRUE))
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
	//背景描画
	DrawRotaGraph(990, 540, 1.0, 0, title_background, TRUE);

	//ロゴの描画
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