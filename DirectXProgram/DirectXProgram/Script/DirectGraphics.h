#ifndef DIRECT_GRAPHICS_H
#define DIRECT_GRAPHICS_H

// DirectGraphicsで必要な関数が定義されているヘッダーファイル
#include <d3d9.h>
#include <d3dx9.h>

struct CustomVertex
{
	float X;
	float Y;
	float Z;
	float Rhw;
	DWORD Color;

	float Tu;
	float Tv;
};

// テクスチャの種類分のenumを作成
enum TextureID
{
	TexIDRailgun,	// Res/Railgun.png
	TexIDKanzaki,	// Res/Kanzaki.png
	TexIDMax,
};

/*
	@brief DirectGraphics初期化関数
	@details 描画を使用するための初期化を行う
	@retval true 初期化成功
	@retval false 初期化失敗
	@param[in] window_handle 描画に使用するwindowハンドル
*/
bool InitDirectGraphics(HWND window_handle);

void ReleaseDirectGraphics();

void StartDrawing();

void FinishDrawing();

void DrawPorigon();

void DrawPorigonWithTriangleList();
void DrawPorigonWithTriangleStrip();
void DrawPorigonWithTriangleFan();

void DrawRect(float X, float Y, float Z, float size, float color);

void DrawPorigonWithTriangleFan(TextureID tex_id);

void DrawTexture(float X, float Y, float Z, TextureID tex_id);

bool LoadTexture(TextureID tex_id);
void ReleaseTexture();

#endif // DIRECT_GRAPHICS_H
