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
	addGameObject(new Paddle());
	addGameObject(new Ball(b2Vec2(16, 16)));

	for (int i = 0; i < TILES_X / 2 - 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			addGameObject(new Brick(b2Vec2(2 * i + 4, TILES_Y - j - 4), 2, 1));
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
	for(std::vector<GameObject*>::iterator it = m_obj.begin(); it != m_obj.end();){
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

void Level::draw(){

	for(std::vector<GameObject*>::iterator it = m_obj.begin(); it != m_obj.end(); it++){
		(*it)->draw();
	}

}