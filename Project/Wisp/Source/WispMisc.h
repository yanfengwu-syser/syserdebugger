#ifndef _WISP_MISC_H_
#define _WISP_MISC_H_

#include "WispProgress.h"
#include "WispForm.h"
#include "WispStatic.h"

bool GetResultFromList(int x,int y,WISP_PCSTR*szTextList,int*pResult,int Default = -1);
bool GetInputText(CWispString&szText,WISP_PSTR szStaticText = NULL,WISP_PSTR szTitle = WISP_STR("Please Input ...."));
bool GetRGBColor(COLORREF*pResult,COLORREF *pDefault=NULL);

class CWispProgressForm : public CWispForm
{
public:
	CWispProgressForm();
	~CWispProgressForm();
	enum WISP_FORM_ID;
	static WISP_FORM_RES_ITEM m_FormRes[];
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
	CWispProgress*m_pProgessCtrl;
	CWispStaticStr*m_pStaticStr;
	void	SetProgressText(WISP_PCSTR szText);
}; 

#endif
