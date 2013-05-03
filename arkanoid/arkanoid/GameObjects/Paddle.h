#pragma once

#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "Gameobjects\gameobject.h"



class Paddle :
	public GameObject
{
public:

	void setBall(Ball* b){m_ball = b;}
	void setSticky(bool flag){sticky = flag;}

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
	float mx, mx_last;
	Ball* m_ball;
	bool sticky;

};


#endif