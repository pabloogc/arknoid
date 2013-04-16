#include "Input.h"

bool Input::keys[255];

Input::Input(void)
{
	for(int i = 0; i < 255; i++)
		keys[i] = false;
}


Input::~Input(void)
{
}

bool Input::isKeyDown(unsigned char key){
	return keys[key];
}

void Input::keyboardUp(unsigned char key, int x, int y){
	keys[key] = false;
}

void Input::keyboardDown(unsigned char key, int x, int y){
	keys[key] = true;
}
