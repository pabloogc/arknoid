#define _USE_MATH_DEFINES
#include <cmath>
#include "Ball.h"
#include "Meta/Game.h"
#include "GL\freeglut.h"
#include <iostream>
#include "Brick.h"

Ball::Ball(b2Vec2 pos):
	GameObject(),
	m_radius(1),
	m_color(255,255,255)
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


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;


	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 1.0f;
	fixtureDef.filter.categoryBits = BALL_FILTER;
	fixtureDef.filter.maskBits = WALL_FILTER | PADDLE_FILTER | BRICK_FILTER;


	m_body->CreateFixture(&fixtureDef);
	m_body->SetLinearVelocity(b2Vec2(0,20));
	m_body->SetUserData(this);
}

void Ball::tick(){

	/*std::cout 
		<< m_body->GetLinearVelocity().Length() << "\t"
		<< m_body->GetLinearVelocity().x << "\t" 
		<< m_body->GetLinearVelocity().y << std::endl;*/
	
	float limit = 40;
	b2Vec2 v = m_body->GetLinearVelocity();

	float velocity = v.Length();

	if(velocity < limit){
		std::cout << "Incrementando " << velocity << endl;
		v *= TIME_STEP *  8 * limit / velocity;
		m_body->ApplyLinearImpulse(v, m_body->GetLocalCenter());
	}
	if(velocity > limit){
		std::cout << "Limitando " << velocity << endl;
		v *= limit / velocity;
		m_body->SetLinearVelocity(v);
	}


}

Ball::~Ball(void)
{
}

void Ball::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * TO_DEGREE;

	glPushMatrix();
	
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle,0,0,1);

	glBegin(GL_POLYGON);
	
	int i = 1;
	int j = 0;
	for(float a=0; a<2 * M_PI; a+= M_PI/8){
		glColor3f(m_color.x,m_color.y, m_color.z);
		glVertex2f(m_radius*cos(a),m_radius*sin(a));
		if(j % 2)
			i = (i * 37) % 255;
		j++;
	}

	glEnd();
	glPopMatrix();	
}


void Ball::startContact(GameObject* g, b2Contact* c){

	g->onContactStarted(this, c);
}

void Ball::onContactStarted(Brick* b, b2Contact* c){
	b2Vec2 v = m_body->GetLinearVelocity();
	
	b2Vec2 v1 = m_body->GetPosition();
	b2Vec2 v2 = b->getBody()->GetPosition();
	b2Vec2 v3 = v2 = v1;

	b2Vec2 normal = c->GetManifold()->localNormal;


	v.x *= normal.x;
	v.y *= normal.y;

	//b->getBody()->ApplyForceToCenter(-v);

	//m_body->SetLinearVelocity(v);
	
}

