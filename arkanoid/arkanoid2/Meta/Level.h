#pragma once

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "GameObjects\GameObject.h"


class Level
{
public:
	Level(void);
	~Level(void);

	void tick();
	void draw();
	void clear();


	b2World* getWorld();
	void addGameObject(GameObject*g) {m_obj.push_front(g);}
	void loadLevel(int code);
	void brickDestroyed();

	Paddle* getPaddle(){return m_paddle;}
	Ball* getBall(){return m_ball;}


private:
	int num_bricks;
	b2World* m_world;
	Ball* m_ball;
	Paddle* m_paddle;
	std::list<GameObject*> m_obj;
};

#endif