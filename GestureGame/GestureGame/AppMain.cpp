/*********************************
ジェスチャーゲームの
お題を出すプログラム
*********************************/
#include "DxLib.h"
#include "Utility/FreamControl.h"
#include "Utility/InputControl.h"
#include "Scene/SceneManager.h"
#include "Scene/GameMainScene.h"

/*********************************
マクロ定義
*********************************/
#define SCREEN_HEIGHT		(1080)		//画面サイズゲーミングPCの解像度基準にしています。
#define SCREEN_WIDTH		(1980)		//上に同じく
#define SCREEN_COLORBIT		(32)		//カラーを32ビットにしています。
#define FONT_SIZE			(30)


/*********************************
プログラムの開始
*********************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	//ウィンドタイトル設定
	SetMainWindowText("ジェスチャーゲーム");

	//ウィンドウモードで起動
	ChangeWindowMode(FALSE);
	//ChangeWindowMode(TRUE);

	//画面サイズの最大サイズ,カラービット数を設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);


	//Dxライブラリ初期化処理
	//エラーが発生したら、終了する
	if (DxLib_Init() == D_ERROR)
	{
		return D_ERROR;
	}

	//シーン管理機能の初期化処理
	//エラーが発生したら、終了する
	if (SceneManager_Initialize(E_TITLE) == D_ERROR)
	{
		return D_ERROR;
	}

	//各機能の初期化処理
	FreamControl_Initialize();	//フレームレート制御機能
	Input_Initialize();			//入力制御機能

	//描画先画面を裏にする
	SetDrawScreen(DX_SCREEN_BACK);

	//文字サイズを設定
	SetFontSize(FONT_SIZE);

	//一回だけにしたいので仕方なく
	//GameMainSceneを呼んでここに関数を書いています。
	file_read();

	//ゲームループ
	while (ProcessMessage() != D_ERROR && Input_Escape() == FALSE)
	{
		//フレームレート制御処理
		FreamControl_Update();
		//入力制御機能更新処理
		Input_Update();

		//画面クリア
		//必ず必要なやつ
		ClearDrawScreen();

		//シーン管理機能更新処理
		SceneManager_Update();

		//シーン管理機能描画処理
		SceneManager_Draw();

		//画面の内容を表画面に反映
		//必ず必要なやつ
		ScreenFlip();
	}

	//Dxライブラリ使用の終了処理
	DxLib_End();

	return 0;
}