#include "stdafx.h"
#include "CHARACTER.h"



CHARACTER::CHARACTER(){
	init();
}


CHARACTER::~CHARACTER(){

}

void CHARACTER::init(){
	local_time = 0;
	//Ű���� < ���� ����Ʈ
	key[KEY_FRONT] = 'w';
	key[KEY_BACK] = 's';
	key[KEY_LEFT] = 'a';
	key[KEY_RIGHT] = 'd';
	item = 0;
	type = 0;
	state = STATE_IDLE;
	key_lock = false;
	item_timer = 0;
	location.x = rand() % 20 + 5;
	location.y = 5;
	b_item_fog = false;
	body_color[0] = 232;
	body_color[1] = 199;
	body_color[2] = 199;
	//1 :: R = 232 G = 199 B = 199
	//2 :: R = 30 G = 120 B = 230
}

void CHARACTER::reset(){

}

void CHARACTER::draw(){
	glPushMatrix(); {
		glTranslatef(location.x, location.y, 0);
		glRotatef(90, 1, 0, 0);
		if (dir == 2) {
			glRotatef(180, 0, 1, 0);
		}
		if (dir == 3) {
			glRotatef(90, 0, 1, 0);
		}
		if (dir == 4) {
			glRotatef(-90, 0, 1, 0);
		}
		draw_body();
		draw_leg();
	}glPopMatrix();
}

void CHARACTER::update(){
	//Ű ��� ����(3��)
	if (key_lock) {
		item_timer++;
		if (item_timer > 180) {
			key_lock = false;
			item_timer = 0;
		}
	}
	//�Ȱ� Ÿ�̸� ���� (3��)
	if (b_item_fog) {
		item_timer++;
		if (item_timer > 180) {
			b_item_fog = false;
			item_timer = 0;
		}
	}
}

void CHARACTER::keyboard(unsigned char input){
	if (key_lock) {//Ű�� ���� �ٷ� ����
		return;
	}
	if (input == key[KEY_FRONT]) {
		std::cout << "FRONT" << std::endl;
		location.y += 1 * CUBE_SIZE;
		dir = 1;
	}
	if (input == key[KEY_BACK]) {
		std::cout << "BACK" << std::endl;
		location.y -= 1 * CUBE_SIZE;
		dir = 2;

	}
	if (input == key[KEY_LEFT]) {
		std::cout << "LEFT" << std::endl;
		location.x -= 1 * CUBE_SIZE;
		dir = 3;
	}
	if (input == key[KEY_RIGHT]) {
		std::cout << "RIGHT" << std::endl;
		location.x += 1 * CUBE_SIZE;
		dir = 4;

	}
}

void CHARACTER::draw_body() {
	glPushMatrix(); {
		glPushMatrix(); {//����
			glColor3ub(body_color[0], body_color[1], body_color[2]);
			glTranslatef(0, 35, 0);
			glScalef(0.9, 0.6, 0.9);
			glutSolidCube(CUBE_SIZE);
			glColor3f(0, 0, 0);
		}glPopMatrix();
		glPushMatrix(); {//��
			glColor3ub(232, 232, 232);
			glTranslatef(-20, 40, -42);
			glutSolidSphere(10, 8, 8);
			glColor3f(0, 0, 0);
			glTranslatef(0, 0, -8);
			glutSolidSphere(5, 8, 8);
		}glPopMatrix();
		glPushMatrix(); {//��
			glColor3ub(232, 232, 232);
			glTranslatef(20, 40, -42);
			glutSolidSphere(10, 8, 8);

			glColor3f(0, 0, 0);
			glTranslatef(0, 0, -8);
			glutSolidSphere(5, 8, 8);
		}glPopMatrix();
		glPushMatrix(); {//��
			glColor3ub(232, 232, 232);
			glTranslatef(-6, 25, -50);
			glScalef(1, 1.2, 1);
			glutSolidCube(10);
			glColor3f(0, 0, 0);
		}glPopMatrix();
		glPushMatrix(); {//��
			glColor3ub(232, 232, 232);
			glTranslatef(6, 25, -50);
			glScalef(1, 1.2, 1);
			glutSolidCube(10);
			glColor3f(0, 0, 0);
		}glPopMatrix();
		glPushMatrix(); {//��
			glColor3ub(body_color[0] - 20, body_color[1] - 20, body_color[2] - 20);
			glTranslatef(25, 80, 0);
			glScalef(0.2, 0.4, 0.2);
			glutSolidCube(CUBE_SIZE);
		}glPopMatrix();
		glPushMatrix(); {
			glColor3ub(body_color[0] - 20, body_color[1] - 20, body_color[2] - 20);
			glTranslatef(-25, 80, 0);
			glScalef(0.2, 0.4, 0.2);
			glutSolidCube(CUBE_SIZE);
		}glPopMatrix();
		glPushMatrix(); {//����
			glColor3ub(body_color[0] - 20, body_color[1] - 20, body_color[2] - 20);
			glTranslatef(0, 22.5, 50);
			glutSolidCube(20);
		}glPopMatrix();
	}glPopMatrix();
}

void CHARACTER::draw_leg(){
	glPushMatrix(); {
		glPushMatrix(); {
			glColor3ub(body_color[0] - 20, body_color[1] - 20, body_color[2] - 20);
			glTranslatef(25, 5, 0);
			glScalef(0.2, 0.2, 0.2);
			glutSolidCube(CUBE_SIZE);
		}glPopMatrix();
		glPushMatrix(); {
			glColor3ub(body_color[0] - 20, body_color[1] - 20, body_color[2] - 20);
			glTranslatef(-25, 5, 0);
			glScalef(0.2, 0.2, 0.2);
			glutSolidCube(CUBE_SIZE);
		}glPopMatrix();
	}glPopMatrix();
}

void CHARACTER::animation(){
	



}

void CHARACTER::load_map(int (*input)[MAP_SIZE_Y]){
	for (int i = 0; i < MAP_SIZE_X; i++) {
		for (int j = 0; j < MAP_SIZE_Y; j++) {
			map[i][j] = input[i][j];
		}
	}
}

int CHARACTER::use_item(){
	if (!item) {
		return 0;
	}

	//======= ����� �ʿ� ===========
	if (item == ITEM_MOVE) {
		int tmp = rand() % 7 + 1;
		location.y += tmp;
		while (map[location.x][location.y] < 1) {
			location.y--;
		}	
	}
	//==================================


	//������ ��쿡 ���ؼ�
	if (item){
		int tmp = item;
		item = 0;//�������� ���������� 0���� �ʱ�ȭ
		return tmp;//�� ��ȯ
	}
	
}

void CHARACTER::hit_item(int input){
	if (!input) {
		return;
	}
	if (input == ITEM_STURN) {
		key_lock = true;
	}
	//�Ȱ� ó���Ͻ� �ɵ�
	if (input == ITEM_FOG) {

	}
}

void CHARACTER::KeySetting(unsigned char front, unsigned char back, unsigned char right, unsigned char left){
	key[KEY_FRONT] = front;
	key[KEY_BACK] = back;	
	key[KEY_RIGHT] = right;
	key[KEY_LEFT] = left;
}

void CHARACTER::SetBodyColor(int R, int G, int B) {
	body_color[0] = R;
	body_color[1] = G;
	body_color[2] = B;
}
