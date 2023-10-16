#ifndef _CODE_H_
#define _CODE_H_

#include "CodeConfig.h"
#include "CodeDepInc.h"
#include "Define.h"

#include "NewAlloc.h"

#ifdef  CODE_DEBUG_ALLOC

#include "DebugNewAlloc.h"

#define new		new(__FILE__,__LINE__)

#endif

#include "alt/alt.hpp"
#include "StrMem.h"
#include "TStrMem.h"
#include "Maths.h"
#include "SysDep.h"
#include "Compress.h"
#include "CmdParser.h"
#include "TXTFile.h"
#include "LogFile.h"
#include "INIFile.h"
#include "PolyFS.h"
#include "Heap.h"
#include "OptionValue.h"
#include "Float2String.h"
#include "LangLib.h"
#include "Crc.h"

#ifdef CODE_OS_WIN
#include "WinReg.h"
#include "HttpDownload.h"
#include "HttpUpload.h"
#endif

#ifdef CODE_OS_NT_DRV
#include "NTDrvRuntime.h"
#endif

#ifdef CODE_USE_NAME_SPACE
using namespace code;
#endif

#endif//_CODE_H_

