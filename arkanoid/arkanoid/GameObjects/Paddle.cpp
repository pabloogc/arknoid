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

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(TILES_X / 2, 2.5);
	m_body = world->CreateBody(&bodyDef);

	b2EdgeShape dynamicBox;

	b2Vec2 vert[2] = {
		b2Vec2(-w/2, h/2), 
		b2Vec2(w/2, h/2)
	};
	dynamicBox.Set(vert[0], vert[1]);


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

	b2Vec2 vel = m_body->GetLinearVelocity();
	b2Vec2 pos = m_body->GetPosition();

	left = Input::isKeyDown('a');
	right = Input::isKeyDown('d');	
	mx = Input::getMouseX();

	b2Vec2 speed(max, 0);

	if (right)
		m_body->SetLinearVelocity(speed);

	if (left)
		m_body->SetLinearVelocity(-speed);



	//Seguir al raton
	if(abs(mx - mx_last) > 0.10){
		mx_last = mx;
		pos.x = mx;
		m_body->SetTransform(pos, 0);
	}


	//Ajustarlo a la pantalla
	if(pos.x - w/2< 1)
		pos.x = 1 + w/2;
	if(pos.x + w/2 > TILES_X - 1)
		pos.x = TILES_X - w/2 - 1;
	m_body->SetTransform(pos, 0);
	if(!left && !right){
		vel *= 0.5f;
		m_body->SetLinearVelocity(vel);
	}

	//cout << Input::getMouseX() << endl;


}

void Paddle::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * TO_DEGREE;

	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle,0,0,1);

	//b2PolygonShape *shape = (b2PolygonShape*) m_body->GetFixtureList()->GetShape();
	//Render::drawPolygon(shape->m_vertices, shape->GetVertexCount(), m_color);
	Render::drawSegment(b2Vec2(-w/2, h/2), b2Vec2(w/2, h/2), m_color);

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

//**************************





