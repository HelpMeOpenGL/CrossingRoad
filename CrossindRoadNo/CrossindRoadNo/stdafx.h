#pragma once

//기본헤더
#include <GL/freeglut.h> 
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "FMOD/include/fmod.hpp"

#define MAP_SIZE_X 30 //좌우로는 30정도?
#define MAP_SIZE_Y 200 //200번정도 뛰면 도착하게 하자구?

#define CUBE_SIZE 50 //한칸의 크기 < 어느정도 점프할지랑 이것저것 요긴하게 쓰일듯

void printtext(int x, int y, std::string String);
