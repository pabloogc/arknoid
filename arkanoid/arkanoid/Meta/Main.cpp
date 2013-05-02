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
#include "GameObjects\Ball.h"
#include "Constants.h"

using namespace std;

int ancho, alto;

/* Funci�n para inicializar algunos par�metros de OpenGL */
void init(void)
{
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	ancho = glutGet(GLUT_SCREEN_WIDTH);
	alto  = glutGet(GLUT_SCREEN_HEIGHT);
}

/* Funci�n que se llamar� cada vez que se dibuje en pantalla */
void display ( void )
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// Aqu� se definen los objetos y se colocan en la escena
	glLoadIdentity();
	
	Game::getInstance()->draw();

	glutSwapBuffers();
}

/* Funci�n que se llamar� cada vez que se redimensione la ventana */
void reshape(int w, int h)
{
	Input::windowReshaped(w, h);

	int x = min(w,h);
	ancho = w;
	alto = h;
	glViewport((w-x) / 2.0, 0, x, x);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, ABSOLUTE_TILES_X, 0, ABSOLUTE_TILES_Y);

	ancho = glutGet(GLUT_SCREEN_WIDTH);
	alto  = glutGet(GLUT_SCREEN_HEIGHT);
}

/* Funci�n que controla los eventos de teclado */
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

void mouse(int x, int y, int s, int t){
	Input::mouseMoved(s, t);
}

void mouseMoved(int x, int y){
	Input::mouseMoved(x, y);
}

/* Funci�n que se ejecuta cuando no hay eventos */
void idle(void)
{
	Game::getInstance()->tick();
	glutPostRedisplay();
}

/* Funci�n principal */
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

	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);

	
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}