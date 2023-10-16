#include "StdAfx.h"
#include "Syser.h"
#include "MainFrame.h"
#include "X86Optr.h"
#include "Services.h"
#include "Int0xe.h"
#include "IOAPIC.h"
#include "VideoDriver.h"
#include "BpintCmd.h"
#include "TimerInterrupt.h"
#include "HardWareInterruptCtrl.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "UHCIDevice.h"
#include "NMIInterruptHandle.h"
#include "VirtualPCSupport.h"
#include "VMWareSupport.h"
#include "CopyOnWritePatch.h"
#include "OSProcessThread.h"
#include "PatchKeBugCheckEx.h"
extern 	DWORD dwgErrorCode;
bool gbVideoBufferOK=true;
CSyser *gpSyser=NULL;
CSyserConfig*gpSyserCfg=NULL;
CSyserPluginUI *gpSyserPluginUI=NULL;
SYSER_BOOT_DEVICE_EXTENSION*gpSysBootDevEx=NULL;
SYSER_LANGUAGE_DEVICE_EXTENSION*gpSysLangDevEx=NULL;

extern BYTE*gpStackBuffer;
extern BYTE*gpStackBufferTop;
extern BYTE*gpStackBufferBottom;

WISP_MSG_MAP_BEGIN(CMoveFramMenu)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP_END(CWispMenu)

bool CMoveFramMenu::OnKeyEvent(IN WISP_MSG*pMsg)
{
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON && (m_Style&WISP_WMS_POPUP)==0 && pMsg->MsgMouseWndPT.x>m_WndMenuItemWidth)
	{
		if(pMsg->KeyEvent.bKeyDown)
		{
			m_pWispBase->BeginMoveWnd();
		}
	}
	return true;
}

void CSyser::SyserWaitThread(void*)
{
	do
	{
		KeWaitForSingleObject(&gpSyser->m_WaitEvent, Executive, KernelMode,0,0);
		KeResetEvent(&gpSyser->m_WaitEvent);		
		for(CSyserDumpList::IT Iter = gpSyser->m_DumpList.Begin();Iter!=gpSyser->m_DumpList.End();Iter++)
		{
			if(gpFileIO->WriteToFile(Iter->DumpFileName,Iter->DumpData,Iter->DumpSize))
			{
				::DbgPrint("Syser : %d Byte(s) dump to %s\n",Iter->DumpSize,(PCSTR)Iter->DumpFileName);
			}
			else
			{
				::DbgPrint("Syser : Fait to dump data to %s\n",(PCSTR)Iter->DumpFileName);
			}
			gpUserHeap[SYSER_MAIN_HEAP]->Free(Iter->DumpData);
			Iter->DumpData = NULL;
			Iter->DumpSize = 0;
		}
		gpSyser->m_DumpList.Clear();
	}while(gpSyser->m_bWaitThread);
	PsTerminateSystemThread(STATUS_SUCCESS);
}

void CSyser::StartSyserWaitThread()
{
	HANDLE hThread;
	KeInitializeEvent(&m_WaitEvent,NotificationEvent,FALSE);
	m_bWaitThread = true;
	PsCreateSystemThread(&hThread,THREAD_ALL_ACCESS,0,0,0,SyserWaitThread,0);
	m_ThreadPointer = NULL;
	ObReferenceObjectByHandle(hThread,THREAD_ALL_ACCESS,NULL,KernelMode,&m_ThreadPointer,NULL);
	ZwClose(hThread);
}

void CSyser::StopSyserWaitThread()
{
	if(m_ThreadPointer)
	{
		m_bWaitThread = false;
		KeSetEvent(&m_WaitEvent,0,FALSE);
		KeWaitForSingleObject(m_ThreadPointer,Executive,KernelMode,FALSE,NULL);
		ObDereferenceObject(gpSyser->m_ThreadPointer);
	}
}

CSyser::CSyser()
{
	m_OSHwndRoot=0;
	m_ThreadPointer = NULL;
	m_CriticalEFlag = 0;
	gpSyserPluginUI = &m_SyserUI;
	m_pOrgProcess = 
	m_pSysDebugger = 
	m_pDebugger = NULL;
	m_OSMajorVersion=0;
	m_OSMinorVersion=0;
	m_OSBuildNumber=0;
	m_VideoBufBackup=NULL;
	m_bUpdateReg=false;
	m_bScrBackup=true;
	m_bUserScrBackuped = false;
	m_bHandle=false;
	m_bSaveReg=false;
	m_bPatchCopyOnWrite = false;
	m_bCopyOnWriteFastCall = false;
	m_bShowSplash = false;
	//m_RtlGetCurrentDirectory_U = NULL;
	gpStackBuffer = NULL;
	m_bHardDriverSuccess=m_bHookSuccess=false;
	gpFileIO = &m_FileIO;
	m_bFaultsStat=(SyserOption.ifaults!=0);
	m_bInterrupt1HereStat =  (SyserOption.i1here!=0);
	m_Interrupt3HereStat = SyserOption.i3here;
	m_bDbgRegAccessMon=false;
	m_OSVer = GetOSVer(&m_OSMajorVersion,&m_OSMinorVersion,&m_OSBuildNumber);
	::DbgPrint("Syser : OSVersion Major %d Minor %d Build %d\n",m_OSMajorVersion,m_OSMinorVersion,m_OSBuildNumber);	
	m_bInitSuccess = false;
	m_bMovingFrame = false;
	m_pSyserConnect = NULL;
	STZeroMemory(m_RealFrameBuffer);
	PDEVICE_OBJECT DeviceObject;
	PFILE_OBJECT FileObject;
	UNICODE_STRING UnicodeName;
	gpSysBootDevEx = NULL;
	RtlInitUnicodeString(&UnicodeName,WSTR("\\Device\\SyserBoot"));
	if(NT_SUCCESS(IoGetDeviceObjectPointer(&UnicodeName,FILE_READ_DATA,&FileObject,&DeviceObject)))
	{
		ObDereferenceObject(FileObject);
		gpSysBootDevEx = (SYSER_BOOT_DEVICE_EXTENSION*)DeviceObject->DeviceExtension;
	}
	::DbgPrint("Syser : Find SyserBoot DevEx = %08X\n",gpSysBootDevEx);
	gpSysLangDevEx = NULL;
	RtlInitUnicodeString(&UnicodeName,WSTR("\\Device\\SyserLanguage"));
	if(NT_SUCCESS(IoGetDeviceObjectPointer(&UnicodeName,FILE_READ_DATA,&FileObject,&DeviceObject)))
	{
		ObDereferenceObject(FileObject);
		gpSysLangDevEx = (SYSER_LANGUAGE_DEVICE_EXTENSION*)DeviceObject->DeviceExtension;
	} 
	::DbgPrint("Syser : Find SysLang DevEx = %08X\n",gpSysLangDevEx);

	RtlInitUnicodeString(&UnicodeName,WSTR("PsRemoveLoadImageNotifyRoutine"));
	(PVOID&)m_PsRemoveLoadImageNotifyRoutine=MmGetSystemRoutineAddress(&UnicodeName);
	KeInitializeSpinLock(&m_NotifyLock);
}

void CSyser::ShowSplash()
{
	m_bShowSplash = false;
	if(m_FrameBuffer.Buffer==NULL || m_RealFrameBuffer.Buffer == NULL || SyserOption.iShowStartSplash == 0)
		return;
	for(int Off = 0;Off<m_RealFrameBuffer.BufferSize;Off+=MP_SIZE)
	{
		if(MmIsAddressValid((BYTE*)m_RealFrameBuffer.Buffer +Off)==false)
		{
			::DbgPrint("***************************************************************************\n");
			::DbgPrint("Syser : Invalid FrameBuf [%08X] ,Invalid Address [%08X]\n",m_RealFrameBuffer.Buffer,(BYTE*)m_RealFrameBuffer.Buffer+Off);
			::DbgPrint("***************************************************************************\n");
			gpSyser->m_RealFrameBuffer.Buffer = NULL;
			return;
		}
	}
	m_OldStyle = m_MainFrame.m_Style;
	m_MainFrame.m_Style = WISP_WS_NULL;
	m_OldFrameSize.cx = m_MainFrame.m_WindowRect.cx;
	m_OldFrameSize.cy = m_MainFrame.m_WindowRect.cy;
	m_MainFrame.m_MainTabWnd.Show(WISP_SH_HIDDEN);
	m_MainFrame.m_CloseBT.Show(WISP_SH_HIDDEN);
	m_MainFrame.LoadBKDIB("\\SyserApp\\syser.bmp");
	m_MainFrame.Resize(m_MainFrame.m_pBKDIB->Width(),m_MainFrame.m_pBKDIB->Height());
	CenterScreen();
	BackupScreen();
	m_MainFrame.Update();
	UpdateFrameBuffer();
	m_bShowSplash=true;
}

void CSyser::HideSplash()
{
	if(m_bShowSplash==false || m_FrameBuffer.Buffer==NULL || m_RealFrameBuffer.Buffer == NULL || SyserOption.iShowStartSplash == 0)
		return;
	RestoreScreen();
	m_MainFrame.m_Style = m_OldStyle;
	m_MainFrame.DetachBKDIB();
	m_DIBLib.ReleaseDIB("\\SyserApp\\syser.bmp");
	m_MainFrame.m_MainTabWnd.Show();
	m_MainFrame.m_CloseBT.Show();
	m_MainFrame.Resize(m_OldFrameSize.cx,m_OldFrameSize.cy);
	CenterScreen();
	m_MainFrame.Update();
}

