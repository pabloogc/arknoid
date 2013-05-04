#include "stdafx.h"
#include "Meta\Game.h"
#include "Meta\Input.h"
#include "Constants.h"

using namespace std;

/* Función para inicializar algunos parámetros de OpenGL */
Texture main_background;
void init(void)
{
	srand((unsigned int)time(NULL));
	Game::init();
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	main_background = Texture::getTexture("fondo_general");
}

/* Función que se llamará cada vez que se dibuje en pantalla */
void display (void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	int w = Input::getWindowWidth();
	int h = Input::getWindowHeight();

	glViewport(0, 0, w, h);

	glPushMatrix();
	main_background.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
	glTexCoord2f(1, 0); glVertex2f(ABSOLUTE_TILES_X, 0);
	glTexCoord2f(1, 1); glVertex2f(ABSOLUTE_TILES_X, ABSOLUTE_TILES_Y);
	glTexCoord2f(0, 1); glVertex2f(0, ABSOLUTE_TILES_Y);
	glEnd();
	main_background.disable();

	int x = min(w,h);
	glViewport((w-x) / 2, 0, x, x);
		
	Game::getInstance()->update();
	
	glutSwapBuffers();
}

/* Función que se llamará cada vez que se redimensione la ventana */
void reshape(int w, int h)
{
	Input::windowReshaped(w, h);
	int x = min(w,h);
	glViewport((w-x) / 2, 0, x, x);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, ABSOLUTE_TILES_X, 0, ABSOLUTE_TILES_Y);
}

/* Función que controla los eventos de teclado */
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
	//El estado del raton se guarda en el array del
	//teclado normal porque no se usan (0x00, 0x01, etc)

	if(state == GLUT_DOWN)
		Input::keyboardDown(button, x, y);

	if(state == GLUT_UP)
		Input::keyboardUp(button, x, y);

	glutPostRedisplay();
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
int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(32 * 24, 32 * 16);
	glutInitWindowPosition(450, 200);
	glutCreateWindow("Hola Mundo OpenGL");

	init();


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