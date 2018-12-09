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

GLuint textures[6];
//============= 맵 =====================
int MAP[MAP_SIZE_X][MAP_SIZE_Y];
float cameramove = 5000;


//============= 캐릭터 =================
CHARACTER character1;
CHARACTER character2;

CAR car[CAR_NUM];

int global_scene = SCENE_LOBBY;


int main(int argc, char *argv[]){
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
	switch (global_scene) {
	case SCENE_LOBBY:
		glPushMatrix(); {			
			glRotated(-90, 1, 0, 0);
			glRotated(180, 0, 0, 1);
			glTranslated(-50, 4900,0 );
			
			character1.draw();
			character2.draw();
		}glPopMatrix();
		char tmp[64];
		glColor3b(1, 1, 1);
		sprintf(tmp, "PRESS ANYKEY");
		printtext(1920 / 2 - 50, 700, tmp);
		break;
	case SCENE_MAINGAME:
		//맵 잘찍히나 테스트
		glPushMatrix(); {
			glRotatef(-30, 1, 0, 0);
			glTranslatef(0, cameramove, 0);
			//cout << "cameramove  :: " << cameramove << endl;
			//맵 잘찍히나 테스트
			glPushMatrix(); {
				glRotated(-90, 1, 0, 0);
				glRotated(90, 0, 1, 0);
				//맵 숫자
				//0_땅 1_도로 2_벽 5_나무 6_돌
				for (int j = 0; j < MAP_SIZE_Y; j++) {
					for (int i = 0; i < MAP_SIZE_X; i++) {
						switch (MAP[i][j])
						{
						case 0:
							glPushMatrix(); {
								glColor3ub(162, 206, 50);
								glBegin(GL_QUADS);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glEnd();
							}glPopMatrix();
							break;
						case 1://도로
							glPushMatrix(); {
								glColor3ub(132, 132, 132);
								glBegin(GL_QUADS);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glEnd();
							}glPopMatrix();
							car[j].y = (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j;
							break;
						case 2://벽
							glPushMatrix(); {
								glColor3ub(152, 186, 50);
								glBegin(GL_QUADS);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glEnd();
							}glPopMatrix();
							break;
						case 3:
							glPushMatrix(); {
								glColor3ub(50, 162, 206);
								glBegin(GL_QUADS);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glEnd();
								glBegin(GL_QUADS);
								glEnd();
							}glPopMatrix();
							break;
						case 5://나무
							glPushMatrix(); {
								glColor3ub(162, 206, 50);
								glBegin(GL_QUADS);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glEnd();
								glTranslatef((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 8) + CUBE_SIZE / 4 * i, 0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 8) + CUBE_SIZE / 4 * j);
								glTranslatef((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 8) + CUBE_SIZE / 4 * i, -50, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 8) + CUBE_SIZE / 4 * j);
								glColor3ub(188, 123, 50);
								glScalef(0.5, 2, 0.5);
								glutSolidCube(CUBE_SIZE / 2);
								glColor3ub(0, 86, 0);
								glScalef(3, 0.3, 3);
								glTranslatef(0, -25, 0);
								glutSolidCube(CUBE_SIZE / 2);
								glColor3ub(0, 126, 0);
								glTranslatef(0, -25, 0);
								glScalef(0.9, 1, 0.9);
								glutSolidCube(CUBE_SIZE / 2);
								glColor3ub(0, 105, 0);
								glTranslatef(0, -25, 0);
								glScalef(0.9, 1, 0.9);
								glutSolidCube(CUBE_SIZE / 2);
								glColor3ub(0, 142, 0);
								glTranslatef(0, -25, 0);
								glScalef(0.7, 1, 0.7);
								glutSolidCube(CUBE_SIZE / 2);
								glColor3ub(0, 122, 0);
								glTranslatef(0, -25, 0);
								glScalef(0.7, 1, 0.7);
								glutSolidCube(CUBE_SIZE / 2);
							}glPopMatrix();
							break;
						case 6://돌
							glPushMatrix(); {
								glColor3ub(162, 206, 50);
								glBegin(GL_QUADS);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * i, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * (j + 1));
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE / 2 * (i + 1), (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE / 2 * j);
								glEnd();
								glColor3ub(86, 86, 86);
								glTranslatef((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 8) + CUBE_SIZE / 4 * i, 0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 8) + CUBE_SIZE / 4 * j);
								glutSolidCube(50);
								glTranslatef((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 8) + CUBE_SIZE / 4 * i, -25, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 8) + CUBE_SIZE / 4 * j);
								glutSolidCube(30);
							}glPopMatrix();
							break;
						case 7://아이템박스
							glPushMatrix(); {
								glColor3ub(162, 206, 50);
								glBegin(GL_QUADS);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE * i / 2, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE * j / 2);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE * i / 2, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE * (j + 1) / 2);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE * (i + 1) / 2, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE * (j + 1) / 2);
								glVertex3f((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 4) + CUBE_SIZE * (i + 1) / 2, (GLfloat)0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 4) + CUBE_SIZE * j / 2);
								glEnd();
								glColor3ub(255, 230, 0);
								glTranslatef((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 8) + CUBE_SIZE / 4 * i, 0, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 8) + CUBE_SIZE / 4 * j);
								glTranslatef((GLfloat)-(CUBE_SIZE*MAP_SIZE_X / 8) + CUBE_SIZE / 4 * i, -25, (GLfloat)-(CUBE_SIZE*MAP_SIZE_Y / 8) + CUBE_SIZE / 4 * j);
								glScalef(1.5, 0.2, 1.5);
								glutSolidCube(CUBE_SIZE / 4);
								glColor3ub(255, 200, 0);
								glTranslatef(0, 5, 0);
								glScalef(1.5, 1, 1.5);
								glutSolidCube(CUBE_SIZE / 4);
							}glPopMatrix();
							break;
						default:
							break;
						}
					}
				}
			}glPopMatrix();
			character1.draw();
			character2.draw();

			//자동차그리기
			for (int i = 0; i < CAR_NUM; i++) {
				if (car[i].go == true) {
					glPushMatrix(); {
						glTranslatef(car[i].x, car[i].y, 0);
						glColor3ub(188, 123, 50);
						glutSolidCube(CUBE_SIZE);
					}glPopMatrix();
				}
			}
		}glPopMatrix();
		break;
	case SCENE_END:
		glPushMatrix(); {
			char tmp[64];
			sprintf(tmp, "THANK YOU FOR ANJOY");
			glColor3b(1, 1, 1);
			printtext(1920 / 2 - 50, 1080/2, tmp);
		}glPopMatrix();
		break;
	}
	
	glutSwapBuffers(); // 화면에 출력하기

}

