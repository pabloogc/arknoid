#pragma once

#ifndef _BRICK_H_
#define _BRICK_H_

#include "GameObject.h"
#include "Meta\Constants.h"

class Brick :
	public GameObject
{
public:
	Brick(b2Vec2 pos, float w, float h);
	~Brick(void);

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

