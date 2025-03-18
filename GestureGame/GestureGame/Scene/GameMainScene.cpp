#include "DxLib.h"
#include "GameMainScene.h"
#include "SceneManager.h"
#include "../Utility/InputControl.h"
#include <string.h>


/****************************
マクロ定義
****************************/
#define ODAI_FILE		("dat/odai_ansi.csv")		//お題をcsvで管理しているので書いてます。
#define ODAI_MAX		(232)						//csvに入っているお題の個数
#define ODAI_NAME_LEN	(25)						//マルチバイト文字のことを考えて12文字は24みたいな感じに多く書いてある
#define ODAI_LIST_MAX	(50)						//実行した時に出すお題の最大個数
#define PI				(3.14f)						//回転率
#define HEIGHT			(490)						//文字の中心座標
#define RAND_MAX		(230)						//お題をランダムで入れたいからそのMAX値

/****************************
型定義
****************************/
typedef struct
{
	int num;
	char odai[ODAI_NAME_LEN];
}J_ODAI;	
//csvの中からこちらに格納するために構造体で作った
//numは文字の個数を格納するところ
//odaiは文字列を格納している。

/****************************
プロトタイプ宣言
****************************/
void Odai_Store();		//お題格納するための関数


/****************************
変数宣言
****************************/
J_ODAI Odai_Read[ODAI_MAX];			//csvのお題を格納するために必要
J_ODAI Odai_List[ODAI_LIST_MAX];	//実行時のお題を格納するために必要
int gamemain_background;			//背景の変数
int around;							//お題を回す変数
int countflag;						//カウントダウンのフラグかお題を出すのか見るフラグ
int count;							//カウントダウンでカウントする値
int successfulcount;				//正解をカウントする変数
int passcount;						//パスの数をカウントする関数
int signal;							//数字を表示させるのに変数に格納している
float count_fontsize;				//カウントダウンのフォントの大きさを変える

