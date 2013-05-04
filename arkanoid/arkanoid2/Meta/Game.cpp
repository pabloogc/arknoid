#include "stdafx.h"
#include "Game.h"
#include "Render.h"

//Variables estaticas
clock_t t1, t2;
Game* Game::m_game = nullptr;

Game::Game(void):
	m_state(PLAYING)
{
	stateFunc[PAUSED] = &Game::pausedState;
	stateFunc[PLAYING] = &Game::playingState;
	stateFunc[SWITCHING_LEVELS] = &Game::switchLevelState;
	stateFunc[WIN] = &Game::gameWonState;
	stateFunc[GAME_OVER] = &Game::gameOverState;
	stateFunc[SPLASH] = &Game::splashState;
	stateFunc[MENU] = &Game::menuState;

	//Mundo sin gravedad
	curLevel = new Level();
	nextLevel = new Level();
	m_listener = new ContactListener();
	curLevel->getWorld()->SetAllowSleeping(false);
	curLevel->getWorld()->SetContactListener(m_listener);

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
	Texture::init();
	Audio::init();
	//Audio::playMusic(Audio::Music::MAIN_MUSIC);
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

	Render::drawString(1,TILES_Y + 0.25f,"EXPLOTA O K ASE");
}

void Game::gameOverState()
{
}

void Game::gameWonState()
{
}

void Game::switchLevelState()
{
}