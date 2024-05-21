#include "DxLib.h"
#include"FreamControl.h"

/*********************************
�}�N����`
*********************************/


/*********************************
�^��`
*********************************/



/*********************************
�ϐ��錾
*********************************/
int FreamTime;
int NowTime;
int Wait;
int LastTime;

/*********************************
�t���[������@�\�F����������
���@���F�Ȃ�
�߂�l�F�Ȃ�
*********************************/
void FreamControl_Initialize(void)
{
	FreamTime = ((int)1000.0f / FREAM_RATE);
	NowTime = 0;
	Wait = 0;
	LastTime = 0;
}

/*********************************
�t���[������@�\�F�X�V����
���@���F�Ȃ�
�߂�l�F�Ȃ�
*********************************/
void FreamControl_Update(void)
{
	NowTime = GetNowCount();
	Wait = FreamTime - (NowTime - LastTime);

	if (Wait > 0)
	{
		WaitTimer(Wait);
	}
	LastTime = GetNowCount();
}