/****************************
ゲームメイン画面：初期化処理
引　数：なし
戻り値：エラー情報
****************************/
int GameMainScene_Initialize(void)
{
	int ret = D_NORMAKITY;

	//お題をcsvから読み込む
	file_read();

	//お題を格納する準備する関数
	Odai_Store();

	//後ろ背景画像を読み込んでいる
	gamemain_background = LoadGraph("texture/back.png");

	//ちゃんと読み込まれているのか確認
	if (gamemain_background == D_ERROR)
	{
		ret = D_ERROR;
	}

	//各種変数の初期化
	around = 0;
	countflag = 1;
	count = 0;
	signal = 3;
	count_fontsize = 1.0f;
	successfulcount = 0;
	passcount = 0;

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
		//カウントダウンの制御をしているが、
		//作った本人も忘れている
		
		//カウントを増やしている
		count++;

		//カウントのフォントを大きくする
		count_fontsize += 0.008f;

		//ここが忘れているポイントなんで80カウントで割って0だったらにしたのかが不明だが
		//イイ感じになってるから80にしたはず
		if (count % 80 == 0)
		{
			//カウントの数字を一つ減らしている
			signal--;

			//カウントのフォントを初期値に戻す
			count_fontsize = 1.0f;
		}

		//カウントが終わったらゲーム終了しなくてもいいように初期化しておく
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
		//お題を描画中の時の操作
		//Enterキーとマウスの左クリックでお題、成功と
		//次のお題を出す。
		if ((GetKeyFlag(KEY_INPUT_RETURN) == TRUE) || (GetMouseFlag(MOUSE_INPUT_1) == TRUE))
		{
			around += 1;
			successfulcount += 1;
		}

		//バックスペースキーとマウスのホイールをクリックするとタイトルに戻る
		if ((GetKeyFlag(KEY_INPUT_BACK) == TRUE) || (GetMouseFlag(MOUSE_INPUT_3) == TRUE))
		{
			Change_Scene(E_TITLE);
		}

		//スペースキーとマウスの右クリックでお題、パスと
		//次のお題を出す。
		if ((GetKeyFlag(KEY_INPUT_SPACE) == TRUE) || (GetMouseFlag(MOUSE_INPUT_2) == TRUE))
		{
			around += 1;
			passcount += 1;
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
	//背景を描画
	DrawRotaGraph(990, 540, 1.0, 0, gamemain_background, TRUE);

	//成功とパスの数を描画
	DrawFormatString(50, 0, 0xED215B, "成功:%d パス数:%d",successfulcount,passcount);
	
	SetFontSize(180);
	
	//フラグで管理していて1ならカウントダウン
	//2ならお題を描画という感じです。
	if (countflag == 1)
	{
		//カウントダウンの描画をしています。
		switch (signal)
		{
		case 0:
			break;
		case 1:
			DrawRotaFormatString(1000, 540, count_fontsize, count_fontsize, 50, 90, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "1");
			break;
		case 2:
			DrawRotaFormatString(1000, 540, count_fontsize, count_fontsize, 50, 90, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "2");
			break;
		case 3:
			DrawRotaFormatString(1000, 540, count_fontsize, count_fontsize, 50, 95, PI * 6, 0xED215B, 0xFFFFFF, FALSE, "3");
			break;
		default:
			break;
		}
	}
	else
	{
		//この中は文字がきれいに見えるように均等に分けております。
		if (Odai_List[around].num == 1)			//一文字
		{
			DrawRotaFormatString(790, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 2)	//二文字
		{
			DrawRotaFormatString(540, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 3)	//三文字
		{
			DrawRotaFormatString(300, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 4)	//四文字
		{
			DrawRotaFormatString(80, 390, 2.5, 2.5, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 5)	//五文字
		{
			DrawRotaFormatString(65, 390, 2.0, 2.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 6)	//六文字
		{
			DrawRotaFormatString(450, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 7)	//七文字
		{
			DrawRotaFormatString(350, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 8)	//八文字
		{
			DrawRotaFormatString(300, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 9)	//九文字
		{
			DrawRotaFormatString(200, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 10)	//十文字以上
		{
			DrawRotaFormatString(150, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
		}
		else if (Odai_List[around].num == 11)	//十一文字以上
		{
			DrawRotaFormatString(100, HEIGHT, 1.0, 1.0, 0, 0, PI / -2, 0x000000, 0, TRUE, "%s", Odai_List[around].odai);
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
	//ファイルの読み込みに使う
	FILE* fp = NULL;
	int i;


	OutputDebugString("========ファイルを読み込みます========\n");

	//ここでファイルを読み込んでいる
	fopen_s(&fp, ODAI_FILE, "r");

	//ファイルがうまく読み込めなかったらデバックに文字列表示
	//うまく行ったらOdai_Readの配列に格納される。
	if (fp == NULL)
	{
		OutputDebugString("========ファイルが読み込めません========\n");
	}
	else
	{
		//ひとつひとつ配列に格納している。
		for (i = 0; i < ODAI_MAX; i++)
		{
			fscanf_s(fp, "%d, %s,\n", &Odai_Read[i].num, Odai_Read[i].odai, ODAI_NAME_LEN);
		}

		//必ずファイルをクローズさせないとプログラムが物故割れるので消さないで
		fclose(fp);

		OutputDebugString("========ファイルを読み込みました========\n");
	}

	
}

/****************************
ゲームメイン画面：お題格納
引　数：なし
戻り値：なし
****************************/
void Odai_Store()
{

	int odai[ODAI_LIST_MAX];

	//0だと0番目を見てしまうので-1を入れている。
	for (int i = 0; i < ODAI_LIST_MAX; i++)
	{
		odai[i] = -1;
	}

	//この中で231個のお題を50個まで絞ってゲームのお題に格納している。
	for (int i = 0; i < ODAI_LIST_MAX; i++)
	{
		int randint;		//ランダムの値が欲しいのでランダムintにしている。
		while (1)
		{

			int isexist = FALSE;	//数字が存在しているのかどうか確認するフラグ
			randint = GetRand(RAND_MAX);	//ランダムで値を入れています。
			
			//odai配列の中に同じ値が入っていないのか確認するループ文
			for (int k = 0; k < ODAI_LIST_MAX; k++)
			{
				//同じ値があったら飛ばす。
				if (odai[k] == randint)
				{
					isexist = TRUE;
					break;
				}
			}
			//同じ値が無かったらブレイクしてwhile文を抜ける
			if (isexist != TRUE)
			{
				break;
			}
		}
		//ランダムの値をお題の配列に格納している
		odai[i] = randint;

		//csvから読み込ん値をゲームで使うリストに格納している
		Odai_List[i].num = Odai_Read[randint].num;

		//こっちはcsvから読み込んだ文字列をゲームで使うリストに格納している
		strcpy_s(Odai_List[i].odai, Odai_Read[randint].odai);		
	}
}