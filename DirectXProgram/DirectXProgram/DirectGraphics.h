#ifndef DIRECT_GRAPHICS_H
#define DIRECT_GRAPHICS_H

// DirectGraphicsで必要な関数が定義されているヘッダーファイル
#include <d3d9.h>
#include <d3dx9.h>

/*
	@brief DirectGraphics初期化関数
	@details 描画を使用するための初期化を行う
	@retval true
*/

bool InitDirectGraphics(HWND window_handle);

void ReleaseDirectGraphics();
#endif // DIRECT_GRAPHICS_H
