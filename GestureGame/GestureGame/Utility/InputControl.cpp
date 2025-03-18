#include "DxLib.h"
#include "InputControl.h"

/****************************
マクロ定義
****************************/
#define KEY_INPUT_MAX		(255)

/****************************
変数宣言
****************************/
char old_key[KEY_INPUT_MAX];
char now_key[KEY_INPUT_MAX];
int old_button;
int now_button;

/****************************
入力制御機能：初期化処理
引　数：なし
戻り値：なし
****************************/
void Input_Initialize(void)
{
	for (int i = 0; i < KEY_INPUT_MAX; i++)
	{
		old_key[i] = NULL;
		now_key[i] = NULL;
	}

	old_button = NULL;
	now_button = NULL;
}

/****************************
入力制御機能：更新処理
引　数：なし
戻り値：なし
****************************/
void Input_Update(void)
{
	//キーボード入力情報の取得
	for (int i = 0; i < KEY_INPUT_MAX; i++)
	{
		old_key[i] = now_key[i];
	}

	//キーステータスをすべて取得する
	GetHitKeyStateAll(now_key);

	//マウスの入力情報を取得する
	old_button = now_button;
	now_button = GetMouseInput();
}

/****************************
入力制御機能：ESCキー入力チェック
引　数：なし
戻り値：TRUE(入力された)、FALSE(未入力)
****************************/
int Input_Escape(void)
{
	int ret = FALSE;

	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ret = TRUE;
	}
	return ret;
}

/*********************************
入力制御機能：入力情報取得処理(離した瞬間)
引　数：指定するキーボード
戻り値：TRUE(入力された)、FALSE(未入力)
*********************************/
int GetOldKey(int key)
{
	int ret = FALSE;
	for (int i = 0; i < KEY_INPUT_MAX; i++)
	{
		if ((key & old_key[i]) != FALSE)
		{
			ret = TRUE;
		}
	}
	return ret;
}

/*********************************
入力制御機能：入力情報取得処理(押している)
引　数：指定するキーボード
戻り値：TRUE(入力された)、FALSE(未入力)
*********************************/
int GetNowKey(int key)
{
	int ret = FALSE;
	for (int i = 0; i < KEY_INPUT_MAX; i++)
	{
		if ((key & now_key[i]) != FALSE)
		{
			ret = TRUE;
		}
	}
	return ret;
}

/*********************************
入力制御機能：入力情報取得処理(押した瞬間)
引　数：指定するキーボード
戻り値：TRUE(入力された)、FALSE(未入力)
*********************************/
int GetKeyFlag(int key)
{
	int ret = FALSE;

	if ((now_key[key] & ~old_key[key]) != FALSE)
	{
		ret = TRUE;
	}

	return ret;
}

/*********************************
入力制御機能：入力情報取得処理(押した瞬間)
引　数：指定するマウスのボタン
戻り値：TRUE(入力された)、FALSE(未入力)
*********************************/
int GetMouseFlag(int key)
{
	int ret = FALSE;
	int mouseflg = now_button & ~old_button;

	if ((key & mouseflg) != FALSE)
	{
		ret = TRUE;
	}

	return ret;
}