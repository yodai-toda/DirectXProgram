#ifndef DIRECT_GRAPHICS_H
#define DIRECT_GRAPHICS_H

// DirectGraphics�ŕK�v�Ȋ֐�����`����Ă���w�b�_�[�t�@�C��
#include <d3d9.h>
#include <d3dx9.h>

/*
	@brief DirectGraphics�������֐�
	@details �`����g�p���邽�߂̏��������s��
	@retval true
*/

bool InitDirectGraphics(HWND window_handle);

void ReleaseDirectGraphics();
#endif // DIRECT_GRAPHICS_H
