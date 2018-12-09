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
	key[KEY_BACK] = 'a';
	key[KEY_LEFT] = 's';
	key[KEY_RIGHT] = 'd';
	item = 0;
	type = 0;
	state = STATE_IDLE;
	key_lock = false;
	item_timer = 0;
	location.x = rand() % 20 + 5;
	location.y = 5;
	b_item_fog = false;
}

void CHARACTER::reset(){

}

void CHARACTER::draw(){

}

void CHARACTER::update(){
	//키 잠금 구현(3초)
	if (key_lock) {
		item_timer++;
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
}

void CHARACTER::keyboard(unsigned char input){
	if (key_lock) {//키가 잠기면 바로 종료
		return;
	}
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
	glPushMatrix(); {

	}glPopMatrix();
}

void CHARACTER::draw_leg(){
	
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
	
}

void CHARACTER::hit_item(int input){
	if (!input) {
		return;
	}
	if (input == ITEM_STURN) {
		key_lock = true;
	}
	//안개 처리하심 될듯
	if (input == ITEM_FOG) {

	}
}

void CHARACTER::KeySetting(unsigned char front, unsigned char back, unsigned char right, unsigned char left){
	key[KEY_FRONT] = front;
	key[KEY_BACK] = back;	
	key[KEY_RIGHT] = right;
	key[KEY_LEFT] = left;
}
