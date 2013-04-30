#include "Game.h"
#include <Box2D\Box2D.h>
#include <time.h>
#include <iostream>
#include <GL\freeglut.h>
#include "Render.h"

//Variables estaticas
clock_t t1, t2;
Game* Game::m_game = nullptr;

Game::Game(void):
	m_state(SPLASH)
{
	//Mundo sin gravedad
	curLevel = new Level();
	nextLevel = new Level();
	m_draw = new DebugDraw();
	curLevel->getWorld()->SetDebugDraw(m_draw);
	curLevel->getWorld()->SetAllowSleeping(false);
	curLevel->getWorld()->SetContactListener(&m_listener);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	m_draw->SetFlags(flags);

	//m_world->SetGravity(b2Vec2(0.0, 0.0));	
}



void Game::addGameObject(GameObject* obj){
	//m_gobj.push_back(obj);
	curLevel->addGameObject(obj);
}

void Game::levelCompleted(){
	static int l = 0;
	
	delete curLevel;
	curLevel = nextLevel;
	nextLevel = new Level();
	nextLevel->loadLevel(l);

	l++;
}

//Inicializacion del singleton
void Game::init(){
	m_game = new Game;
	t1 = t2 = clock();
	m_game->curLevel->loadLevel(0);

}

//Limpiar la memoria aqui
void Game::realese(){
	delete m_game;
}

Game* Game::getInstance(){
	return m_game;
}

b2World* Game::getWorld(){
	return curLevel->getWorld();
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
		curLevel->tick();
	}

}

//El render aqui
void Game::draw(){	
	curLevel->draw();	
}



