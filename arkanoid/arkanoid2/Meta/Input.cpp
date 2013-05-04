#include "stdafx.h"
#include "Input.h"

bool Input::keys[256];
bool Input::skeys[256];

int Input::mx = 0;
int Input::my = 0;
int Input::wx = 0;
int Input::wy = 0;

Input::Input(void)
{
	for(int i = 0; i < 256; i++){
		keys[i] = false;
		skeys[i] = false;
	}
}

void Input::mouseMoved(int x, int y){
	mx = x;
	my = y;
}