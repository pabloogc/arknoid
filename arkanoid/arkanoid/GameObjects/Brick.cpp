#include "Brick.h"
#include "GL\freeglut.h"
#include "Meta\Game.h"
#include <iostream>
#include "Ball.h"

Brick::Brick(b2Vec2 pos, float _w, float _h):
	GameObject(),
	w(_w),
	h(_h)
{

	b2World* world = Game::getInstance()->getWorld();

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = pos;
	m_body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(w/2.0f, h/2.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 100.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	fixtureDef.filter.categoryBits = BRICK_FILTER;
	fixtureDef.filter.maskBits = WALL_FILTER | BALL_FILTER;

	// Add the shape to the body.
	m_body->CreateFixture(&fixtureDef);

	// Set the user data
	m_body->SetUserData(this);
}


Brick::~Brick(void)
{
}

void Brick::tick(){
}

void Brick::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * TO_DEGREE;

	glPushMatrix();
	
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle,0,0,1);

	glBegin(GL_QUADS);
	glColor3f(1,0,0);
	glVertex2f(-w/2, -h/2);
	glColor3f(0,0,1);
	glVertex2f(+w/2, -h/2);
	glVertex2f(+w/2, +h/2);
	glColor3f(0,1,0);
	glVertex2f(-w/2, +h/2);

	glEnd();
	glPopMatrix();	
}

void Brick::startContact(GameObject* g, b2Contact* c){
	g->onContactStarted(this, c);
}

void Brick::endContact(GameObject* g, b2Contact* c){
	g->onContactEnded(this, c);
}

void Brick::onContactEnded(Ball* b, b2Contact* c){
	this->kill();
}

void Brick::onContactStarted(Ball* b, b2Contact* c){
	b2Filter f = m_body->GetFixtureList()->GetFilterData();
	f.maskBits = WALL_FILTER | BRICK_FILTER;
	m_body->GetFixtureList()->SetFilterData(f);
}