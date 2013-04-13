#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Meta\Game.h"
#include "GameObjects\Brick.h"
#include "GameObjects\Wall.h"
#include "GameObjects\GameObject.h"

using namespace std;

int ancho, alto;

/* Función para inicializar algunos parámetros de OpenGL */
void init(void)
{

	glClearColor(0.0,0.0,0.0,0.0);
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

	//glTranslatef((ancho - 800) / 2.0f, 0, 0);

	Game::getInstance()->draw();

	glutSwapBuffers();
}

/* Función que se llamará cada vez que se redimensione la ventana */
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, TILES_X, 0, TILES_Y);

	ancho = glutGet(GLUT_SCREEN_WIDTH);
	alto  = glutGet(GLUT_SCREEN_HEIGHT);
}

/* Función que controla los eventos de teclado */
void keyboard ( unsigned char key, int x, int y )
{
	switch ( key )
	{
	case 27:  exit(0); /* tecla escape*/
		break;
	case 'f':
	case 'F': glutFullScreen();
		break;
	case 'w':
	case 'W': glutReshapeWindow(16*60, 9*60);
		break;

	case 'i':
		Game::getInstance()->getWorld()->SetGravity(b2Vec2(0,10));
		break;

	case 'k':
		Game::getInstance()->getWorld()->SetGravity(b2Vec2(0,-10));
		break;
	}

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

	for (int i = 0; i < TILES_X / 2 - 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
		g->addGameObject(new Brick(b2Vec2(2 * i + 4, 29 - j), 1.9,0.9));
		}
	}
	
	//Comenta esto para aun efecto mas realista
	for (int i = 0; i < TILES_X / 2 - 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
		g->addGameObject(new Brick(b2Vec2(19, 20), 2, 1));
		}
	}
	
	g->addGameObject(new Brick(b2Vec2(16.9, 9.3), 7,6));
	//fin codigo a comentar

	//CODIGO DE TEST

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}