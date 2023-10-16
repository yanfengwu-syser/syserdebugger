#ifndef _STDAFX_H_
#define _STDAFX_H_

#ifndef CODE_OS_NT_DRV
#include <iostream>
#include <fstream>
#include <list>  
#include <map> 
#include <vector>
#include <algorithm> 
using namespace std;
#endif 
   
#include "../../Code/Source/Code.h"
#include "../../EXEAnalyzer/Source/EXEAnalyzer.h"
#include "../../Wisp/Source/Wisp.h"
//#include "../../SerialNumber/Source/SerialNumber.h"
//#include "../../SerialNumber/Source/Validate.h"


#include "X86Define.h"
#include <SyserDebugger.h>
#include "../../Addition/DiaSDK2005/include/cvconst.h"

#ifdef	CODE_OS_NT_DRV

#include <windef.h>
#include <wingdi.h>
#include <winddi.h>
#include <ntddvdeo.h>
#include <hidusage.h>
#include <hidpi.h>
#include "NTUtility.h" 
#include "Undoc.h"
#include "pcidef.h"
#include "pci.h"
#include "SyserDefine.h"
#include "OSData.h"
#include "X86Optr.h"
#include "GlobalVariable.h"

#include "../../SysBoot/Source/SysBoot.h"
#include "../../SysLang/Source/SysLang.h"
//#include "../../SDbgMsg/Source/SDbgMsg.h"
#include "../../BootVid/Source/bootvid.h"

#define	AnsiToUnicode			SyserAnsiToUnicode
#define	UnicodeToAnsi			SyserUnicodeToAnsi

#else	//CODE_OS_WIN

#include <DbgHelp.h>
#include <tlhelp32.h>
#include <PsApi.h>
#include "SyserDefine.h"
#include "../../WinWisp/Source/WinWisp.h"
#include "../../SyserApp/Source/SourceDebug.h"
#include "../../SyserApp/Source/NoPDBSymbol.h"

#endif

#include "Resource.h"
#include "SyserResource.h"
#include "SyserOption.h"
#include "ColorOption.h"
#include "SyserMemoryReadWrite.h"
#include "../../Addition/SyserDebugger/SDSymbol.h"
#include "../../Addition/SyserDebugger/SyserVersion.h"
#endif




