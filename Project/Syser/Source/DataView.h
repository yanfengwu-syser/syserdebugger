#ifndef _DATA_VIEW_H_
#define _DATA_VIEW_H_

#include "DataOperatorDlg.h"

class CDataView	: public CWispHexWnd
{
	//typedef bool (CDataView::*DATA_HOTKEY_FP)(IN UINT Index);

	//class CDataHotKey
	//{
	//public:
	//	UINT m_ViewIndex;
	//	DATA_HOTKEY_FP m_fpHotKey;
	//	CDataHotKey(){};
	//	CDataHotKey(UINT Index,DATA_HOTKEY_FP fpHotKey):m_ViewIndex(Index),m_fpHotKey(fpHotKey){};
	//	~CDataHotKey(){}
	//};

	typedef TMap<UINT,UINT> DATAHOTKEYMAP;
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG(OnChar);
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnEventShowData)
	DECLARE_WISP_MSG_EVENT(OnEventDasmAddr)
	DECLARE_WISP_MSG_EVENT(OnEventShowDataNewWnd)
	DECLARE_WISP_MSG_EVENT(OnEventDasmAddrNewWnd)
	DECLARE_WISP_MSG_EVENT(OnEventShowPhysAddr)
	DECLARE_WISP_MSG_EVENT(OnEventDasmPhysAddr)
	DECLARE_WISP_MSG_EVENT(OnEventShowToolbar)
	DECLARE_WISP_MSG_EVENT(OnEventShowOffset)	
	DECLARE_WISP_MSG_EVENT(OnEventDataOperation)
	DECLARE_WISP_MSG_EVENT(OnEventAddressModeHex)
	DECLARE_WISP_MSG_EVENT(OnEventOffsetModeHex)
	DECLARE_WISP_MSG_EVENT(OnEventToggleAddressMode)	
	DECLARE_WISP_MSG_EVENT(OnEventToggleFloatMode)

	DECLARE_WISP_MSG_EVENT(OnGotoDataViewByValue)
	DECLARE_WISP_MSG_EVENT(OnGotoDataViewByValueWithOffset)
	DECLARE_WISP_MSG_EVENT(OnGotoCodeViewByValue )
	DECLARE_WISP_MSG_EVENT( OnCopyValueToClipboard)
	DECLARE_WISP_MSG_EVENT(OnCopyAddressToClipboard )
	DECLARE_WISP_MSG_EVENT(OnCopySelectValue )
	DECLARE_WISP_MSG_EVENT(OnActiveDataView )

	bool	OnActiveDataView(IN UINT Index);
	bool	DispatchHotKey(IN UINT Type);
	ULSIZE	WriteData(ULPOS Address,BYTE*Buffer,ULSIZE Size);
	ULSIZE	ReadData(ULPOS Address,BYTE*Buffer,ULSIZE Size);
	DWORD	GetPopMenuDataPos();
	DWORD	GetDataOperatorPos();
	bool	GetDataOperatorParam(DWORD* BeginAddr,DWORD* EndAddr,DWORD* DataWidth);
	void	OnAddrChange();
	void OnDataChange();
	int		GetStartLine();
	void	PopupMenu(IN WISP_MSG*pMsg);
	ULPOS	GetFloatAddress(CStrW& CmdStr);
	void	AttachShortcutKey();
	DWORD	FindShortcutKey(DWORD CmdID);

public:
	ULPOS				m_MenuShowPos;
	ULPOS				m_DataOperatorAddr;
	ULPOS				m_BaseAddressActive;
	CWispMenu			m_PopupMenu;
	CWispToolbar		m_Toolbar;
	CDataOperatorDlg	m_DataOperatorDlg;
	DATAHOTKEYMAP		m_HotKeyMap;
};

#endif
