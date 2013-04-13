#pragma once

#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <Box2D\Box2D.h>
#include "Object.h"

//Objetos que estan dentro del mundo box2D
class GameObject :
	public Object
{
public:
	GameObject(void);
	virtual ~GameObject(void);

	virtual bool isAlive(){ return alive; };

protected:
	b2Body* m_body; //El cuerpo
	bool alive;  //Si debe ser borrado del mundo en la siguiente iteracion
	//TODO: mas cosas?
	
};

#endif