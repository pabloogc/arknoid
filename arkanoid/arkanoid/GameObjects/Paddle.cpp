#include "Paddle.h"
#include "Meta\Game.h"
#include "Meta\Input.h"
#include "GL\freeglut.h"
#include <iostream>
#include "Ball.h"

Paddle::Paddle(void):
	w(5),
	h(1)
{


	b2World* world = Game::getInstance()->getWorld();

	//****************************************************************

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(TILES_X / 2, 2.5);
	m_body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(w/2.0, h/2.0);


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 100.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = PADDLE_FILTER;
	fixtureDef.filter.maskBits = BALL_FILTER | WALL_FILTER;

	m_body->CreateFixture(&fixtureDef);

	// Set the user data
	m_body->SetUserData(this);

	//****************************************************************

	b2BodyDef body2Def;
	bodyDef.position.Set(TILES_X / 2, 0);
	b2Body* body2 =  world->CreateBody(&body2Def);
	body2->CreateFixture(&fixtureDef);

	//****************************************************************


	b2PrismaticJointDef jointDef;
	b2Vec2 worldAxis(1.0f, 0.0f);
	jointDef.Initialize(m_body, body2, m_body->GetWorldCenter(), worldAxis);
	//jointDef.maxMotorForce = 50.0f;
	//jointDef.motorSpeed = 50.0f;
	//jointDef.enableMotor = true;

	//m_body->ApplyForceToCenter(b2Vec2(5000,0));

	world->CreateJoint(&jointDef);


}


Paddle::~Paddle(void)
{
}

void Paddle::tick(){

	float max = TILES_X;

	bool left, right;

	left = Input::isKeyDown('a');
	right = Input::isKeyDown('d');

	b2Vec2 speed(max, 0);

	if (right)
		m_body->SetLinearVelocity(speed);

	if (left)
		m_body->SetLinearVelocity(-speed);

	b2Vec2 vel = m_body->GetLinearVelocity();

	//Seguir al raton!!!

	b2Vec2 pos = m_body->GetPosition();

	if(pos.x - w/2< 1)
		pos.x = 1 + w/2;

	if(pos.x + w/2 > TILES_X - 1)
		pos.x = TILES_X - w/2 - 1;

	m_body->SetTransform(pos, 0);

	if(!left && !right){
		vel *= 0.5f;
		m_body->SetLinearVelocity(vel);
	}


}

void Paddle::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * 57.2957795131;

	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle,0,0,1);

	glColor3f(1,0.3,0);
	glBegin(GL_QUADS);
	glVertex2f(-w/2, -h/2);
	glVertex2f(+w/2, -h/2);
	glVertex2f(+w/2, +h/2);
	glVertex2f(-w/2, +h/2);
	glEnd();

	//float skin = 0.03f;

	//glBegin(GL_LINE_LOOP);
	//glVertex2f(-w/2 - skin, -h/2 - skin);
	//glVertex2f(+w/2 + skin, -h/2 - skin);
	//glVertex2f(+w/2 + skin, +h/2 + skin);
	//glVertex2f(-w/2 - skin, +h/2 + skin);
	//glEnd();

	glPopMatrix();	
}

void Paddle::startContact(GameObject* g, b2Contact* c){
	g->onContactStarted(this, c);
}

void Paddle::endContact(GameObject* g, b2Contact* c){
	g->onContactEnded(this, c);
}

void Paddle::onContactStarted(Ball* b, b2Contact* c){

	
}

void Paddle::onContactEnded(Ball* b, b2Contact* c){

	b2Vec2 v = b->getBody()->GetLinearVelocity();
	
	b2Vec2 p1 = m_body->GetPosition();
	b2Vec2 p2 = b->getBody()->GetPosition();

	b2Vec2 p = p2 - p1;
	p *= v.Length() / p.Length();

	b->getBody()->SetLinearVelocity(p);


}
