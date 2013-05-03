#pragma once

//Clase estatica para acceder el input de teclado y raton

#ifndef _INPUT_H_
#define _INPUT_H_

#include "GL\freeglut.h"
#include "Constants.h"
#include <cstdio>
#include <cstdlib>

class Input
{
public:

	static bool isKeyDown(unsigned char key){return keys[key];}
	static bool isSpecialKeyDown(int key){return skeys[key];}

	static void keyboardDown(int key, int x, int y){keys[key] = true;}
	static void keyboardUp(int key, int x, int y){keys[key] = false;}

	static void skeyboardDown(int key, int x, int y){skeys[key] = true;}
	static void skeyboardUp(int key, int x, int y){skeys[key] = false;}

	static void mouseMoved(int x, int y);
	static void windowReshaped(int w, int h){wx = w; wy = h;}
	//coordenadas del raton en 0-32
	static float getMouseX()
	{return ((float)(mx) / (wx > wy ? wy : wx)) * ABSOLUTE_TILES_X;}
	//coordenadas del raton en 0-32
	static float getMouseY()
	{return ((float)(my) / (wx > wy ? wy : wx)) * ABSOLUTE_TILES_Y;}
	static int getWindowMouseX(){return mx;}
	static int getWindowMouseY(){return my;}


private:
	Input(void);

	static int mx, my, wx, wy;
	static bool keys[];
	static bool skeys[];
};

#endif