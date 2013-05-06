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

//Los niveles están en código, leer de fichero no parece necesario por ahora.
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

		num_bricks = (6+3+3)+(8+3+5+3)+(8+8+5);

		//Codigo para la I
		for (int j = 0; j < 6; j++)
		{
			Brick* b = new Brick(b2Vec2(6, (TILES_Y-4) - j ), 1.8, 0.8, 1);
			addGameObject(b);
		}

		for (int i = 0; i < 3; i++)
		{
			Brick* b = new Brick(b2Vec2(4+2*i, TILES_Y - 3), 1.8, 0.8, 1);
			addGameObject(b);
		}

		for (int i = 0; i < 3; i++)
		{
			Brick* b = new Brick(b2Vec2(4+2*i, TILES_Y - 4-6), 1.8, 0.8, 1);
			addGameObject(b);
		}


		//Codigo para la P

		for (int j = 0; j < 8; j++)
		{
			Brick* b = new Brick(b2Vec2(12, (TILES_Y-3) - j ), 1.8, 0.8, 2);
			addGameObject(b);
		}

		for (int i = 0; i < 3; i++)
		{
			Brick* b = new Brick(b2Vec2(13.7+i, TILES_Y - 3), 0.8, 0.8, 2);
			addGameObject(b);
		}

		for (int j = 0; j < 5; j++)
		{
			Brick* b = new Brick(b2Vec2(17, (TILES_Y-3) - j ), 0.8, 0.8, 2);
			addGameObject(b);
		}

		for (int i = 0; i < 3; i++)
		{
			Brick* b = new Brick(b2Vec2(13.7+i, TILES_Y -4 -3), 0.8, 0.8, 2);
			addGameObject(b);
		}

		//Codigo para la M


		for (int j = 0; j < 8; j++)
		{
			Brick* b = new Brick(b2Vec2(21, (TILES_Y-3) - j ), 1.8, 0.8, 3);
			addGameObject(b);
		}

		addGameObject(new Brick(b2Vec2(23,TILES_Y-3.2), 1.8, 0.8, 3));

		addGameObject(new Brick(b2Vec2(24,TILES_Y-4.2), 1.8, 0.8, 3));

		addGameObject(new Brick(b2Vec2(25,TILES_Y-5.2), 1.8, 0.8, 3));
		
		addGameObject(new Brick(b2Vec2(26,TILES_Y-4.2), 1.8, 0.8, 3));

		addGameObject(new Brick(b2Vec2(27,TILES_Y-3.2), 1.8, 0.8, 3));

		

		for (int j = 0; j < 8; j++)
		{
			Brick* b = new Brick(b2Vec2(29, (TILES_Y-3) - j ), 1.8, 0.8, 3);
			addGameObject(b);
		}

		break;

	case 1 :

		num_bricks = 13 * 2 + 13 * 4;

		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Brick* b = new Brick(b2Vec2(2 * i + 4, TILES_Y - j - 4), 1.8, 0.8, 1);
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