bool CSyser::SetClipboardString(PCSTR String)
{
	m_ClipboardString.Preallocate(TStrLen(String)+1);
	m_ClipboardString.m_Length = SyserAnsiToUnicode(String,m_ClipboardString.m_pData,m_ClipboardString.m_MaxLength);
	return true;
}

void CSyser::OnMouseMove(IN int DeltaX,IN int DeltaY)
{
	DeltaY = DeltaY*SyserOption.iMouseSensitivity/10;
	DeltaX = DeltaX*SyserOption.iMouseSensitivity/10;
	CWispBase::OnMouseMove(DeltaX,DeltaY);
}

bool CSyser::Init()
{
	
	KeInitializeEvent(&m_ImageLoadSyncEvent, SynchronizationEvent, TRUE);
	if(gpSysBootDevEx==NULL)
	{
		::DbgPrint("***************************************************\n");
		::DbgPrint("Syser : SysBoot.sys isn't actived ! Please reboot !\n");
		::DbgPrint("***************************************************\n");
		return false;
	}
	if(gpSysBootDevEx)
	{
		if(gpSysBootDevEx->cbSize!=sizeof(SYSER_BOOT_DEVICE_EXTENSION) || 
			gpSysBootDevEx->Version!=SYSER_BOOT_VER)
		{
			::DbgPrint("***************************************************************\n");
			::DbgPrint("Syser : Detected previous version SysBoot.sys ! Please reboot !\n");
			::DbgPrint("***************************************************************\n");
			return false;
		}
		if(gpSysBootDevEx->bCanceled)
		{
			gpSysBootDevEx->bCanceled = false;
			::DbgPrint("Syser : User canceled!\n");
			return false;
		}
	}
	m_bInitSuccess = false;
	if(InitFileIO()==false)
	{
		::DbgPrint("Syser : InitFileIO error!\n");
		return false;
	}
#ifndef __DEMO__VERSION__
	SERIALNAME* gStr= GetSerialNumber();
	for(int i=0;i<28;i++)
	{
		m_GSnMap.InsertUnique(gStr[i].MulVal,gStr[i].Name);
	}	
#endif
	dwgErrorCode=9;
	m_SyserUI.LoadAPIDefine();
	dwgErrorCode=901;
	m_pszDiskList = "Wisp.dat;Syser.dat";
	m_DefaultFontType = SyserOption.iBigFont?WISP_FONT_8X16:WISP_FONT_6X12;
	if(CWispBase::Init()==false)
	{
		::DbgPrint("Syser : CWispBase::Init() error!\n");
		return false;
	}
	
	dwgErrorCode=10;
	InitHotKeyInfo();
	m_OrgWindowWidth = SyserOption.iStartWndWidth;
	m_OrgWindowHeight = SyserOption.iStartWndHeight;
	MAX_LIMIT(m_OrgWindowWidth,SyserOption.iMaxWndWidth);
	MAX_LIMIT(m_OrgWindowHeight,SyserOption.iMaxWndHeight);
	MAX_LIMIT(m_OrgWindowWidth,2048);
	MAX_LIMIT(m_OrgWindowHeight,2048);
	dwgErrorCode=110;
	if(CreateFrame(WSTR("Syser Kernel Debugger"),m_OrgWindowWidth,m_OrgWindowHeight,0)==false)
	{
		::DbgPrint("Syser : CreateFrame() error!\n");
		return false;
	}
	dwgErrorCode=11;
	if(gpSyser->m_SysInfo.m_bSNPass==false && gpSyser->m_SysInfo.m_bEvlVer==false)
	{
		::DbgPrint("***************************************************\n");
		::DbgPrint("Syser : %ws\n",(PCWSTR)gpSyser->m_SysInfo.m_LicTip);
		::DbgPrint("***************************************************\n");
		return false;
	}
	switch(SyserOption.iVideoDetectMode)
	{
	case SYSER_VDM_AUTO:
		::DbgPrint("Syser : Detect Video mode -> Auto\n");
		break;
	case SYSER_VDM_USER:
		::DbgPrint("Syser : Detect Video mode -> User Mode\n");
		break;
	case SYSER_VDM_KERNEL:
		::DbgPrint("Syser : Detect Video mode -> Kernel Mode\n");
		break;
	default:
		::DbgPrint("Syser : Detect Video mode -> Error Mode\n");
		break;
	}
	if(SyserOption.iVideoDetectMode!= SYSER_VDM_USER && InstallDdrawHook()==false)
		return false;
	dwgErrorCode=12;
	if(m_PCSystem.Init()==false)
	{
		::DbgPrint("Syser : m_PCSystem.Init() error!\n");
		return false;
	}
		dwgErrorCode=113;
	ShowSplash();
	dwgErrorCode=13;
	if(m_SysInfo.Init()==false)
	{
		HideSplash();
		::DbgPrint("Syser : m_SysInfo.Init() error!\n");
		return false;
	}
	m_SyserUI.LoadComment();
	//////////////////////////////////////////////////////////////
	//  初始化 Syser 堆栈
	//////////////////////////////////////////////////////////////
	MAX_LIMIT(SyserOption.iStackSizeK,4096);
	MIN_LIMIT(SyserOption.iStackSizeK,512);
	gpStackBuffer = new BYTE[SyserOption.iStackSizeK*1024];
	dwgErrorCode=14;
	if(gpStackBuffer==NULL)
	{
		HideSplash();
		::DbgPrint("Syser : new %dk StackBuffer error!\n",SyserOption.iStackSizeK);
		return false;
	}
	ZeroMemory(gpStackBuffer,SyserOption.iStackSizeK*1024);
	gpStackBufferTop = &gpStackBuffer[SyserOption.iStackSizeK*1024];
	gpStackBufferTop = (BYTE*)(((DWORD)gpStackBufferTop) & 0xFFFFFFF0);
	//////////////////////////////////////////////////////////////
	m_bSaveReg=false;
	dwgErrorCode=15;
	if(InstallDebug()==false)
	{
		HideSplash();
		::DbgPrint("Syser : InstallDebug() error!\n");
		return false;
	}
	LoadPlugin();
	m_bInitSuccess = true;
	m_MainFrame.m_ConsoleWnd.RunModulePathBat("Syser.cmd","-s");
	HideSplash();
	dwgErrorCode=16;
	m_SysInfo.LoadSDSList();
	if(m_SysInfo.m_bSNPass || m_SysInfo.m_bEvlVer)
	{
		OUTPUT(WSTR("%<B>%s\n"),(PCWSTR)m_SysInfo.m_LicTip);
		SYSEXPLR_OUTPUT(WSTR("%<B>%s\n"),(PCWSTR)m_SysInfo.m_LicTip);
	}
	StartSyserWaitThread();
	dwgErrorCode=17;
	::DbgPrint("Syser : Version %s  Build Date %s!\n",VER_PRODUCTVERSION_STR,__DATE__);
	::DbgPrint("Syser : Load Success ! You can press \"CTRL+F12\" to active Syser !\n");	
	return true;
}

void CSyser::InitRemoteConnect()
{
	m_pSyserConnect = NULL;
	switch(SyserOption.iConnectType)
	{
	case SYSER_NO_CONNECT:
		break;
	case SYSER_SERIAL_PORT_CONNECT:
		if(m_SerialPortConnect.Init())
			m_pSyserConnect = &m_SerialPortConnect;
		break;
	default:
		OUTPUT(WSTR("Syser : Unknow Connect Type\n"));
		break;
	}
	if(m_pSyserConnect)
		m_SDServer.Init(m_pSyserConnect);
}

void CSyser::ReleaseRemoteConnect()
{
	if(m_pSyserConnect)
	{
		m_SDServer.Release();
		m_pSyserConnect->Release();
	}
}

void CSyser::Release()
{
	KeSetEvent(&m_ImageLoadSyncEvent,0,FALSE);
	gpSyser->m_pDebugger = gpSyser->m_pSysDebugger;
	StopSyserWaitThread();
	UnloadPlugin();
	ReleaseBreakPoint();
	m_SysInfo.Release();
	m_PCSystem.Release();
	RemoveDdrawHook();
	UninstallDebug();//注意断点要在中断1，3之前卸载
	CWispBase::Release();
	DestroyFrame();
	SafeDelete(gpStackBuffer);
	::DbgPrint("Syser : Unload Success!\n");
}

int CSyser::LoadPlugin()
{
	char szPlugin[MAX_FN_LEN];
	TStrCpy(szPlugin,m_szImagePath);
	TStrCat(szPlugin,"Plugin\\i386\\*");
	return gpFileIO->XScan(szPlugin,XScanPlugin,NULL,true);
}

extern "C"
{
	NTSYSAPI NTSTATUS NTAPI ZwLoadDriver(IN PUNICODE_STRING DriverServiceName);
	NTSYSAPI NTSTATUS NTAPI ZwUnloadDriver(IN PUNICODE_STRING DriverServiceName);
}

XSCAN_RES CSyser::XScanPlugin(CFileIO*pFileIO,PCSTR FullPathFileName,ULSIZE FileSize,void*CBParem)
{	
	PSTR FileName;
	WCHAR *WFileName;
	DWORD Len;
	char RegString[] = "\\Registry\\Machine\\System\\CurrentControlSet\\Services\\";
	PUNICODE_STRING pRegistryServiceName;
	FileName = TGetFileName(FullPathFileName);
	Len = TStrLen(FileName);
	if(Len<=4)
		return XSCAN_RES_CONTINUE;
	if(TStrICmp(&FileName[Len-4],".sys"))
		return XSCAN_RES_CONTINUE;
	pRegistryServiceName =(PUNICODE_STRING) new char[(TStrLen(RegString)+Len)*sizeof(WCHAR)+sizeof(UNICODE_STRING)];
	WFileName=(WCHAR*)&pRegistryServiceName[1];
	TStrCpy(WFileName,RegString);
	TStrCat(WFileName,FileName);
	Len=TStrLen(WFileName);
	WFileName[Len-4]=0;
	RtlInitUnicodeString(pRegistryServiceName,WFileName);
	RegisterPluginService(pRegistryServiceName,FullPathFileName);
	ZwLoadDriver(pRegistryServiceName);
	return XSCAN_RES_CONTINUE;
}

