#pragma once

#ifndef _BALL_H_
#define _BALL_H_


#include "GameObjects/GameObject.h"


class Ball :
	public GameObject
{
public:
	Ball(b2Vec2 pos);
	virtual ~Ball(void);

	virtual void draw();
	virtual void tick();

private:
	float m_radius;
};
#endif