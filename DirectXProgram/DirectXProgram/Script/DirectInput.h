#ifndef DIRECT_INPUT_H
#define DIRECT_INPUT_H

#include <dinput.h>

bool InitDirectInput();
void UpdateDirectInput();
void ReleaseDirectInput();

// キーが押されているか調べる関数
bool IsKeyHeld( int key );

#endif	// DIRECT_INPUT_H