#include "StdAfx.h"
#include "syser.h"
#include "HwndCmd.h"
#include "OSProcessThread.h"
#include "OSData.h"

CWndHwnd::CWndHwnd(void* WindowHwndPtr)
{
	memset(&m_HwndInfo,0,sizeof(m_HwndInfo));
}
DWORD CWndHwnd::GetNextWindowCaption(WCHAR* Caption,DWORD CaptionLen)
{
	return 0;
}
DWORD CWndHwnd::GetPrevWindowCaption(WCHAR* Caption,DWORD CaptionLen)
{
	return 0;
}
DWORD CWndHwnd::GetParentWindowCaption(WCHAR* Caption,DWORD CaptionLen)
{
	return 0;
}
DWORD CWndHwnd::GetFirstChildWindowCaption(WCHAR* Caption,DWORD CaptionLen)
{
	return 0;
}
DWORD CWndHwnd::GetOwnerWindowCaption(WCHAR* Caption,DWORD CaptionLen)
{
	return 0;
}
DWORD CWndHwnd::GetClassName(WCHAR* Caption,DWORD CaptionLen)
{
	return 0;
}

WND_STYLE_INFO gOSPredefineColor[]=
{
{1,	WSTR("COLOR_SCROLLBAR" )               },        
{2,	WSTR("COLOR_BACKGROUND" )              },
{3,	WSTR("COLOR_ACTIVECAPTION" )           },
{4,	WSTR("COLOR_INACTIVECAPTION")          },
{5,	WSTR("COLOR_MENU")              },
{6,	WSTR("COLOR_WINDOW")            },
{7,	WSTR("COLOR_WINDOWFRAME")       },
{8,	WSTR("COLOR_MENUTEXT")          },
{9,	WSTR("COLOR_WINDOWTEXT")        },
{10,WSTR("COLOR_CAPTIONTEXT")   },    
{11,	WSTR("COLOR_ACTIVEBORDER")  },    
{12,	WSTR("COLOR_INACTIVEBORDER")},    
{13,	WSTR("COLOR_APPWORKSPACE")   },   
{14,	WSTR("COLOR_HIGHLIGHT")      },   
{15,	WSTR("COLOR_HIGHLIGHTTEXT")  },   
{16,	WSTR("COLOR_BTNFACE")        },   
{17,	WSTR("COLOR_BTNSHADOW")          },
{18,	WSTR("COLOR_GRAYTEXT")		   },
{19,	WSTR("COLOR_BTNTEXT")			   },
{20,	WSTR("COLOR_INACTIVECAPTIONTEXT")}, 
{21,	WSTR("COLOR_BTNHIGHLIGHT")      },
{22,	WSTR("COLOR_3DDKSHADOW")		  },
{23,	WSTR("COLOR_3DLIGHT")           },
{24,	WSTR("COLOR_INFOTEXT")          },
{26,	WSTR("COLOR_INFOBK")                  },
{27,	WSTR("COLOR_HOTLIGHT")				},
{28,	WSTR("COLOR_GRADIENTACTIVECAPTION")	},
{29,	WSTR("COLOR_GRADIENTINACTIVECAPTION") },
{30,	WSTR("COLOR_MENUHILIGHT")      },
{31,	WSTR("COLOR_MENUBAR")			 },
};
WND_STYLE_INFO gOSClassStyle[]={
{0x0001,WSTR("CS_VREDRAW")},          
{0x0002,WSTR("CS_HREDRAW")},          
{0x0008,WSTR("CS_DBLCLKS")},          
{0x0020,WSTR("CS_OWNDC")},            
{0x0040,WSTR("CS_CLASSDC")},          
{0x0080,WSTR("CS_PARENTDC")},         
{0x0200,WSTR("CS_NOCLOSE")},          
{0x0800,WSTR("CS_SAVEBITS")},         
{0x1000,WSTR("CS_BYTEALIGNCLIENT")},  
{0x2000,WSTR("CS_BYTEALIGNWINDOW")},  
{0x4000,WSTR("CS_GLOBALCLASS")},      
{0x00010000,WSTR("CS_IME")},              
{0x00020000,WSTR("CS_DROPSHADOW")},       
};

