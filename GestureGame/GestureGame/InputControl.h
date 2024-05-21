#pragma once

/****************************
プロトタイプ宣言
****************************/
void Input_Initialize(void);
void Input_Update(void);
int Input_Escape(void);

int GetOldKey(int key);
int GetNowKey(int key);
int GetKeyFlag(int key);