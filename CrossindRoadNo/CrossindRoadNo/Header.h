#pragma once
#define SOUND_COUNT 10

void printtext(int x, int y, std::string String);
//======== 초기화 관련 함수============
void Map_Reset();

void LoadFile();

void global_init();


//========= 맵관련 함수 =============

void Draw_Barrier(int Type, int x, int y);

//======= 사운드 클래스 추가 ==========