WND_STYLE_INFO gOSPredefineCursor[]=
{
	{0x10011,WSTR("IDC_ARROW")},      
	{0x10013,WSTR("IDC_IBEAM")},      
	{0x10015,WSTR("IDC_WAIT")},       
	{0x10017,WSTR("IDC_CROSS")},      
	{0x10019,WSTR("IDC_UPARROW")},    
	{0x1001b,WSTR("IDC_SIZENWSE")},   
	{0x1001d,WSTR("IDC_SIZENESW")},   
	{0x1001f,WSTR("IDC_SIZEWE")},     
	{0x10021,WSTR("IDC_SIZENS")},     
	{0x10023,WSTR("IDC_SIZEALL")},    
	{0x10025,WSTR("IDC_NO")},              
	{0x10027,WSTR("IDC_APPSTARTING")},
	{0x10029,WSTR("IDC_HELP")},  
	{0x1002d,WSTR("IDC_HAND")},  
};

WND_STYLE_INFO gWndStyleExInfo[]=
{
	{0x08000000L,WSTR("WS_EX_NOACTIVATE")},
	{0x02000000L,WSTR("WS_EX_COMPOSITED")},
	{0x00400000L,WSTR("WS_EX_LAYOUTRTL")},
	{0x00100000L,WSTR("WS_EX_NOINHERITLAYOUT")},
	{0x00080000L,WSTR("WS_EX_LAYERED")},
	{0x00040000L,WSTR("WS_EX_APPWINDOW")},
	{0x00020000L,WSTR("WS_EX_STATICEDGE")},
	{0x00010000L,WSTR("WS_EX_CONTROLPARENT")},
	//{0x00004000L,WSTR("WS_EX_LEFTSCROLLBAR")},
	//{0x00002000L,WSTR("WS_EX_RTLREADING")},
	//{0x00001000L,WSTR("WS_EX_RIGHT")},
	{0x00000400L,WSTR("WS_EX_CONTEXTHELP")},
	{0x00000200L,WSTR("WS_EX_CLIENTEDGE")},
	{0x00000100L,WSTR("WS_EX_WINDOWEDGE")},
	{0x00000080L,WSTR("WS_EX_TOOLWINDOW")},
	{0x00000040L,WSTR("WS_EX_MDICHILD")},
	{0x00000020L,WSTR("WS_EX_TRANSPARENT")},	
	{0x00000010L,WSTR("WS_EX_ACCEPTFILES")},	
	{0x00000008L,WSTR("WS_EX_TOPMOST")},	
	{0x00000004L,WSTR("WS_EX_NOPARENTNOTIFY")},	
	{0x00000001L,WSTR("WS_EX_DLGMODALFRAME")},	
};

WCHAR* StyleExToString(DWORD Value,WCHAR* Buffer,DWORD BufferLen)
{
	WCHAR ValueString[11];
	Buffer[0]=0;
	if((Value & WS_EX_OVERLAPPEDWINDOW)==WS_EX_OVERLAPPEDWINDOW)
	{
		TStrCat(Buffer,"WS_EX_OVERLAPPEDWINDOW");
		Value &= (~WS_EX_OVERLAPPEDWINDOW);
	}
	else if((Value &WS_EX_PALETTEWINDOW)==WS_EX_PALETTEWINDOW)
	{
		TStrCat(Buffer,"WS_EX_PALETTEWINDOW");
		Value &= (~WS_EX_PALETTEWINDOW);
	}
		
	for(int i =0;i<sizeof(gWndStyleExInfo)/sizeof(gWndStyleExInfo[0]);i++)
	{
		if(Value & gWndStyleExInfo[i].Value)
		{
			if(Buffer[0])
				TStrCat(Buffer," | ");
			TStrCat(Buffer,gWndStyleExInfo[i].Name);
			Value&=~(gWndStyleExInfo[i].Value);
		}
	}
	
	if(Buffer[0])
		TStrCat(Buffer," | ");
	TStrCat(Buffer,Value&WS_EX_LEFTSCROLLBAR?"WS_EX_LEFTSCROLLBAR":"WS_EX_RIGHTSCROLLBAR");
	if(Buffer[0])
		TStrCat(Buffer," | ");
	TStrCat(Buffer,Value&WS_EX_RTLREADING?"WS_EX_RTLREADING":"WS_EX_LTRREADING");	
	if(Buffer[0])
		TStrCat(Buffer," | ");
	TStrCat(Buffer,Value&WS_EX_RIGHT?"WS_EX_RIGHT":"WS_EX_LEFT");
	Value&= ~(WS_EX_LEFTSCROLLBAR|WS_EX_RTLREADING|WS_EX_RIGHT);
	if(Value)
	{
		if(Buffer[0])
			TStrCat(Buffer," | ");
		TSPrintf(ValueString,WSTR("0x%08x"),Value);
		TStrCat(Buffer,ValueString);
	}
	return Buffer;
}

