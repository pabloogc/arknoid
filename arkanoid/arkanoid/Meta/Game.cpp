#include "Game.h"
#include <Box2D\Box2D.h>
#include <time.h>
#include <iostream>
#include <GL\freeglut.h>


//Variables estaticas
clock_t t1, t2;
Game* Game::m_game = nullptr;

Game::Game(void)
{
	m_world = new b2World(b2Vec2(0,-10.0));
	//m_world->SetContactListener();
}


void Game::addGameObject(GameObject* obj){
	m_gobj.push_back(obj);
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

//La logica del juego va aqui
void Game::tick(){

	t2 = clock();

	float diff = ((float)t2 - (float)t1) / 1000.0f;

	//Cuando haya pasado el tiempo suficiente se hace step del mundo
	//Esta forma de calcular el tiempo es muy poco precisa, por eso el 0.7
	//as� se ve m�s fluido.
	
	if(diff >= TIME_STEP * 0.7f){
		t1 = t2;
		m_world->Step(TIME_STEP, 6, 2);	

		//La l�gica extra va aqui
		for(vector<Object*>::iterator it = m_obj.begin(); it != m_obj.end(); it++){
			(*it)->tick();
		}

	}

}

//El render aqui
void Game::draw(){

	for(vector<Object*>::iterator it = m_obj.begin(); it != m_obj.end(); it++){
		(*it)->draw();
	}
}

