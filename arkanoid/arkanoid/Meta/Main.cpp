#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Meta\Game.h"
#include "Meta\Input.h"
#include "GameObjects\Brick.h"
#include "GameObjects\Wall.h"
#include "GameObjects\GameObject.h"
#include "GameObjects\Paddle.h"

using namespace std;

int ancho, alto;

/* Función para inicializar algunos parámetros de OpenGL */
void init(void)
{

	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);
	ancho = glutGet(GLUT_SCREEN_WIDTH);
	alto  = glutGet(GLUT_SCREEN_HEIGHT);
}

/* Función que se llamará cada vez que se dibuje en pantalla */
void display ( void )
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// Aquí se definen los objetos y se colocan en la escena
	glLoadIdentity();
	
	Game::getInstance()->draw();

	glutSwapBuffers();
}

/* Función que se llamará cada vez que se redimensione la ventana */
void reshape(int w, int h)
{
	float x = min(w,h);
	ancho = w;
	alto = h;
	glViewport((w-x) / 2, 0, x, x);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, ABSOLUTE_TILES_X, 0, ABSOLUTE_TILES_Y);

	ancho = glutGet(GLUT_SCREEN_WIDTH);
	alto  = glutGet(GLUT_SCREEN_HEIGHT);
}

/* Función que controla los eventos de teclado */
void keyboardDown(unsigned char key, int x, int y)
{
	Input::keyboardDown(key, x, y);
	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
	Input::keyboardUp(key, x, y);
	glutPostRedisplay();
}

/* Función que se ejecuta cuando no hay eventos */
void idle(void)
{
	Game::getInstance()->tick();
	glutPostRedisplay();
}

/* Función principal */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(450, 200);
	glutCreateWindow("Hola Mundo OpenGL");

	init();	

	Game::init();

	//CODIGO DE TEST

	Game* g = Game::getInstance();
	g->addGameObject(new Wall(Side::TOP));
	g->addGameObject(new Wall(Side::BOTTOM));
	g->addGameObject(new Wall(Side::LEFT));
	g->addGameObject(new Wall(Side::RIGT));
	g->addGameObject(new Paddle());

	for (int i = 0; i < TILES_X / 2 - 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			g->addGameObject(new Brick(b2Vec2(2 * i + 4, TILES_Y - j - 4), 1.9,0.9));
		}
	}
	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}