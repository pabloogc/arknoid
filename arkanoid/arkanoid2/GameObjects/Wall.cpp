#include "stdafx.h"
#include "Wall.h"
#include "Meta\Game.h"

Wall::Wall(Side side) :
	m_side(side)
{
	b2World* world = Game::getInstance()->getWorld();

	// Define the ground body.
	b2BodyDef bodyDef;
	b2PolygonShape wallShape;

	const float tx = TILES_X / 2.0f;
	const float ty = TILES_Y / 2.0f;
	const float dx = 0.5f;

	switch (m_side)
	{
	case TOP:
		bodyDef.position.Set(tx, TILES_Y - dx);
		w = tx;
		h = dx;
		break;
	case LEFT:
		bodyDef.position.Set(dx, ty);
		w = dx;
		h = ty;
		break;
	case RIGT:
		bodyDef.position.Set(TILES_X - dx, ty);
		w = dx;
		h = ty;
		break;
	case BOTTOM:
		bodyDef.position.Set(tx, dx);
		w = tx;
		h = dx;
		break;
	default:
		break;
	}

	wallShape.SetAsBox(w, h);

	w *= 2.0f;
	h *= 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &wallShape;

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	fixtureDef.filter.categoryBits = WALL_FILTER;
	fixtureDef.filter.maskBits = BALL_FILTER | BRICK_FILTER;

	m_body = world->CreateBody(&bodyDef);
	m_body->SetType(b2_kinematicBody);
	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);
	m_texture = Texture::getTexture("muro");
}

Wall::~Wall(){
}

void Wall::tick(){
}

void Wall::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * TO_DEGREE;

	//cout << pos.x << pos.y << endl;

	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle + 180,0,0,1);

	//glColor3b(115,115,115);

	m_texture.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-w/2, -h/2);
	glTexCoord2f(w, 0.0); glVertex2f(+w/2, -h/2);
	glTexCoord2f(w, h); glVertex2f(+w/2, +h/2);
	glTexCoord2f(0.0, h); glVertex2f(-w/2, +h/2);
	glEnd();
	m_texture.disable();

	glPopMatrix();
}

void Wall::startContact(GameObject* g, b2Contact* c){
	g->onContactStarted(this, c);
	if(m_side!=BOTTOM)
		(Audio::Sound::WALL_HIT);
}

void Wall::endContact(GameObject* g, b2Contact* c){
	g->onContactEnded(this, c);
}