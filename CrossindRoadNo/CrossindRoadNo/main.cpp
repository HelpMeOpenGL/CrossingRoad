#include "stdafx.h"
#include "Header.h"


//TEST MERGE ARR << 머지에러 테스트용
//한번더 테스트 가즈아ㅏ


using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timer(int value);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Draw_Barrier(int Type, int x, int y);

//============= 맵 =====================
int MAP[MAP_SIZE_X][MAP_SIZE_Y];

//============= 캐릭터 =================


void main(int argc, char *argv[])
{
	global_init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100);	// 윈도우의 위치지정 
	glutInitWindowSize(1920, 1080);	// 윈도우의 크기 지정 
	glutCreateWindow("CrossingRoad");	// 윈도우 생성 (윈도우 이름) 
	glutFullScreenToggle();
	glutDisplayFunc(drawScene);	// 출력 함수의 지정
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

	if (in.fail()) { cout << "파일을 여는 데 실패했습니다." << endl; }
	else { cout << "파일을 정상적으로 열었습니다" << endl; }

	for (int i = 0; i < MAP_SIZE_X; i++)
	{
		for (int j = 0; j < MAP_SIZE_Y; j++)
		{
			in.get(c);
			MAP[i][j] = c - 48;
		}
		in.get(c);
	}
	//출력해보기
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

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// 바탕색을 'blue' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 설정된 색으로 전체를 칠하기 
	//출력 전후
	glEnable(GL_DEPTH_TEST);
	//맵 잘찍히나 테스트
	glPushMatrix(); {
		glRotated(-90, 1, 0, 0);
		glRotated(90, 0, 1, 0);

		for (int j = 0; j < MAP_SIZE_Y; j++) {
			for (int i = 0; i < MAP_SIZE_X; i++) {
				if (MAP[i][j] == 0) {//0번타일(풀)
					glPushMatrix(); {
						//cout << "0번" << endl;
						glColor3ub(162, 206, 50);
						glBegin(GL_QUADS);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glEnd();
					}glPopMatrix();
				}
				if (MAP[i][j] == 1) {//1번타일(물)
					glPushMatrix(); {
						//cout << "1번" << endl;
						glColor3ub(50, 162, 206);
						glBegin(GL_QUADS);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * i, 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * (j + 1));
						glVertex3f(-(CUBE_SIZE*MAP_SIZE_X / 2) + CUBE_SIZE * (i + 1), 0, -(CUBE_SIZE*MAP_SIZE_Y / 2) + CUBE_SIZE * j);
						glEnd();
					}glPopMatrix();
				}
				else;
			}
		}
	}glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)1920 / 1080, 1.0, 1000);
	glTranslatef(0, 0, -500);
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

