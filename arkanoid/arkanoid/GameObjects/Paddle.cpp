#include "Paddle.h"
#include "Meta\Game.h"
#include "Meta\Input.h"
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
	bodyDef.position.Set(TILES_X / 2, 2.5);
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

	//m_body->ApplyForceToCenter(b2Vec2(5000,0));

	world->CreateJoint(&jointDef);


}


Paddle::~Paddle(void)
{
}

void Paddle::tick(){
	
	b2Vec2 f(1000,0);

	bool left, right;

	left = Input::isKeyDown('a');
	right = Input::isKeyDown('d');

	if (right){
		m_body->ApplyForceToCenter(f);
	}

	if (left){
		m_body->ApplyForceToCenter(-f);
	}

	float max = 8;
	b2Vec2 vel = m_body->GetLinearVelocity();

	if(vel.Length() > max){
		vel.x = vel.x * ((1/vel.Length()) * max);
		m_body->SetLinearVelocity(vel);
	}

	if(!left && !right){
		vel *= 0.7f;
		m_body->SetLinearVelocity(vel);
	}


}

void Paddle::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * 57.2957795131;

	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle,0,0,1);
	
	glBegin(GL_QUADS);
	glColor4f(1,0,0,0);
	glVertex2f(-w/2, -h/2);
	glVertex2f(+w/2, -h/2);
	glVertex2f(+w/2, +h/2);
	glVertex2f(-w/2, +h/2);
	glEnd();

	float skin = 0.03f;

	glBegin(GL_LINE_LOOP);
	glColor3f(1,1,1);
	glVertex2f(-w/2 - skin, -h/2 - skin);
	glVertex2f(+w/2 + skin, -h/2 - skin);
	glVertex2f(+w/2 + skin, +h/2 + skin);
	glVertex2f(-w/2 - skin, +h/2 + skin);
	glEnd();

	glPopMatrix();	
}