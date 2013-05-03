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

/* Funci�n para inicializar algunos par�metros de OpenGL */
void init(void)
{
	srand(time(NULL));
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
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
	
	Game::getInstance()->update();

	glutSwapBuffers();
}

/* Funci�n que se llamar� cada vez que se redimensione la ventana */
void reshape(int w, int h)
{
	Input::windowReshaped(w, h);

	int x = min(w,h);
	glViewport((w-x) / 2.0, 0, x, x);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, ABSOLUTE_TILES_X, 0, ABSOLUTE_TILES_Y);
}

/* Funci�n que controla los eventos de teclado */
void specialKeyboardDown(int key, int x, int y)
{
	Input::skeyboardDown(key, x, y);
	glutPostRedisplay();
}

void specialKeyboardUp(int key, int x, int y)
{
	Input::skeyboardUp(key, x, y);
	glutPostRedisplay();
}

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

void mouse(int button, int state, int x, int y){
	if(state == GLUT_DOWN)
		Input::keyboardDown(button, x, y);

	if(state == GLUT_UP)
		Input::keyboardUp(button, x, y);

	glutPostRedisplay();
}

void mouseMoved(int x, int y){
	Input::mouseMoved(x, y);
}

/* Funci�n que se ejecuta cuando no hay eventos */
void idle(void)
{
	Game::getInstance()->update();
	glutPostRedisplay();
}

/* Funci�n principal */
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
	glutMouseFunc(mouse);
	//glutSetCursor(GLUT_CURSOR_NONE); 
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialKeyboardDown);
	glutSpecialUpFunc(specialKeyboardUp);

	
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}