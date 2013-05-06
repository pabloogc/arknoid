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

	//Push en la cima para que se vea por detras
	//(estamos abusando de las funciones inline?)
	void addGameObject(GameObject*g) {m_obj.push_front(g);} 
	void loadLevel(int code);
	void brickDestroyed();

	Paddle* getPaddle(){return m_paddle;}
	Ball* getBall(){return m_ball;}

private:
	int num_bricks; //numero de la drillos del nivel
	b2World* m_world; //el mundo box2d
	Ball* m_ball; //un referencia a la bola, por comodidad
	Paddle* m_paddle; //lo mismo para la barra
	std::list<GameObject*> m_obj; //la lista de objetos
};

#endif