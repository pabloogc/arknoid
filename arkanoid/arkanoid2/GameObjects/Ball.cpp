#include "stdafx.h"

#include "Ball.h"
#include "Meta/Game.h"
#include "Brick.h"
#include "Wall.h"
#include "Paddle.h"

Ball::Ball(b2Vec2 pos):
	GameObject(),
	m_radius(1),
	m_color(255,255,255),
	limit(25)
{
	b2World* world = Game::getInstance()->getWorld();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = pos;
	m_body = world->CreateBody(&bodyDef);

	m_body->SetBullet(true);

	// La pelota en version circular
	/*
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = m_radius;
	//*/

	// La pelota en version cuadrada
	//*
	b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(0.1, 0.1);
	dynamicBox.SetAsBox(m_radius /2, m_radius /2);
	m_body->SetFixedRotation(true);
	//*/

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 1.0f;
	fixtureDef.filter.categoryBits = BALL_FILTER;
	fixtureDef.filter.maskBits = WALL_FILTER | PADDLE_FILTER | BRICK_FILTER;

	m_body->CreateFixture(&fixtureDef);
	m_body->SetLinearVelocity(b2Vec2(0,limit));
	m_body->SetUserData(this);
	m_texture = Texture::getTexture("bola");
}

void Ball::tick(){
	/*std::cout
	<< m_body->GetLinearVelocity().Length() << "\t"
	<< m_body->GetLinearVelocity().x << "\t"
	<< m_body->GetLinearVelocity().y << std::endl;*/
}

Ball::~Ball(void)
{
}

void Ball::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * TO_DEGREE;

	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle + 180,0,0,1);

	m_texture.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-1, -1);
	glTexCoord2f(1.0, 0.0); glVertex2f(+1, -1);
	glTexCoord2f(1.0, 1.0); glVertex2f(+1, +1);
	glTexCoord2f(0.0, 1.0); glVertex2f(-1, +1);
	glEnd();
	m_texture.disable();

	glEnd();
	glPopMatrix();
}

void Ball::startContact(GameObject* g, b2Contact* c){
	g->onContactStarted(this, c);
}

void Ball::endContact(GameObject* g, b2Contact* c){
	g->onContactEnded(this, c);

	limitVelocity();
}

void Ball::onContactStarted(Brick* b, b2Contact* c){
}

void Ball::onContactStarted(Wall* w, b2Contact* c){
	if(w->getSide() == Side::BOTTOM){
		m_body->SetLinearVelocity(b2Vec2(0, limit));
		Game::getInstance()->getCurrentLevel()->getPaddle()->setSticky(true);
		Game::getInstance()->addLives(-1);
	}
}

void Ball::limitVelocity(){
	b2Vec2 v = m_body->GetLinearVelocity();

	float velocity = v.Length();

	if(velocity < limit){
		v *= limit / velocity;
		m_body->SetLinearVelocity(v);
		//std::cout << "Incrementando " << velocity << "  " << v.Length() << endl;
	}
	if(velocity > limit){
		v *= limit / velocity;
		m_body->SetLinearVelocity(v);
		//std::cout << "Limitando     " << velocity << "  " << v.Length() << endl;
	}
}