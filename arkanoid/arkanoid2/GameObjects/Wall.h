#pragma once

#ifndef _WALL_H_
#define _WALL_H_

#include "GameObject.h"

enum Side {
	TOP,
	LEFT,
	RIGT,
	BOTTOM
};

class Wall :
	public GameObject
{
public:
	Wall(Side side);
	virtual ~Wall(void);

	virtual void tick();
	virtual void draw();

	virtual void startContact(GameObject*, b2Contact*);
	virtual void endContact(GameObject*, b2Contact*);

	Side getSide(){return m_side;}

private:
	float w, h; //ancho y alto
	Side m_side; //que lado es
};

#endif