WND_STYLE_INFO gWndStyleInfo[]=
{
	{0x80000000L,WSTR("WS_POPUP")},
	{0x40000000L,WSTR("WS_CHILD")},
	{0x20000000L,WSTR("WS_MINIMIZE")},
	{0x10000000L,WSTR("WS_VISIBLE")},
	{0x08000000L,WSTR("WS_DISABLED")},
	{0x04000000L,WSTR("WS_CLIPSIBLINGS")},
	{0x02000000L,WSTR("WS_CLIPCHILDREN")},
	{0x01000000L,WSTR("WS_MAXIMIZE")},
	//{0x00C00000L,WSTR("WS_CAPTION")},
	{0x00800000L,WSTR("WS_BORDER")},
	{0x00400000L,WSTR("WS_DLGFRAME")},
	{0x00200000L,WSTR("WS_VSCROLL")},
	{0x00100000L,WSTR("WS_HSCROLL")},
	{0x00080000L,WSTR("WS_SYSMENU")},
	{0x00040000L,WSTR("WS_THICKFRAME")},
	{0x00020000L,WSTR("WS_GROUP")},
	{0x00100000L,WSTR("WS_TABSTOP")},
	{0x00100000L,WSTR("WS_HSCROLL")},	
};

WCHAR* StyleToString(DWORD Value,WCHAR* Buffer,DWORD BufferLen)
{
	WCHAR ValueString[11];
	Buffer[0]=0;
	if((Value & WS_OVERLAPPEDWINDOW)==WS_OVERLAPPEDWINDOW)
	{
		TStrCat(Buffer,"WS_OVERLAPPEDWINDOW");
		Value &= (~WS_OVERLAPPEDWINDOW);
	}
	else if((Value &WS_POPUPWINDOW)==WS_POPUPWINDOW)
	{
		TStrCat(Buffer,"WS_POPUPWINDOW");
		Value &= (~WS_POPUPWINDOW);
	}
	else if(Value & WS_CHILDWINDOW)
	{
		TStrCat(Buffer,"WS_CHILDWINDOW");
		Value &= (~WS_CHILDWINDOW);
	} if(Value==WS_OVERLAPPED)
		TStrCat(Buffer,"WS_OVERLAPPED");
	if((Value&WS_CAPTION)==WS_CAPTION)
	{
		if(Buffer[0])
			TStrCat(Buffer," | ");
		TStrCat(Buffer,"WS_CAPTION");
		Value &= (~WS_CAPTION);
	}
	for(int i =0;i<sizeof(gWndStyleInfo)/sizeof(gWndStyleInfo[0]);i++)
	{
		if(Value & gWndStyleInfo[i].Value)
		{
			if(Buffer[0])
				TStrCat(Buffer," | ");
			TStrCat(Buffer,gWndStyleInfo[i].Name);
			Value&=~(gWndStyleInfo[i].Value);
		}
	}
	if(Value)
	{
		if(Buffer[0])
			TStrCat(Buffer," | ");
		TSPrintf(ValueString,WSTR("0x%08x"),Value);
		TStrCat(Buffer,ValueString);
	}
	return Buffer;
}

bool GetHwndInfoByWndStructForXP(void* OsWindowPtr,PSYSER_HWND_INFO SyserHwndInfo)
{
	SYSER_HWND_INFO HwndInfo;
	if(OsWindowPtr==NULL || SyserHwndInfo==NULL)
		return false;
	memset(SyserHwndInfo,0,sizeof(*SyserHwndInfo));
	if(SyserPrivateMemCopy((BYTE*)&HwndInfo,(BYTE*)OsWindowPtr,sizeof(HwndInfo))!=sizeof(HwndInfo))
		return false;
	memcpy(SyserHwndInfo,&HwndInfo,sizeof(HwndInfo));
	return true;

}

bool GetHwndInfoByWndStructFor2K(void* OsWindowPtr,PSYSER_HWND_INFO SyserHwndInfo)
{
	SYSER_HWND_INFO HwndInfo;
	if(OsWindowPtr==NULL || SyserHwndInfo==NULL)
		return false;
	memset(SyserHwndInfo,0,sizeof(*SyserHwndInfo));
	if(SyserPrivateMemCopy((BYTE*)&HwndInfo,(BYTE*)OsWindowPtr,sizeof(HwndInfo))!=sizeof(HwndInfo))
		return false;
	memcpy(SyserHwndInfo,&HwndInfo,0x30);
	memcpy(&SyserHwndInfo->ParentHwnd,&HwndInfo.PreviousHwnd,0x68);
	return true;

}

