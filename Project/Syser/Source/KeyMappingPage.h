#ifndef _KEY_MAPPING_PAGE_H_
#define _KEY_MAPPING_PAGE_H_
#include "../../Code/Source/Code.h"
#include "../../Syser/Source/SyserOption.h"




typedef TList<KEY_PAIR> HOTKEYLIST;
typedef TMap<DWORD,HOTKEYLIST> CMDHOTKEYMAP;

class CKeyMappingPage : public CWispForm
{
public:
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate);
	DECLARE_WISP_MSG(OnResize);
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_CMD(OnFileListCommand)
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_EVENT(OnButtonAdd)
	DECLARE_WISP_MSG_EVENT(OnButtonRemove)
	DECLARE_WISP_MSG_EVENT(OnButtonSave)
	DECLARE_WISP_MSG_EVENT(OnButtonReload)
	DECLARE_WISP_MSG_EVENT(OnButtonDefault)
	DECLARE_WISP_MSG_EVENT(OnNewKeyEdit)
	DECLARE_WISP_MSG_EVENT(OnExistKeyList)
	CKeyMappingPage();
	CWispStaticGroup*m_pGroup;
	CWispStaticGroup*m_pGroupDescription;
	CWispStaticStr* m_CommandStr;
	CWispStaticStr* m_NewKeyStr;
	CWispEdit* m_NewKeyEdit;
	CWispStaticStr* m_ExistStr;
	CWispList*	m_pCommandsList;
	CWispList*	m_pExistList;
	CWispButton*m_pSaveBT;
	CWispButton*m_pDefaultSignBT;
	CWispButton*m_pReloadBT;
	CWispButton*m_pDefaultBT;
	CWispButton*m_pAddBT;
	CWispButton*m_pRemoveBT;
	CHAR	m_HotKeyFile[MAX_FN_LEN];
	WCHAR	m_szSystemRootDir[MAX_FN_LEN];
	bool	LoadHotKeyConfigFile();
	bool	LoadHotKeyConfigFileByMap(CMDHOTKEYMAP *pCmdHotKeyMap);
	bool	SaveHotKeyConfigFile();
	bool	IsListItem(PCWSTR szName);
	int		m_PreviousKeyType;
	WCHAR* GetHotKeyName(DWORD dwFuncKey,DWORD dwSecondKey,WCHAR* Buffer);
	WCHAR* GetHotKeyName(DWORD KeyValue,WCHAR* Buffer);
	CMDHOTKEYMAP m_CmdHotKeyMap;
	HOTKEYLIST* GetCurrentHotKeyList();
	KEY_PAIR GetHotKey();
	void LoadDefaultAll();
	void Popup();
	//CMDHOTKEYMAP m_CurrentCMDHotKeyMap;

	HANDLE m_ItemHotkey[5];
	//HANDLE m_CodeViewHotkey;
	//HANDLE m_DataViewHotkey;
	//HANDLE m_StackViewHotkey;
	//HANDLE m_RegisterViewHotkey;

};

#endif   //_KEY_MAPPING_PAGE_H_

