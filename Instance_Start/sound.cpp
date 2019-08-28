#include "sound.h"


bool dxSound::Init()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);

	sSound->Load("../../data/00_Menu.mp3", false);//0
	sSound->Load("../../data/box_open.wav", false);//1
	sSound->Load("../../data/Sea.mp3", false);//2
	sSound->Load("../../data/wall.wav", false);//3
	sSound->Load("../../data/Explosion.mp3", false);//4
	sSound->Load("../../data/sprite.wav", false);//5
	sSound->Load("../../data/fail_ending.wav", false);//6
	sSound->Load("../../data/succes_ending.wav", false);//7

	return true;
}
int    dxSound::Load(const char* pLoadName, bool bPlay)
{
	Channel* pChannel = nullptr;
	m_pSystem->createSound(pLoadName, FMOD_DEFAULT,
		0, &m_pSound[m_iSoundList++]);
	if (bPlay == true)
	{
		m_pSystem->playSound(m_pSound[m_iSoundList - 1], 0,
			false, &pChannel);
		m_pChannel[m_iSoundList - 1] = pChannel;
	}

	return m_iSoundList - 1;
};
void     dxSound::PlayEffect(int iIndex)
{
	if (g_bActiveApp == false) return;
	Channel* pChannel = nullptr;
	m_pSystem->playSound(m_pSound[iIndex], false,
		false, &pChannel);
	m_pChannel[iIndex] = pChannel;
}
void    dxSound::Play(int iIndex, bool bPlay, bool bLoop)
{
	if (g_bActiveApp == false) return;
	bool playing = false;
	if (m_pChannel[iIndex] != nullptr)
	{
		m_pChannel[iIndex]->isPlaying(&playing);
	}
	if (playing == false)
	{
		if (bLoop)
			m_pSound[iIndex]->setMode(FMOD_LOOP_NORMAL);
		else
			m_pSound[iIndex]->setMode(FMOD_LOOP_OFF);

		m_pSystem->playSound(m_pSound[iIndex], false,
			false, &m_pChannel[iIndex]);
	}
}
void    dxSound::Stop(int iIndex)
{
	if (g_bActiveApp == false) return;
	m_pChannel[iIndex]->stop();
}
void    dxSound::paused(int iIndex)
{
	if (g_bActiveApp == false) return;
	bool paused;
	m_pChannel[iIndex]->getPaused(&paused);
	m_pChannel[iIndex]->setPaused(!paused);
}
void    dxSound::Volume(int iIndex, float fVolume, bool bUp)
{
	if (g_bActiveApp == false) return;
	float fCurrentVolume;
	m_pChannel[iIndex]->getVolume(&fCurrentVolume);
	if (bUp == true)
	{
		fCurrentVolume += fVolume;
		fCurrentVolume = min(1.0f, fCurrentVolume);
	}
	else
	{
		fCurrentVolume -= fVolume;
		fCurrentVolume = max(0.0f, fCurrentVolume);
	}
	m_pChannel[iIndex]->setVolume(fCurrentVolume);
}
bool dxSound::Frame()
{
	m_pSystem->update();

	unsigned int total = 0;
	unsigned int ms = 0;
	m_pSound[0]->getLength(&total, FMOD_TIMEUNIT_MS);
	m_pChannel[0]->getPosition(&ms, FMOD_TIMEUNIT_MS);

	return true;
}
bool dxSound::Render()
{
	return true;
}
bool dxSound::Release()
{
	for (int iSound = 0; iSound < g_iMaxSound; iSound++)
	{
		m_pSound[iSound]->release();
	}
	m_pSystem->close();
	m_pSystem->release();
	return true;
}
dxSound::dxSound()
{
	m_iSoundList = 0;
}


dxSound::~dxSound()
{
}
