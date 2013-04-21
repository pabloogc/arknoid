#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <Box2D\Box2D.h>
#include <vector>
#include "GameObjects\GameObject.h"
#include "Object.h"

using namespace std;


//Constantes
#define TIME_STEP 0.0166666666667f
#define TILES_X 32
#define TILES_Y 32
#define TO_DEGREE 57.2957795131 


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
	
	//Anyade un objeto al la lista de actualizacion
	//Hay que crearlo en el mundo tambien!
	//b2World.createBody(def)
	void addGameObject(GameObject*);

private:
	static Game* m_game; //Singleton
	Game();

	//Cosas box2d
	b2World* m_world; //El mundo de box2D donde ocurre la simulacion
	b2Vec2 m_gravity; //Gravedad, por ahora es de prueba
	vector<Object*> m_obj; //Objetos Generales
	vector<GameObject*> m_gobj; //Objetos simulados
	
};

#endif