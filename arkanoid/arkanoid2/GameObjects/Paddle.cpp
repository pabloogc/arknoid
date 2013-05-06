#include "stdafx.h"
#include "Paddle.h"
#include "Meta\Game.h"
#include "Meta\Input.h"
#include "Ball.h"
#include "Meta\Audio.h"

Paddle::Paddle(void):
	w(5),
	h(1),
	sticky(true)
{
	b2World* world = Game::getInstance()->getWorld();

	//****************************************************************

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.bullet = true;
	bodyDef.position.Set(TILES_X / 2, 2.5);
	m_body = world->CreateBody(&bodyDef);


	b2PolygonShape paddleShape;
	//Los vertices tienen una forma rara y no es un
	//simple rectángulo
	//para hacer que dependiendo del punto de golpe
	//rebote en otra dirección.
	//La opción por código no quedaba natural, la simulación
	//lo hace más realista.
	b2Vec2 vert[] = {
		b2Vec2(-w/2, 0),
		b2Vec2(-w/2 + 1, -h),
		b2Vec2(w/2 - 1, -h),
		b2Vec2(w/2, 0),
		b2Vec2(0, 1.2*(h/2))
	};

	paddleShape.Set(vert, 5);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &paddleShape;
	fixtureDef.density = 100.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = PADDLE_FILTER;
	fixtureDef.filter.maskBits =
		BALL_FILTER |
		WALL_FILTER |
		BRICK_FILTER;

	m_body->CreateFixture(&fixtureDef);


	m_body->SetUserData(this);
	m_texture = Texture::getTexture("barra");

	//****************************************************************

	//El eje horizontal de la barra es un joint de box2d
	//Podemos haber hecho cosas "raras" como que su eje sea circular
	//al nivel

	b2BodyDef body2Def;
	bodyDef.position.Set(TILES_X / 2, 0);
	b2Body* body2 =  world->CreateBody(&body2Def);
	body2->CreateFixture(&fixtureDef);

	b2PrismaticJointDef jointDef;
	b2Vec2 worldAxis(1.0f, 0.0f);
	jointDef.Initialize(m_body, body2, m_body->GetWorldCenter(), worldAxis);

	world->CreateJoint(&jointDef);

	//****************************************************************
}

Paddle::~Paddle(void)
{
}

void Paddle::tick(){
	float max = TILES_X;
	bool left, right, space;

	b2Vec2 vel = m_body->GetLinearVelocity();
	b2Vec2 pos = m_body->GetPosition();

	left = Input::isKeyDown('a') | Input::isKeyDown('A')
		| Input::isSpecialKeyDown(GLUT_KEY_LEFT);
	right = Input::isKeyDown('d') | Input::isKeyDown('D')
		| Input::isSpecialKeyDown(GLUT_KEY_RIGHT);
	space = Input::isKeyDown('s') | Input::isKeyDown('S')
		| Input::isKeyDown(' ') | Input::isKeyDown(GLUT_LEFT_BUTTON);

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

	//Control por teclas
	if(!left && !right){
		vel *= 0.5f;
		m_body->SetLinearVelocity(vel);
	}

	//Ajustarlo a la pantalla
	if(pos.x - w/2< 1)
		pos.x = 1 + w/2;
	if(pos.x + w/2 > TILES_X - 1)
		pos.x = TILES_X - w/2 - 1;

	m_body->SetTransform(pos, 0);

	//Lanzar la bola si esta pegada
	if(space)
		sticky = false;

	if(sticky){
		m_ball->getBody()->SetTransform(
			b2Vec2(pos.x, pos.y + 1.8*(h / 2) + m_ball->getRadius()),	0);
	}
}

void Paddle::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * TO_DEGREE;

	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0);
	glRotatef(angle + 180,0,0,1);
	m_texture.bind();
	//por qué no ajusta a la barra y se repite
	//fix usando GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-w/2, -h/2);
	glTexCoord2f(1, 0); glVertex2f(+w/2, -h/2);
	glTexCoord2f(1, 1); glVertex2f(+w/2, +h/2);
	glTexCoord2f(0, 1); glVertex2f(-w/2, +h/2);
	glEnd();
	m_texture.disable();

	glPopMatrix();
}

void Paddle::startContact(GameObject* g, b2Contact* c){
	g->onContactStarted(this, c);
	Audio::playSound(Audio::Sound::PADDLE_HIT);
}

void Paddle::endContact(GameObject* g, b2Contact* c){
	g->onContactEnded(this, c);
}

void Paddle::onContactStarted(Ball* b, b2Contact* c){
}

void Paddle::onContactEnded(Ball* b, b2Contact* c){

	//Rebote por código, no queda bien.

	/*
	b2Vec2 v = b->getBody()->GetLinearVelocity();

	b2Vec2 p1 = m_body->GetPosition();
	b2Vec2 p2 = b->getBody()->GetPosition();

	b2Vec2 p = p2 - p1;
	p *= v.Length() / p.Length();

	b->getBody()->SetLinearVelocity(p);
	*/
}