bool GetHwndInfoByWndStructForVista(void* OsWindowPtr,PSYSER_HWND_INFO SyserHwndInfo)
{
	SYSER_HWND_INFO HwndInfo;
	if(OsWindowPtr==NULL || SyserHwndInfo==NULL)
		return false;
	memset(SyserHwndInfo,0,sizeof(*SyserHwndInfo));
	if(SyserPrivateMemCopy((BYTE*)&HwndInfo,(BYTE*)OsWindowPtr,sizeof(HwndInfo))!=sizeof(HwndInfo))
		return false;
	memcpy(SyserHwndInfo,&HwndInfo,0x7c);
	memcpy(&SyserHwndInfo->Unknow5,&HwndInfo.WindowCaptionLen,0x20);
	return true;

}


bool GetClassInfoByHwndInfoForXP_Vista(PSYSER_HWND_INFO SyserHwndInfo,PSYSER_HWND_CLASS_INFO SyserHwndClassInfo)
{
	SYSER_HWND_CLASS_INFO ClassInfo;
	memset(&ClassInfo,0,sizeof(ClassInfo));
	if(SyserPrivateMemCopy((BYTE*)&ClassInfo,(BYTE*)SyserHwndInfo->ClassInfo,sizeof(ClassInfo))!=sizeof(ClassInfo))
		return false;
	memcpy(SyserHwndClassInfo,&ClassInfo,sizeof(ClassInfo));
	return true;
}
bool GetClassInfoByHwndInfoFor2K(PSYSER_HWND_INFO SyserHwndInfo,PSYSER_HWND_CLASS_INFO SyserHwndClassInfo)
{
	SYSER_HWND_CLASS_INFO ClassInfo;
	memset(&ClassInfo,0,sizeof(ClassInfo));
	if(SyserPrivateMemCopy((BYTE*)&ClassInfo,(BYTE*)SyserHwndInfo->ClassInfo,sizeof(ClassInfo))!=sizeof(ClassInfo))
		return false;
	memcpy(SyserHwndClassInfo,&ClassInfo,8);
	memcpy(SyserHwndClassInfo->Unknow2,&ClassInfo.Unknow1,sizeof(ClassInfo)-8);
	OUTPUT(WSTR("GetClassInfoByHwndInfoFor2K  %08x\n"),SyserHwndClassInfo->lpszClassName);
	return true;
}
bool GetClassInfoByHwndInfo(PSYSER_HWND_INFO SyserHwndInfo,PSYSER_HWND_CLASS_INFO SyserHwndClassInfo)
{
	if(gpSyser->m_OSMajorVersion==5 && gpSyser->m_OSMinorVersion==0)
		return GetClassInfoByHwndInfoFor2K(SyserHwndInfo,SyserHwndClassInfo);
	if((gpSyser->m_OSMajorVersion==5 && gpSyser->m_OSMinorVersion==1)|| (gpSyser->m_OSMajorVersion==6 && gpSyser->m_OSMinorVersion==0))
		return GetClassInfoByHwndInfoForXP_Vista(SyserHwndInfo,SyserHwndClassInfo);
	memset(SyserHwndClassInfo,0,sizeof(*SyserHwndClassInfo));
	return false;
}
bool GetHwndInfoByWndStruct(void* OsWindowPtr,PSYSER_HWND_INFO SyserHwndInfo)
{	
	if(gpSyser->m_OSMajorVersion==5 && gpSyser->m_OSMinorVersion==1)
		return GetHwndInfoByWndStructForXP(OsWindowPtr,SyserHwndInfo);
	if(gpSyser->m_OSMajorVersion==5 && gpSyser->m_OSMinorVersion==0)
		return GetHwndInfoByWndStructFor2K(OsWindowPtr,SyserHwndInfo);
	if(gpSyser->m_OSMajorVersion==6 && gpSyser->m_OSMinorVersion==0)
		return GetHwndInfoByWndStructForVista(OsWindowPtr,SyserHwndInfo);
	return false;
}