bool CSyser::RegisterPluginService(PUNICODE_STRING ServiceName,PCSTR DriverFileFullName)
{
	NTSTATUS Status;
	WCHAR* wszImagePath=NULL;
	HANDLE KeyHandle;
	DWORD DataSize;
	ACCESS_MASK AccessMask=KEY_ALL_ACCESS;
	OBJECT_ATTRIBUTES ObjectAttributs;
	ULONG TitleIndex=0;
	WCHAR DisplayNameValue[]=L"DisplayName";
	WCHAR TypeValue[]=L"Type";
	WCHAR ErrorControlValue[]=L"ErrorControl";
	WCHAR StartValue[]=L"Start";
	WCHAR ImagePathValue[]=L"ImagePath";
	WCHAR* TempName;
	UNICODE_STRING ValueName;
	PUNICODE_STRING pClass=NULL;
	DWORD dwValue;
	ULONG CreateOptions=REG_OPTION_NON_VOLATILE,Disposition;
	InitializeObjectAttributes(&ObjectAttributs,ServiceName,OBJ_CASE_INSENSITIVE,NULL,NULL);
	Status = ZwCreateKey(&KeyHandle,AccessMask,&ObjectAttributs,TitleIndex,pClass,CreateOptions,&Disposition);
	if(Status)
		return false;
	DataSize=TStrLen(DriverFileFullName)+1;
	wszImagePath=new WCHAR[DataSize];
	if(wszImagePath==NULL)goto ErrorQuit;
	TStrCpy(wszImagePath,DriverFileFullName);
	RtlInitUnicodeString(&ValueName,ImagePathValue);
	Status = ZwSetValueKey(KeyHandle,&ValueName,TitleIndex,REG_EXPAND_SZ,wszImagePath,sizeof(WCHAR)*DataSize);
	if(Status)
	{
		delete []wszImagePath;
		goto ErrorQuit;
	}
	TempName = TGetFileName(wszImagePath);
	DataSize = TStrLen(TempName)+1;
	RtlInitUnicodeString(&ValueName,DisplayNameValue);
	Status = ZwSetValueKey(KeyHandle,&ValueName,TitleIndex,REG_SZ,TempName,sizeof(WCHAR)*DataSize);
	delete []wszImagePath;
	if(Status)goto ErrorQuit;
	RtlInitUnicodeString(&ValueName,TypeValue);
	dwValue=1;
	Status = ZwSetValueKey(KeyHandle,&ValueName,TitleIndex,REG_DWORD,&dwValue,sizeof DWORD);
	if(Status)goto ErrorQuit;
	RtlInitUnicodeString(&ValueName,StartValue);
	dwValue=3;
	Status = ZwSetValueKey(KeyHandle,&ValueName,TitleIndex,REG_DWORD,&dwValue,sizeof DWORD);
	if(Status)goto ErrorQuit;
	RtlInitUnicodeString(&ValueName,ErrorControlValue);
	dwValue=1;
	Status = ZwSetValueKey(KeyHandle,&ValueName,TitleIndex,REG_DWORD,&dwValue,sizeof DWORD);
	if(Status==0)
		return true;
ErrorQuit:
	ZwClose(KeyHandle);
	return false;
}

