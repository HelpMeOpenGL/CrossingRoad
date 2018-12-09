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
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
GLubyte *pBytes[6]; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수

GLuint textures[6];
//============= 맵 =====================
int MAP[MAP_SIZE_X][MAP_SIZE_Y];
float cameramove = 5000;


//============= 캐릭터 =================
CHARACTER character1;
CHARACTER character2;

CAR car[CAR_NUM];

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

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// 바탕색을 'blue' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 설정된 색으로 전체를 칠하기 
	//출력 전후
	glEnable(GL_DEPTH_TEST);
	//큐브맵
	glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		{
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			//앞
			glTexCoord2f(1, 1);
			glVertex3f(WORLD_SIZE, WORLD_SIZE, WORLD_SIZE);
			glTexCoord2f(0, 1);
			glVertex3f(-WORLD_SIZE, WORLD_SIZE, WORLD_SIZE);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-WORLD_SIZE, WORLD_SIZE, -WORLD_SIZE);
			glTexCoord2f(1, 0);
			glVertex3f(WORLD_SIZE, WORLD_SIZE, -WORLD_SIZE);
		}
		glEnd();
	glPushMatrix(); {
		glRotatef(90, 0, 1, 0);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glBegin(GL_QUADS);
		{
			//왼쪽
			glTexCoord2f(1, 1);
			glVertex3f(-WORLD_SIZE, WORLD_SIZE, -WORLD_SIZE);
			glTexCoord2f(0, 1);
			glVertex3f(-WORLD_SIZE, WORLD_SIZE, WORLD_SIZE);
			glTexCoord2f(0, 0);
			glVertex3f(-WORLD_SIZE, -WORLD_SIZE, WORLD_SIZE);
			glTexCoord2f(1, 0);
			glVertex3f(-WORLD_SIZE, -WORLD_SIZE, -WORLD_SIZE);

		}
		glEnd();
	}glPopMatrix();

	//맵 잘찍히나 테스트
	glPushMatrix(); {
		glRotatef(-30, 1, 0, 0);
		glTranslatef(0, cameramove, 0);
		cout << "cameramove  :: " << cameramove << endl;
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
					case 4://물거품
						glPushMatrix(); {
							glColor3ub(232, 232, 232);
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
					case 5:

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
	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)1920 / 1080, 1.0, 2000);
	glTranslatef(0, 0, -700);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Timer(int value) {
	character1.update();
	character2.update();
	cameramove-=0.7;
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
		
	}

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
	case '1':
		character1.get_item(1);
		character2.get_item(1);
		break;
	case '2':
		character1.get_item(2);
		character2.get_item(2);
		break;
	default:
		break;
	}
	character1.load_location(character2.get_location());
	character1.keyboard(key);
	character2.load_location(character1.get_location());
	character2.keyboard(key);
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

	glGenTextures(6, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	pBytes[0] = LoadDIBitmap("skybox_top.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	pBytes[1] = LoadDIBitmap("skybox_left.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	pBytes[2] = LoadDIBitmap("skybox_front.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	pBytes[3] = LoadDIBitmap("skybox_right.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	pBytes[4] = LoadDIBitmap("skybox_back.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	pBytes[5] = LoadDIBitmap("skybox_bottom.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);	
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

