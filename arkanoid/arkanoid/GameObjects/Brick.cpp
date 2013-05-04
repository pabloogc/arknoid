#include "Brick.h"
#include "GL\freeglut.h"
#include "Meta\Game.h"
#include <iostream>
#include "Ball.h"
#include <vector>


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
	m_texture = Texture::getTexture("ladrillo");
}

Brick::~Brick(void)
{

}

void Brick::tick(){
}

void Brick::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * TO_DEGREE;

	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle + 180, 0,0,1);

	m_texture.bind();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-w/2, -h/2);
	glTexCoord2f(1.0, 0.0); glVertex2f(+w/2, -h/2);
	glTexCoord2f(1.0, 1.0); glVertex2f(+w/2, +h/2);
	glTexCoord2f(0.0, 1.0); glVertex2f(-w/2, +h/2);
	glEnd();
	m_texture.disable();

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
	ball_vel = b->getBody()->GetLinearVelocity();

}

float random(float min, float max){
	float dif = max - min;
	return ((rand() % 1000) / 1000.0f) * dif + min;
}

void Brick::explode(){

	const int divx = random(3,6), divy = random(3,6);
	const float dx =(w / (divx - 1));
	const float dy =(h / (divy - 1));
	const float hdx = (dx / 2) - (dx / 2) * 0.55;
	const float hdy = (dy / 2) - (dy / 2) * 0.55;
	b2Vec2 v[4], pos;

	std::vector<std::vector<b2Vec2>> mat;
	mat.resize(divx);

	for(int i = 0; i < divx; i++){
		mat[i].resize(divy);
		for(int j = 0; j < divy; j++){
			mat[i][j] = b2Vec2(-w/2 + i * dx, h/2 - j * dy);
		}
	}

	for(int i = 0; i < divx - 0; i++){
		for(int j = 0; j < divy - 0; j++){
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
			b->getBody()->ApplyTorque(random(-500,500));

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
	fixtureDef.density = 10.0f;
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.filter.categoryBits = BRICK_FILTER;
	fixtureDef.filter.maskBits = BRICK_FILTER;
	m_body->CreateFixture(&fixtureDef);

	m_body->SetUserData(this);	
}

void BrickBit::tick(){
	//b2Vec2 ballpos = Game::getInstance()->getCurrentLevel()->getBall()->getBody()->GetPosition();
	//b2Vec2 f = m_body->GetPosition() - ballpos;
	b2Vec2 f(0,50);

	m_body->ApplyForceToCenter(-f);
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
	Render::drawSolidPolygon(shape->m_vertices, shape->GetVertexCount(), b2Color(0.1,0.1,0.1));

	glEnd();
	glPopMatrix();	
}