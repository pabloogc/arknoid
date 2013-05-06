#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <Box2D\Box2D.h>
#include <vector>
#include "GameObjects\GameObject.h"
#include "ContactListener.h"
#include "Constants.h"
#include "Level.h"
#include "Audio.h"

using namespace std;

enum GameState{
	PAUSED, PLAYING, SWITCHING_LEVELS,
	SPLASH, GAME_OVER, WIN, MENU
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

	int pausedCount;
	int musicPausedCount;

	//actualizar
	void update();

	//El mundo box2D
	b2World* getWorld();

	//El nivel cargado
	Level* getCurrentLevel(){return curLevel;}



	//Anyade un objeto al la lista de actualizacion
	//Hay que crearlo en el mundo tambien!
	//b2World.createBody(def)
	void addGameObject(GameObject*);

	void levelCompleted();
	GameState getState(){return m_state;}
	void changeState(GameState newState){m_state = newState;}
	void addScore(int score){m_score += score;}

	void addLives(int amount){
		m_lives += amount;
		if(m_lives <= 0)
			changeState(GAME_OVER);
	}


private:
	static Game* m_game; //Singleton
	Game();

	int level;
	int levelsCompleted;
	float timer;
	Level* curLevel;
	Level* nextLevel;
	ContactListener* m_listener; //Listener para las colisiones
	GameState m_state;

	void menuState();
	void pausedState();
	void splashState();
	void playingState();
	void gameOverState();
	void gameWonState();
	void switchLevelState();
	void displayScore();

	void (Game::*stateFunc[10])(void);
	
	int m_score;
	int m_lives;
	int TimesSoundGameOver;
	int TimesSoundVictory;
	bool playingMusic;

};

#endif