DWORD GetHwndInfoByHandle(DWORD dwHwnd,DWORD Value,PSYSER_HWND_INFO pHwndInfo)
{
	SYSER_HWND_INFO HwndInfo;
	DWORD Type;
	while(dwHwnd && GetHwndInfoByWndStruct(*(void**)&dwHwnd,&HwndInfo))
	{
		if(Value==HwndInfo.hWnd)
		{
			memcpy(pHwndInfo,&HwndInfo,sizeof(HwndInfo));
			return dwHwnd;
		}
		Type = GetHwndInfoByHandle((DWORD)HwndInfo.ChildHwnd,Value,pHwndInfo);
		if(Type)
			return Type;
		dwHwnd=(DWORD)HwndInfo.NextHwnd;
	}
	return 0;
}
DWORD GetHwndInfoByHwnd(DWORD HwndID,PSYSER_HWND_INFO HwndInfo)
{
#ifdef CODE_OS_NT_DRV
	BOOL bOK;
	gpSyser->InitOSHwndRoot();
	CDbgProcess*pDbgProcess;
	
	pDbgProcess=gpSyser->m_SysInfo.GetProcess(WSTR("csrss"));
	if(pDbgProcess==NULL)
	{
		pDbgProcess=gpSyser->m_SysInfo.GetProcess(WSTR("explorer"));
		if(pDbgProcess==NULL)
			return 0;
	}
	gpSyser->MapToProcess(pDbgProcess);
	DWORD dwHwnd=gpSyser->m_OSHwndRoot;
	return GetHwndInfoByHandle(dwHwnd,HwndID,HwndInfo);
#endif 
	return 0;
}

