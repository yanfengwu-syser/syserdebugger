#ifndef _SYSERCONFIG_H_
#define _SYSERCONFIG_H_

#include "SyserRegistryConfig.h"


class CSyserConfig
{
	WCHAR m_DriverRegistryPath[256];
public:	
	CSyserConfig();
	~CSyserConfig(){};
	bool ReadDwordValue(WCHAR *pValue,DWORD *pRetDword,WCHAR *pKey=NULL);
	bool WriteDwordValue(WCHAR *pValue,DWORD dwValue,WCHAR *pKey=NULL);

	bool ReadQwordValue(WCHAR *pValue,QWORD *pRetQword,WCHAR *pKey=NULL);
	bool WriteQwordValue(WCHAR *pValue,QWORD qwValue,WCHAR *pKey=NULL);

	bool WriteStringValue(WCHAR *pValue,WCHAR* szValue,WCHAR *pKey=NULL);
	bool ReadStringValue(WCHAR *pValue,WCHAR* szValue,WCHAR *pKey=NULL);
	void LoadConfig();
	void SetDriverRegistryPath(PUNICODE_STRING RegistryPath);
	DWORD m_RegStart;
	DWORD m_SupportSofticeCheck;
	DWORD m_SupportDebugRegisterMontior;
	DWORD m_SupportTimerInterrupt;
	DWORD m_SupportKeyboardLedProgram;
	DWORD m_DisableDisplay;
	DWORD m_DebugKeyboardInterrupt;
	DWORD m_PatchKeBugCheckEx;
	DWORD m_ExceptionDebugInfo;
	DWORD m_CheckPS2Mouse;
	DWORD m_PS2MouseType;
	DWORD m_PS2NULLKeyboard;
	DWORD m_MouseDoubleClickTimeInterval;
	DWORD m_DisableUSBInput;
	DWORD m_DisableRWPortHook;
	DWORD m_DisableHookException;
	DWORD m_SupportVMWareMouse;
	DWORD m_DisableCopyOnWrite;
};


#endif /* _SYSERCONFIG_H_ */