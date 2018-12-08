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
}

void CHARACTER::reset(){

}

void CHARACTER::draw(){

}

void CHARACTER::update(){

}

void CHARACTER::keyboard(unsigned char input){
	if (input == key[KEY_FRONT]) {

	}
	if (input == key[KEY_BACK]) {

	}
	if (input == key[KEY_RIGHT]) {

	}
	if (input == key[KEY_LEFT]) {

	}
}

void CHARACTER::draw_body(){

}

void CHARACTER::draw_leg(){
	
}

void CHARACTER::animation(){
	



}

void CHARACTER::KeySetting(unsigned char front, unsigned char back, unsigned char right, unsigned char left){
	key[KEY_FRONT] = front;
	key[KEY_BACK] = back;
	key[KEY_LEFT] = left;
	key[KEY_RIGHT] = right;
}
