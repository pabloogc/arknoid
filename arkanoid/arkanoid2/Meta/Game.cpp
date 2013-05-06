#include "stdafx.h"
#include "Game.h"
#include "Render.h"
#include "GameObjects\Paddle.h"
#include "Input.h"

//Variables estaticas
clock_t t1, t2;
Game* Game::m_game = nullptr;

Game::Game(void):
	m_state(PLAYING),
	m_score(0),
	m_lives(1),
	level(0)
{
	stateFunc[PAUSED] = &Game::pausedState;
	stateFunc[PLAYING] = &Game::playingState;
	stateFunc[SWITCHING_LEVELS] = &Game::switchLevelState;
	stateFunc[WIN] = &Game::gameWonState;
	stateFunc[GAME_OVER] = &Game::gameOverState;
	stateFunc[SPLASH] = &Game::splashState;
	stateFunc[MENU] = &Game::menuState;


	curLevel = new Level();
	nextLevel = new Level();
	m_listener = new ContactListener();
	curLevel->getWorld()->SetContactListener(m_listener);

}

void Game::addGameObject(GameObject* obj)
{
	//m_gobj.push_back(obj);
	curLevel->addGameObject(obj);
}

void Game::levelCompleted()
{	
	timer = 3;
	changeState(SWITCHING_LEVELS);
}

//Inicializacion del singleton
void Game::init(){
	Texture::init();
	Audio::init();
	Audio::playMusic(Audio::Music::MAIN_MUSIC);
	m_game = new Game;
	m_game->curLevel->loadLevel(0);
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
	return curLevel->getWorld();
}

void Game::update(){
	(this->*stateFunc[m_state])();
}

void Game::menuState()
{
}

void Game::pausedState()
{
}

void Game::splashState()
{
	cout << "ESTADO : SPLASH -> Pulsa Enter";
	cin.get();
	changeState(PLAYING);
}

void Game::playingState()
{
	t2 = clock();
	float diff = ((float)t2 - (float)t1) / 1000.0f;

	//Cuando haya pasado el tiempo suficiente se hace step del mundo
	//Esta forma de calcular el tiempo es muy poco precisa, por eso el 0.7
	//así se ve más fluido.
	if(diff >= TIME_STEP * 0.7f){
		t1 = t2;
		curLevel->tick();
	}
	curLevel->draw();
	displayScore();

}

void Game::displayScore()
{
	stringstream ss;
	ss << "Pts-";
	ss << m_score;
	Render::drawString(1,TILES_Y + 0.25f, ss.str().c_str());
	ss.clear();
	ss.str(std::string());
	ss << "Vidas-";
	ss << m_lives > 0 ? m_lives : 0;
	Render::drawString(TILES_X - 13 ,TILES_Y + 0.25f, ss.str().c_str());
}

void Game::gameOverState()
{
	Audio::haltMusic();
	Audio::playSound(Audio::Sound::GAME_OVER);

	Render::drawString(3,20, "Has perdido :(");
	Render::drawString(3,16, "Jugar (y/n)");
	curLevel->draw();
	

	if(Input::isKeyDown('y')){
		Audio::haltSound();
		Audio::playMusic(Audio::Music::MAIN_MUSIC);
		m_score = 0;
		level = 0;
		m_lives = 3;
		delete curLevel;
		curLevel = new Level();
		curLevel->loadLevel(level);
		curLevel->getWorld()->SetContactListener(m_listener);
		curLevel->tick();
		curLevel->draw();
		changeState(PLAYING);
	}
	else if (Input::isKeyDown('n')){
		exit(0);
	}	
	displayScore();
}

void Game::gameWonState()
{
}

void Game::switchLevelState()
{
	if(timer > 0) {
		timer -= TIME_STEP;
		Audio::playSound(Audio::Sound::GAME_OVER);
		Render::drawString(3,16, "Siguiente nivel!");
		curLevel->getPaddle()->tick();
		curLevel->draw();
		displayScore();

	}
	else {
		level++;
		delete curLevel;
		curLevel = new Level();
		curLevel->loadLevel(level);
		curLevel->getWorld()->SetContactListener(m_listener);
		curLevel->tick();
		curLevel->draw();
		changeState(PLAYING);
	}

}