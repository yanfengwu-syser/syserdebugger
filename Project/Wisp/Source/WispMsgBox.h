#ifndef _WISP_MESSAGEBOX_H_
#define _WISP_MESSAGEBOX_H_

/*
	使用说明：
	1.如果要自定义按钮按钮，按如下方法：
		CWispMsgBox	box;
		box.Create(m_pWispBase, this);
		box.AddButton(WISP_STR("shit"), 0);
		box.AddButton(WISP_STR("another shit"), 1);
		box.ShowMsgBox(WISP_STR("What you want?"), WISP_STR("Caption"), WISP_MB_CUSTOMIZE);

	2.如果使用默认方式，在一个CWispBaseWnd的继承类中，直接用MsgBox即可：
		MsgBox(WISP_STR("What you want?"), WISP_STR("Caption"), WISP_MB_YESNO|WISP_MB_ICONQUESTION);

	3.如果不在CWispBaseWnd的继承类中，调用CWispBase的MsgBox即可：
		m_pWispBase->MsgBox(WISP_STR("What you want?"), WISP_STR("Caption"), WISP_MB_YESNO|WISP_MB_ICONQUESTION);

	4.在任何地方都可以直接调用CWispMsgBox的静态方法，以上2、3两种方法都是通过本方法实现的：
		CWispMsgBox::StaticShowMsgBox(m_pWispBase, WISP_STR("What you want?"), WISP_STR("Caption"), WISP_MB_YESNO|WISP_MB_ICONALERT, this);
 */

#include "WispButton.h"

#define MSGBOX_BTN_SPACE		2

#define WISP_MB_OK				0x00000001
#define WISP_MB_CANCEL			0x00000002
#define WISP_MB_ABORT			0x00000004
#define WISP_MB_RETRY			0x00000008
#define WISP_MB_IGNORE			0x00000010
#define WISP_MB_YES				0x00000020
#define WISP_MB_NO				0x00000040
#define WISP_MB_CONTINUE		0x00000080
#define WISP_MB_TRY				0x00000100

#define WISP_MB_ABORTRETRYIGNORE	(WISP_MB_ABORT|WISP_MB_RETRY|WISP_MB_IGNORE)
#define WISP_MB_CANCELTRYCONTINUE	(WISP_MB_CANCEL|WISP_MB_TRY|WISP_MB_CONTINUE)
#define WISP_MB_OKCANCEL			(WISP_MB_OK|WISP_MB_CANCEL)
#define WISP_MB_RETRYCANCEL			(WISP_MB_RETRY|WISP_MB_CANCEL)
#define WISP_MB_YESNO				(WISP_MB_YES|WISP_MB_NO)
#define WISP_MB_YESNOCANCEL			(WISP_MB_YES|WISP_MB_NO|WISP_MB_CANCEL)

#define WISP_MB_BTNMASK			0x00000FFFL
#define WISP_MB_CUSTOMIZE		0x00001000L

#define WISP_MB_ICONINFOMATION	0x00010000L
#define WISP_MB_ICONQUESTION	0x00020000L
#define WISP_MB_ICONALERT		0x00030000L
#define WISP_MB_ICONERROR		0x00040000L
#define WISP_MB_ICONEXCLAMATION	WISP_MB_ICONALERT
#define WISP_MB_ICONWARNING		WISP_MB_ICONALERT
#define WISP_MB_ICONASTERISK	WISP_MB_ICONINFOMATION
#define WISP_MB_ICONSTOP		WISP_MB_ICONERROR
#define WISP_MB_ICONHAND		WISP_MB_ICONERROR
#define WISP_MB_ICONMASK		0x000F0000L


#include "WispWnd.h"
#include "WispDIB.h"
class CWispMsgBox : public CWispWnd
{
public:
	CWispMsgBox(void);
	~CWispMsgBox(void);
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdateClient);
	DECLARE_WISP_MSG(OnCommand);
public:
	bool Create(IN CWispBaseWnd*pParentWnd);
	static int StaticShowMsgBox(WISP_CHAR* pText, WISP_CHAR* pCaption, UINT uType ,CWispBaseWnd* pParentWnd = NULL);
	int ShowMsgBox(WISP_CHAR* pText, WISP_CHAR* pCaption, UINT uType);
	void AddButton(WISP_CHAR* pText, int nID);
	void AddDefaultButton(UINT uType);
	void AddDefaultIcon(UINT uType);
	void RemoveAllButtons();
	struct BTNPAIR
	{
		TString<WISP_CHAR>	pBtnText;
		int					nID;
	};
	TList<BTNPAIR>		m_vButtons;
	TString<WISP_CHAR> m_strText;
	int m_nBtnWidth;
	CWispDIB	m_dibIcon;
	int			m_nReturnStatus;
};

#endif//_WISP_MESSAGEBOX_H_

