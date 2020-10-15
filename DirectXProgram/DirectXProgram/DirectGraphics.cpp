#include "DirectGraphics.h"

LPDIRECT3D9 g_Interface = nullptr;
LPDIRECT3DDEVICE9 g_Device = nullptr;


bool InitDirectGraphics(HWND window_handle)
{
	/*
		Direct3DCreate9
			IDirect3D9�����֐�

			�����F
				DirectX�̃o�[�W����(D3D_SDK_VERSION�Œ�)

			�߂�l�F
				�����G
					IDirect3D9*
				���s�F
					nullptr
	*/
	g_Interface = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_Interface == nullptr)
	{
		// ���������s
		return false;
	}
	
	// Device�̏���ݒ肷�邽�߂̍\����
	D3DPRESENT_PARAMETERS parameters;

	// �w�肳�ꂽ�f�[�^���T�C�Y������0�ŏ���������
	ZeroMemory(&parameters, sizeof(D3DPRESENT_PARAMETERS));

	// �o�b�N�o�b�t�@�̃t�H�[�}�b�g
	// D3DFMT_UNKNOWN => �m��܂���
	parameters.BackBufferFormat = D3DFMT_UNKNOWN;

	// �E�B���h�E�w��
	/*
		true => �E�B���h�E���[�h

		false => �t���X�N���[�����[�h
				���t���X�N���[���͕ʓr�����w�肷��K�v������
	*/
	parameters.Windowed = true;

	/*
		�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̐؂�ւ����@
			D3DSWAPEFFECT_DISCARD => �����ݒ�
	*/
	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;

	HRESULT result = g_Interface->CreateDevice(
		// �f�B�X�v���C�A�_�v�^�̎��
		D3DADAPTER_DEFAULT,
		// �f�o�C�X�̎��
		D3DDEVTYPE_HAL,
		// �f�o�C�X���g�p����E�B���h�E�̃n���h��
		window_handle,
		// �f�o�C�X����̕��@
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		// PRESENT_PARAMETERS
		&parameters,
		// Device�̕ۑ��ϐ��w��
		&g_Device
	);

	/*
		FAILED => HRESULT�̌��ʂ𔻒f���Ă����}�N��
	*/
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void ReleaseDirectGraphics()
{
	if (g_Device != nullptr)
	{
		//Release => ����֐�
		g_Device->Release();
		// �����̕s���A�N�Z�X�Ή�
		g_Device = nullptr;
	}
	if (g_Interface != nullptr)
	{
		//Release => ����֐�
		g_Interface->Release();
		// �����̕s���A�N�Z�X�Ή�
		g_Interface = nullptr;
	}
}
