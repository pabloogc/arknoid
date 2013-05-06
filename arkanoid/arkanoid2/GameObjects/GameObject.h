#pragma once

#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "stdafx.h"
#include "Meta\Render.h"

//Declaraciones previas para poder hacer inclusion recursiva
class Ball;
class Paddle;
class Wall;
class Brick;
class BrickBit;

//Objetos que estan dentro del mundo box2D
//En esta clase se tiene que definir toda la interfaz
//comun a los objetos.
//A partir del m_body se puede obtener la referencia
//a nuestro objeto con getUserData()

class GameObject
{
public:
	GameObject(void);
	virtual ~GameObject(void);

	virtual void tick(){}
	virtual void release(){}
	virtual void draw(){}

	virtual bool isAlive(){ return alive; }
	virtual void kill(){ alive = false; }
	b2Body* getBody(){return m_body;}

	//Colisiones de nuevos cuerpos aqui
	//con definir esto basta para crear un nuevo objeto.
	//y que entre en los callbacks.

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

	virtual void onContactStarted(BrickBit*, b2Contact*){}
	virtual void onContactEnded(BrickBit*, b2Contact*){}

protected:
	b2Body* m_body; //El cuerpo
	bool alive;  //Si debe ser borrado del mundo en la siguiente iteracion
	b2Color m_color; //Color (actualmente sin uso)
	Texture m_texture; //Textura
};

#endif