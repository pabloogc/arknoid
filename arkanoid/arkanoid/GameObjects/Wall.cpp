#include "Wall.h"
#include "Meta\Game.h"
#include "GL\freeglut.h"

Wall::Wall(int side)
{

	b2World* world = Game::getInstance()->getWorld();

	// Define the ground body.
	b2BodyDef groundBodyDef;
	b2PolygonShape groundBox;

	const float tx = TILES_X / 2.0f;
	const float ty = TILES_Y / 2.0f;
	const float dx = 0.5f;

	switch (side)
	{
	case TOP:
		groundBodyDef.position.Set(tx, TILES_Y - dx);
		w = tx;
		h = dx;
		break;
	case LEFT:
		groundBodyDef.position.Set(dx, ty);
		w = dx;
		h = ty;
		break;
	case RIGT:
		groundBodyDef.position.Set(TILES_X - dx, ty);
		w = dx;
		h = ty;
		break;
	case BOTTOM:
		groundBodyDef.position.Set(tx, dx);
		w = tx;
		h = dx;
		break;	
	default:
		break;
	}

	groundBox.SetAsBox(w, h);

	w *= 2.0f;
	h *= 2.0f;

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	m_body = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.

	// The extents are the half-widths of the box.

	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&groundBox, 0.0f);


	m_body->SetUserData(this);
}

Wall::~Wall(){

}

void Wall::tick(){

}

void Wall::draw(){
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle() * 57.2957795131;

	//cout << pos.x << pos.y << endl;

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