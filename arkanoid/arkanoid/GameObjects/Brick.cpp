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

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = pos;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(w/2.0f, h/2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 100.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = BRICK_FILTER;
	fixtureDef.filter.maskBits = WALL_FILTER | BALL_FILTER;
	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);
}


Brick::~Brick(void)
{
	//explode();
}

void Brick::tick(){
}

void Brick::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * TO_DEGREE;

	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle,0,0,1);

	b2PolygonShape *shape = (b2PolygonShape*) m_body->GetFixtureList()->GetShape();
	Render::drawSolidPolygon(shape->m_vertices, shape->GetVertexCount(), b2Color(0.8,0.33,0.41));

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
	ball_vel = b->getBody()->GetLinearVelocity();

}

float random(float min, float max){
	float dif = max - min;
	return ((rand() % 1000) / 1000.0f) * dif + min;
}

void Brick::explode(){

	const int divx = 4, divy = 4;
	float dx =(w / (divx - 1));
	float dy =(h / (divy - 1));
	const float hdx = (dx / 2) - (dx / 2) * 0.55;
	const float hdy = (dy / 2) - (dy / 2) * 0.55;
	b2Vec2 v[4], pos;

	b2Vec2 mat[divx][divy];

	for(int i = 0; i < divx; i++){
		for(int j = 0; j < divy; j++){
			mat[i][j] = b2Vec2(-w/2 + i * dx, h/2 - j * dy);
		}
	}

	for(int i = 1; i < divx - 1; i++){
		for(int j = 1; j < divy - 1; j++){
			float xr, yr;

			xr = random(-hdx, hdx);
			yr = random(-hdy, hdy);
			mat[i][j].x += xr;
			mat[i][j].y += yr;
		}
	}

	ball_vel *= 10.f;

	for(int i = 0; i < divx - 1; i++){
		for(int j = 0; j < divy - 1; j++){
			pos = b2Vec2(-w/2 + i * dx + dx / 2,
				h/2 - j * dy - dy / 2);
			v[0] = mat[i][j] - pos;
			v[1] = mat[i][j + 1] - pos;
			v[2] = mat[i + 1][j + 1] - pos;
			v[3] = mat[i + 1][j] - pos;


			BrickBit* b = new BrickBit(m_body->GetPosition() - pos, v);
			Game::getInstance()->addGameObject(b);

			b->getBody()->ApplyForceToCenter(ball_vel);
			b->getBody()->ApplyTorque(random(-3,3));
		}
	}

}



//*************************************************


void BrickBit::startContact(GameObject* g, b2Contact* c){
	g->onContactStarted(this, c);
}

void BrickBit::endContact(GameObject* g, b2Contact* c){
	g->onContactEnded(this, c);
}

BrickBit::BrickBit(b2Vec2 pos, b2Vec2 vertices[]) :
	m_life(random(1, 4))
{
	b2World* world = Game::getInstance()->getWorld();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = pos;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.Set(vertices, 4);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = BRICK_FILTER;
	fixtureDef.filter.maskBits = WALL_FILTER;
	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);	
}

void BrickBit::tick(){
	m_body->ApplyForceToCenter(b2Vec2(0,-10));
	m_life -= TIME_STEP;
	if(m_life < 0)
		this->kill();
}

void BrickBit::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * TO_DEGREE;

	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle,0,0,1);

	b2PolygonShape *shape = (b2PolygonShape*) m_body->GetFixtureList()->GetShape();
	Render::drawPolygon(shape->m_vertices, shape->GetVertexCount(), m_color);

	glEnd();
	glPopMatrix();	
}