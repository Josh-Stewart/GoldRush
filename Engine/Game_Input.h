//Game_Input.h

#ifndef GAME_INPUT
#define GAME_INPUT

#include "Globals.h"

void SetAcquire();
HRESULT InitDirectInput();
void FreeDirectInput();
int UpdateInput();

extern g_bActive;

extern int mouse_x;
extern int mouse_y;
extern int mouse_1;
extern int mouse_2;

extern bool keyboard_active;
extern string keyboard_buffer;

#endif