/*********************************
�W�F�X�`���[�Q�[����
������o���v���O����
*********************************/
#include "DxLib.h"
#include "FreamControl.h"
#include "InputControl.h"
#include "SceneManager.h"

/*********************************
�}�N����`
*********************************/
#define SCREEN_HEIGHT		(1080)
#define SCREEN_WIDTH		(1980)
#define SCREEN_COLORBIT		(32)
#define FONT_SIZE			(30)


/*********************************
�v���O�����̊J�n
*********************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	//�E�B���h�^�C�g���ݒ�
	SetMainWindowText("�W�F�X�`���[�Q�[��");

	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(FALSE);

	//��ʃT�C�Y�̍ő�T�C�Y,�J���[�r�b�g����ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);


	//Dx���C�u��������������
	//�G���[������������A�I������
	if (DxLib_Init() == D_ERROR)
	{
		return D_ERROR;
	}

	//�V�[���Ǘ��@�\�̏���������
	if (SceneManager_Initialize(E_TITLE) == D_ERROR)
	{
		return D_ERROR;
	}

	//�e�@�\�̏���������
	FreamControl_Initialize();	//�t���[�����[�g����@�\
	Input_Initialize();			//���͐���@�\

	//�`����ʂ𗠂ɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	//�����T�C�Y��ݒ�
	SetFontSize(FONT_SIZE);

	//�Q�[�����[�v
	while (ProcessMessage() != D_ERROR && Input_Escape() == FALSE)
	{
		//�t���[�����[�g���䏈��
		FreamControl_Update();
		//���͐���@�\�X�V����
		Input_Update();

		//��ʃN���A
		ClearDrawScreen();

		//�V�[���Ǘ��@�\�X�V����
		SceneManager_Update();

		//�V�[���Ǘ��@�\�`�揈��
		SceneManager_Draw();

		//��ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	//Dx���C�u�����g�p�̏I������
	DxLib_End();

	return 0;
}