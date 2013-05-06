#include "stdafx.h"
#include "Level.h"
#include "Game.h"
#include "GameObjects\Ball.h"
#include "GameObjects\Brick.h"
#include "GameObjects\Paddle.h"
#include "GameObjects\Wall.h"
#include "Input.h"

Level::Level(void)
{
	m_world = new b2World(b2Vec2(0,0));
	m_world->SetAllowSleeping(false);
	num_bricks = 1;
}

void Level::brickDestroyed(){
	num_bricks--;
}

void Level::loadLevel(int code){



	addGameObject(new Wall(Side::TOP));
	addGameObject(new Wall(Side::BOTTOM));
	addGameObject(new Wall(Side::LEFT));
	addGameObject(new Wall(Side::RIGT));

	Paddle* p = new Paddle();
	m_paddle = p;
	addGameObject(p);

	Ball* ball = new Ball(b2Vec2(16, 4));
	m_ball = ball;
	addGameObject(ball);

	p->setBall(ball);
	switch (code)
	{

	case 0 :

		num_bricks = 91;
		
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				Brick* b = new Brick(b2Vec2(2 * i + 4, TILES_Y - j - 4), 1.8, 0.8, 1);
				addGameObject(b);
			}
		}

		break;

	case 1 : 

		num_bricks = 91;
	
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Brick* b = new Brick(b2Vec2(2 * i + 4, TILES_Y - j- 4), 1.8, 0.8, 1);
				addGameObject(b);
			}
		}


		for (int i=0; i < 13; i++)
		{
			for (int j=2; j < 6; j++)
			{
				Brick* b = new Brick(b2Vec2(2 * i + 4, TILES_Y - j - 4), 1.8, 0.8, 2);
				addGameObject(b);
			}
		}

		break;

	case 2 :

		num_bricks = 130;

		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Brick* b = new Brick(b2Vec2(2 * i + 4, TILES_Y - j- 4), 1.8, 0.8, 1);
				addGameObject(b);
			}
		}


		for (int i=0; i < 13; i++)
		{
			for (int j=1; j < 5; j++)
			{
				Brick* b = new Brick(b2Vec2(2 * i + 4, TILES_Y - j - 4), 1.8, 0.8, 2);
				addGameObject(b);
			}
		}


		for (int i=0; i < 13; i++)
		{
			for (int j=4; j < 8; j++)
			{
				Brick* b = new Brick(b2Vec2(2 * i + 4, TILES_Y - j - 4), 1.8, 0.8, 3);
				addGameObject(b);
			}
		}

		break;

	}

}

b2World* Level::getWorld(){
	return m_world;
}

Level::~Level(void)
{
	clear();
	delete m_world;
}

void Level::clear(){
	for(std::list<GameObject*>::iterator it = m_obj.begin(); it != m_obj.end();){
		m_world->DestroyBody((*it)->getBody());
		delete *it;
		it = m_obj.erase(it);	
	}
}

void Level::tick(){


	if(Game::getInstance()->pausedCount>0) Game::getInstance()->pausedCount--;
	else{
		if(Input::isKeyDown('p')){
			Game::getInstance()->changeState(PAUSED);
			Game::getInstance()->pausedCount= 30;
		}
	}


	m_world->Step(TIME_STEP, 6, 2);

	//La lógica extra va aqui
	for(std::list<GameObject*>::iterator it = m_obj.begin(); it != m_obj.end();){
		if((*it)->isAlive()){
			(*it)->tick();
			it++;
		}
		else{
			(*it)->release();
			m_world->DestroyBody((*it)->getBody());
			delete *it;
			it = m_obj.erase(it);
		}
	}

	if(num_bricks <= 0)
		Game::getInstance()->levelCompleted();
}

void Level::draw(){

	for(std::list<GameObject*>::iterator it = m_obj.begin(); it != m_obj.end(); it++){
		(*it)->draw();
	}
}