#include "Input.h"

bool Input::keys[255];
int Input::mx = 0;
int Input::my = 0;

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

void Input::mouseMoved(int x, int y){
	mx = x;
	my = y;
}
