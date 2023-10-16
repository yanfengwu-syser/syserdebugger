#ifndef _STDAFX_H_
#define _STDAFX_H_

#include "../../Code/Source/Code.h"
#include "../../Wisp/Source/Wisp.h"

#ifdef CODE_OS_WIN
#include "../../WinWisp/Source/WinWisp.h"
#endif
#ifdef CODE_OS_UNIX
#include "SdlBase.h"
#endif


#endif
