#include "xStd.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
using namespace FMOD;
const int g_iMaxSound = 32;
#pragma comment(lib, "fmod64_vc.lib")

class dxSound
{
public:
	static dxSound* Get()
	{
		static dxSound sound;
		return &sound;
	}
public:
	FMOD::System*   m_pSystem;
	FMOD::Sound*	m_pSound[g_iMaxSound];
	FMOD::Channel*  m_pChannel[g_iMaxSound];
	int   m_iSoundList;
	wchar_t    m_szBuffer[128];
public:
	bool	Init();
	bool	Frame();
	bool	Release();
	bool	Render();
public:
	int     Load(const char* pLoadName, bool bPlay);
	void    Play(int iIndex, bool bPlay = true, bool bLoop = false);
	void    PlayEffect(int iIndex);
	void    Stop(int iIndex);
	void    paused(int iIndex);
	void    Volume(int iIndex, float fVolume, bool bUp);
public:
	dxSound();
	virtual ~dxSound();
};
#define sSound dxSound::Get()