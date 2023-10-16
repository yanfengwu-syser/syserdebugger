#ifndef _SYSER_VERSION_H_
#define _SYSER_VERSION_H_  
#include "SyserBuildNumber.h"

#define VER_SPECIALBUILD_INFO "$Rev: 1071 $"

 
#define VER_PRODUCTMAJORVERSION     1
#define VER_PRODUCTMINORVERSION     99

#define VER_PRODUCTBUILD            1900

#define VER_PRODUCTBETA_STR         ""

#define VER_PRODUCTVERSION_MAJORMINOR2(x,y) #x "." #y
#define VER_PRODUCTVERSION_MAJORMINOR1(x,y) VER_PRODUCTVERSION_MAJORMINOR2(x, y)
#define VER_PRODUCTVERSION_STRING   VER_PRODUCTVERSION_MAJORMINOR1(VER_PRODUCTMAJORVERSION, VER_PRODUCTMINORVERSION)

#define VER_PRODUCTVERSION          VER_PRODUCTMAJORVERSION,VER_PRODUCTMINORVERSION,VER_PRODUCTBUILD,VER_PRODUCTBUILD_QFE
#define VER_PRODUCTVERSION_W        ((VER_PRODUCTMAJORVERSION << 8)|VER_PRODUCTMINORVERSION)
#define VER_PRODUCTVERSION_DW        ((VER_PRODUCTVERSION_W <<16) | VER_PRODUCTBUILD)

#if     (VER_PRODUCTBUILD < 10)
#define VER_BPAD "000"
#elif   (VER_PRODUCTBUILD < 100)
#define VER_BPAD "00"
#elif   (VER_PRODUCTBUILD < 1000)
#define VER_BPAD "0"
#else
#define VER_BPAD
#endif

#if     (VER_PRODUCTBUILD_QFE < 10)
#define VER_BPAD_QFE "000"
#elif   (VER_PRODUCTBUILD_QFE < 100)
#define VER_BPAD_QFE "00"
#elif   (VER_PRODUCTBUILD_QFE < 1000)
#define VER_BPAD_QFE "0"
#else
#define VER_BPAD_QFE
#endif

#define VER_PRODUCTVERSION_STR2(x,y) VER_PRODUCTVERSION_STRING "." VER_BPAD #x "." VER_BPAD_QFE #y
#define VER_PRODUCTVERSION_STR1(x,y) VER_PRODUCTVERSION_STR2(x, y)
#define VER_PRODUCTVERSION_STR       VER_PRODUCTVERSION_STR1(VER_PRODUCTBUILD, VER_PRODUCTBUILD_QFE)


#if DBG
#define VER_DEBUG                   VS_FF_DEBUG
#else
#define VER_DEBUG                   0
#endif
 
/* default is prerelease */
#if BETA
#define VER_PRERELEASE              VS_FF_PRERELEASE
#else
#define VER_PRERELEASE              0
#endif

#if OFFICIAL_BUILD
#define VER_PRIVATE                 0
#else
#define VER_PRIVATE                 VS_FF_PRIVATEBUILD
#endif

#define VER_FILEFLAGSMASK           VS_FFI_FILEFLAGSMASK
#define VER_FILEOS                  VOS_NT_WINDOWS32
#define VER_FILEFLAGS               (VER_PRERELEASE|VER_DEBUG|VER_PRIVATE)

#define VER_COMPANYNAME_STR         "Syser Software Corporation"
#define VER_PRODUCTNAME_STR         "Syser Kernel Debugger for Windows"
#define VER_LEGALTRADEMARKS_STR     "Syser (R) is a registered trademark of Syser Software Corporation."
#define	VER_LEGALCOPYRIGHT_STR		"Syser Software Corporation. All rights reserved." 
#define VER_FILEVERSION_STR   VER_PRODUCTVERSION_MAJORMINOR1(VER_PRODUCTMAJORVERSION, VER_PRODUCTMINORVERSION)

#define	VER_FILEVERSION									VER_PRODUCTVERSION
#endif //_SYSER_VERSION_H_


