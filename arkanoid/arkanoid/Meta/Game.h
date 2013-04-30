#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <Box2D\Box2D.h>
#include <vector>
#include "GameObjects\GameObject.h"
#include "ContactListener.h"
#include "Object.h"
#include "Constants.h"
#include "Level.h"

using namespace std;

enum GameState{
	PAUSED, PLAYING, SWITCHING_LEVELS,
	SPLASH, GAVE_OVER, WIN
};

//Clase singleton responsable de actualizar la simulacion
//y renderizar los objetos. Desde aqui se gestiona toda
//la logica del juego
class Game
{
public:
	
	static Game* getInstance();
	static void init();
	static void realese();

	//Control de la logica del juego
	void tick();
	//Renderizar todo
	void draw();
	
	//El mundo box2D
	b2World* getWorld();

	Level* getCurrentLevel(){return curLevel;}

	//Anyade un objeto al la lista de actualizacion
	//Hay que crearlo en el mundo tambien!
	//b2World.createBody(def)
	void addGameObject(GameObject*);
	
	void levelCompleted();
	void changeState(int newState);

private:
	static Game* m_game; //Singleton
	Game();

	//Cosas box2d
	Level* curLevel;
	Level* nextLevel;

	b2Draw* m_draw;
	ContactListener m_listener; //Listener para las colisiones
	GameState m_state;
	
	
};



#endif