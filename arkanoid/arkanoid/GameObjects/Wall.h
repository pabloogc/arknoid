#pragma once

#ifndef _WALL_H_
#define _WALL_H_

#include "GameObject.h"

class Wall :
	public GameObject
{
public:
	Wall(int side);
	virtual ~Wall(void);

	virtual void tick();
	virtual void draw();

	virtual void startContact(GameObject*, b2Contact*);
	virtual void endContact(GameObject*, b2Contact*);

private:
	float w, h;

};

enum Side {
	TOP,
	LEFT,
	RIGT,
	BOTTOM
};

#endif
