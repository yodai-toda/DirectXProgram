#include<Windows.h>

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
	// メッセージを何も対応しないときに実行する関数
	// 引数にはウィンドウプロシージャで渡されている引数そのまま渡す
	return DefWindowProc(window_handle, message_id, wparam, lparam);
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
	WNDCLASSA window_class =
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
		"WindowClass",						// ●クラス名
	};

	// 初期化したウィンドウ情報を登録する
	/*
		RegisterClass
			ウィンドウ情報を登録する関数
		戻り値	非0 => 登録成功、	0 => 登録失敗
	*/
	if (RegisterClassA(&window_class) == 0)
	{
		// 失敗
		return 0;
	}

	int width = 640;
	int height = 480;


	// ウィンドウ作成
	HWND window_handle = CreateWindowA(
		// 登録しているウィンドウクラス構造体の名前
		"WindowClass",
		// ウィンドウ名(タイトルバーに表示される)
		"ウィンドウ生成サンプル",
		// ウィンドウスタイル
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME),
		// 表示位置
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		// サイズ
		width,
		height,
		// 親ハンドル
		NULL,
		// メニューハンドル
		NULL,
		// インスタンスハンドル
		hInstance,
		// WM_CREATEメッセージでlpparamに渡したい値
		NULL);

	ShowWindow(window_handle, SW_SHOW);

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
			// 受信したデータを翻訳する
			TranslateMessage(&message);
			// ウィンドウプロシージャの送信する
			DispatchMessage(&message);
		}
		else
		{
			// ゲームに関連する処理
			// ゲーム処理と描画処理を実装する
		}
	}
	return 0;
}