void CSyser::UnloadPlugin()
{
	UNICODE_STRING ServiceName;
	WCHAR szName[MAX_LONG_NAME_LEN],*pszService;
	pszService = szName+TStrCpy(szName,"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\");
	for(CPluginMap::IT Iter=m_PluginMap.Begin();Iter.IsExist();Iter++)
	{
		TStrCpy(pszService,(PCWSTR)Iter.Key());
		RtlInitUnicodeString(&ServiceName,szName);
		ZwUnloadDriver(&ServiceName);
	}
}


void CSyser::ReleaseBreakPoint()
{
	if(m_pSysDebugger==NULL)
		return;
	if(m_bDbgRegAccessMon)
	{//如果系统留有我们的硬件断点
		::DbgPrint("Syser : Clear Hardware Breakpoint\n");
		ZeroMemory(SyserDR,sizeof(SyserDR));
		SyserDisableDebugRegisterMontior();
		m_bDbgRegAccessMon = false;
		SyserSaveSyserDRX();
		UpdateOtherCPUDRX();
		SyserStopOtherCPUs();
		SyserStartOtherCPUs();
	}
}

bool CSyser::InitFileIO()
{
	UNICODE_STRING UniImagePath;
	RTL_QUERY_REGISTRY_TABLE RegTable[2];
	ZeroMemory(RegTable,sizeof(RegTable));
	ZeroMemory(m_szImagePath,sizeof(m_szImagePath));
	UniImagePath.Length=0;
	UniImagePath.MaximumLength=sizeof(m_szImagePath);
	UniImagePath.Buffer=m_szImagePath;
	RegTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT | RTL_QUERY_REGISTRY_REQUIRED;
	RegTable[0].Name = WSTR("ImagePath");
	RegTable[0].EntryContext = &UniImagePath;
	if(!NT_SUCCESS(RtlQueryRegistryValues(RTL_REGISTRY_SERVICES,WSTR("Syser"),RegTable,NULL,NULL)))
		return false;
	PWSTR pStr=TStrRChr(m_szImagePath,(WCHAR)'\\');
	if(pStr)
		*pStr=0;
	if(TStrICmp(m_szImagePath,WSTR("system32\\drivers"))==0)
	{
		TStrCpy(m_szImagePath,m_SysInfo.m_szSystem32Drivers);
	}
	m_FileIO.SetCurDir(m_szImagePath);
	gpFileIO = &m_FileIO;
	return true;
}

bool CSyser::CreateFrame(WISP_CHAR*WndName,int Width,int Height,int Bpp)
{
	SwitchHeap(SYSER_SCREEN_HEAP);
	m_FrameBuffer.Width = Width;
	m_FrameBuffer.Height = Height;
	m_FrameBuffer.Bpp = 32;
	m_FrameBuffer.PixelFormat = 0;
	m_FrameBuffer.LineDistance = m_FrameBuffer.Width*sizeof(COLORREF);
	m_FrameBuffer.Flag = 0;
	m_FrameBuffer.BufferSize = SyserOption.iMaxWndWidth*SyserOption.iMaxWndHeight*sizeof(COLORREF);
	m_FrameBuffer.Buffer = new BYTE[m_FrameBuffer.BufferSize];
	m_VideoBufBackup = new BYTE[m_FrameBuffer.BufferSize];
	SwitchHeap(SYSER_MAIN_HEAP);
	m_RootPos.x = CENTER_ALGN(Width,m_RealFrameBuffer.Width);
	m_RootPos.y = CENTER_ALGN(Height,m_RealFrameBuffer.Height);
	STZeroMemory(m_FrameRect);
	if(m_MainFrame.Create(WndName,0,0,Width,Height,NULL,0,WISP_WS_BORDER)==false)
		return false;
	m_MainFrame.m_pWispBase->SetKeyboardLayer(SyserOption.iKeyboardLayer);
	return true;
}

bool CSyser::ResizeHostFrame(int Width,int Height)
{
	return true;
}

bool CSyser::ResizingFrame(int Width,int Height)
{
	if(Width > SyserOption.iMaxWndWidth  || Height > SyserOption.iMaxWndHeight)
		return false;
	m_FrameBuffer.Width = Width;
	m_FrameBuffer.Height = Height;
	return true;
}

void CSyser::DestroyFrame()
{
	SafeDelete(m_FrameBuffer.Buffer);
	SafeDelete(m_VideoBufBackup);
}

void CSyser::RestoreMovingFrame()
{
	for(int n=0;n<m_FrameRect.cx;n++)
	{
		m_RealFrameBuffer.pDrawHAL->DrawXorPixel(&m_RealFrameBuffer,m_FrameRect.x+n,m_FrameRect.y,WISP_RGB(255,255,255));
		m_RealFrameBuffer.pDrawHAL->DrawXorPixel(&m_RealFrameBuffer,m_FrameRect.x+n,m_FrameRect.y+m_FrameRect.cy-1,WISP_RGB(255,255,255));
	}

	for(int n=0;n<m_FrameRect.cy;n++)
	{
		m_RealFrameBuffer.pDrawHAL->DrawXorPixel(&m_RealFrameBuffer,m_FrameRect.x,m_FrameRect.y+n,WISP_RGB(255,255,255));
		m_RealFrameBuffer.pDrawHAL->DrawXorPixel(&m_RealFrameBuffer,m_FrameRect.x+m_FrameRect.cx-1,m_FrameRect.y+n,WISP_RGB(255,255,255));
	}
}

void CSyser::DrawMovingFrame()
{
	for(int n=0;n<m_FrameRect.cx;n++)
	{
		m_RealFrameBuffer.pDrawHAL->DrawXorPixel(&m_RealFrameBuffer,m_FrameRect.x+n,m_FrameRect.y,WISP_RGB(255,255,255));
		m_RealFrameBuffer.pDrawHAL->DrawXorPixel(&m_RealFrameBuffer,m_FrameRect.x+n,m_FrameRect.y+m_FrameRect.cy-1,WISP_RGB(255,255,255));
	}

	for(int n=0;n<m_FrameRect.cy;n++)
	{
		m_RealFrameBuffer.pDrawHAL->DrawXorPixel(&m_RealFrameBuffer,m_FrameRect.x,m_FrameRect.y+n,WISP_RGB(255,255,255));
		m_RealFrameBuffer.pDrawHAL->DrawXorPixel(&m_RealFrameBuffer,m_FrameRect.x+m_FrameRect.cx-1,m_FrameRect.y+n,WISP_RGB(255,255,255));
	}
}

bool CSyser::MoveFrame(int dx,int dy)
{
	WISP_RECT Rect;
	m_RootPos.x+=dx;
	m_RootPos.y+=dy;

	Rect.x=Rect.y=0;
	Rect.cx=m_RealFrameBuffer.Width;
	Rect.cy=m_RealFrameBuffer.Height;

	RestoreMovingFrame();
	m_FrameRect.x = m_RootPos.x;
	m_FrameRect.y = m_RootPos.y;
	m_FrameRect.cx = m_pRootWnd->m_WindowRect.cx;
	m_FrameRect.cy = m_pRootWnd->m_WindowRect.cy;

	if(ClipRect(&m_FrameRect,&Rect)==false)
		return false;
	DrawMovingFrame();
	return true;
}

bool CSyser::WakeUpMsgThread()
{
	m_bMsgSleeping = false;
	return true;
}

void CSyser::IdleEvent()
{
	ULONGLONG CurTSC,ms,Sub;
	ms=0;
	CurTSC=SyserGetTSC();
	Sub = CurTSC-gPrevTSC;
	ms = Sub/gTSCTickCount;
	if(ms>20)
	{
		gPrevTSC=CurTSC;
		OnTimer(*(int*)&ms);
	}
	m_PCSystem.USBDeviceService();
}

bool CSyser::SleepMsgThread()
{
	if(gpSyserCfg->m_SupportTimerInterrupt)
	{
// 		__asm
// 		{
// 			sti
// 			hlt
// 		}

		SyserSti();
		SyserHlt();
	}
	else
	{
		while(m_InputMsgQueue.Count()==0)
		{
			IdleEvent();
		}
	}
	return true;
}

void CSyser::EnterCriticalSection()
{
	if(!gInVirtualPC)
		SyserCloseInterrupt();
}

void CSyser::LeaveCriticalSection()
{
	if(!gInVirtualPC)
		SyserOpenInterrupt();
}

void CSyser::ResetInputState()
{
	ZeroMemory(m_KeyMap,sizeof(m_KeyMap));
	ZeroMemory(m_LockMap,sizeof(m_LockMap));
	dwWaitMouseInterrupt = 0;
	dwMouseBeginBufferIndex = 0;
	stKeyGlobalVariable.dwMouseDataIndex=0;
	gLButtonDblClkSecond=false;
	gRButtonDblClkSecond=false;
	gMButtonDblClkSecond=false;
	m_RepKeyIndex=WISP_VK_NULL;
	m_RepKeyElapse = 0;
	m_RepKeyPeriod = 0;
}

void CSyser::Active()
{
	if(m_pDebugger==NULL || gbActive || m_RealFrameBuffer.Buffer == NULL)
	{
		if(m_RealFrameBuffer.Buffer==NULL)
		{
			::DbgPrint("************************************************************\n");
			::DbgPrint("Syser : Fail to attach System Video Frame Buffer !\n");
			if(gInVMWARE)
				::DbgPrint("Syser : Please Install VMWare Tools !\n");
			if(gInVirtualPC)
				::DbgPrint("Syser : Please Install or Update Virtual Machine Additions !\n");
			::DbgPrint("************************************************************\n");
		}
		return;
	}
	
	m_pOrgProcess = m_pDebugger;	//保存原始进程
	SyserClrCR0WP();
	SyserDisableHardwaveBreakpoint();
	ActiveHookInt0e(true);
	ClearBPR();
	gpSyser->m_SyserUI.m_SyserDI.ResetTrace();
	gpSyser->m_pDebugger->RemoveAllCodeBP(BP_TYPE_DEBUG);
	m_MainFrame.Update();

	m_pDebugger->UpdateRegister();
	gbActive=true;
	gpSyser->m_SyserUI.m_SyserDI.OnDebugPlunge(0);
	ResetInputState();
	MouseInterruptCount=0;
	stKeyGlobalVariable.dwMouseDataIndex=0;
	m_bExit=false;
	SyserDisableAllHardInterrupt();
	EnableHardWareInterrupt(1);				//允许键盘中断
	EnableLocalAPICInterrupt();
	if(gHasPS2Mouse)
		EnableHardWareInterrupt(0x0C);		//允许鼠标中断
	SetInteruptEOI(1);						//发送硬件中断结束标志
	if(gpSyserCfg->m_SupportTimerInterrupt)
	{
		InstallTimeInterrupt();
		if(gbIsUseAPIC)
			EnableHardWareInterrupt(IOAPIC_TIMER_INTERRUPT_NUM);		//允许时间中断
		else
			EnableHardWareInterrupt(0x08);		//允许时间中断
	}
#if SUPPORT_COM_INTERRUPT
	EnableHardWareInterrupt(0x03);
	EnableHardWareInterrupt(0x04);
#endif
// 	__asm
// 	{
// 		nop 
// 		nop 
// 		push eax 
// 		in al,0x64 
// 		test al,1 
// 		jz local_0098
// 		push eax
// 		in al,0x60
// 		pop eax
// local_0098:
// 		test al,0xe0
// 		jz local_0099
// 		test al,2 
// 		jnz local_0099
// 		mov al,0xff 
// 		out 0x60,al 
// 		nop 
// 		nop 
// local_0099:
// 		pop eax 
// 	}

	BYTE	value = 0;
	value = SyserReadPortByte(0x64);
	if(!(value&1))
	{
		SyserReadPortByte(0x60);
	}

	if (!(value&0xe0))
	{
		if (value&2)
		{
			SyserWritePortByte(0x60,0xff);
		}
	}


	if(gpSyserCfg->m_DisableUSBInput == 0 && gInVMWARE==false && gInVirtualPC==false)			
			m_PCSystem.AttachUSBDevice();
	if(m_bScrBackup)
		BackupScreen();
	
	SyserOpenInterrupt();						//开放中断
	if(gpSyser->m_SysInfo.m_bEvlVer==false && gpSyser->m_SysInfo.m_bSNPass==false)
	{
		OUTPUT(WSTR("%<3>%s\n"),(PCWSTR)m_SysInfo.m_LicTip);
		SYSEXPLR_OUTPUT(WSTR("%<3>%s\n"),(PCWSTR)m_SysInfo.m_LicTip);
	}
	Pump();
	SyserCloseInterrupt();
	if(gpSyserCfg->m_DisableUSBInput == 0 && gInVMWARE==false && gInVirtualPC==false)
			m_PCSystem.DetachUSBDevice();
	if(m_bScrBackup)
	{
		RestoreScreen();
	}
	if(gpSyserCfg->m_SupportTimerInterrupt)
		UninstallTimeInterrupt();
	if(m_pOrgProcess!=gpSyser->m_pDebugger)//恢复原始进程
		gpSyser->MapToProcess(m_pOrgProcess);
	SetBPR();
	ActiveHookInt0e(false);
	EnableHardwaveBreakpoint();
	SyserRestoreCR0();
}

void CSyser::Exit(bool bRestoreScr)
{
	if(gbSystemCrash)
	{
		RUNCMD(WSTR("hboot"));
	}
	m_bScrBackup=bRestoreScr;
	m_bExit=true;
	if(m_bSaveReg)
		PrevReg=Reg;
	gpSyser->m_MainFrame.m_SystemExplorer.m_TracePrevReg=Reg;
	SAVE_MEMORY_VIEW();
}

void CSyser::ClearInputState()
{
	dwMouseBeginBufferIndex = 0;
}

void CSyser::BackupScreen()
{
	int SrcDelta,DesDelta;
	BYTE*pSrc,*pDes,*pDes2;
	WISP_RECT ScrRect;
	if(m_RealFrameBuffer.Buffer == NULL || gpSyserCfg->m_DisableDisplay)
		return;

	ScrRect.x=ScrRect.y=0;
	ScrRect.cx=m_RealFrameBuffer.Width;
	ScrRect.cy=m_RealFrameBuffer.Height;

	m_BackupFrameRect.x = m_RootPos.x;
	m_BackupFrameRect.y = m_RootPos.y;
	m_BackupFrameRect.cx = m_FrameBuffer.Width;
	m_BackupFrameRect.cy = m_FrameBuffer.Height;

	if(ClipRect(&m_BackupFrameRect,&ScrRect)==false)
	{
		m_BackupFrameRect.cx = 0;
		m_BackupFrameRect.cy = 0;
		return;
	}
	pSrc = RT_PBYTE(m_RealFrameBuffer.Buffer,(m_BackupFrameRect.x*m_RealFrameBuffer.Bpp)/8+m_BackupFrameRect.y*m_RealFrameBuffer.LineDistance);
	SrcDelta = m_RealFrameBuffer.LineDistance;
	pDes = m_VideoBufBackup;
	DesDelta = (m_BackupFrameRect.cx*m_RealFrameBuffer.Bpp)/8;
	if(gbVideoBufferOK)
	{
		for(int y=0;y<m_BackupFrameRect.cy;y++)
		{
			gbVideoBufferOK=SafeVideoMemCopy(pDes,pSrc,DesDelta);
			if(gbVideoBufferOK==false)
				break;
			pSrc+=SrcDelta;
			pDes+=DesDelta;
		}
	}	
	if(gbVideoBufferOK==false)
	{
		::DbgPrint("Syser : Video Buffer Read Write Error!\n");
	}
	m_bUserScrBackuped = true;
}

void CSyser::RestoreScreen()
{
	int SrcDelta,DesDelta;
	BYTE*pSrc,*pDes;	
	if(m_RealFrameBuffer.Buffer==NULL || gpSyserCfg->m_DisableDisplay)
		return;
	pDes = RT_PBYTE(m_RealFrameBuffer.Buffer,(m_BackupFrameRect.x*m_RealFrameBuffer.Bpp)/8+m_BackupFrameRect.y*m_RealFrameBuffer.LineDistance);
	DesDelta = m_RealFrameBuffer.LineDistance;
	pSrc = m_VideoBufBackup;
	SrcDelta = (m_BackupFrameRect.cx*m_RealFrameBuffer.Bpp)/8;
	if(gbVideoBufferOK)
	{
		for(int y=0;y<m_BackupFrameRect.cy;y++)
		{
			gbVideoBufferOK=SafeVideoMemCopy(pDes,pSrc,SrcDelta);
			pSrc+=SrcDelta;
			pDes+=DesDelta;
		}
	}
	m_bScrRestored = true;
	if(gInVMWARE)
		FlushVedioBuffer(0,0, m_RealFrameBuffer.Width,m_RealFrameBuffer.Height);
	else if(gInVirtualPC)
		FlushVirtualPCScreenBuffer(0,0,m_RealFrameBuffer.Width,m_RealFrameBuffer.Height);
	m_bUserScrBackuped = false;
}

void CSyser::CenterScreen()
{
	m_RootPos.x = CENTER_ALGN(m_FrameBuffer.Width,m_RealFrameBuffer.Width);
	m_RootPos.y = CENTER_ALGN(m_FrameBuffer.Height,m_RealFrameBuffer.Height);
	MIN_LIMIT(m_RootPos.x,0);
	MIN_LIMIT(m_RootPos.y,0);
}

void CSyser::EndDraw(WISP_RECT*pUpdateRect)
{
	DWORD Width=m_RealFrameBuffer.Width;
	DWORD Height=m_RealFrameBuffer.Height;
	if(gpSyserCfg->m_DisableDisplay || m_RealFrameBuffer.Buffer==NULL)
		return;
	CopyToScreen(&m_RealFrameBuffer,&m_RootPos,pUpdateRect);
	m_bScrRestored = false;

	if(gInVMWARE)
		FlushVedioBuffer(0,0, m_RealFrameBuffer.Width,m_RealFrameBuffer.Height);
	else if(gInVirtualPC)	
		FlushVirtualPCScreenBuffer(0,0,m_RealFrameBuffer.Width,m_RealFrameBuffer.Height);	
}

ULSIZE CSyser::ReadMemory(ULPOS Address,void*Buffer,ULSIZE Size,CSyser*pThis)
{
	return pThis->m_pDebugger->ReadMemory(Address,Buffer,Size);
}

bool CSyser::IntallHardDriver()
{
	InstallAllInterrupt();
	return true;
}

void CSyser::RemoveHardDriver()
{
	UninstallAllInterrupt();
}

bool CSyser::InstallHooks()
{
	PsSetCreateProcessNotifyRoutine(CreateProcessHookProc,false);
	if(m_PsRemoveLoadImageNotifyRoutine)
	{
		PsSetLoadImageNotifyRoutine(LoadImageHookProc);
	}
	else if(gpSysBootDevEx && gpSysBootDevEx->cbSize==sizeof(SYSER_BOOT_DEVICE_EXTENSION))
		gpSysBootDevEx->pfnLoadImageNotifyRoutine = LoadImageHookProc;

	SyserClrCR0WP();
	if(m_SysInfo.m_HidP_TranslateUsageAndPagesToI8042ScanCodes)
		PATCH_SYSTEM("USB Hid Hook",m_SysInfo.m_HidP_TranslateUsageAndPagesToI8042ScanCodes,OnPatchTranslateUsageAndPagesToI8042ScanCodes);
	//if(m_SysInfo.m_MmUnmapViewOfSection)
	//	PATCH_SYSTEM("MmUnmapViewOfSection Hook",m_SysInfo.m_MmUnmapViewOfSection,OnPatchMmUnmapViewOfSection);
	PatchKeBugCheckEx();
	if(gpSyserCfg->m_DisableCopyOnWrite)
		::DbgPrint("Syser : Disable MiCopyOnWrite Patch!\n");
	else
		PatchMiCopyOnWrite();
	SyserRestoreCR0();
	if(gpSyser->m_bPatchCopyOnWrite==false)
		::DbgPrint("Syser : ******* Fail to patch MiCopyOnWrite ******* !\n");
	return true;
}

void CSyser::RemoveHooks()
{
	PsSetCreateProcessNotifyRoutine(CreateProcessHookProc,true);
	if(m_PsRemoveLoadImageNotifyRoutine)
		m_PsRemoveLoadImageNotifyRoutine(LoadImageHookProc);
	else if(gpSysBootDevEx && gpSysBootDevEx->pfnLoadImageNotifyRoutine==LoadImageHookProc)
		gpSysBootDevEx->pfnLoadImageNotifyRoutine = NULL;
}

void CSyser::DbgPrint(int x,int y,IN WCHAR*Format,...)
{
	WISP_RECT Rect;
	va_list Next;
	WCHAR szBuffer[0x200];
	if(m_RealFrameBuffer.Buffer==NULL||gpSyserCfg->m_DisableDisplay)
		return;
	va_start(Next,Format);
	TVSPrintf(szBuffer,Format,Next);
	va_end(Next);
	Rect.x=Rect.y=0;
	Rect.cx=m_RealFrameBuffer.Width;
	Rect.cy=m_RealFrameBuffer.Height;
	CWispDC	ScreenDC(&m_RealFrameBuffer,&Rect);
	ScreenDC.SetTextStyle(WISP_TEXT_OPAQUE);
	ScreenDC.SetTextBKColor(WISP_RGB(0,0,0));
	ScreenDC.SetTextColor(WISP_RGB(255,255,0));
	ScreenDC.DrawString(x,y,szBuffer);
	if(gInVMWARE)
		FlushVedioBuffer(x,y, m_RealFrameBuffer.Width,y+16);
	else if(gInVirtualPC)
		FlushVirtualPCScreenBuffer(x,y,m_RealFrameBuffer.Width,y+16);

}

bool CSyser::PumpCondition()
{
	if(m_bExit)
		return false;
	if(stKeyGlobalVariable.dwFuncKeyState == FUNCKEYPRESS && m_KeyMap[WISP_VK_F12])
	{
		m_bScrBackup=true;
		return false;
	}
	return true;
}

void CSyser::MapToProcess(CDbgProcess*pProcess)
{
	SyserSetCR3Reg(pProcess->m_CR3);
	m_bUpdateReg = true;
	m_pDebugger = pProcess;
}

bool CSyser::InstallDebug()
{
	VADDR32 IDTBaseAddress;
	DWORD dwIdtSize;
	DWORD dwCopySize;
	m_bDbgRegAccessMon = false;
	CheckSofticeExist();
	InitBpintCmdEntryPointer();
	ZeroMemory(gOldInterruptProcAddress,sizeof(gOldInterruptProcAddress));
	ZeroMemory(gOldInterruptDescropterTable,sizeof(gOldInterruptDescropterTable));
	IDTBaseAddress = SyserGetIDTBase(&dwIdtSize);
	dwCopySize = MIN(sizeof(gOldInterruptDescropterTable),(dwIdtSize+1));
	memcpy(gOldInterruptDescropterTable,(const void *)IDTBaseAddress,sizeof(gOldInterruptDescropterTable));
	for(DWORD i = 0;i< dwCopySize / sizeof(X86_GATE_DECR);i++)
	{
		gOldInterruptProcAddress[i]=MAKE_DWORD(gOldInterruptDescropterTable[i].OffsetHigh,gOldInterruptDescropterTable[i].OffsetLow);
	}
	m_bHardDriverSuccess=m_bHookSuccess=false;
	m_bHardDriverSuccess=IntallHardDriver();
	if(m_bHardDriverSuccess==false)
	{
		::DbgPrint("Syser : Fail to IntallHardDriver !\n");
		return false;
	}
	m_bHookSuccess=InstallHooks();
	if(m_bHookSuccess==false)
	{
		RemoveHardDriver();
		::DbgPrint("Syser : InstallHooks Error !\n");
		return false;
	}
	return true;
}

bool CSyser::UninstallDebug()
{
	if(m_bHardDriverSuccess)
		RemoveHardDriver();
	if(m_bHookSuccess)
		RemoveHooks();
	return true;
}

void  CSyser::ReportMsg(IN const WISP_CHAR* Format,...)
{
	WISP_RECT Rect;
	va_list Next;
	WCHAR szBuffer[0x200];
	if(m_RealFrameBuffer.Buffer==NULL)
		return;
	va_start(Next,Format);
	TVSPrintf(szBuffer,Format,Next);
	va_end(Next);
	Rect.x=Rect.y=0;
	Rect.cx=m_RealFrameBuffer.Width;
	Rect.cy=m_RealFrameBuffer.Height;
	CWispDC	ScreenDC(&m_RealFrameBuffer,&Rect);
	ScreenDC.SetTextStyle(WISP_TEXT_OPAQUE);
	ScreenDC.SetTextBKColor(WISP_RGB(0,0,0));
	ScreenDC.SetTextColor(WISP_RGB(255,255,0));
	ScreenDC.DrawString(0,0,szBuffer);
	//SYSEXPLR_OUTPUT(WSTR("%s\n"),szBuffer);
}

/*

///////////////////////////////////////////////////////
//        SwitchIDT
//
// Switch to each logical processor with Hyperthreading
// and retrieve the base address of the relevant IDT
///////////////////////////////////////////////////////


BOOL SwitchIDT () {

///////////////////////////////////////////////////////

struct IDT_INFO
{
unsigned short wReserved;
unsigned short wLimit;		     // size of table
IDT_GATE* pIdt;			// base address of table
};

IDT_INFO IdtInfo = {0};

ULONG lpProcessAffinityMask = 0;
ULONG lpSystemAffinityMask = 0;

///////////////////////////////////////////////////////

// Affinity Info

GetProcessAffinityMask(
GetCurrentProcess(),	// HANDLE hProcess,
&lpProcessAffinityMask,	// OUT PDWORD_PTR lpProcessAffinityMask,
&lpSystemAffinityMask);	// OUT PDWORD_PTR lpSystemAffinityMask

// function obtains lpProcessAffinityMask value from EPROCESS.Affinity
// function obtains lpSystemAffinityMask value from BaseStaticServerData
// both are generally same value of 0x03 (binary mask 11) 
// with Hyperthreading enabled

fprintf (stderr, "ProcessAffinityMask %x \n", lpProcessAffinityMask);
fprintf (stderr, "SystemAffinityMask %x \n", lpSystemAffinityMask);


///////////////////////////////////////////////////////

// Switch current thread to processor 1
SetProcessAffinityMask(
GetCurrentProcess(),	// HANDLE hProcess,
1);			// DWORD_PTR dwProcessAffinityMask

Sleep(0); // Give OS a chance to switch to the desired CPU


// Read IDTR register
__asm sidt IdtInfo.wLimit			

// Output current IDT base address
fprintf (stderr, "CPU1 IDT Base %x \n", IdtInfo.pIdt);


// Switch current thread to processor 2 if HT is enabled
if (lpProcessAffinityMask != 1)
{
SetProcessAffinityMask(
GetCurrentProcess(),	// HANDLE hProcess,
2);		// DWORD_PTR dwProcessAffinityMask

Sleep(0); // Give OS a chance to switch to the desired CPU


// Read IDTR register
__asm sidt IdtInfo.wLimit

// Output current IDT base address
fprintf (stderr, "CPU2 IDT Base %x \n", IdtInfo.pIdt);
}

///////////////////////////////////////////////////////

return TRUE;

}	//

Hi,

First, you need to get the physical address of the APIC by
using the RDMSR instruction to read the IA32_APIC_BASE_MSR value.

After this, you can use the MmMapIoSpace function
to map from this physical address to a virtual one.

The standard physical address for the apic is 0xFEC00000.
You can use "PHYS 0xFEC00000" in SoftICE to get the virtual address.

The address 0xFFDFF120 is the _KPRCB structure.
You can use WinDBG to see the whole structure.
Or use the "types _KPRCB" in SoftICE.

When you are using a MP/HT system, the two _KPRCB addresses
are inside the KiProcessorBlock kernel variable.


Code:

lkd> dd KiProcessorBlock
8054b080  ffdff120 f7acf120 00000000 00000000
8054b090  00000000 00000000 00000000 00000000
8054b0a0  00000000 00000000 00000000 00000000

To get the PCR address of each processor is just simple:
FIRST KPCR address = 0xFFDFF120 - 0x120
SECOND KPCR address = 0xF7ACF120 - 0x120

We can easily find the IDT address inside the KPCR structure.
The problem is that the KiProcessorBlock is not exported  

Regards,
Opc0de


Oops, I'm wrong.  

You can use my little trick at
http://www.rootkit.com/newsread.php?newsid=101
to get the KiProcessorBlock address.

The KiProcessorBlock is exported by the KdVersionBlock structure
as you can see here:
http://www.rootkit.com/newsread.php?newsid=153

Regards,
Opc0de

反编译  http://boomerang.sourceforge.net/
*/
#ifndef __DEMO__VERSION__
PSERIALNAME CSyser::GetSerialNumber()
{
	return gSerialName;
}
bool CSyser::CheckSN(char* SerialNum,char* Name)
{
	return true;
// 	char Buf[9],ch1;
// 	DWORD dwValue1,dwValue2,dwValue3,dwValue4;
// 	int i,j;
// 	char SnName[256];
// 	unsigned __int64 mx,mx1,mx2;
// 	for(i=0;i<8;i++)
// 		Buf[i]=SerialNum[i];
// 	Buf[i]=0;
// 	SHexStrToNum(Buf,&dwValue1);
// 	for(i=0;i<8;i++)
// 		Buf[i]=SerialNum[i+8];
// 	Buf[i]=0;
// 	SHexStrToNum(Buf,&dwValue2);
// 	dwValue3=dwValue1-dwValue2;
// 	dwValue4=dwValue1+dwValue2;
// 	mx1=dwValue3;
// 	mx2=dwValue4;
// 	mx=mx1*mx2;	
// 	GSNMAP::IT FindIT=m_GSnMap.Find(mx);
// 	if(FindIT!=m_GSnMap.End())
// 	{
// 		for(int i=0;i<sizeof(gSerialName)/sizeof(gSerialName[0]);i++)
// 		{
// 			memset(SnName,0,sizeof(SnName));
// 			for(j=0;Name[j];j++)
// 			{
// 				ch1=Name[j];
// 				if(ch1>='A'&&ch1<='Z')
// 					ch1=ch1+('a'-'A');
// 				ch1 = ((ch1^(0x7a+i))+0x2a)&0xff;
// 				SnName[j]=ch1;
// 			}
// 			SnName[j]=0;
// 			if(memcmp((*FindIT).m_pData,SnName,(*FindIT).m_Length)==0)
// 			{
// 				if(mx==0x77753661edc73e5d || mx==0x07d32d3fcdbf572d||mx==0x01497eb46d08b395)
// 					*Type=SN_ENTERPRISE;
// 				else if(mx==0xc15dd19fc39daf05)
// 					*Type=SN_STUDENT;
// 				else
// 					*Type=SN_PERSONAL;
// 				return true;
// 			}
// 		}
// 	}
//	return false;
}

SERIALNAME CSyser::gSerialName[28]={
	{"\x32\x3f\x40\x46\x81\x48\x3d\x49\x38\x49\x32\x84\x3b\x40\x49\x3d\x3e\x00",0x4168ea9dc6497ee0},
		/*0*/	/* "Rolf-Dieter Klein" ^0x7a+0x2a */
	{"\x40\x47\x44\x46\x44\x3f\x65\x40\x3e\x3a\x3e\x3f\x48\x39\x7f\x42\x3e\x40\x00",0x2e7f9176e5e9ed50},
	/*1*/	/* "mfagan@mokonet.com" ^0x7b+0x2a */
	{"\x35\x47\x3a\x32\x43\x38\x86\x45\x2f\x45\x3a\x3f\x00",0x24a8a43bd4887d0},
	/*2*/	/* "Walter Gygli" ^0x7c+0x2a */
	{"\x41\x3c\x3f\x3d\x87\x3a\x48\x48\x46\x3d\x3d\x00",0x581c9ca398ef4820},
	/*3*/	/* "John McCann" ^0x7d+0x2a */
	{"\x37\x3b\x42\x34\x33\x41\x3a\x00",0x15a8386850c14168},
	/*4*/	/* "SOFTWIN" ^0x7e+0x2a */
	{"\x48\x46\x41\x44\x37\x34\x3b\x36\x00",0x289149745b1cf198},
	/*5*/	/* "acheruns" ^0x7f+0x2a */
	{"\x1d\x1e\x0f\x1a\x12\x0b\x18\xca\x1d\x13\x1e\x1e\x0b\x00",0x3d1ea311acedcf50},
	/*6*/	/* "Stephan Sitta" ^0x80+0x2a */
	{"\x14\x12\x16\xcb\x14\x22\x18\x1e\x19\x10\xcb\x13\x18\x00",0xb97a4907f773900},
	/*7*/	/* "kim kyoung ho" ^0x81+0x2a */
	{"\x0b\x0d\x1a\x17\x18\xcc\x22\x11\x25\x16\x17\x21\x16\x00",0x1ee7bc52389c0d78},
	/*8*/	/* "Carol Zeynoun" ^0x82+0x2a */
	{"\x12\x20\x16\xcd\x12\x14\x17\x12\x14\x00",0xb49ea594df126b48},
	/*9*/	/* "kuo kinki" ^0x83+0x2a */
	{"\x18\x10\x0b\x1a\x28\x00",0x467f1c526445e2d0},
	/*10*/	/* "jbetz" ^0x84+0x2a */
	{"\x0e\x13\x0a\x15\x1c\x00",0xbfae82b7a343038},
	/*11*/	/* "alenw" ^0x85+0x2a */
	{"\x15\x1d\x1c\x1f\x1d\x15\x19\xd0\x13\x0b\x11\x1b\x11\x00",0x127f900f6857ef10},
	/*12*/	/* "Mutsumi Ogawa" ^0x86+0x2a */
	{"\x14\x18\x16\x0c\x0d\xd2\x1e\x18\x0a\x13\x10\x1d\x0c\x0e\x00",0xdf8be9c049491b8},
	/*13*/	/* "MikeD/Signatec" ^0x87+0x2a */
	{"\x0d\x27\x10\x0b\x0d\x13\x1c\x27\xd2\x26\x13\x16\x13\x00",0x1dc9b0378c41c178},
	/*14*/	/* "kunikazu tada" ^0x88+0x2a */
	{"\x0f\x0a\x15\x16\x25\x10\x00",0x254d88b3358274d0},
	/*15*/	/* "libero" ^0x89+0x2a */
	{"\x23\x15\x23\x28\x22\x1d\xd4\x0b\x0f\x11\x24\x19\x10\x10\x15\x00",0x7c308545acf1b18},
	/*16*/	/* "Sastry Kompella" ^0x8a+0x2a */
	{"\x0a\x0c\x10\xd5\x23\x0e\x13\x18\x23\x22\x0e\x0f\x00",0x1058a01846617cb8},
	/*17*/	/* "Kim Roberson" ^0x8b+0x2a */
	{"\x19\x0e\x28\x0f\x29\x22\x0f\x17\x0c\xd6\x0e\x0d\x14\x14\x0b\x17\x0c\x0c\x00",0x15e6528b84dc7808},
	/*18*/	/* "Christian Hoffmann" ^0x8c+0x2a */
	{"\x19\x29\x0e\x16\x0d\xd7\x18\x16\x27\x12\x0b\x0b\x16\x29\x0c\x00",0xb3ee0572cb780ec0},
	/*19*/	/* "brian capellaro" ^0x8d+0x2a */
	{"\x0a\x27\x26\x11\x00",0x24c1669d1c52b0a0},
	/*20*/	/* "NSRI" ^0x8e+0x2a */
	{"\x0b\x0a\x23\x14\x16\xd9\x24\x26\x14\x27\x00",0x1be17f1a0793bca0},
	/*21*/	/* "NOVEC User" ^0x8f+0x2a */
	{"\x1b\x26\x1b\x1e\x1e\x23\x28\xda\x1f\x0f\x0c\x29\x0a\x1f\xda\x21\x27\x1c\x22\x00",0x27f1ee3d581395a0},
	/*22*/	/* "Aladdin Europe GmbH" ^0x90+0x2a */
	{"\x22\x29\x0f\x1e\x0d\x1f\x22\x20\x22\x0f\x1a\x27\x00",0x16a2124a67be6bc8},
	/*23*/	/* "InterDigital" ^0x91+0x2a */
	{"\x28\x1d\x0a\x0a\x15\xdc\x28\x1d\x14\x20\x1d\x28\x00",0xc15dd19fc39daf05},
	/*24*/	/* "Larry Laxdal" ^0x92+0x2a */
	{"\x7c\xa5\x7b\xa2\x6d\x80\x86\x5b\x59\x59\x83\x90\x00",0x01497eb46d08b395},
	/*25*/	/* "凌码信息技术" ^0x93+0x2a */
	{"\x11\x1f\x27\x21\x00",0x07d32d3fcdbf572d},
	/*26*/	/* "SAIC" ^0x94+0x2a */
	{"\x1a\x28\x1e\x27\x1e\x0a\xdf\x24\x16\x00",0x77753661edc73e5d},
	/*27*/	/* "Ekahau Oy" ^0x95+0x2a */
};

#endif

void CSyser::InitHotKeyInfo()
{
	DWORD *Buffer=LoadCFGHotKey();
	if(Buffer==NULL)
		return;
	DWORD* OrgBuffer,i,j,k;
	CMDHOTKEYMAP::IT BeginIT;
	KEY_PAIR KeyPair;
	OrgBuffer=Buffer;
	Buffer++;//skip crc	
	Buffer++;//skip total number
	for(i=0;i<OrgBuffer[1];i++)
	{

		BeginIT = m_CmdHotKeyMap.InsertUnique(*Buffer++,HOTKEYLIST());
		if(BeginIT!=m_CmdHotKeyMap.End())
		{
			k=*Buffer++;
			for(j=0;j<k;j++)
			{
				KeyPair.FuncKeyCode=*Buffer++;
				KeyPair.SecondKeyCode=*Buffer++;
				(*BeginIT).Append(KeyPair);				
			}
		}
		else
			break;
	}
	
	delete []OrgBuffer;
	HOTKEYLIST::IT HotKeyIT;
	BeginIT=m_CmdHotKeyMap.Find(0);
	if(BeginIT!=m_CmdHotKeyMap.End())
	{
		HotKeyIT=BeginIT->Begin();
		for(;HotKeyIT!=BeginIT->End();HotKeyIT++)
		{
			SetActiveHotKey(HotKeyIT->FuncKeyCode,HotKeyIT->SecondKeyCode);
		}
	}
}

void CSyser::SetActiveHotKey(DWORD FuncKeyCode,DWORD SecondKeyCode)
{	
	if(FuncKeyCode & WISP_MOD_CTRL)
	{
		FuncKeyCode= GetScanCode(WISP_VK_CONTROL);
	}
	else if(FuncKeyCode & WISP_MOD_ALT)
	{
		FuncKeyCode= GetScanCode(WISP_VK_ALT);
	}
	else if(FuncKeyCode & WISP_MOD_SHIFT)
	{
		FuncKeyCode= GetScanCode(WISP_VK_SHIFT);
	}
	SecondKeyCode = GetScanCode(SecondKeyCode);
	stKeyGlobalVariable.chFuncKeyScanCode=(BYTE)FuncKeyCode;
	stKeyGlobalVariable.chSecondKeyScanCode=(BYTE)SecondKeyCode;
}
void CSyser::AttachPopupProcess(DWORD dwCR3)
{
	DWORD dwCurThread,dwCurProcess;
	SYSER_THREAD pThread;
	SYSER_PROCESS pProcess;
	ActiveHookInt0e(true);
	GetCurrentProcessAndThread(&m_PopupProcess,&m_PopupThread);
	if(GetThreadInfoByETHREAD((DWORD)m_PopupThread,&pThread))
	{
		m_PopupThreadID=pThread.ThreadID;
		if(GetProcessInfoByEPROCESS(pThread.Process,&pProcess))
			m_PopupProcessID=pProcess.UniqueProcessId;
	}
	m_pDebugger=m_SysInfo.GetProcessByCR3(dwCR3);
	if(gpSyser->m_pDebugger==NULL)
	{
		OUTPUT(WSTR("%<3>Syser : not match process CR3=%08x\n"),dwCR3);
		m_pDebugger=m_pSysDebugger;
	}
	MapToProcess(m_pDebugger);
	m_pOrgProcess=m_pDebugger;	
	m_SyserUI.m_CodeDoc.UpdatePID_TID(m_PopupProcessID,m_PopupThreadID);
	ActiveHookInt0e(false);
}
void	CSyser::AttachHotKey(DWORD dwCmdID,CWispWnd* pWnd)
{	
	CMDHOTKEYMAP::IT FindIT;
	HOTKEYLIST::IT BeginIT;
	if(dwCmdID==0)
		return;
	FindIT=m_CmdHotKeyMap.Find(dwCmdID);
	if(FindIT!=m_CmdHotKeyMap.End())
	{
		BeginIT=FindIT->Begin();
		for(;BeginIT!=FindIT->End();BeginIT++)
		{
			if(BeginIT->SecondKeyCode)
			{			
				pWnd->RegisterHotKey(dwCmdID,BeginIT->SecondKeyCode,BeginIT->FuncKeyCode);
			}
			else
			{				
				pWnd->RegisterHotKey(dwCmdID,BeginIT->FuncKeyCode,0);
			}
		}
	}	
}


DWORD CSyser::AttachShortcutKey(DWORD dwCmdID,TMap<UINT,UINT> & pMap)
{	
	CMDHOTKEYMAP::IT FindIT;
	HOTKEYLIST::IT BeginIT;
	if(dwCmdID==0)
		return 0;
	FindIT=m_CmdHotKeyMap.Find(dwCmdID);
	if(FindIT!=m_CmdHotKeyMap.End())
	{
		BeginIT=FindIT->Begin();
		for(;BeginIT!=FindIT->End();BeginIT++)
		{
			pMap.InsertUnique(BeginIT->SecondKeyCode|BeginIT->FuncKeyCode,dwCmdID);
		}
		return FindIT->Count();
	}	
	return 0;
}
bool CSyser::InitOSHwndRoot()
{
	static bool bInit=false;
	BOOL bOK;
	DWORD dwHwndAddr,dwHwndAddr2;	
	SYSER_PROCESS Process;
	SYSER_THREAD Thread;
	CDbgProcess*pDbgProcess;
	if(bInit)
		return m_OSHwndRoot!=0;
	bInit=true;
	if(GetProcessByName("syserapp", &Process))
	{		
		pDbgProcess=gpSyser->m_SysInfo.GetProcess(WSTR("syserapp"));
		if(pDbgProcess==NULL)
			return false;
		gpSyser->MapToProcess(pDbgProcess);
		bOK = GetThreadInfoByETHREAD((DWORD)Process.ThreadHead,&Thread);
		while(bOK)
		{
			if(Thread.Teb)
			{
				dwHwndAddr2=0;
				dwHwndAddr=Thread.Teb+gOSOffsetInfo->TEB_Win32ClientInfo_OFFSET+sizeof(DWORD)*6;				
				if(ReadDword((void**)dwHwndAddr,&dwHwndAddr2))
				{
					if(dwHwndAddr2)
					{
						dwHwndAddr2+=gOSOffsetInfo->WIN32CLIENT_hwnd_OFFSET;
						dwHwndAddr=0;
						if(ReadDword((void**)dwHwndAddr2,&dwHwndAddr))
						{
							if(dwHwndAddr)
							{
								m_OSHwndRoot=dwHwndAddr;						
								return true;
							}						
						}
					}
					
				}						
			}
			bOK=GetNextThread(&Thread);
			dwHwndAddr=0;
		}
	}
	if(GetProcessByName("explorer", &Process))
	{
		pDbgProcess=gpSyser->m_SysInfo.GetProcess(WSTR("explorer"));
		if(pDbgProcess==NULL)
			return false;
		gpSyser->MapToProcess(pDbgProcess);
		bOK = GetThreadInfoByETHREAD((DWORD)Process.ThreadHead,&Thread);
		while(bOK)
		{
			if(Thread.Teb)
			{
				dwHwndAddr2=0;
				dwHwndAddr=Thread.Teb+gOSOffsetInfo->TEB_Win32ClientInfo_OFFSET+sizeof(DWORD)*6;				
				if(ReadDword((void**)dwHwndAddr,&dwHwndAddr2))
				{
					if(dwHwndAddr2)
					{
						dwHwndAddr2+=gOSOffsetInfo->WIN32CLIENT_hwnd_OFFSET;
						dwHwndAddr=0;
						if(ReadDword((void**)dwHwndAddr2,&dwHwndAddr))
						{
							if(dwHwndAddr)
							{
								m_OSHwndRoot=dwHwndAddr;						
								return true;
							}						
						}
					}

				}						
			}
			bOK=GetNextThread(&Thread);
			dwHwndAddr=0;
		}
	}
	if(GetProcessByName("csrss", &Process))
	{
		pDbgProcess=gpSyser->m_SysInfo.GetProcess(WSTR("csrss"));
		if(pDbgProcess==NULL)
			return false;
		gpSyser->MapToProcess(pDbgProcess);
		bOK = GetThreadInfoByETHREAD((DWORD)Process.ThreadHead,&Thread);
		while(bOK)
		{
			if(Thread.Teb)
			{
				dwHwndAddr2=0;
				dwHwndAddr=Thread.Teb+gOSOffsetInfo->TEB_Win32ClientInfo_OFFSET+sizeof(DWORD)*6;				
				if(ReadDword((void**)dwHwndAddr,&dwHwndAddr2))
				{
					if(dwHwndAddr2)
					{
						dwHwndAddr2+=gOSOffsetInfo->WIN32CLIENT_hwnd_OFFSET;
						dwHwndAddr=0;
						if(ReadDword((void**)dwHwndAddr2,&dwHwndAddr))
						{
							if(dwHwndAddr)
							{
								m_OSHwndRoot=dwHwndAddr;						
								return true;
							}						
						}
					}

				}						
			}
			bOK=GetNextThread(&Thread);
			dwHwndAddr=0;
		}
	}
	return false;
}

void CSyser::ClearBPR()
{
	PROC_RANGE_BP_MAP::IT BeginIT,EndIT;
	BP_RANGE_LIST::IT ListBIT,ListEIT;
	DWORD count=0;
	DWORD dwValue;
	if(!gpSyser->m_RangeBPList.Count())
	{
		return;
	}
	BeginIT = gpSyser->m_RangeBPList.Begin();
	EndIT = gpSyser->m_RangeBPList.End();
	for(;BeginIT!=EndIT;BeginIT++)
	{
		CDbgProcess* pDbgProcess = gpSyser->m_SysInfo.GetProcessByEPROCESS(BeginIT.Key());
		if(pDbgProcess==NULL)
		{			
			continue;
		}

		gpSyser->MapToProcess(pDbgProcess);

		ListBIT = BeginIT->Begin();
		ListEIT = BeginIT->End();
		for(;ListBIT!=ListEIT;ListBIT++)
		{
			DWORD PageSize,PTESize;
			DWORD PtePtr;
			DWORD TotalSize,StartAddr,EndAddr;
			TotalSize=ListBIT->RangeLength;
			StartAddr=ListBIT->RangeStartAddress;
			EndAddr = StartAddr+ListBIT->RangeLength-1;
			for(;StartAddr<EndAddr;)
			{
				PtePtr = (DWORD)GetPTE(StartAddr,&PageSize,&PTESize,false);
				if(!PtePtr)
				{
					PageSize=0x1000;
					StartAddr &= (~(PageSize-1));
					StartAddr+=PageSize;	
					OUTPUT(WSTR("ClearBPR SKIP page\n"));
					continue;
				}
				StartAddr &= (~(PageSize-1));
				StartAddr+=PageSize;
				if(ReadDword((void*)PtePtr,&dwValue))
				{
					//if(!(dwValue & 1))
					{
						if(WriteDword((void*)PtePtr,(dwValue|1)))
						{
							ListBIT->Type |= BP_REV_BPR_TYPE;
							dwValue = (DWORD)PtePtr;	
							count++;
// 							__asm
// 							{
// 								invlpg dwValue
// 								push eax 
// 								mov eax, cr3 
// 								mov cr3, eax 
// 								pop eax
// 							}

							SyserFlushInsCache((BYTE*)PtePtr);
						}
					}
				}
				//else
				//{
				//	OUTPUT(WSTR("ClearBPR read ptr error\n"));
				//}
			}				
		}		
	}
	//if(count==0)
	//{
	//	OUTPUT(WSTR("NOT CLEAR BPR. THIS IS A ERROR\n"));
	//}
}
void CSyser::ClearProcessBPR(DWORD dwProcess)
{
	PROC_RANGE_BP_MAP::IT BeginIT,EndIT;
	BP_RANGE_LIST::IT ListBIT,ListEIT;
	DWORD dwValue;
	if(!gpSyser->m_RangeBPList.Count())
		return;
	
	BeginIT = gpSyser->m_RangeBPList.Find(dwProcess);
	EndIT = gpSyser->m_RangeBPList.End();
	if(BeginIT==EndIT)
		return;
	CDbgProcess* pDbgProcess = gpSyser->m_SysInfo.GetProcessByEPROCESS(BeginIT.Key());
	if(pDbgProcess==NULL)
		return;

	gpSyser->MapToProcess(pDbgProcess);
	if(pDbgProcess)
	{
		ListBIT = BeginIT->Begin();
		ListEIT = BeginIT->End();
		for(;ListBIT!=ListEIT;ListBIT++)
		{
			DWORD PageSize,PTESize;
			DWORD PtePtr;
			DWORD TotalSize,StartAddr,EndAddr;
			TotalSize=ListBIT->RangeLength;
			StartAddr=ListBIT->RangeStartAddress;
			EndAddr = StartAddr+ListBIT->RangeLength-1;
			for(;StartAddr<EndAddr;)
			{
				PtePtr = (DWORD)GetPTE(StartAddr,&PageSize,&PTESize,false);
				if(!PtePtr)
				{
					PageSize=0x1000;
					StartAddr &= (~(PageSize-1));
					StartAddr+=PageSize;						
					continue;
				}
				StartAddr &= (~(PageSize-1));
				StartAddr+=PageSize;
				if(ReadDword((void*)PtePtr,&dwValue))
				{
					//if((dwValue & 0))
					{
						if(WriteDword((void*)PtePtr,(dwValue|1)))
						{
							ListBIT->Type |= BP_REV_BPR_TYPE;
							dwValue = (DWORD)PtePtr;								
// 							__asm
// 							{
// 								invlpg dwValue
// 								push eax 
// 								mov eax, cr3 
// 								mov cr3, eax 
// 								pop eax
// 							}

							SyserFlushInsCache((BYTE*)PtePtr);
						}
					}
				}
			}					
		}
	}	
	gpSyser->m_RangeBPList.Remove(dwProcess);
}
void CSyser::SetBPR()
{
	PROC_RANGE_BP_MAP::IT BeginIT,EndIT;
	BP_RANGE_LIST::IT ListBIT,ListEIT;
	DWORD dwValue;
	static int count=0;
	if(!gpSyser->m_RangeBPList.Count())
		return;
	BeginIT = gpSyser->m_RangeBPList.Begin();
	EndIT = gpSyser->m_RangeBPList.End();
	for(;BeginIT!=EndIT;BeginIT++)
	{
		CDbgProcess* pDbgProcess = gpSyser->m_SysInfo.GetProcessByEPROCESS(BeginIT.Key());
		if(pDbgProcess)
		{
			gpSyser->MapToProcess(pDbgProcess);
			
			if(pDbgProcess)
			{
				ListBIT = BeginIT->Begin();
				ListEIT = BeginIT->End();
				for(;ListBIT!=ListEIT;ListBIT++)
				{
					if(ListBIT->State != BP_STATE_ENABLE)
						continue;
					DWORD PageSize,PTESize;
					DWORD PtePtr;
					DWORD TotalSize,StartAddr,EndAddr;
					TotalSize=ListBIT->RangeLength;
					StartAddr=ListBIT->RangeStartAddress;
					EndAddr = StartAddr+ListBIT->RangeLength-1;
					for(;StartAddr<EndAddr;)
					{
						PtePtr = (DWORD)GetPTE(StartAddr,&PageSize,&PTESize);
						if(!PtePtr)
						{
							PageSize=0x1000;
							StartAddr &= (~(PageSize-1));
							StartAddr+=PageSize;						
							continue;
						}
						StartAddr &= (~(PageSize-1));
						StartAddr+=PageSize;
						if(ReadDword((void*)PtePtr,&dwValue)==false)
							continue;
						if((dwValue & 1)==0)
							continue;
						if(WriteDword((void*)PtePtr,(dwValue&0xfffffffe))==false)
							continue;
						ListBIT->Type |= BP_SET_BPR_TYPE;
						dwValue = (DWORD)PtePtr;	
						
						//gpSyser->DbgPrint(0,0,WSTR("[%d]setbpr pte=[%08x] eip=%08x \n"),count++,PtePtr,Reg.EIP);
//						__asm
// 						{
// 							invlpg dwValue
// 							push eax 
// 							mov eax, cr3 
// 							mov cr3, eax 
// 							pop eax
// 						}

						SyserFlushInsCache((BYTE*)PtePtr);
					}					
				}
			}
		}		
	}
}

