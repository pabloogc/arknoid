//Un objeto del juego que tiene que actualizarse y dibujarse
//Ver GameObject.h, objetos que se simulan en el mundo box2D

#ifndef _OBJECT_H_
#define _OBJECT_H_

class Object {	
public:
	virtual void tick() = 0;
	virtual void draw() = 0;
};

#endif