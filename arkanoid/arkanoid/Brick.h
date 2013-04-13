#pragma once

#ifndef _BRICK_H_
#define _BRICK_H_

#include "GameObject.h"

class Brick :
	public GameObject
{
public:
	Brick(b2Vec2 pos, float w, float h);
	~Brick(void);

	virtual void draw();
	virtual void tick();

private:
	float w, h;
};

#endif

