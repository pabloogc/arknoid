#define _USE_MATH_DEFINES
#include <cmath>
#include "Ball.h"
#include "Meta/Game.h"
#include "GL\freeglut.h"

Ball::Ball(b2Vec2 pos):
	GameObject(),
	m_radius(0.5)
{
	
	b2World* world = Game::getInstance()->getWorld();

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = pos;
	m_body = world->CreateBody(&bodyDef);

	m_body->SetBullet(true);

	// Define another box shape for our dynamic body.
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = m_radius;

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	fixtureDef.restitution = 0.99f;
	// Add the shape to the body.
	m_body->CreateFixture(&fixtureDef);

	//m_body->ApplyForce(b2Vec2(5,-55),b2Vec2(w,h));

	// Set the user data
	m_body->SetUserData(this);
}

void Ball::tick(){

	b2Vec2 f (0,-100);
	b2Vec2 f2;
	m_body->ApplyForceToCenter(f);
	f2 = m_body->GetLinearVelocity();
	f2 += b2Vec2(0, 2.1f);
	m_body->SetLinearVelocity(f2);


}

void Ball::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * TO_DEGREE;

	glPushMatrix();
	
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle,0,0,1);

	glBegin(GL_POLYGON);
	

	for(float a=0; a<2 * M_PI; a+= M_PI/20){
		glColor3f(1,1,a / (2 * M_PI));
		glVertex2f(m_radius*cos(a),m_radius*sin(a));
	}

	glEnd();
	glPopMatrix();	
}

Ball::~Ball(void)
{
}
