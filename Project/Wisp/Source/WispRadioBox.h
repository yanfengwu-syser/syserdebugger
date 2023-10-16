#ifndef _WISP_REDIOBOX_H_
#define _WISP_REDIOBOX_H_
#include "WispWnd.h"
#include "Utility.h"

#define WISP_RBS_NORMAL							WISP_RBS_TEXTLEFT

#define WISP_RBS_MULTILINE						0x80000000
#define WISP_RBS_PUSHLIKE						0x40000000
#define WISP_RBS_TEXTLEFT						0x20000000
#define WISP_RBS_ICON							0x10000000
#define WISP_RBS_BMP							0x08000000
#define WISP_RBS_NOTIFY							0x04000000
#define WISP_RBS_RIGHT							0x02000000
#define WISP_RBS_RTLREADING						0x01000000
#define WISP_RBS_STATICEDGE						0x00800000
#define WISP_RBS_TABSTOP						0x00400000
#define WISP_RBS_BOTTOM							0x00080000
#define WISP_RBS_TOP							0x00040000
#define WISP_RBS_FLAT							0x00020000
#define WISP_RBS_CLIENTEDGE						0x00010000

#define WISP_CHECKBOX_WIDTH						WISP_SSI_CHECKBOX_SIZE+2
#define WISP_CHECKBOX_HEIGH						WISP_SSI_CHECKBOX_SIZE+2
#define WISP_TEXT_CHECKBOX_DISTANCE				0x6

class CWispRadioBox :public CWispBaseWnd
{	
public:
	CWispRadioBox();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdate);
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG(OnMouseLDown);
	DECLARE_WISP_MSG(OnMouseLUp);
	DECLARE_WISP_MSG(OnMouseLeave);
	DECLARE_WISP_MSG(OnMouseMove);
public:
	virtual bool	InitWnd();
private:
	// 用来显示文字的矩形区域
	CWispRect m_TextRect;
	CWispRect m_CheckBoxRect;
public:
	// 是否支持多行文本
	bool m_bIsMultiLine;
	// 化点取框
	void DrawBorder();
	void DrawCheckBox(IN WISP_MSG*pMsg);
	// 显示文本信息
	void DrawCaption(void);
public:
	void Check(bool bCheck=true);
	bool IsChecked(){return (m_Style&WISP_WS_MARKED)!=0;}
	void UpdateRelation();
public:
	// 鼠标是否被按下
	bool m_bMouseDown;
	// 鼠标是否在本窗口中
	bool m_bMouseIn;

};
#endif /* _WISP_REDIOBOX_H_ */


