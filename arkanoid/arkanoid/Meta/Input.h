#pragma once

//Clase estatica para acceder el input de teclado y raton

#ifndef _INPUT_H_
#define _INPUT_H_

#include "GL\freeglut.h"
#include "Constants.h"

class Input
{
public:

	static bool isKeyDown(unsigned char key);
	static void keyboardDown(unsigned char key, int x, int y);
	static void keyboardUp(unsigned char key, int x, int y);
	static void mouseMoved(int x, int y);
	static void windowReshaped(int w, int h){wx = w; wy = h;}
	//coordenadas del raton en 0-32
	static float getMouseX(){return ((float)(mx) / wx) * ABSOLUTE_TILES_X;}
	//coordenadas del raton en 0-32
	static float getMouseY(){return ((float)(my) / wy) * ABSOLUTE_TILES_Y;}
	static int getWindowMouseX(){return mx;}
	static int getWindowMouseY(){return my;}


private:
	Input(void);
	~Input(void);
	
	static int mx, my, wx, wy;
	static bool keys[255];
};

#endif