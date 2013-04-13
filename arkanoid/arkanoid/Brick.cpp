#include "Brick.h"
#include "GL\freeglut.h"
#include "Game.h"
#include <iostream>

Brick::Brick(b2Vec2 pos, float _w, float _h):
	GameObject(),
	w(_w),
	h(_h)
{

	b2World* world = Game::getInstance()->getWorld();

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(16.0f, 0.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(16.0f, 0.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(16.0f, 16.0f);
	m_body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	m_body->CreateFixture(&fixtureDef);

	//This is our little game loop.

	m_body->ApplyForce(b2Vec2(5,-55),b2Vec2(w,h));

	m_body->SetUserData(this);
}


Brick::~Brick(void)
{
}

void Brick::tick(){
}

void Brick::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * 57.2957795131;

	glPushMatrix();
	glLoadIdentity();

	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle,0,0,1);
	glBegin(GL_QUADS);

	glColor3f(1,1,1);

	glVertex2f(-w/2, -h/2);
	glVertex2f(+w/2, -h/2);
	glVertex2f(+w/2, +h/2);
	glVertex2f(-w/2, +h/2);

	glEnd();
	glPopMatrix();	
}