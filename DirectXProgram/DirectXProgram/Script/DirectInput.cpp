#include "DirectInput.h"

LPDIRECTINPUT8 g_InputInterface;			// DIRECTINPUT8のポインタ
LPDIRECTINPUTDEVICE8 g_InputKeyboardDevice;	// Keyboard用Deviceのポインタ

InputState g_KeyStates[256];	// キー情報の保存用

InputState UpdateInputState(bool is_push, InputState state);

InputState UpdateInputState(bool is_push, InputState state)
{
	if(is_push == true)
	{
		// 前回押されていなかった
		if(state == InputState::NoHeld)
		{
			return InputState::Pushed;
		}
		// 前回押された or 前回押されている
		else if(state == InputState::Pushed ||
				state == InputState::Held)
		{
			return InputState::Held;
		}
	}
	else
	{
		// 前回押されている or 前回押された
		if(state == InputState::Pushed ||
			state == InputState::Held)
		{
			return InputState::Released;
		}
	}

	return InputState::NoHeld;
}

bool InitDirectInput()
{
	/*
		GetModuleHandle => 現在のアプリのインスタンスハンドルを取得できる
	*/
	HRESULT hr = DirectInput8Create(
		GetModuleHandle(nullptr),	//インスタンスハンドル
		DIRECTINPUT_VERSION,		// DirectInputのバージョン(固定値)
		IID_IDirectInput8,			// 使用する機能(固定値)
		(void**)&g_InputInterface,	// 作成されたIDirectInput8保存用変数指定
		nullptr						// nullptr固定
	);

	if(FAILED(hr))
	{
		// 失敗
		return false;
	}

	/*
		GUID_SysKeyboard => キーボードを使用する

		DirectInputはLPDIRECTDEVICE8一つにつき一つのデバイスを扱える

		例：
			キーボード、マウスを扱う場合
			LPDIRECTDEVICE8は二つ必要
	*/
	hr = g_InputInterface->CreateDevice(
		GUID_SysKeyboard,			// 使用するデバイス
		&g_InputKeyboardDevice,		// 作成されたIDirectInputDevice8保存用変数指定
		nullptr						// nullptr固定
	);

	if(FAILED(hr))
	{
		// 失敗
		return false;
	}

	/*
		作成されたデバイスをフォーマット(初期化)する
	*/
	hr = g_InputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hr))
	{
		// 失敗
		return false;
	}

	/*
		FindWindow(クラスネーム、ウィンドウネーム)

			指定した名前のウィンドウを見つけてハンドルに返す
	*/
	// 協調モード設定
	hr = g_InputKeyboardDevice->SetCooperativeLevel(
		FindWindow(TEXT("WindowClass"), nullptr),
		DISCL_BACKGROUND | DISCL_NONEXCLUSIVE 
	);

	if(FAILED(hr))
	{
		// 失敗
		return false;
	}

	// 制御開始
	hr = g_InputKeyboardDevice->Acquire();
	if(FAILED(hr))
	{
		// 失敗
		return false;
	}

	//成功
	return true;
}

void UpdateDirectInput()
{
	// キーボード情報格納用
	BYTE key_states[256];
	HRESULT hr;

	/*
		関数成功で第二引数にキーボード情報が保存される

		256 => DirectInputによるキーボードデバイスの情報の数
	*/
	hr = g_InputKeyboardDevice->GetDeviceState(
		256,			// デバイス情報のサイズ
		key_states		// デバイス情報格納用変数指定
	);
	if(SUCCEEDED(hr))
	{
		for(int i = 0; i < 256; i++)
		{
			bool is_push = false;

			if(key_states[i] & 0x80)
			{
				is_push = true;
			}

			// キーの状態を更新する
			g_KeyStates[i] = UpdateInputState(is_push, g_KeyStates[i]);
		}
	}
}

void ReleaseDirectInput()
{
	if(g_InputKeyboardDevice != nullptr)
	{
		// 制御停止 <= Input系のデバイスでは必要
		g_InputKeyboardDevice->Unacquire();

		//デバイスを解散
		g_InputKeyboardDevice->Release();
		g_InputKeyboardDevice = nullptr;
	}

	if(g_InputInterface != nullptr)
	{
		// インターフェースを解散
		g_InputInterface->Release();
		g_InputInterface = nullptr;
	}
}

bool IsKeyHeld(int key)
{
	// 要素番号以外が設定されていないかチェック
	if(key < 0 || key >= 256)
	{
		return false;
	}

	return g_KeyStates[key] == InputState::Held ? true : false;
}

bool IsKeyPushed(int key)
{
	// 要素番号以外が設定されていないかチェック
	if(key < 0 || key >= 256)
	{
		return false;
	}

	if(g_KeyStates[key] == InputState::Pushed)
	{
		return true;
	}

	return false;
}

bool IsKeyReleased(int key)
{
	// 要素番号以外が設定されていないかチェック
	if(key < 0 || key >= 256)
	{
		return false;
	}

	return g_KeyStates[key] == InputState::Released ? true : false;
}