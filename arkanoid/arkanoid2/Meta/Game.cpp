#include "stdafx.h"
#include "Game.h"
#include "Render.h"
#include "GameObjects\Paddle.h"
#include "Input.h"

//Variables estaticas
clock_t t1, t2;
Game* Game::m_game = nullptr;

Game::Game(void):
	m_state(SPLASH),
	m_score(0),
	m_lives(3),
	level(0),
	levelsCompleted(0),
	TimesSoundGameOver(1),
	TimesSoundVictory(1),
	playingMusic(true),
	pausedCount(0),
	musicPausedCount(0),
	timer(120)
{
	stateFunc[PAUSED] = &Game::pausedState;
	stateFunc[PLAYING] = &Game::playingState;
	stateFunc[SWITCHING_LEVELS] = &Game::switchLevelState;
	stateFunc[WIN] = &Game::gameWonState;
	stateFunc[GAME_OVER] = &Game::gameOverState;
	stateFunc[SPLASH] = &Game::splashState;
	stateFunc[MENU] = &Game::menuState;

	m_splashTexture = Texture::getTexture("s");

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

	levelsCompleted++;
	if(levelsCompleted<3)
		changeState(SWITCHING_LEVELS);
	else changeState(WIN);
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
	if(Input::isKeyDown(27)) exit(0);
	(this->*stateFunc[m_state])();
}

void Game::menuState()
{
}

void Game::pausedState()
{

	Render::drawString(3,13, "Juego Pausado");
	curLevel->draw();
	displayScore();
	Audio::pause();

	if(pausedCount>0) pausedCount--;
	else{

		if(Input::isKeyDown('p')){
			changeState(PLAYING);
			Audio::playMusic(Audio::Music::MAIN_MUSIC);
			pausedCount= 60;
		}
	}

}

void Game::splashState()
{
	m_splashTexture.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
	glTexCoord2f(1.0, 0.0); glVertex2f(ABSOLUTE_TILES_X,0);
	glTexCoord2f(1.0, 1.0); glVertex2f(ABSOLUTE_TILES_X, ABSOLUTE_TILES_Y);
	glTexCoord2f(0.0, 1.0); glVertex2f(0, ABSOLUTE_TILES_Y);
	glEnd();
	m_splashTexture.disable();
	
	timer--;
	if(timer<0)	changeState(PLAYING);
}

void Game::playingState()
{

	if(musicPausedCount>0) musicPausedCount--;
	else{
		if(Input::isKeyDown('m')){

			if(playingMusic)
			{   
				Audio::pause();
				playingMusic=false;
			}
			else {
				Audio::haltMusic();
				Audio::playMusic(Audio::Music::MAIN_MUSIC);
				playingMusic=true;
			}

			musicPausedCount=30;
		}
	}

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
	ss << "Puntos:";
	ss << m_score;
	Render::drawString(0,TILES_Y + 0.25f, ss.str().c_str());
	ss.clear();
	ss.str(std::string());
	ss << "Vidas:";
	ss << m_lives > 0 ? m_lives : 0;
	Render::drawString(TILES_X - 12 ,TILES_Y + 0.25f, ss.str().c_str());

	ss.clear();
	ss.str(std::string());
	ss << "Nivel:";
	ss << level+1;
	Render::drawString(TILES_X - 21,TILES_Y + 0.25f, ss.str().c_str());

}

void Game::gameOverState()
{
	Audio::haltMusic();

	if(TimesSoundGameOver>0){
		Audio::playSound(Audio::Sound::GAME_OVER);
		TimesSoundGameOver--;
	}

	Render::drawString(3,13, "Has perdido :(");
	Render::drawString(3,9, "Jugar (y/n)");
	curLevel->draw();


	if(Input::isKeyDown('y')){
		Audio::haltSound();
		Audio::playMusic(Audio::Music::MAIN_MUSIC);
		m_score = 0;
		level = 0;
		m_lives = 3;
		TimesSoundGameOver=1;
		TimesSoundVictory=1;
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
	Audio::haltMusic();

	if(TimesSoundVictory>0){
		Audio::playSound(Audio::Sound::GAME_WON);
		TimesSoundVictory--;
	}

	Render::drawString(3,13, "Ganaste!");
	Render::drawString(3,9, "Jugar (y/n)");
	curLevel->draw();
	displayScore();

	if(Input::isKeyDown('y')){
		Audio::haltSound();
		Audio::playMusic(Audio::Music::MAIN_MUSIC);
		m_score = 0;
		level = 0;
		m_lives = 3;
		levelsCompleted=0;
		TimesSoundGameOver=1;
		TimesSoundVictory=1;
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

}

void Game::switchLevelState()
{
	if(timer > 0) {
		timer -= TIME_STEP;
		curLevel->getPaddle()->tick();
		curLevel->draw();
		displayScore();
		Render::drawString(3,13, "Siguiente nivel!");
		
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