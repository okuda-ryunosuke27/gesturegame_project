#include "SceneManager.h"
#include "DxLib.h"
#include "Title.h"
#include "GameMainScene.h"
#include "Demo.h"

/****************************
変数宣言
****************************/
GAME_MODE game_mode;
GAME_MODE next_mode;
int read_error;

/****************************
シーン管理機能：初期化処理
引　数：ゲームモード情報
戻り値：なし
****************************/
int SceneManager_Initialize(GAME_MODE mode)
{
	read_error = D_NORMAKITY;
	switch (mode)
	{
		case E_TITLE:
			read_error = Title_Initialize();
			break;
		case E_GAMEMAIN:
			read_error = GameMainScene_Initialize();
			break;
		case E_DEMO:
			read_error = Demo_Initialize();
			break;
		default:
			break;
	}

	game_mode = mode;
	next_mode = game_mode;

	return read_error;
}

/****************************
シーン管理機能：更新処理
引　数：なし
戻り値：なし
****************************/
void SceneManager_Update(void)
{
	//前フレームとゲームモードが違ってたらシーンを切り替える
	if (game_mode != next_mode)
	{
		SceneManager_Initialize(next_mode);
	}

	switch (game_mode)
	{
		case E_TITLE:
			Title_Update();
			break;
		case E_GAMEMAIN:
			GameMainScene_Update();
			break;
		case E_DEMO:
			Demo_Update();
			break;
	default:
		break;
	}
}

/****************************
シーン管理機能：描画処理
引　数：なし
戻り値：なし
****************************/
void SceneManager_Draw(void)
{
	switch (game_mode)
	{
		case E_TITLE:
			Title_Draw();
			break;
		case E_GAMEMAIN:
			GameMainScene_Draw();
			break;
		case E_DEMO:
			Demo_Draw();
			break;
	default:
		break;
	}
}

/****************************
シーン管理機能：シーン変更処理
引　数：変更するゲームモード
戻り値：なし
****************************/
void Change_Scene(GAME_MODE mode)
{
	next_mode = mode;
}