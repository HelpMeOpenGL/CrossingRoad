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

}

void CHARACTER::draw_leg(){
	
}

void CHARACTER::animation(){
	



}

void CHARACTER::KeySetting(unsigned char front, unsigned char back, unsigned char right, unsigned char left){
	key[KEY_FRONT] = front;
	key[KEY_BACK] = back;	
	key[KEY_RIGHT] = right;
	key[KEY_LEFT] = left;
}
