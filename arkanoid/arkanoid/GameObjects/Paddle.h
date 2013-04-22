#pragma once

#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "Gameobjects\gameobject.h"



class Paddle :
	public GameObject
{
public:
	Paddle(void);
	~Paddle(void);

	virtual void draw();
	virtual void tick();

	virtual void startContact(GameObject*, b2Contact* c);

private:
	float w, h;

};


#endif