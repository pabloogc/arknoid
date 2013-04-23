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

	virtual void startContact(GameObject*, b2Contact*);
	virtual void endContact(GameObject*, b2Contact*);
	
	virtual void onContactStarted(Brick*, b2Contact*);

	void limitVelocity();

private:
	float m_radius;
	b2Vec3 m_color;
};
#endif