#include "stdafx.h"
#include "CHARACTER.h"



CHARACTER::CHARACTER(){
	init();
}


CHARACTER::~CHARACTER(){

}

void CHARACTER::init(){
	local_time = 0;
	//Å°¼¼ÆÃ < ¿ÏÀü µðÆúÆ®
	key[KEY_FRONT] = 'w';
	key[KEY_BACK] = 'a';
	key[KEY_LEFT] = 's';
	key[KEY_RIGHT] = 'd';
}

void CHARACTER::reset(){

}

void CHARACTER::draw(){

}

void CHARACTER::update(){

}

void CHARACTER::keyboard(unsigned char input){
	if (input == key[KEY_FRONT]) {
		std::cout << "FRONT" << std::endl;
	}
	if (input == key[KEY_BACK]) {
		std::cout << "BACK" << std::endl;
	}
	if (input == key[KEY_RIGHT]) {
		std::cout << "RIGHT" << std::endl;
	}
	if (input == key[KEY_LEFT]) {
		std::cout << "LEFT" << std::endl;
	}
}

void CHARACTER::draw_body(){
	glRotatef(90, 1, 0, 0);
	glPushMatrix(); {//¸öÅë
		glColor3ub(232, 199, 199);
		glTranslatef(0, 35, 0);
		glScalef(0.9, 0.6, 0.9);
		glutSolidCube(CUBE_SIZE);
		glColor3f(0, 0, 0);
		//glutWireCube(CUBE_SIZE);
	}glPopMatrix();
	glPushMatrix(); {//´«
		glColor3ub(232, 232, 232);
		glTranslatef(-20, 40, -42);
		glutSolidSphere(10, 8, 8);

		glColor3f(0, 0, 0);
		glTranslatef(0,0,-8);
		glutSolidSphere(5, 8, 8);
	}glPopMatrix();
	glPushMatrix(); {//´«
		glColor3ub(232, 232, 232);
		glTranslatef(20, 40, -42);
		glutSolidSphere(10, 8, 8);

		glColor3f(0, 0, 0);
		glTranslatef(0, 0, -8);
		glutSolidSphere(5, 8, 8);
	}glPopMatrix();
	glPushMatrix(); {//ÀÌ
		glColor3ub(232, 232, 232);
		glTranslatef(-6, 25, -50);
		glScalef(1, 1.2, 1);
		glutSolidCube(10);
		glColor3f(0, 0, 0);
		//glutWireCube(10);
	}glPopMatrix();
	glPushMatrix(); {//ÀÌ
		glColor3ub(232, 232, 232);
		glTranslatef(6, 25, -50);
		glScalef(1, 1.2, 1);
		glutSolidCube(10);
		glColor3f(0, 0, 0);
		//glutWireCube(10);
	}glPopMatrix();
	glPushMatrix(); {//±Í
		glColor3ub(232, 199, 199);
		glTranslatef(25, 80, 0);
		glScalef(0.2, 0.4, 0.2);
		glutSolidCube(CUBE_SIZE);
		glColor3f(0, 0, 0);
		glutWireCube(CUBE_SIZE);
	}glPopMatrix();
	glPushMatrix(); {
		glColor3ub(232, 199, 199);
		glTranslatef(-25, 80, 0);
		glScalef(0.2, 0.4, 0.2);
		glutSolidCube(CUBE_SIZE);
		glColor3f(0, 0, 0);
		glutWireCube(CUBE_SIZE);
	}glPopMatrix();
	glPushMatrix(); {//²¿¸®
		glColor3ub(232, 199, 199);
		glTranslatef(0, 22.5, 50);
		glutSolidCube(20);
		glColor3f(0, 0, 0);
		glutWireCube(20);
	}glPopMatrix();
}

void CHARACTER::draw_leg(){
	glPushMatrix(); {
		glColor3ub(232, 199, 199);
		glTranslatef(25, 5, 0);
		glScalef(0.2, 0.2, 0.2);
		glutSolidCube(CUBE_SIZE);
		glColor3f(0, 0, 0);
		glutWireCube(5);
	}glPopMatrix();
	glPushMatrix(); {
		glColor3ub(232, 199, 199);
		glTranslatef(-25, 5, 0);
		glScalef(0.2, 0.2, 0.2);
		glutSolidCube(CUBE_SIZE);
		glColor3f(0, 0, 0);
		glutWireCube(5);
	}glPopMatrix();
}

void CHARACTER::animation(){
	



}

void CHARACTER::KeySetting(unsigned char front, unsigned char back, unsigned char right, unsigned char left){
	key[KEY_FRONT] = front;
	key[KEY_BACK] = back;	
	key[KEY_RIGHT] = right;
	key[KEY_LEFT] = left;
}