static WCHAR gHwndName[256];
static bool gbShowTitle;
//static WCHAR gHwndTitle[]=WSTR("Handle    Class                         WinProc    TID  Module\n");
static WCHAR gHwndTitle[]=WSTR("Handle   WinProc   TID     Class             Module\n");
SYSER_PROCESS gHwndSyserProces;
SYSER_THREAD gHwndSyserThread;
static DWORD gHwndCount=0;
#ifdef CODE_OS_NT_DRV
bool hwnd_display_info(DWORD Address,DWORD dwDisplayFlags,SYSER_HWND_INFO &HwndInfo,DWORD dwParam)
{
	WCHAR StyleString[512];
	DWORD ProcessID=0,ThreadID=0;
	DWORD dwLen;
	WCHAR StrNum[10];
	SYSER_HWND_CLASS_INFO ClassInfo;
	
	if((dwDisplayFlags&16)  || (dwDisplayFlags&8))
	{
		if(ReadDword((void*)HwndInfo.Thread,&dwLen))
		{		
			if(GetThreadInfoByETHREAD((DWORD)dwLen,&gHwndSyserThread))
			{					
				ThreadID=gHwndSyserThread.ThreadID;
				if((dwDisplayFlags&16) && dwParam!=ThreadID)
					return false;
				if(GetProcessInfoByEPROCESS(dwLen,&gHwndSyserProces))
				{
					ProcessID = gHwndSyserProces.UniqueProcessId;
					if((dwDisplayFlags&8)  && ProcessID!=dwParam)
						return false;
				}
			}
		}
	}
	if(dwDisplayFlags&1)
	{
		OUTPUT(WSTR("    %-16s:%06x (%08x)\n"),WSTR("Hwnd"),HwndInfo.hWnd,Address);
		OUTPUT(WSTR("    %-16s:%08x\n"),WSTR("Window Proc"),HwndInfo.WndProc);
		if(HwndInfo.PreviousHwnd)
			if(ReadDword(HwndInfo.PreviousHwnd,&Address))
				OUTPUT(WSTR("    %-16s:%06x (%08x)\n"),WSTR("Previous"),Address,HwndInfo.PreviousHwnd);	
		if(HwndInfo.NextHwnd)
			if(ReadDword(HwndInfo.NextHwnd,&Address))
				OUTPUT(WSTR("    %-16s:%06x (%08x)\n"),WSTR("Next"),Address,HwndInfo.NextHwnd);
		if(HwndInfo.ParentHwnd)
			if(ReadDword(HwndInfo.ParentHwnd,&Address))
				OUTPUT(WSTR("    %-16s:%06x (%08x)\n"),WSTR("Parent"),Address,HwndInfo.ParentHwnd);
		if(HwndInfo.ChildHwnd)
			if(ReadDword(HwndInfo.ChildHwnd,&Address))
				OUTPUT(WSTR("    %-16s:%06x (%08x)\n"),WSTR("1st Child"),Address,HwndInfo.ChildHwnd);
		if(HwndInfo.OwnerHwnd)
			if(ReadDword(HwndInfo.OwnerHwnd,&Address))
				OUTPUT(WSTR("    %-16s:%06x (%08x)\n"),WSTR("Owner"),Address,HwndInfo.OwnerHwnd);

		StyleToString(HwndInfo.Style,StyleString,sizeof(StyleString)/sizeof(StyleString[0]));
		OUTPUT(WSTR("    %-16s:%08x (%s)\n"),WSTR("Style"),HwndInfo.Style,StyleString);
		StyleExToString(HwndInfo.StyleEx,StyleString,sizeof(StyleString)/sizeof(StyleString[0]));
		OUTPUT(WSTR("    %-16s:%08x (%s)\n"),WSTR("Ex. Style"),HwndInfo.StyleEx,StyleString);


		if(HwndInfo.Style&WS_CHILD) 
			OUTPUT(WSTR("    %-16s:%04x\n"),WSTR("Child Id"),HwndInfo.ControlID);
		else
		{
			if(HwndInfo.Menu)
			{
				if(ReadDword((void*)HwndInfo.Menu,&Address)==false)
					Address=HwndInfo.Menu;
				OUTPUT(WSTR("    %-16s:%06x\n"),WSTR("Menu"),Address);
			}
		}

		if(HwndInfo.UserData)
			OUTPUT(WSTR("    %-16s:%08x\n"),WSTR("User Data"),HwndInfo.UserData);
		OUTPUT(WSTR("    %-16s:%d, %d, %d, %d (%d x %d)\n"),WSTR("Window Rect"),HwndInfo.WndLeft,HwndInfo.WndTop,HwndInfo.WndRight,HwndInfo.WndBottom,HwndInfo.WndRight-HwndInfo.WndLeft,HwndInfo.WndBottom-HwndInfo.WndTop);
		OUTPUT(WSTR("    %-16s:%d, %d, %d, %d (%d x %d)\n"),WSTR("Client Rect"),HwndInfo.CliLeft-HwndInfo.WndLeft,
			HwndInfo.CliTop-HwndInfo.WndTop,HwndInfo.CliRight-HwndInfo.WndRight,HwndInfo.CliBottom-HwndInfo.WndBottom,HwndInfo.CliRight-HwndInfo.CliLeft,HwndInfo.CliBottom-HwndInfo.CliTop);
	}
	else
	{
		TSPrintf(StrNum,WSTR("%06x"),HwndInfo.hWnd);
		TSPrintf(gHwndName,WSTR("%-9s"),StrNum);
		OUTPUT(gHwndName);
		
		OUTPUT(WSTR("%08x  "),HwndInfo.WndProc);

		if(ReadDword((void*)HwndInfo.Thread,&dwLen))
		{		
			if(GetThreadInfoByETHREAD((DWORD)dwLen,&gHwndSyserThread)==false)
				gHwndSyserThread.ThreadID=0;
		}
		else 
			gHwndSyserThread.ThreadID=0;

		
		

		OUTPUT(WSTR("%06x  "),gHwndSyserThread.ThreadID);
		if(GetClassInfoByHwndInfo(&HwndInfo,&ClassInfo))
		{			
			if(ClassInfo.lpszClassName)			
			{				
				if(SyserPrivateFindByte((BYTE*)ClassInfo.lpszClassName,0,256)!=NULL)
				{					
					TStrCpy(gHwndName,(char*)ClassInfo.lpszClassName);
					OUTPUT(WSTR("%-32s  "),gHwndName);
				}
			}						
		}
		for(CProcMap::IT Iter=gpSyser->m_SysInfo.m_ProcMap.Begin();Iter!=gpSyser->m_SysInfo.m_ProcMap.End();Iter++)
		{
			if((DWORD)Iter->m_PEProcess==gHwndSyserThread.Process)
			{
				CDbgModule*pDbgModule = Iter->m_ModuleList.GetModule(HwndInfo.WndProc);
				if(pDbgModule)
				{					
					AnsiToUnicode(pDbgModule->m_ModuleTitle,gHwndName,sizeof(gHwndName)/sizeof(gHwndName[0]));
					OUTPUT(gHwndName);
				}
				else
				{
					pDbgModule = gpSyser->m_pSysDebugger->m_ModuleList.GetModule(HwndInfo.WndProc);
					if(pDbgModule)
					{					
						AnsiToUnicode(pDbgModule->m_ModuleTitle,gHwndName,sizeof(gHwndName)/sizeof(gHwndName[0]));
						OUTPUT(gHwndName);
					}
				}
				break;
			}

		}

		OUTPUT(WSTR("\n"));
	}
	return true;
}



