#include <Windows.h>
#include "DirectGraphics.h"
#include "DirectInput.h"

// pragma commentによるlibファイルの設定
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

/*
	ウィンドウプロシージャ
		戻り値：LRESULT 　　実行結果
		引数　：HWND　　　　メッセージの対象となっているウィンドウのハンドル
					HWND		ウィンドウハンドルを保存する型
				UINT　　　　メッセージ情報、クリックされた等の情報が保存されている
				WPARAM　　　メッセージ付加情報その１
				LPARAM　　　メッセージ付加情報その２
				付加情報にはメッセージ情報の補足情報が保存されている
					例：キーの詳細情報(大文字、小文字など)
*/
LRESULT CALLBACK WindowProcedure(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		// メッセージを何も対応しないときに実行する関数
		// 引数にはウィンドウプロシージャで渡されている引数そのまま渡す
		return DefWindowProc(window_handle, message_id, wparam, lparam);
	}
	return 0;
}

/*
	WinMain
		Windowsアプリにおいてのエントリーポイント
		戻り値：アプリ結果0を返しとくとOK
		引数　：HINSTANCE hInstace		アプリのインスタンスハンドル	H => Handleの略
			　　HINSTANCE hPrevInstance		古い仕様の残りなので使わない	情報としての勝ちはない
				LPSTR lpCmpLine		コマンドラインのパラメータのリスト
				INT nCmdShow		コマンドラインの引数の数
*/
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR	  lpCmpLine,
	INT		  nCmdShow)
{
	// ウィンドウの生成(メインループ前)
	WNDCLASS window_class =
	{
		CS_HREDRAW | CS_VREDRAW,			// クラスのスタイル(CS_HREDRAW と CS_VREDRAWは横と縦の変更許可設定)
		WindowProcedure,					// ●ウィンドウプロシージャ
		0,									// 補助メモリ(0固定で問題ない)
		0,									// 補助メモリ(0固定で問題ない)
		hInstance,							// ●このプログラムのインスタンスハンドル
		LoadIcon(nullptr, IDI_APPLICATION),	// アイコン画像
		LoadCursor(nullptr, IDC_ARROW),		// カーソル画像
		nullptr,							// 背景ブラシ
		nullptr,							// メニュー名
		// TEXT() char* => wchar_t* に変換してくれる
		TEXT("WindowClass"),				// ●クラス名
	};

	// 初期化したウィンドウ情報を登録する
	/*
		RegisterClass
			ウィンドウ情報を登録する関数
		戻り値	非0 => 登録成功、	0 => 登録失敗
	*/
	if (RegisterClass(&window_class) == 0)
	{
		// 失敗
		return 0;
	}

	int width = 640;
	int height = 480;


	// ウィンドウ作成
	HWND window_handle = CreateWindow(
		// ●登録しているウィンドウクラス構造体の名前
		TEXT("WindowClass"),
		// ●ウィンドウ名(タイトルバーに表示される文字列)
		TEXT("ウィンドウ生成サンプル"),
		// ウィンドウスタイル
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME),
		// ●表示位置
		/*
			ウィンドウを表示する位置を指定する
			(CW_USEDEFAULT => OS任せ)
		*/
		CW_USEDEFAULT,	// x軸
		CW_USEDEFAULT,	// y軸
		// ●サイズ => ウィンドウのサイズ
		width,
		height,
		// 親ハンドル
		NULL,
		// メニューハンドル
		NULL,
		// ●インスタンスハンドル
		// WinMainの第一引数を使用
		hInstance,
		// WM_CREATEメッセージでlpparamに渡したい値
		NULL);

	RECT window_rect;

	if (GetWindowRect(window_handle, &window_rect) == false)
	{
		// 失敗
		return 0;
	}

	RECT client_rect;

	if (GetClientRect(window_handle, &client_rect) == false)
	{
		// 失敗
		return 0;
	}

	// フレームサイズの算出
	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);

	// リサイズ用のサイズの算出
	int resize_width = frame_size_x + width;
	int resize_height = frame_size_y + height;

	// ウィンドウサイズの更新
	SetWindowPos(
		window_handle,
		nullptr,
		// 表示座標
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		// ●リサイズの横幅
		resize_width,
		// ●リサイズの縦幅
		resize_height,
		// オプションの設定
		SWP_NOMOVE
	);

	// ウィンドウ表示
	ShowWindow(window_handle, SW_SHOW);

	if (InitDirectGraphics(window_handle) == false)
	{
		return 0;
	}

	if (InitDirectInput() == false)
	{
		return 0;
	}

	if (LoadTexture(TextureID::TexIDRailgun) == false)
	{
		return 0;
	}

	if (LoadTexture(TextureID::TexIDKanzaki) == false)
	{
		return 0;
	}

	// メインループ
	while (true)
	{
		// フレーム管理
		/*
			フレーム管理はループが一定周期になるように管理する
			例えば60FPSでゲームが進行するなら、1回のループは約0.016秒で実行する
			※DirectXが60FPSでフレーム管理を自動で行うので今回はDirectXに管理は任せる
		*/
		// メッセージ対応
		/*
			Windows(OS)から送られてくるメッセージの対応を行う必要がある
			メッセージの例
			ウィンドウをクリックした、ウィンドウの×ボタンをクリックした
		*/
		MSG message;

		/*
			GetMwssage
				Windowsからメッセージが通知されるまで次の処理まで移行しない
				if(GetMessage(&message, nullptr, 0, 100)){}
		*/
		/*
			PeekMessage
				メッセージの有無にかかわらず次の処理を実行する
				戻り値：true => メッセージ有り	false => メッセージ無し
				第一引数：受信したメッセージ情報
				第二～第五引数：固定値で問題ない
		*/
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// 受信したデータを翻訳する
				TranslateMessage(&message);
				// ウィンドウプロシージャの送信する
				DispatchMessage(&message);
			}
		}
		else
		{
			UpdateDirectInput();

			// ゲームに関連する処理
			// ゲーム処理と描画処理を実装する

			// カメラの設定
			SetUpView();

			StartDrawing();

			// 2Dオブジェクトの描画
			//DrawPorigon();

			//DrawPorigonWithTriangleList();

			//DrawPorigonWithTriangleStrip();

			//DrawPorigonWithTriangleFan();

			//DrawRect(540.0f, 0.0f, 0.0f, 1.0f, 0x00ffff);

			//DrawPorigonWithTriangleFan( TextureID::TexIDRailgun );

			//DrawTexture(352.0f, 0.0f, 0.0f, TextureID::TexIDKanzaki);

			// 3Dオブジェクトの描画
			Draw3DPorigon();

			Draw3DPorigon(3.0f, 0.0f, 0.0f, 0xff0000ff);

			FinishDrawing();
		}
	}

	// 解放
	ReleaseTexture();
	ReleaseDirectInput();
	ReleaseDirectGraphics();

	return 0;
}

