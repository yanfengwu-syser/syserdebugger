#include "StdAfx.h"
#include "LocalApp.h"
#include "resource.h"
#include "MainFrame.h"

CLocalApp	theApp;

#ifdef CODE_OS_WIN

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return theApp.WinMainStart(hInstance,lpCmdLine,nCmdShow);
}

#endif

CLocalApp::CLocalApp(void)
{
}

CLocalApp::~CLocalApp(void)
{
}

bool CLocalApp::InitInstance()
{
	if(CWispApp::InitInstance()==FALSE)
		return false;
	m_bHideMouse = true;
	m_hIcon = LoadIcon(m_hLocalInst,MAKEINTRESOURCE(IDI_ICON_WISP));
	CreateFrame(WSTR("Wisp Demo"),GetSystemMetrics(SM_CXFULLSCREEN)*5/6,GetSystemMetrics(SM_CYFULLSCREEN)*5/6,0);
	CMainFrame* pFrameWnd = new CMainFrame;
	pFrameWnd->Create(NULL,0,0,m_FrameBuffer.Width,m_FrameBuffer.Height,NULL,WISP_ID_MAIN_FRAME,WISP_WS_NULL);
	//TODO:
	//
	return true;
}

int	CLocalApp::ExitInstance()
{
	//TODO:
	//
	CMainFrame* pFrameWnd = (CMainFrame*)m_pRootWnd;
	pFrameWnd->Destroy();
	delete pFrameWnd;
	m_pRootWnd = NULL;
	DestroyFrame();
	return CWispApp::ExitInstance();
}
