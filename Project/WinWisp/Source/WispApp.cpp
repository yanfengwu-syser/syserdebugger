#include "StdAfx.h"
#include "WispApp.h"

CWispApp::CWispApp()
{
}

CWispApp::~CWispApp()
{
}

bool CWispApp::InitInstance()
{
	return Init();
}

int	CWispApp::ExitInstance()
{
	Release();
	return 0;
}

int	CWispApp::Run()
{
	Pump();
	return 0;
}


