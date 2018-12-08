#pragma once

//기본헤더
#include <GL/freeglut.h> 
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <string>
#include "FMOD/include/fmod.hpp"

#define MAP_SIZE_X 200 //좌우로는 30정도?
#define MAP_SIZE_Y 30 //200번정도 뛰면 도착하게 하자구?

#define CUBE_SIZE 10 //한칸의 크기 < 어느정도 점프할지랑 이것저것 요긴하게 쓰일듯

#define SCENE_LOBBY 10000
#define SCENE_MAINGAME 10001
#define SCENE_END 10002

