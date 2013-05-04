#include "Level.h"
#include "Constants.h"

#include "GameObjects\Ball.h" 
#include "GameObjects\Brick.h"
#include "GameObjects\Paddle.h"
#include "GameObjects\Wall.h"

Level::Level(void)
{
	m_world = new b2World(b2Vec2(0,0));	
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

	for (int i = 0; i < TILES_X / 2 - 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Brick* b = new Brick(b2Vec2(2 * i + 4, TILES_Y - j - 4), 1.8, 0.8);
			addGameObject(b);
		}
	}

}

b2World* Level::getWorld(){
	return m_world;
}


Level::~Level(void)
{

}

void Level::tick(){

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
}

void Level::draw(){

	for(std::list<GameObject*>::iterator it = m_obj.begin(); it != m_obj.end(); it++){
		(*it)->draw();
	}

}