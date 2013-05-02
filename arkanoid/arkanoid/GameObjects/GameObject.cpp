#include "GameObject.h"
#include "Ball.h" 
#include "Brick.h"
#include "Paddle.h"
#include "Wall.h"

GameObject::GameObject(void):
	alive(true),
	m_color(1,1,1)
{

}


GameObject::~GameObject(void)
{
}