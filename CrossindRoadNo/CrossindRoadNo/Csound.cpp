#include "stdafx.h"
#include "Csound.h"


CSound::CSound()
{
	FMOD::System_Create(&pSystem);
	pSystem->init(
		SOUND_NUM
		, FMOD_INIT_NORMAL
		, nullptr
	);
	for (auto& p : pSound) p = nullptr;
}


CSound::~CSound()
{
	for (int i = 0; i < SOUND_NUM; ++i)
	{
		pSound[i]->release();
	}

	pSystem->release();
	pSystem->close();
}

void CSound::Add_sound()
{
	//사운드 추가 
	//배경음
	pSystem->createStream(
		"Sound/handclap_ingame_vol.mp3"
		, FMOD_2D | FMOD_LOOP_NORMAL
		, nullptr
		, &pSound[0]
	);

}

void CSound::Play(int n)
{
	pSystem->update();

	pSystem->playSound(pSound[n]
		, nullptr, false, &pChannel[n]);

}
