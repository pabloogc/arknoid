#include "Game.h"
#include <Box2D\Box2D.h>
#include <time.h>
#include <iostream>
#include <GL\freeglut.h>
#include "Render.h"

//Variables estaticas
clock_t t1, t2;
Game* Game::m_game = nullptr;

Game::Game(void)
{
	//Mundo sin gravedad
	m_world = new b2World(b2Vec2(0.0, 0.0));
	m_draw = new DebugDraw();
	m_world->SetDebugDraw(m_draw);
	m_world->SetAllowSleeping(false);
	m_world->SetContactListener(&m_listener);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_pairBit;
	//flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_centerOfMassBit;
	m_draw->SetFlags(flags);

	//m_world->SetGravity(b2Vec2(0.0, 0.0));	
}



void Game::addGameObject(GameObject* obj){
	//m_gobj.push_back(obj);
	m_obj.push_back(obj);
}


//Inicializacion del singleton
void Game::init(){
	m_game = new Game;
	t1 = t2 = clock();
}

//Limpiar la memoria aqui
void Game::realese(){
	delete m_game;
}

Game* Game::getInstance(){
	return m_game;
}

b2World* Game::getWorld(){
	return m_world;
}

//La logica del juego va aqui
void Game::tick(){

	t2 = clock();

	float diff = ((float)t2 - (float)t1) / 1000.0f;

	//Cuando haya pasado el tiempo suficiente se hace step del mundo
	//Esta forma de calcular el tiempo es muy poco precisa, por eso el 0.7
	//así se ve más fluido.

	if(diff >= TIME_STEP * 0.7f){
		t1 = t2;
		m_world->Step(TIME_STEP, 6, 2);	

		//La lógica extra va aqui
		for(vector<GameObject*>::iterator it = m_obj.begin(); it != m_obj.end();){
			if((*it)->isAlive()){
				(*it)->tick();
				it++;
			}
			else{
				m_world->DestroyBody((*it)->getBody());
				it = m_obj.erase(it);
			}
		}

	}

}

//El render aqui
void Game::draw(){

	m_world->DrawDebugData();
	for(vector<GameObject*>::iterator it = m_obj.begin(); it != m_obj.end(); it++){
		//(*it)->draw();
	}
}

