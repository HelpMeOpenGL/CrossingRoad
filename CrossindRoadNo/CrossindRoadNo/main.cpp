#include "stdafx.h"
#include "Header.h"
#include "CHARACTER.h"

#include "Csound.h"



using namespace std;
CSound snd;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timer(int value);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void Draw_Barrier(int Type, int x, int y);

//============= 맵 =====================
int MAP[MAP_SIZE_X][MAP_SIZE_Y];
int cameramove = 0;


//============= 캐릭터 =================
CHARACTER character1;

int main(int argc, char *argv[]){
	global_init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100);	// 윈도우의 위치지정 
	glutInitWindowSize(1920, 1080);	// 윈도우의 크기 지정 
	glutCreateWindow("CrossingRoad");	// 윈도우 생성 (윈도우 이름) 
	//glutFullScreenToggle();
	glutDisplayFunc(drawScene);	// 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(Motion);
	glutTimerFunc(10, Timer, 1);
	glutMainLoop();
	return 0;
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
		//맵 숫자
		//0_땅 1_도로 2_벽 3_물 4_물거품(물 뽀글뽀글) 5_나무 6_돌
		for (int j = 0; j < MAP_SIZE_Y; j++) {
			for (int i = 0; i < MAP_SIZE_X; i++) {
				switch (MAP[i][j])
				{
				case 0:
					glPushMatrix(); {
						glColor3ub(162, 206, 50);
						glBegin(GL_QUADS);
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * j);
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * (j + 1));
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * (j + 1));
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * j);
						glEnd();
					}glPopMatrix();
					break;
				case 1:
					glPushMatrix(); {
						glColor3ub(132, 132, 132);
						glBegin(GL_QUADS);
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * j);
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * (j + 1));
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * (j + 1));
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * j);
						glEnd();
					}glPopMatrix();
					break;
				case 2://벽
					glPushMatrix(); {
						glColor3ub(152, 186, 50);
						glBegin(GL_QUADS);
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * j);
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * (j + 1));
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * (j + 1));
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * j);
						glEnd();
					}glPopMatrix();
					break;
				case 3:
					glPushMatrix(); {
						glColor3ub(50, 162, 206);
						glBegin(GL_QUADS);
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * j);
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * (j + 1));
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * (j + 1));
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * j);
						glEnd();
						glBegin(GL_QUADS);
						glEnd();
					}glPopMatrix();
					break;
				case 4://물거품
					glPushMatrix(); {
						glColor3ub(232, 232, 232);
						glBegin(GL_QUADS);
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * j);
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * (j + 1));
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * (j + 1));
						glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE/2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE/2 * j);
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
	glPushMatrix(); {
		character1.draw_body();
		character1.draw_leg();
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
	character1.update();

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
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
	case 'x':
		glRotatef(5, 1, 0, 0);
		break;
	case 'X':
		glRotatef(-5, 1, 0, 0);
		break;
	case 'y':
		glRotatef(5, 0, 1, 0);
		break;
	case 'Y':
		glRotatef(-5, 0, 1, 0);
		break;
	case 'z':
		glRotatef(5, 0, 0, 1);
		break;
	case 'Z':
		glRotatef(-5, 0, 0, 1);
	case '1':
		character1.hit_item(1);//character1.hit_item(character1.use_item()); <<원래는 이런느낌의 코드
		break;
	default:
		break;
	}
	character1.keyboard(key);
}

void SpecialKeyboard(int key, int x, int y) {
	
	character1.keyboard(key);
}
void global_init() {
	LoadFile();


	//1 :: R = 232 G = 199 B = 199
	//2 :: R = 30 G = 120 B = 230
	character1.KeySetting(GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_LEFT);
	character1.SetBodyColor(232, 199, 199);


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

