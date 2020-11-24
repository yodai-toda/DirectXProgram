#include "DirectGraphics.h"

LPDIRECT3D9 g_Interface = nullptr;
LPDIRECT3DDEVICE9 g_Device = nullptr;
// テクスチャデータ
LPDIRECT3DTEXTURE9 g_Textures[TextureID::TexIDMax];
/*
	TexIDRailgun,	// Res/Railgun.png
	TexIDKanzaki,	// Res/Kanzaki.png
*/
LPCWSTR g_TextureNameList[] =
{
	TEXT("Res/Railgun.png"),	// TexIDRailgun
	TEXT("Res/Kanzaki.png"),	// TexIDKanzaki
};

bool InitDirectGraphics(HWND window_handle)
{
	/*
		Direct3DCreate9
			IDirect3D9生成関数

			引数：
				DirectXのバージョン(D3D_SDK_VERSION固定)

			戻り値：
				成功；
					IDirect3D9*
				失敗：
					nullptr
	*/
	g_Interface = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_Interface == nullptr)
	{
		// 初期化失敗
		return false;
	}
	
	// Deviceの情報を設定するための構造体
	D3DPRESENT_PARAMETERS parameters;

	// 指定されたデータをサイズ分だけ0で初期化する
	ZeroMemory(&parameters, sizeof(D3DPRESENT_PARAMETERS));

	// バックバッファのフォーマット
	// D3DFMT_UNKNOWN => 知りません
	parameters.BackBufferFormat = D3DFMT_UNKNOWN;

	// ウィンドウ指定
	/*
		true => ウィンドウモード

		false => フルスクリーンモード
				※フルスクリーンは別途情報を指定する必要がある
	*/
	parameters.Windowed = true;

	/*
		バックバッファとフロントバッファの切り替え方法
			D3DSWAPEFFECT_DISCARD => 自動設定
	*/
	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;

	HRESULT result = g_Interface->CreateDevice(
		// ディスプレイアダプタの種類
		D3DADAPTER_DEFAULT,
		// デバイスの種類
		D3DDEVTYPE_HAL,
		// デバイスが使用するウィンドウのハンドル
		window_handle,
		// デバイス制御の方法
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		// PRESENT_PARAMETERS
		&parameters,
		// Deviceの保存変数指定
		&g_Device
	);

	/*
		FAILED => HRESULTの結果を判断してくれるマクロ
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
		//Release => 解放関数
		g_Device->Release();
		// 解放後の不正アクセス対応
		g_Device = nullptr;
	}
	if (g_Interface != nullptr)
	{
		//Release => 解放関数
		g_Interface->Release();
		// 解放後の不正アクセス対応
		g_Interface = nullptr;
	}
}

void StartDrawing()
{
	// バックバッファをクリアする
	g_Device->Clear(
		0,						// 0固定
		nullptr,				// nullptr固定
		D3DCLEAR_TARGET,		// D3DCLEAR_TARGET固定
		D3DCOLOR_XRGB(0, 0, 0),	// 塗りつぶす色
		1.0f,					// 1.0f固定
		0						// 0固定
	);

	// DirectXで描画を開始する
	g_Device->BeginScene();
}

void FinishDrawing()
{
	// DirectXの描画を終了する
	g_Device->EndScene();

	// バックバッファをフロントバッファに転送する
	g_Device->Present(nullptr, nullptr, nullptr, nullptr);
}

void DrawPorigon()
{
	CustomVertex vertices[] =
	{
		{ 300.0f, 100.0f, 0.0f, 1.0f, 0xffffff },
		{ 500.0f, 300.0f, 0.0f, 1.0f, 0xffffff },
		{  50.0f, 300.0f, 0.0f, 1.0f, 0xffffff }
	};

	// DirectXに頂点構造情報を通知
	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,		// ポリゴンの作り方
		1,						// ポリゴンの数
		vertices,				// 頂点リスト
		sizeof(CustomVertex)	// 1頂点のサイズ
	);
}

void DrawPorigonWithTriangleList()
{
	CustomVertex vertices[] =
	{
		// 1つ目
		{   0.0f,   0.0f, 0.0f, 1.0f, 0xff0000 },
		{ 100.0f,   0.0f, 0.0f, 1.0f, 0xff0000 },
		{   0.0f, 100.0f, 0.0f, 1.0f, 0xff0000 },

		// 2つ目
		{ 100.0f,   0.0f, 0.0f, 1.0f, 0x00ff00 },
		{ 100.0f, 100.0f, 0.0f, 1.0f, 0x00ff00 },
		{   0.0f, 100.0f, 0.0f, 1.0f, 0x00ff00 }
	};

	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		2,						// 描画するポリゴン => 2
		vertices,
		sizeof(CustomVertex)
	);
}

void DrawPorigonWithTriangleStrip()
{
	CustomVertex vertices[] =
	{
		{ 300.0f,   0.0f, 0.0f, 1.0f, 0xffffff },
		{ 350.0f,   0.0f, 0.0f, 1.0f, 0x808080 },
		{ 300.0f, 200.0f, 0.0f, 1.0f, 0x808080 },
		{ 350.0f, 200.0f, 0.0f, 1.0f, 0x000000 }
	};

	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,	// D3DPT_TRIANGLESTRIPでポリゴン作成
		2,
		vertices,
		sizeof(CustomVertex)
	);
}

void DrawPorigonWithTriangleFan()
{
	CustomVertex vertices[] =
	{
		{ 540.0f, 380.0f, 0.0f, 1.0f, 0xffffff },
		{ 640.0f, 380.0f, 0.0f, 1.0f, 0xffffff },
		{ 640.0f, 480.0f, 0.0f, 1.0f, 0xffffff },
		{ 540.0f, 480.0f, 0.0f, 1.0f, 0xffffff }
	};

	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertices,
		sizeof(CustomVertex)
	);
}

void DrawRect(float X, float Y, float Z, float size, float color)
{
	CustomVertex vertices[] =
	{
		{ X    , Y    , Z, size, color },
		{ X+100, Y    , Z, size, color },
		{ X+100, Y+100, Z, size, color },
		{ X    , Y+100, Z, size, color }
	};

	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertices,
		sizeof(CustomVertex)
	);
}

void DrawPorigonWithTriangleFan(TextureID tex_id)
{
	if (g_Textures[tex_id] == nullptr)
	{
		return;
	}

	CustomVertex vertices[] =
	{
		{   0.0f,   0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
		{ 200.0f,   0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f },
		{ 200.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f },
		{   0.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f }
	};

	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// DirectX(Computer)に今回のポリゴン描画で使用するテクスチャを教える
	g_Device->SetTexture(0, g_Textures[tex_id]);

	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertices,
		sizeof(CustomVertex)
	);
}

void DrawTexture(float X, float Y, float Z, TextureID tex_id)
{
	if (g_Textures[tex_id] == nullptr)
	{
		return;
	}

	CustomVertex vertices[] =
	{
		{ X    , Y    , Z, 1.0f, 0xffffff, 0.0f, 0.0f},
		{ X+288, Y    , Z, 1.0f, 0xffffff, 1.0f, 0.0f},
		{ X+288, Y+480, Z, 1.0f, 0xffffff, 1.0f, 1.0f},
		{ X    , Y+480, Z, 1.0f, 0xffffff, 0.0f, 1.0f}
	};
	
	g_Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	g_Device->SetTexture(0, g_Textures[tex_id]);

	g_Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertices,
		sizeof(CustomVertex)
	);
}

bool LoadTexture(TextureID tex_id)
{
	HRESULT hr = D3DXCreateTextureFromFile(
		g_Device,					// DirectX9のデバイス
		g_TextureNameList[tex_id],	// ファイル名
		&g_Textures[tex_id]			// 読み込まれたテクスチャじょうほうが保存される変数
	);

	// FAILED => HRESULT型の変数を指定して、その値が失敗していたらtrue
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void ReleaseTexture()
{
	for (int i = 0; i < TextureID::TexIDMax; i++)
	{
		if (g_Textures[i] != nullptr)
		{
			g_Textures[i]->Release();
			g_Textures[i] = nullptr;
		}
	}
}
