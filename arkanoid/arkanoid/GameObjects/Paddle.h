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

	virtual void startContact(GameObject*, b2Contact*);
	virtual void endContact(GameObject*, b2Contact*);

	virtual void onContactStarted(Ball*, b2Contact*);
	virtual void onContactEnded(Ball*, b2Contact*);

private:
	float w, h;

};


#endif