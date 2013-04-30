#pragma once

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <Box2D\Box2D.h>
#include "GameObjects\GameObject.h" 
#include <vector>

class Level
{
public:
	Level(void);
	~Level(void);
	
	void tick();
	void draw();

	b2World* getWorld();
	void addGameObject(GameObject*g) {m_obj.push_back(g);}
	void loadLevel(int code);

private:
	b2World* m_world;
	std::vector<GameObject*> m_obj;
};

#endif