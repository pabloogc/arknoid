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


private:
	Input(void);
	~Input(void);
	
	static bool keys[255];
};

#endif