#pragma once
#include "FMOD\include\fmod.hpp"

//사운드 채널 갯수 정의
#define SOUND_NUM 10
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")

using namespace FMOD;


class CSound
{
public:
	CSound();
	virtual ~CSound();
	System * pSystem;
	Sound * pSound[SOUND_NUM];
	Channel * pChannel[SOUND_NUM];

	void Add_sound();
	void Play(int n);
};

