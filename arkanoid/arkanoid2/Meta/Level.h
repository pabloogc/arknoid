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

	b2World* getWorld();
	void addGameObject(GameObject*g) {m_obj.push_front(g);}
	void loadLevel(int code);

	Paddle* getPaddle(){return m_paddle;}
	Ball* getBall(){return m_ball;}

private:
	b2World* m_world;
	Ball* m_ball;
	Paddle* m_paddle;
	std::list<GameObject*> m_obj;
	Texture m_background;
};

#endif