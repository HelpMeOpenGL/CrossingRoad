#include "stdafx.h"
#include "CHARACTER.h"

CHARACTER::CHARACTER(){
	init();
}


CHARACTER::~CHARACTER(){

}

void CHARACTER::init(){
	local_time = 0;
	//키세팅 < 완전 디폴트
	key[KEY_FRONT] = 'w';
	key[KEY_BACK] = 's';
	key[KEY_LEFT] = 'a';
	key[KEY_RIGHT] = 'd';
	key_item = GLUT_KEY_SHIFT_R;
	item = 0;
	type = 0;
	state = STATE_IDLE;
	key_lock = false;
	item_timer = 0;
	item_timer2 = 0;
	location.x = 5;
	location.y = 5;
	b_item_fog = false;
	body_color[0] = 232;
	body_color[1] = 199;
	body_color[2] = 199;
	//1 :: R = 232 G = 199 B = 199
	//2 :: R = 30 G = 120 B = 230
	idle_UD_T = 0;
	idle_LR_T = 0;
	idle_LR = true;
	idle_UD = true;
	jump_b = false;
	jump_timer = 0;
	jump_height = 0;
	move_b = false;
	move_timer = 0;
	move_tmp = { 0,0 };
	moveTmp = 0;
	other_location = { 0,0 };
}

void CHARACTER::reset(){

}

void CHARACTER::draw(){
	glPushMatrix(); {
		//std::cout <<"CHARACTER :: 55 ::  " <<location.x << "   " << location.y << std::endl;
		glTranslatef((GLfloat)location.x+move_tmp.x, (GLfloat)location.y + move_tmp.y, (GLfloat)jump_height);
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
		switch (state) {
		case STATE_IDLE:
			idle_draw();
			if (key_lock) {
				sturn_draw();
			}
			break;
		default:
			//바디그리기
			glPushMatrix(); {

			}glPopMatrix();
			//다리그리기
			break;
		}
		
	}glPopMatrix();
}

void CHARACTER::update(){
	//키 잠금 구현(3초)
	if (key_lock) {
		item_timer++;
		item_timer2++;
		if (item_timer2 > 60) {
			item_timer2 = 0;
		}
		if (item_timer > 180) {
			key_lock = false;
			item_timer = 0;
		}
		
	}
	//안개 타이머 구현 (3초)
	if (b_item_fog) {
		item_timer++;
		if (item_timer > 180) {
			b_item_fog = false;
			item_timer = 0;
		}
	}

	if (jump_b) {
		jump_timer++;
		if (jump_timer <= 7) {
			jump_height += 2;
		}
		if (jump_timer > 7) {
			jump_height -= 2;
		}
		if (jump_timer >= 15) {
			jump_timer = 0;
			jump_b = false;
		}	

	}
	if (move_b) {
		move_timer += 0.1;
		moveTmp = CUBE_SIZE * (sin(move_timer));
		switch (dir) {
		case 1:
			move_tmp.y = moveTmp;
			break;
		case 2:
			move_tmp.y = -moveTmp;
			break;
		case 3:
			move_tmp.x = -moveTmp;
			break;
		case 4:
			move_tmp.x = +moveTmp;
			break;
		default:
			break;
		}

		if (move_timer > 1.57) {
			switch (dir) {
			case 1:
				location.y += CUBE_SIZE;
				break;
			case 2:
				location.y -= CUBE_SIZE;
				break;
			case 3:
				location.x -= CUBE_SIZE;
				break;
			case 4:
				location.x += CUBE_SIZE;
				break;
			default:
				break;
			}
			move_b = false;
			move_tmp = { 0,0 };
		}
	}

		switch (state) {
		case STATE_IDLE:
			idle_update();
			break;
		case STATE_MOVE:
			break;

		default:
			break;
		}
	
}

