#ifndef RENDER_H_
#define RENDER_H_

#include <Box2D\Box2D.h>
#include <GL/freeglut.h>
#include <IL/ilut.h> 
#include "Constants.h"
#include <string>
#include <iostream>


// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class Render
{
public:
	static void drawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	static void drawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	static void drawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	static void drawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	static void drawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	static void drawPoint(const b2Vec2& p, float32 size, const b2Color& color);
	static void drawString(float32 x, float32 y, const char* string); 
	static void drawAABB(b2AABB* aabb, const b2Color& color);
};


#define MAX_TEXTURES 50
using namespace std;

class Texture{
public:
	Texture(){id = -1;}
	Texture(int _id){id = _id;}
	static void init();
	static void add(std::string, const char*);
	static Texture getTexture(string);
	
	void bind();
	void disable();

private:
	
	GLuint id;
	
	static string name_list[MAX_TEXTURES];
	static GLuint id_list[MAX_TEXTURES];
	static int last;

};

#endif
