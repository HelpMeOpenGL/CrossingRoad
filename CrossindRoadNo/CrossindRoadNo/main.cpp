#include <GL/freeglut.h> 
#include <iostream>

using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timer(int value);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void printtext(int x, int y, string String);



void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100);	// �������� ��ġ���� 
	glutInitWindowSize(1920, 1080);	// �������� ũ�� ���� 
	glutCreateWindow("CrossingRoad");	// ������ ���� (������ �̸�) 
	glutFullScreenToggle();
	glutDisplayFunc(drawScene);	// ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(Motion);
	glutTimerFunc(100, Timer, 1);


	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// ������ ������ ��ü�� ĥ�ϱ� 
	//��� ����
	glEnable(GL_DEPTH_TEST);


	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)1920 / 1080, 1.0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Timer(int value) {



	glutPostRedisplay();
	glutTimerFunc(100, Timer, 1);
}

void Mouse(int button, int state, int x, int y) {


}
void Motion(int x, int y) {

}

void Keyboard(unsigned char key, int x, int y) {

}

void printtext(int x, int y, string String)
{
	//(x,y) is from the bottom left of the window
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1920, 1080, 0, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2i(x, y);
	for (int i = 0; i < String.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
	}
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}