void hwnd_display_list(DWORD dwAddress,DWORD dwDisplayFlags,DWORD Param1)
{
	SYSER_HWND_INFO HwndInfo;
	
	while(dwAddress && GetHwndInfoByWndStruct(*(void**)&dwAddress,&HwndInfo))
	{	
		if(gbShowTitle==false && ((dwDisplayFlags&0x1)==0))
		{
			OUTPUT(gHwndTitle);
			gbShowTitle=true;
		}
		if(hwnd_display_info(dwAddress,dwDisplayFlags,HwndInfo,Param1))
			gHwndCount++;
		if(dwDisplayFlags&0x1)
			OUTPUT(WSTR("\n"));//如果是详细显示句柄的所有信息
		if(dwDisplayFlags&0x2)
			hwnd_display_list((DWORD)HwndInfo.ChildHwnd,dwDisplayFlags,Param1);
		dwAddress=(DWORD)HwndInfo.NextHwnd;
		if(dwDisplayFlags&0x8000)
			break;
	}
}
const WCHAR cmd_hwnd_usage[]=
{
	L"hwnd: Display window handle information\n"
	L"Format: hwnd [-xc] [hwnd | thread | process]\n"
	L"Example1: hwnd 10016 \n"
	L"Example2: hwnd -x 10018\n"
	L"Example3: hwnd -c\n"
};
int hwnd_command(int argc, WCHAR *argv[],PCWSTR szCommandLine,CSyser*pSyser)
{
	
	DWORD Address;
	DWORD dwDisplayFlags=0;
	gbShowTitle=false;
	DWORD dwCount=0;
	int i;
	pSyser->InitOSHwndRoot();
	Address=pSyser->m_OSHwndRoot;
	gHwndCount=0;
	argc--;
	for(i=0;i<argc;i++)
	{
		if(argv[i+1][0]=='/' || argv[i+1][0]=='-')
		{
			if((argv[i+1][1]=='x' || argv[i+1][1]=='X')&&argv[i+1][2]==0)
				dwDisplayFlags |= 0x1;
			else if((argv[i+1][1]=='c' || argv[i+1][1]=='C')&&argv[i+1][2]==0)
				dwDisplayFlags |= 0x2;
			else 
			{
				OUTPUT(WSTR("hwnd input error!\n"));
				return 1;
			}
			argv[i+1][0]=0;
		}
		else
			dwCount++;
	}
	SYSER_VALUE_TYPE Type;
	SYSER_HWND_INFO HwndInfo;
	CDbgProcess*pDbgProcess=NULL;
	SYSER_PROCESS Process;
	SYSER_THREAD Thread;
	DWORD dwParam;

	pDbgProcess=gpSyser->m_SysInfo.GetProcess(WSTR("csrss"));
	if(pDbgProcess==NULL)
		return 0;
	gpSyser->MapToProcess(pDbgProcess);		

	if(dwCount)
	{
		for(i=0;i<argc;i++)
		{
			if(CALCEXP(argv[i+1],&dwParam)==false)
				continue;
			Type = GetValueType(dwParam);
			Address=pSyser->m_OSHwndRoot;
			switch(Type)
			{
			case VALUE_TYPE_PROCESS_PTR:
				if(GetProcessInfoByEPROCESS(dwParam,&Process)==false)
					continue;
					dwParam=Process.UniqueProcessId;
			case VALUE_TYPE_PROCESS_ID:		
				dwDisplayFlags|=10;
				break;
			case VALUE_TYPE_THREAD_PTR:
				if(GetThreadInfoByETHREAD(dwParam,&Thread)==false)
					continue;
			case VALUE_TYPE_THREAD_ID:
				dwDisplayFlags|=18;
				break;
			case VALUE_TYPE_HWND_ID:
				dwParam = GetHwndInfoByHwnd(dwParam,&HwndInfo);
			case VALUE_TYPE_HWND_PTR:
				Address=dwParam;
				dwDisplayFlags|=0x8000;
				break;
			}
			hwnd_display_list(Address,dwDisplayFlags,dwParam);
		}
	}
	else
	{
		dwDisplayFlags|=4;
		dwParam=0;
		hwnd_display_list(Address,dwDisplayFlags,dwParam);
	}
	if(gHwndCount>1)
		OUTPUT(WSTR("%d Hwnd(s)\n"),gHwndCount);
	return 0;
}
#endif
const WCHAR cmd_bmsg_usage[]=
{
	L"bpx: Breadpoint on Window message\n"
	L"Format: bmsg hWnd [begin-msg [end-msg]] [if condition_string] [do command_string]\n"
	L"Example1: bmsg 70370 WM_RBUTTONDOWN\n"
	L"Example2: bmsg 10018 WM_MOUSEFIRST WM_MOUSELAST\n"
	L"Example3: bmsg 10018 WM_CHAR if (*esi)&FF==0 do d eip\n"
};
int get_do_command_string(int argc, WCHAR *argv[ ],PCWSTR szCommandLine,char* szDoCmd,int MaxSize);
int get_command_condition_string(int argc, WCHAR *argv[ ],PCWSTR szCommandLine,char* szCondition,int MaxSize);

