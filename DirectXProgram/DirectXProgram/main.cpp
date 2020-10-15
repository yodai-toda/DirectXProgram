#include <Windows.h>
#include "DirectGraphics.h"

// pragma comment�ɂ��lib�t�@�C���̐ݒ�
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

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
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		// ���b�Z�[�W�������Ή����Ȃ��Ƃ��Ɏ��s����֐�
		// �����ɂ̓E�B���h�E�v���V�[�W���œn����Ă���������̂܂ܓn��
		return DefWindowProc(window_handle, message_id, wparam, lparam);
	}
	return 0;
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
	WNDCLASS window_class =
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
		// TEXT() char* => wchar_t* �ɕϊ����Ă����
		TEXT("WindowClass"),				// ���N���X��
	};

	// �����������E�B���h�E����o�^����
	/*
		RegisterClass
			�E�B���h�E����o�^����֐�
		�߂�l	��0 => �o�^�����A	0 => �o�^���s
	*/
	if (RegisterClass(&window_class) == 0)
	{
		// ���s
		return 0;
	}

	int width = 640;
	int height = 480;


	// �E�B���h�E�쐬
	HWND window_handle = CreateWindow(
		// ���o�^���Ă���E�B���h�E�N���X�\���̖̂��O
		TEXT("WindowClass"),
		// ���E�B���h�E��(�^�C�g���o�[�ɕ\������镶����)
		TEXT("�E�B���h�E�����T���v��"),
		// �E�B���h�E�X�^�C��
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME),
		// ���\���ʒu
		/*
			�E�B���h�E��\������ʒu���w�肷��
			(CW_USEDEFAULT => OS�C��)
		*/
		CW_USEDEFAULT,	// x��
		CW_USEDEFAULT,	// y��
		// ���T�C�Y => �E�B���h�E�̃T�C�Y
		width,
		height,
		// �e�n���h��
		NULL,
		// ���j���[�n���h��
		NULL,
		// ���C���X�^���X�n���h��
		// WinMain�̑��������g�p
		hInstance,
		// WM_CREATE���b�Z�[�W��lpparam�ɓn�������l
		NULL);

	RECT window_rect;

	if (GetWindowRect(window_handle, &window_rect) == false)
	{
		// ���s
		return 0;
	}

	RECT client_rect;

	if (GetClientRect(window_handle, &client_rect) == false)
	{
		// ���s
		return 0;
	}

	// �t���[���T�C�Y�̎Z�o
	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);

	// ���T�C�Y�p�̃T�C�Y�̎Z�o
	int resize_width = frame_size_x + width;
	int resize_height = frame_size_y + height;

	// �E�B���h�E�T�C�Y�̍X�V
	SetWindowPos(
		window_handle,
		nullptr,
		// �\�����W
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		// �����T�C�Y�̉���
		resize_width,
		// �����T�C�Y�̏c��
		resize_height,
		// �I�v�V�����̐ݒ�
		SWP_NOMOVE
	);

	// �E�B���h�E�\��
	ShowWindow(window_handle, SW_SHOW);

	if (InitDirectGraphics(window_handle) == false)
	{
		return 0;
	}

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
			if (message.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// ��M�����f�[�^��|�󂷂�
				TranslateMessage(&message);
				// �E�B���h�E�v���V�[�W���̑��M����
				DispatchMessage(&message);
			}			
		}
		else
		{
			// �Q�[���Ɋ֘A���鏈��
			// �Q�[�������ƕ`�揈������������
		}
	}

	// ���
	ReleaseDirectGraphics();

	return 0;
}

