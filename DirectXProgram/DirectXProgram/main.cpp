#include<Windows.h>

/*
	�E�B���h�E�v���V�[�W��
		�߂�l�FLRESULT �@�@���s����
		�����@�FHWND�@�@�@�@���b�Z�[�W�̑ΏۂƂȂ��Ă���E�B���h�E�̃n���h��
					HWND		�E�B���h�E�n���h����ۑ�����^
				UINT�@�@�@�@���b�Z�[�W���A�N���b�N���ꂽ���̏�񂪕ۑ�����Ă���
				WPARAM�@�@�@���b�Z�[�W�t����񂻂̂P
				LPARAM�@�@�@���b�Z�[�W�t����񂻂̂Q
				�t�����ɂ̓��b�Z�[�W���̕⑫��񂪕ۑ�����Ă���
					��F�L�[�̏ڍ׏��(�啶���A�������Ȃ�)
*/
LRESULT CALLBACK WindowProcedure(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	// ���b�Z�[�W�������Ή����Ȃ��Ƃ��Ɏ��s����֐�
	// �����ɂ̓E�B���h�E�v���V�[�W���œn����Ă���������̂܂ܓn��
	return DefWindowProc(window_handle, message_id, wparam, lparam);
}

/*
	WinMain
		Windows�A�v���ɂ����ẴG���g���[�|�C���g
		�߂�l�F�A�v������0��Ԃ��Ƃ���OK
		�����@�FHINSTANCE hInstace		�A�v���̃C���X�^���X�n���h��	H => Handle�̗�
			�@�@HINSTANCE hPrevInstance		�Â��d�l�̎c��Ȃ̂Ŏg��Ȃ�	���Ƃ��Ă̏����͂Ȃ�
				LPSTR lpCmpLine		�R�}���h���C���̃p�����[�^�̃��X�g
				INT nCmdShow		�R�}���h���C���̈����̐�
*/
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR	  lpCmpLine,
	INT		  nCmdShow)
{
	// �E�B���h�E�̐���(���C�����[�v�O)
	WNDCLASSA window_class =
	{
		CS_HREDRAW | CS_VREDRAW,			// �N���X�̃X�^�C��(CS_HREDRAW �� CS_VREDRAW�͉��Əc�̕ύX���ݒ�)
		WindowProcedure,					// ���E�B���h�E�v���V�[�W��
		0,									// �⏕������(0�Œ�Ŗ��Ȃ�)
		0,									// �⏕������(0�Œ�Ŗ��Ȃ�)
		hInstance,							// �����̃v���O�����̃C���X�^���X�n���h��
		LoadIcon(nullptr, IDI_APPLICATION),	// �A�C�R���摜
		LoadCursor(nullptr, IDC_ARROW),		// �J�[�\���摜
		nullptr,							// �w�i�u���V
		nullptr,							// ���j���[��
		"WindowClass",						// ���N���X��
	};

	// �����������E�B���h�E����o�^����
	/*
		RegisterClass
			�E�B���h�E����o�^����֐�
		�߂�l	��0 => �o�^�����A	0 => �o�^���s
	*/
	if (RegisterClassA(&window_class) == 0)
	{
		// ���s
		return 0;
	}

	int width = 640;
	int height = 480;


	// �E�B���h�E�쐬
	HWND window_handle = CreateWindowA(
		// �o�^���Ă���E�B���h�E�N���X�\���̖̂��O
		"WindowClass",
		// �E�B���h�E��(�^�C�g���o�[�ɕ\�������)
		"�E�B���h�E�����T���v��",
		// �E�B���h�E�X�^�C��
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME),
		// �\���ʒu
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		// �T�C�Y
		width,
		height,
		// �e�n���h��
		NULL,
		// ���j���[�n���h��
		NULL,
		// �C���X�^���X�n���h��
		hInstance,
		// WM_CREATE���b�Z�[�W��lpparam�ɓn�������l
		NULL);

	ShowWindow(window_handle, SW_SHOW);

	// ���C�����[�v
	while (true)
	{
		// �t���[���Ǘ�
		/*
			�t���[���Ǘ��̓��[�v���������ɂȂ�悤�ɊǗ�����
			�Ⴆ��60FPS�ŃQ�[�����i�s����Ȃ�A1��̃��[�v�͖�0.016�b�Ŏ��s����
			��DirectX��60FPS�Ńt���[���Ǘ��������ōs���̂ō����DirectX�ɊǗ��͔C����
		*/
		// ���b�Z�[�W�Ή�
		/*
			Windows(OS)���瑗���Ă��郁�b�Z�[�W�̑Ή����s���K�v������
			���b�Z�[�W�̗�
			�E�B���h�E���N���b�N�����A�E�B���h�E�́~�{�^�����N���b�N����
		*/
		MSG message;

		/*
			GetMwssage
				Windows���烁�b�Z�[�W���ʒm�����܂Ŏ��̏����܂ňڍs���Ȃ�
				if(GetMessage(&message, nullptr, 0, 100)){}
		*/
		/*
			PeekMessage
				���b�Z�[�W�̗L���ɂ�����炸���̏��������s����
				�߂�l�Ftrue => ���b�Z�[�W�L��	false => ���b�Z�[�W����
				�������F��M�������b�Z�[�W���
				���`��܈����F�Œ�l�Ŗ��Ȃ�
		*/
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			// ��M�����f�[�^��|�󂷂�
			TranslateMessage(&message);
			// �E�B���h�E�v���V�[�W���̑��M����
			DispatchMessage(&message);
		}
		else
		{
			// �Q�[���Ɋ֘A���鏈��
			// �Q�[�������ƕ`�揈������������
		}
	}
	return 0;
}

