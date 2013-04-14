#include "Paddle.h"
#include "Meta\Game.h"
#include "GL\freeglut.h"

Paddle::Paddle(void):
	w(3),
	h(1)
{

	

	b2World* world = Game::getInstance()->getWorld();

	//****************************************************************

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(TILES_X / 2, 2);
	m_body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(w/2, h/2);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
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

	m_body->ApplyForceToCenter(b2Vec2(5000,0));

	world->CreateJoint(&jointDef);

	
}


Paddle::~Paddle(void)
{
}

void Paddle::tick(){

}

void Paddle::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * 57.2957795131;

	glPushMatrix();
	
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