void CHARACTER::keyboard(unsigned char input){
	if (key_lock) {//키가 잠기면 바로 종료
		return;
	}
	if (move_b) {//움직이는 동안 키입력 중단
		return;
	}
	if (input == key[KEY_FRONT]) {
		std::cout << "FRONT" << std::endl;
		//location.y += 1 * CUBE_SIZE;
		call_jump();
		dir = 1;
		
		//객체충돌
		if (map[(int)location.x / CUBE_SIZE][(int)location.y / CUBE_SIZE+1] == 5) {
			return;
		}
		if (map[(int)location.x / CUBE_SIZE][(int)location.y / CUBE_SIZE + 1] == 6) {
			return;
		}
		//상대 플레이어 충돌체크
		if (abs(other_location.x - location.x)+10 < CUBE_SIZE && abs(other_location.y - (location.y + CUBE_SIZE)) + 10 < CUBE_SIZE) {
			return;
		}
		call_move();
		
	}
	if (input == key[KEY_BACK]) {
		std::cout << "BACK" << std::endl;
		//location.y -= 1 * CUBE_SIZE;
		dir = 2; 
		call_jump();

		//객체충돌
		if (map[(int)location.x / CUBE_SIZE][(int)location.y / CUBE_SIZE - 1] == 5) {
			return;
		}
		if (map[(int)location.x / CUBE_SIZE][(int)location.y / CUBE_SIZE - 1] == 6) {
			return;
		}

		//상대 플레이어 충돌체크
		if (abs(other_location.x - location.x) + 10 < CUBE_SIZE && abs(other_location.y - (location.y - CUBE_SIZE)) + 10 < CUBE_SIZE) {
			return;
		}
		call_move();
		
	}
	if (input == key[KEY_LEFT]) {
		std::cout << "LEFT" << std::endl;
		//location.x -= 1 * CUBE_SIZE;
		dir = 3;
		call_jump();

		//객체충돌
		if (map[(int)location.x / CUBE_SIZE - 1][(int)location.y / CUBE_SIZE] == 5) {
			return;
		}
		if (map[(int)location.x / CUBE_SIZE - 1][(int)location.y / CUBE_SIZE] == 6) {
			return;
		}

		//상대 플레이어 충돌체크
		if (abs(other_location.x - (location.x - CUBE_SIZE)) + 10 < CUBE_SIZE && abs(other_location.y - location.y) + 10 < CUBE_SIZE) {
			return;
		}

		call_move();
		
	}
	if (input == key[KEY_RIGHT]) {
		std::cout << "RIGHT" << std::endl;
		//location.x += 1 * CUBE_SIZE;
		dir = 4;
		call_jump();

		//객체충돌
		if (map[(int)location.x / CUBE_SIZE + 1][(int)location.y / CUBE_SIZE] == 5) {
			return;
		}
		if (map[(int)location.x / CUBE_SIZE + 1][(int)location.y / CUBE_SIZE] == 6) {
			return;
		}

		if (abs(other_location.x - (location.x + CUBE_SIZE)) + 10 < CUBE_SIZE && abs(other_location.y - location.y) + 10 < CUBE_SIZE) {
			return;
		}

		call_move();
		
	}
}

void CHARACTER::draw_body() {
	glPushMatrix(); {
		glPushMatrix(); {//몸통
			glColor3ub(body_color[0], body_color[1], body_color[2]);
			glTranslatef(0, 35, 0);
			glScalef(0.9f, 0.6f, 0.9f);
			glutSolidCube(CUBE_SIZE);
			glColor3f(0, 0, 0);
		}glPopMatrix();
		glPushMatrix(); {//눈
			glColor3ub(232, 232, 232);
			glTranslatef(-20, 40, -42);
			glutSolidSphere(10, 8, 8);
			glColor3f(0, 0, 0);
			glTranslatef(0, 0, -8);
			glutSolidSphere(5, 8, 8);
		}glPopMatrix();
		glPushMatrix(); {//눈
			glColor3ub(232, 232, 232);
			glTranslatef(20, 40, -42);
			glutSolidSphere(10, 8, 8);

			glColor3f(0, 0, 0);
			glTranslatef(0, 0, -8);
			glutSolidSphere(5, 8, 8);
		}glPopMatrix();
		glPushMatrix(); {//이
			glColor3ub(232, 232, 232);
			glTranslatef(-6, 25, -50);
			glScalef(1.0f, 1.2f, 1.0f);
			glutSolidCube(10);
			glColor3f(0, 0, 0);
		}glPopMatrix();
		glPushMatrix(); {//이
			glColor3ub(232, 232, 232);
			glTranslatef(6, 25, -50);
			glScalef(1.0f, 1.2f, 1.0f);
			glutSolidCube(10);
			glColor3f(0, 0, 0);
		}glPopMatrix();
		glPushMatrix(); {//귀
			glColor3ub(body_color[0] - 20, body_color[1] - 20, body_color[2] - 20);
			glTranslatef(25, 80, 0);
			glScalef(0.2f, 0.4f, 0.2f);
			glutSolidCube(CUBE_SIZE);
		}glPopMatrix();
		glPushMatrix(); {
			glColor3ub(body_color[0] - 20, body_color[1] - 20, body_color[2] - 20);
			glTranslatef(-25, 80, 0);
			glScalef(0.2f, 0.4f, 0.2f);
			glutSolidCube(CUBE_SIZE);
		}glPopMatrix();
		glPushMatrix(); {//꼬리
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
			glScalef(0.2f, 0.2f, 0.2f);
			glutSolidCube(CUBE_SIZE);
		}glPopMatrix();
		glPushMatrix(); {
			glColor3ub(body_color[0] - 20, body_color[1] - 20, body_color[2] - 20);
			glTranslatef(-25, 5, 0);
			glScalef(0.2f, 0.2f, 0.2f);
			glutSolidCube(CUBE_SIZE);
		}glPopMatrix();
	}glPopMatrix();
}

void CHARACTER::animation(){
	



}

void CHARACTER::idle_draw(){
	glPushMatrix(); {
		glPushMatrix(); {
			glRotated(idle_LR_T, 0, 0, 1);
			glTranslated(0, idle_UD_T + 3, 0);
			draw_body();
		}glPopMatrix();
		draw_leg();		
	}glPopMatrix();	
}

