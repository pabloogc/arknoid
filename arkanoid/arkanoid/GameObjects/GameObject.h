#pragma once

#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <Box2D\Box2D.h>
#include "Meta\Object.h"


class Ball;
class Paddle;
class Wall;
class Brick;


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

	bool isAlive(){ return alive; }
	void kill(){ alive = false; }
	b2Body* getBody(){return m_body;}

	//Colisiones aqui

	virtual void startContact(GameObject*, b2Contact*){}
	virtual void endContact(GameObject*, b2Contact*){}

	virtual void onContactStarted(Ball*, b2Contact*){}
	virtual void onContactEnded(Ball*, b2Contact*){}
	
	virtual void onContactStarted(Paddle*, b2Contact*){}
	virtual void onContactEnded(Paddle*, b2Contact*){}
		
	virtual void onContactStarted(Wall*, b2Contact*){}
	virtual void onContactEnded(Wall*, b2Contact*){}
		
	virtual void onContactStarted(Brick*, b2Contact*){}
	virtual void onContactEnded(Brick*, b2Contact*){}

	

protected:
	b2Body* m_body; //El cuerpo
	bool alive;  //Si debe ser borrado del mundo en la siguiente iteracion

	//TODO: mas cosas?

};

#endif