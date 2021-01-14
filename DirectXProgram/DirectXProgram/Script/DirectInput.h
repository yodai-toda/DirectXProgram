#ifndef DIRECT_INPUT_H
#define DIRECT_INPUT_H

#include <dinput.h>

enum InputState
{
	NoHeld,		// 押していない
	Pushed,		// 押した
	Held,		// 押している
	Released,	// 離した
};

bool InitDirectInput();
void UpdateDirectInput();
void ReleaseDirectInput();

// キーが押されているか調べる関数
bool IsKeyHeld(int key);
bool IsKeyPushed(int key);
bool IsKeyReleased(int key);

#endif	// DIRECT_INPUT_H