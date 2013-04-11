/*****************************************************/
/*                                                   */
/*           H O L A   M U N D O   G L U T           */
/*                                                   */
/*****************************************************/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int ancho, alto;

/* Función para inicializar algunos parámetros de OpenGL */
void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glEnable(GL_DEPTH_TEST);
	ancho = glutGet(GLUT_SCREEN_WIDTH);
	alto  = glutGet(GLUT_SCREEN_HEIGHT);
}

/* Función que se llamará cada vez que se dibuje en pantalla */
void display ( void )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Aquí pondríamos la función gluLookAt si el observador se mueve

	// Aquí se definen los objetos y se colocan en la escena
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 255);
	glVertex2i(100, 100);
	glVertex2i(200, 100);
	glVertex2i(200, 200);
	glVertex2i(100, 200);
	glEnd();

	glutSwapBuffers();
}

/* Función que se llamará cada vez que se redimensione la ventana */
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
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
	case 'W': glutReshapeWindow(ancho/2, alto/2);
		break;
	}

	glutPostRedisplay();
}

/* Función que controla los eventos de raton */
//void mouse ( int button, int x, int y )
//{
//	switch (button)
//	{
//	case 27:  exit(0); /* tecla escape*/
//		break;
//	case 'f':
//	case 'f': glutfullscreen();
//		break;
//	case 'w':
//	case 'w': glutreshapewindow(ancho/2, alto/2);
//		break;
//	}
//
//	glutPostRedisplay();
//}


/* Función que se ejecuta cuando no hay eventos */
void idle(void)
{
	glutPostRedisplay();
}

/* Función principal */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(350, 350);
	glutInitWindowPosition(450, 200);
	glutCreateWindow("Hola Mundo OpenGL");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}
