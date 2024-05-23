#include "Demo.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "InputControl.h"



/****************************
変数宣言
****************************/
int demo_background;			//デモの背景画像




/****************************
デモ画面：初期化処理
引　数：なし
戻り値：エラー情報
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
デモ画面：更新処理
引　数：なし
戻り値：なし
****************************/
void Demo_Update(void)
{
	if ((GetKeyFlag(KEY_INPUT_BACK) == TRUE) || (GetMouseFlag(MOUSE_INPUT_3) == TRUE))
	{
		Change_Scene(E_TITLE);
	}
}

/****************************
デモ画面：描画処理
引　数：なし
戻り値：なし
****************************/
void Demo_Draw(void)
{
	DrawFormatString(650, 490, 0XED215B, "デモだよ");
}