GLvoid Reshape(int w, int h){

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)1920 / 1080, 1.0, 2000);
	glTranslatef(0, 0, -700);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Timer(int value) {
	switch (global_scene) {
	case SCENE_LOBBY:
		character1.update();
		character2.update();
		glutPostRedisplay();
		glutTimerFunc(10, Timer, 1);
		break;
	case SCENE_MAINGAME:
		character1.update();
		character2.update();

		cameramove -= 0.5;


		cameramove -= 0.7;
		character1.load_Camera(cameramove);
		character2.load_Camera(cameramove);

		car[0].go = true;
		//자동차마다 타이머두자
		for (int i = 0; i < CAR_NUM; i++) {
			if (car[i].y != 0) {
				car[i].timer++;
				if (car[i].timer == 180) {
					car[i].go = true;
				}
			}
			//if (car[i].go == true)
				//car[i].x++;
		}
		character1.update_map_obj(car);
		character2.update_map_obj(car);

		if (character1.get_life() || character2.get_life()) {
			cout << "dead" << endl;
			global_scene = SCENE_END;
		}

		glutPostRedisplay();
		glutTimerFunc(10, Timer, 1);
		break;
	}
	
}

void Mouse(int button, int state, int x, int y) {


}

void Motion(int x, int y) {

}

void Keyboard(unsigned char key, int x, int y) {
	switch (global_scene) {
	case SCENE_LOBBY:
		global_scene = SCENE_MAINGAME;
		break;
	case SCENE_MAINGAME:
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
		case '1':
			character1.get_item(1);
			character2.get_item(1);
			break;
		case '2':
			character1.get_item(2);
			character2.get_item(2);
			break;
		case 'y':
			glRotatef(-5, 1, 0, 0);
			break;
		default:
			break;
		}
		character1.load_location(character2.get_location());
		character1.keyboard(key);
		character2.load_location(character1.get_location());
		character2.keyboard(key);
		break;
	case SCENE_END:
		break;
	}
}

void SpecialKeyboard(int key, int x, int y) {
	character1.keyboard(key);
	character2.keyboard(key);
	if (character1.check_itemkey(key)) {
		character2.hit_item(character1.use_item());
	}
	if (character2.check_itemkey(key)) {
		character1.hit_item(character2.use_item());
	}
	character1.load_location(character2.get_location());
	character1.keyboard(key);
	character2.load_location(character1.get_location());
	character2.keyboard(key);
}

void global_init() {
	LoadFile();

	//1 :: R = 232 G = 199 B = 199
	//2 :: R = 30 G = 126 B = 158
	character1.KeySetting(GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_LEFT);
	character1.SetBodyColor(232, 199, 199);
	character1.Setlocaiton(1,-48);
	character1.keySetting_item(GLUT_KEY_SHIFT_R);
	character2.KeySetting('s', 'x', 'c', 'z');
	character2.SetBodyColor(30, 126, 158);
	character2.Setlocaiton(0, -48);
	character2.keySetting_item(GLUT_KEY_SHIFT_L);

		
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

