#pragma once

//Clase estatica para acceder el input de teclado y raton

#ifndef _INPUT_H_
#define _INPUT_H_

#include "GL\freeglut.h"


class Input
{
public:

	static bool isKeyDown(unsigned char key);
	static void keyboardDown(unsigned char key, int x, int y);
	static void keyboardUp(unsigned char key, int x, int y);
	static void mouseMoved(int x, int y);
	static int getMouseX(){return mx;}
	static int getMouseY(){return my;}


private:
	Input(void);
	~Input(void);
	
	static int mx, my;
	static bool keys[255];
};

#endif