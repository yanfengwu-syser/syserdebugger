#include "StdAfx.h"
#include "ObjectViewApp.h"

CObjectViewApp	theApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return theApp.WinMainStart(hInstance,lpCmdLine,nCmdShow);
}

CObjectViewApp::CObjectViewApp(void)
{
}

CObjectViewApp::~CObjectViewApp(void)
{
}




bool CObjectViewApp::InitInstance()
{
	m_hMutex = OpenMutex(MUTEX_ALL_ACCESS,false,"Object View");
	if(m_hMutex)
		return false;
	m_hMutex = CreateMutex(NULL,false,"Object View");
	m_pszDiskList = "Wisp.dat;Syser.dat";
	if(CLocalWispApp::InitInstance()==false)
		return false;
	m_bHideMouse = true;
	m_hIcon = LoadIcon(m_hLocalInst,MAKEINTRESOURCE(IDI_ICON_SYSER_OPTION));
	m_FrameStyle&=~WS_VISIBLE;
	CreateFrame(WSTR("Object View"),540,400,0);
	m_MainFrame.Create(NULL,0,0,0,0,NULL,WISP_ID_MAIN_FRAME,WISP_WS_NULL);
	m_MainFrame.Resize(m_FrameBuffer.Width,m_FrameBuffer.Height);
	ShowWindow(m_hLocalWnd,SW_NORMAL);

	return true;
}

int	CObjectViewApp::ExitInstance()
{
	m_MainFrame.Destroy();
	DestroyFrame();
	CloseHandle(m_hMutex);
	return CLocalWispApp::ExitInstance();
}