void CHARACTER::idle_update(){
	if (idle_UD) {
		idle_UD_T += 0.5f;
		if (idle_UD_T > (CUBE_SIZE / 30)) {
			idle_UD = false;
		}
	}
	else {
		idle_UD_T -= 0.5f;
		if (idle_UD_T < -(CUBE_SIZE / 30)) {
			idle_UD = true;
		}
	}
	if (idle_LR) {
		idle_LR_T += 0.1f;
		if (idle_LR_T > 10) {
			idle_LR = false;
		}
	}
	else {
		idle_LR_T -= 0.1f;
		if (idle_LR_T < -10) {
			idle_LR = true;
		}
	}
}

void CHARACTER::call_jump(){
	jump_b = true;
	jump_height = 0;
	jump_timer = 0;
}

void CHARACTER::call_move(){
	move_b = true;
	move_timer = 0;
	move_tmp = { 0,0 };
}

void CHARACTER::sturn_draw(){
	glPushMatrix(); {
		glRotated(item_timer * 2, 0, 1, 0);
		glTranslated(0, CUBE_SIZE, CUBE_SIZE);		
		if (item_timer2 <= 30) {
			glRotated(-15+item_timer2, 0, 0, 1);
		}
		else {
			glRotated(45-item_timer2, 0, 0, 1);
		}		
		glPushMatrix(); {
			glScaled(2, 2, 1);
			glColor3ub(250, 237, 125);
			glutSolidCube(CUBE_SIZE / 5);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslated(0, CUBE_SIZE / 5, 0);
			glColor3ub(234,234,234);
			glScaled(1, 1.5, 1);
			glutSolidTorus(CUBE_SIZE / 8 - 8, CUBE_SIZE / 8, 4, 8);
		}glPopMatrix();
	}glPopMatrix();
	glPushMatrix(); {
		glRotated(item_timer * 2, 0, 1, 0);
		glTranslated(0, CUBE_SIZE, -CUBE_SIZE);
		if (item_timer2 <= 30) {
			glRotated(-15 + item_timer2, 0, 0, 1);
		}
		else {
			glRotated(45 - item_timer2, 0, 0, 1);
		}
		glPushMatrix(); {
			glScaled(2, 2, 1);
			glColor3ub(250, 237, 125);
			glutSolidCube(CUBE_SIZE / 5);
		}glPopMatrix();
		glPushMatrix(); {
			glTranslated(0, CUBE_SIZE / 5, 0);
			glColor3ub(234, 234, 234);
			glScaled(1, 1.5, 1);
			glutSolidTorus(CUBE_SIZE / 8 - 8, CUBE_SIZE / 8, 4, 8);
		}glPopMatrix();
	}glPopMatrix();
}




void CHARACTER::load_map(int (*input)[MAP_SIZE_Y]){
	for (int i = 0; i < MAP_SIZE_X; i++) {
		for (int j = 0; j < MAP_SIZE_Y; j++) {
			map[i][j] = input[i][j];
		}
	}
}

POINT CHARACTER::get_location(){
	return location;
}

void CHARACTER::load_location(POINT input){
	other_location = input;
}

void CHARACTER::update_map_obj(CAR *obj){
	for (int i = 0; i < CAR_NUM; i++) {
		car_data[i] = obj[i];
	}
}

bool CHARACTER::check_itemkey(int input){
	if (input == key_item) {
		return true;
	}
	else {
		return false;
	}	
}


int CHARACTER::use_item(){
	//======= 디버그 필요 ===========
	if (item == ITEM_MOVE) {
		int tmp = rand() % 7 + 1;
		location.y += tmp;
		while (map[location.x][location.y] < 1) {
			location.y--;
		}	
	}
	//==================================


	//나머지 경우에 대해서
	if (item){
		int tmp = item;
		item = 0;//아이템이 사용됫음으로 0으로 초기화
		return tmp;//값 반환
	}
	else {
		return 0;
	}
	
}

void CHARACTER::hit_item(int input){
	if (!input) {
		return;
	}
	if (input == ITEM_STURN) {
		key_lock = true;
		item_timer = 0;
		item_timer2 = 0;
	}
	//안개 처리하심 될듯
	if (input == ITEM_FOG) {

	}
}

void CHARACTER::get_item(int input){
	item = input;
}

void CHARACTER::KeySetting(unsigned char front, unsigned char back, unsigned char right, unsigned char left){
	key[KEY_FRONT] = front;
	key[KEY_BACK] = back;	
	key[KEY_RIGHT] = right;
	key[KEY_LEFT] = left;
}

void CHARACTER::keySetting_item(unsigned char input){
	key_item = input;
}

void CHARACTER::SetBodyColor(int R, int G, int B) {
	body_color[0] = R;
	body_color[1] = G;
	body_color[2] = B;
}

void CHARACTER::Setlocaiton(int x, int y){
	location = { x*CUBE_SIZE,y*CUBE_SIZE };
}
