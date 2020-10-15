#include "DirectGraphics.h"

LPDIRECT3D9 g_Interface = nullptr;
LPDIRECT3DDEVICE9 g_Device = nullptr;


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
