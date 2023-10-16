#ifndef _DX_TEST_H_
#define _DX_TEST_H_

class CSyserDX
{
public:
	CSyserDX();
	bool Init();
	void Release();
	void LockFrameSurfacer();
	void UnlockFrameSurfacer();
public:
	LPDIRECTDRAW4	m_pDD4;
	LPDIRECTDRAW	m_pDD;
	LPDIRECTDRAWSURFACE4 m_pFrameSurfacer;
};

#endif