#ifdef CODE_OS_NT_DRV

int bmsg_command(int argc,WCHAR *argv[],PCWSTR szCommandLine,CSyser *pSyser)
{
	DWORD dwValue,dwParam;
	int n;
	CHAR Name[256],Condition[256],DoCmd[256];
	if(argc<3)
	{
		OUTPUT_COMMAND_USAGE;
		return 0;
	}
	UnicodeToAnsi(argv[1],Name,sizeof(Name));
	if(get_command_condition_string(argc,argv,szCommandLine,Condition,256)>0)
	{
		if(CALCEXP(Condition,NULL)==false)
		{
			OUTPUT(WSTR("Error : Invalid condition string !\n"));
			return -1;
		}
	}
	get_do_command_string(argc,argv,szCommandLine,DoCmd,256);
	for(n=2;n<argc;n++)
	{
		if(TStrICmp(argv[n],"if")==0)
		{
			break;
		}
	}
	argc=n;
	if(argc < 3)
	{
		OUTPUT_COMMAND_USAGE;
		return 0;
	}
	if(CALCEXP(argv[1],&dwParam)==false)
	{
		OUTPUT_COMMAND_USAGE;
		return 0;
	}
	DWORD dwBegin,dwEnd=0x80000000;
	bool bBeginOK=false;
	if(CALCEXP(argv[2],&dwBegin)==false)
	{
		for(n=0;stMsgList[n].MsgName;n++)
		{
			if(TStrICmp(argv[2],stMsgList[n].MsgName)==0)
			{
				dwBegin=stMsgList[n].MsgNumber;
				bBeginOK=true;
				break;
			}
		}
		if(bBeginOK==false)
		{
			OUTPUT_COMMAND_USAGE;
			return 0;
		}
	}
	if(argc>3)
	{
		bBeginOK=false;
		if(CALCEXP(argv[3],&dwEnd)==false)
		{
			for(n=0;stMsgList[n].MsgName;n++)
			{
				if(TStrICmp(argv[2],stMsgList[n].MsgName)==0)
				{
					dwEnd=stMsgList[n].MsgNumber;
					bBeginOK=true;
					break;
				}
			}
			if(bBeginOK==false)
			{
				OUTPUT_COMMAND_USAGE;
				return 0;
			}
		}
	}
	char Condition1[320];
	if(dwEnd==0x80000000)
		TSPrintf(Condition1,"(*(esp+4)==%x && *(esp+8)==%x)",dwParam,dwBegin);
	else
		TSPrintf(Condition1,"(*(esp+4)==%x && *(esp+8)>=%x && *(esp+8)<%x)",dwParam,dwBegin,dwEnd);
	if(Condition[0])
	{
		TStrCat(Condition1,"&&(");
		TStrCat(Condition1,Condition);
		TStrCat(Condition1,")");
	}
	pSyser->InitOSHwndRoot();
	SYSER_HWND_INFO HwndInfo;
	dwParam = GetHwndInfoByHwnd(dwParam,&HwndInfo);
	if(dwParam==0)
	{
		OUTPUT(WSTR("Invalid window handle\n"));
		return 0;
	}
	DWORD dwLen;
	memset(&gHwndSyserThread,0,sizeof(gHwndSyserThread));
	if(ReadDword((void*)HwndInfo.Thread,&dwLen))
	{		
		if(GetThreadInfoByETHREAD((DWORD)dwLen,&gHwndSyserThread)==false)
			gHwndSyserThread.Process=0;
	}
	for(CProcMap::IT Iter=gpSyser->m_SysInfo.m_ProcMap.Begin();Iter!=gpSyser->m_SysInfo.m_ProcMap.End();Iter++)
	{
		if((DWORD)Iter->m_PEProcess==gHwndSyserThread.Process)
		{
			gpSyser->MapToProcess(&*Iter);
			break;
		}
	}
	
	if(gpSyser->m_SyserUI.InsertCodeBP(HwndInfo.WndProc,Name,Condition1,DoCmd)==false)
		OUTPUT(WSTR("Error : Fail to set code breakpoint at %08X!\n"),HwndInfo.WndProc);
	else
		OUTPUT(WSTR("Set code break point at %<B>%08X%<1>!\n"),HwndInfo.WndProc);
	UPDATE_CODE_VIEW();
	UPDATE_SOURCE_CODE_VIEW();
	UPDATE_BP_FORM();
	return 0;
}

#endif
