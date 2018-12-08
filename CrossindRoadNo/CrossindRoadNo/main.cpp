#include "stdafx.h"
#include "Header.h"
#include "CHARACTER.h"

#include "Csound.h"

//TEST MERGE ARR << �������� �׽�Ʈ��
//�ѹ��� �׽�Ʈ ����Ƥ�


using namespace std;
CSound snd;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timer(int value);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Draw_Barrier(int Type, int x, int y);

//============= �� =====================
int MAP[MAP_SIZE_X][MAP_SIZE_Y];

//============= ĳ���� =================
CHARACTER character1;


void main(int argc, char *argv[])
{
	global_init();
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

void LoadFile(){

	ifstream in("mapdata.txt");

	int i = 0;
	int j = 0;
	char c;

	if (in.fail()) { cout << "������ ���� �� �����߽��ϴ�." << endl; }
	else { cout << "������ ���������� �������ϴ�" << endl; }

	for (int i = 0; i < MAP_SIZE_X; i++)
	{
		for (int j = 0; j < MAP_SIZE_Y; j++)
		{
			in.get(c);
			MAP[i][j] = c - 48;
		}
		in.get(c);
	}
	//����غ���
	/*for (int i = 0; i < MAP_SIZE_X; i++)
	{
		for (int j = 0; j < MAP_SIZE_Y; j++)
		{
			printf("%d", MAP[i][j]);
		}
		printf("\n");
	}
	in.close();*/

}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// ������ ������ ��ü�� ĥ�ϱ� 
	//��� ����
	glEnable(GL_DEPTH_TEST);

	//�� �������� �׽�Ʈ
	glPushMatrix(); {
		glRotated(-90, 1, 0, 0);
		glRotated(90, 0, 1, 0);
		//�� ����
		//0_�� 1_���� 2_�� 3_�� 4_����ǰ(�� �ǱۻǱ�) 5_���� 6_��
		for (int j = 0; j < MAP_SIZE_Y; j++) {
			for (int i = 0; i < MAP_SIZE_X; i++) {
				switch (MAP[i][j])
				{
				case 0:
					glPushMatrix(); {
						glColor3ub(162, 206, 50);
						glBegin(GL_QUADS);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glEnd();
					}glPopMatrix();
					break;
				case 1:
					glPushMatrix(); {
						glColor3ub(132, 132, 132);
						glBegin(GL_QUADS);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glEnd();
					}glPopMatrix();
					break;
				case 2://��
					glPushMatrix(); {
						glColor3ub(152, 186, 50);
						glBegin(GL_QUADS);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glEnd();
					}glPopMatrix();
					break;
				case 3:
					glPushMatrix(); {
						glColor3ub(50, 162, 206);
						glBegin(GL_QUADS);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glEnd();
						glBegin(GL_QUADS);
						glEnd();
					}glPopMatrix();
					break;
				case 4://����ǰ
					glPushMatrix(); {
						glColor3ub(232, 232, 232);
						glBegin(GL_QUADS);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glEnd();
						glBegin(GL_QUADS);
						glEnd();
					}glPopMatrix();
					break;
				default:
					break;
				}
			}
		}
	}glPopMatrix();
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)1920 / 1080, 1.0, 1000);
	glTranslatef(0, 0, -300);
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
	switch (key)
	{
	case 'q':
		glutDestroyWindow(0);
		exit(1);
		break;
	case 'b':
		snd.pSound[0]->release();
		snd.Add_sound();
		snd.Play(0);
		break;
	case '.':
		glTranslatef(0, CUBE_SIZE, 0);
		break;
	case ',':
		glTranslatef(0, -CUBE_SIZE, 0);
		break;
	default:
		break;
	}
}

void global_init() {
	LoadFile();

}

void Draw_Barrier(int Type, int x, int y) {
	glPushMatrix(); {
		glTranslated(x*CUBE_SIZE, 0, y*CUBE_SIZE);
		switch (Type) {
		case 0:
			glRotated(-90, 1, 0, 0);
			glutSolidCone(CUBE_SIZE, CUBE_SIZE, 12, 3);
			break;
		case 1:
			glColor3ub(255, 255, 255);
			glutSolidCube(CUBE_SIZE);
			break;
		}
	}glPopMatrix();
}

void Map_Reset() {

}

