#pragma once

#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <Box2D\Box2D.h>
#include "Meta\Object.h"

//Objetos que estan dentro del mundo box2D
//En esta clase se tiene que definir toda la interfaz
//comun a los objetos.
//A partir del m_body se puede obtener la referencia
//a su objeto con getUserData()
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