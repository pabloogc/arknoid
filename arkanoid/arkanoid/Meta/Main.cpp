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
#include "Constants.h"
#include <time.h>

using namespace std;

int ancho, alto;

/* Función para inicializar algunos parámetros de OpenGL */
void init(void)
{
	srand(time(NULL));
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
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
	
	Game::getInstance()->update();

	glutSwapBuffers();
}

/* Función que se llamará cada vez que se redimensione la ventana */
void reshape(int w, int h)
{
	Input::windowReshaped(w, h);

	int x = min(w,h);
	glViewport((w-x) / 2.0, 0, x, x);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, ABSOLUTE_TILES_X, 0, ABSOLUTE_TILES_Y);
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

void mouse(int x, int y, int s, int t){
	Input::mouseMoved(s, t);
}

void mouseMoved(int x, int y){
	Input::mouseMoved(x, y);
}

/* Función que se ejecuta cuando no hay eventos */
void idle(void)
{
	Game::getInstance()->update();
	glutPostRedisplay();
}

/* Función principal */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(32 * 24, 32 * 16);
	glutInitWindowPosition(450, 200);
	glutCreateWindow("Hola Mundo OpenGL");

	init();	

	Game::init();

	//CODIGO DE TEST

	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(mouseMoved);
	//glutSetCursor(GLUT_CURSOR_NONE); 
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);

	
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}