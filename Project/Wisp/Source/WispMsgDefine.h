#ifndef _WISP_MSG_DEFINE_H_
#define _WISP_MSG_DEFINE_H_

enum WISP_SB_EVENT_TYPE
{
	WISP_SB_INC,
	WISP_SB_DEC,
	WISP_SB_PAGE_UP,
	WISP_SB_PAGE_DOWN,
	WISP_SB_POS_CHANGE,
};

#define WISP_LAST_POS						-1
//Window Hit Area
#define	WISP_HIT_WND_NON					0x00000000
#define	WISP_HIT_WND_CLIENT					0x00000001
#define	WISP_HIT_WND_MOVE					0x00000002
#define	WISP_HIT_WND_NON_CLIENT				0x00000003
#define	WISP_HIT_WND_BT_CLOSE				0x00000004
#define	WISP_HIT_WND_BT_MAX					0x00000005
#define	WISP_HIT_WND_BT_MIN					0x00000006

#define	WISP_HIT_WND_RESIZE_LEFT			0x00010000
#define	WISP_HIT_WND_RESIZE_RIGHT			0x00020000
#define	WISP_HIT_WND_RESIZE_TOP				0x00040000
#define	WISP_HIT_WND_RESIZE_BOTTOM			0x00080000
#define WISP_HIT_WND_RESIZE_MASK			0x000F0000

#define	WISP_HIT_WND_RESIZE_LEFT_TOP		(WISP_HIT_WND_RESIZE_LEFT | WISP_HIT_WND_RESIZE_TOP)
#define	WISP_HIT_WND_RESIZE_RIGHT_TOP		(WISP_HIT_WND_RESIZE_RIGHT | WISP_HIT_WND_RESIZE_TOP)
#define	WISP_HIT_WND_RESIZE_LEFT_BOTTOM		(WISP_HIT_WND_RESIZE_LEFT | WISP_HIT_WND_RESIZE_BOTTOM)
#define	WISP_HIT_WND_RESIZE_RIGHT_BOTTOM	(WISP_HIT_WND_RESIZE_RIGHT | WISP_HIT_WND_RESIZE_BOTTOM)

//Window's Ctrl Hit Area
#define	WISP_HIT_CTRL_NON					0x00000000

#define	WISP_HIT_CTRL_VERT_INC_BT			0x00000001
#define	WISP_HIT_CTRL_VERT_DEC_BT			0x00000002
#define	WISP_HIT_CTRL_VERT_SLIDE_RECT		0x00000003
#define	WISP_HIT_CTRL_VERT_SPACE_RECT		0x00000004
#define	WISP_HIT_CTRL_VERT_SCROLL_RECT		0x00000005

#define	WISP_HIT_CTRL_HORZ_INC_BT			0x00000011
#define	WISP_HIT_CTRL_HORZ_DEC_BT			0x00000012
#define	WISP_HIT_CTRL_HORZ_SLIDE_RECT		0x00000013
#define	WISP_HIT_CTRL_HORZ_SPACE_RECT		0x00000014
#define	WISP_HIT_CTRL_HORZ_SCROLL_RECT		0x00000015

#define WISP_CMD_USER_START			0x00000001
#define WISP_CMD_DEVELOP_START		0x40000000
#define WISP_CMD_SYSTEM_START		0x80000000
///////////////////////////////////////////////////////////////////////////////////////
//Command子消息<Start>
///////////////////////////////////////////////////////////////////////////////////////
#define WISP_CMD_BT_DOWN			0x80000001			//按钮按下
#define WISP_CMD_BT_UP				0x80000002			//按钮抬起
///////////////////////////////////////////////////////////////////////////////////////
#define WISP_CMD_GET_CMD			0x80000010			//控制台窗口取得消息
///////////////////////////////////////////////////////////////////////////////////////
#define WISP_CMD_ITEM_EXPANDING		0x80000100			//item is being expanded
#define WISP_CMD_ITEM_EXPANDED		0x80000101			//item has been expanded
#define WISP_CMD_ITEM_UNEXPANDING	0x80000102			//item is being unexpanded
#define WISP_CMD_ITEM_UNEXPANDED	0x80000103			//item has been unexpanded
#define WISP_CMD_ITEM_SELECTING		0x80000104			//item is being selected
#define WISP_CMD_ITEM_SELECTED		0x80000105			//item has been selected
#define WISP_CMD_ITEM_UNSELECTING	0x80000106			//item is being unselected
#define WISP_CMD_ITEM_UNSELECTED	0x80000107			//item has been unselected
#define WISP_CMD_ITEM_CHECKING		0x80000108			//item is being checked
#define WISP_CMD_ITEM_CHECKED		0x80000109			//item has been checked
#define WISP_CMD_ITEM_UNCHECKING	0x8000010A			//item is being unchecked
#define WISP_CMD_ITEM_UNCHECKED		0x8000010B			//item has been unchecked
#define WISP_CMD_ITEM_CHANGED		0x8000010E			//item has been edited
#define WISP_CMD_ITEM_ENABLED		0x8000010F			//item has been enabled
#define WISP_CMD_ITEM_DISABLED		0x80000110			//item has been disabled
#define WISP_CMD_ITEM_BEGIN_EDIT	0x80000111			//begin to edit a label
#define WISP_CMD_ITEM_END_EDIT		0x80000112			//end to edit a label
#define WISP_CMD_ITEM_CANCEL_EDIT	0x80000113			//end to edit a label
#define WISP_CMD_ITEM_HOVER			0x80000114			//item hover
#define WISP_CMD_ITEM_UNHOVER		0x80000115			//item lost hover
#define WISP_CMD_ITEM_CLICK			0x80000116			//click an item
#define WISP_CMD_ITEM_RDBCLICK		0x80000117			//right button double click an item
#define WISP_CMD_ITEM_LDBCLICK		0x80000118			//left button double click an item
#define WISP_CMD_ITEM_KEY_DOWN		0x80000119			//recive a key event down
#define WISP_CMD_ITEM_KEY_UP		0x80000120			//recive a key event up
#define WISP_CMD_TITLE_CLICK		0x80000121			//
#define WISP_CMD_TITLE_RCLICK		0x80000122			//
///////////////////////////////////////////////////////////////////////////////////////
#define WISP_CMD_CTRL_GET_FOCUS		0x80000201			//ctrl get focus
#define WISP_CMD_CTRL_LOST_FOCUS	0x80000202			//ctrl lost focus
#define WISP_CMD_CTRL_CLICK			0x80000203			//click an item
#define WISP_CMD_CTRL_RCLICK		0x80000204			//right click an item
#define WISP_CMD_CTRL_DBCLICK		0x80000205			//double click an item
///////////////////////////////////////////////////////////////////////////////////////
#define WISP_CMD_CB_CLICK			0x80000300			//checkbox click
///////////////////////////////////////////////////////////////////////////////////////
#define WISP_CMD_COMBOX_SELCHANGE	0x80000400			//COMBOX BOX SELECT CHANGE
///////////////////////////////////////////////////////////////////////////////////////
#define WISP_CMD_STATIC_URL_CLICK	0x80000500			//COMBOX BOX SELECT CHANGE

///////////////////////////////////////////////////////////////////////////////////////
#define WISP_CMD_EN_CHANGING		0x80000700			//Edit change before update screen
#define WISP_CMD_EN_KILLFOCUS		0x80000701			//The edit control loses the input focus
#define WISP_CMD_EN_SETFOCUS		0x80000702			//Sent when an edit control receives the input focus. 
#define WISP_CMD_EN_INPUT_KEY_DOWN	0x80000703			//Edit recive a key down
#define WISP_CMD_EN_INPUT_KEY_UP	0x80000704			//Edit recive a key up
#define WISP_CMD_EN_CHANGED			0x80000705			//Edit changed
///////////////////////////////////////////////////////////////////////////////////////
#define WISP_CMD_TAB_ACTIVE_CHG		0x80000800			//Tab
///////////////////////////////////////////////////////////////////////////////////////
#define WISP_CMD_LANGUAGE_CHANGE	0x80001000			//语言改变通知。所有的窗口都得到通知。
///////////////////////////////////////////////////////////////////////////////////////
#define WISP_CMD_HOTKEY				0x80002000
///////////////////////////////////////////////////////////////////////////////////////
//Command子消息<End>
///////////////////////////////////////////////////////////////////////////////////////

class CWispBaseWnd;
struct WISP_MSG
{
	CWispBaseWnd*hWnd;
	CWispBaseWnd*hSrcWnd;
	UINT	Msg;
	bool	bMsgLBTDown;
	bool	bMsgRBTDown;
	WISP_POINT	MsgMouseScrPT;
	WISP_POINT	MsgMouseWndPT;
	WISP_POINT	MsgMouseCltPT;
	union
	{
		struct
		{
			UINT		ID;
			UINT		UserData;
			void*		UserPtr;
		}Timer;
		struct
		{
			WISP_POINT	BeginMouseWndPT;
			UINT		UserData;
			void*		UserPtr;
			int			DeltaX;
			int			DeltaY;
		}DragEvent;
		struct
		{
			UINT		HitAreaType;
			UINT		HitCtrlType;
			UINT		KeyType;
			bool		bKeyDown;
			UINT		ScanCode;
		}KeyEvent;
		struct
		{
			UINT		HitAreaType;
			UINT		HitCtrlType;
			CWispBaseWnd*hWndMouseAt;
			int			DeltaX;
			int			DeltaY;
			int			DeltaZ;
		}MouseEvent;
		struct
		{
			WISP_CTRL_TYPE	CtrlType;	//defined bellow
			UINT		CmdMsg;
			UINT		CmdID;
			int			Param1;
			void*		Param2;
		}Command;
		struct
		{
			int			DeltaX;
			int			DeltaY;
		}Move;
		struct
		{
			int			nRepeat;
			WISP_CHAR	Char;
		}Char;
		struct
		{
			UINT			Event;
			WISP_SB_TYPE	SBType;
			WISP_SCROLL_LONG	CurPos;
			WISP_SCROLL_LONG	Delta;
		}ScrollEvent;
		struct
		{
			UINT		HitAreaType;
			UINT		HitCtrlType;
			bool		bKeyDown;
		}HitTest;						//WISP_WM_HIT_TEST
		struct 
		{
			WISP_SIZE	NewSize;
			WISP_SIZE	NewSizeDelta;
		}Resize;						//WISP_WM_SIZE,WISP_WM_SIZING
		CWispBaseWnd*	hOtherWnd;		//WISP_WM_GET_FOCUS WISP_WM_LOST_FOCUS
	};
};

struct WISP_INPUT_MSG
{
	UINT InputMsg;
	union
	{
		struct
		{
			int PosX;
			int PosY;
		}MousePosChg;
		struct 
		{
			int DeltaX;
			int DeltaY;
		}MouseMove;
		struct 
		{
			int DeltaZ;
		}MouseWheel;
		struct
		{
			UINT KeyType;
		}MouseBTDBClick;
		struct 
		{
			int MilliSec;
		}Timer;
		struct
		{
			UINT KeyType;
			bool bKeyDown;
			UINT ScanCode;
		}KeyEvent;
	};
};

//////////////////////////////////////////////////////
//消息
//////////////////////////////////////////////////////
#define WISP_IGNORE_MSG						0xFFFFFFFF
#define WISP_INVALID_MSG					0x00000000

#define WISP_WM_USER_START					0x00000001

#define WISP_WM_DEVELOP_START				0x40000000

//外部硬件输入消息
#define WISP_INPUT_EVENT_START				0x70000000

#define WISP_INPUT_KEY_EVENT				0x70000001
#define WISP_INPUT_MOUSE_POS_CHG			0x70000002
#define WISP_INPUT_MOUSE_MOVE				0x70000003
#define WISP_INPUT_MOUSE_WHEEL				0x70000004
#define WISP_INPUT_MOUSE_BT_DB_CLICK		0x70000005
#define WISP_INPUT_TIMER					0x70000006

#define WISP_INPUT_EVENT_END				0x80000000
//外部硬件输入消息

#define WISP_WM_SYS_START					0x80000000

#define WISP_APP_INIT						0x80000000
#define WISP_APP_EXIT						0x80000001

#define WISP_WM_PRECREATE					0x80000010
#define WISP_WM_CREATE						0x80000011
#define WISP_WM_FORM_CREATE					0x80000012
#define WISP_WM_DESTROY						0x80000013
#define WISP_WM_CLOSE						0x80000014
//////////////////////////////////////////////////////
#define WISP_WM_KEY_EVENT					0x80000020
#define WISP_WM_NON_CLIENT_MOUSE_KEY_EVENT	0x80000021
//////////////////////////////////////////////////////
#define WISP_WM_MOUSE_ENTER					0x80000030
#define WISP_WM_MOUSE_MOVE					0x80000031
#define WISP_WM_MOUSE_LEAVE					0x80000032
#define WISP_WM_MOUSE_WHEEL					0x80000033
#define WISP_WM_MOUSE_DBCLICK				0x80000034
//////////////////////////////////////////////////////
#define WISP_WM_COMMAND						0x80000040
#define WISP_WM_EVENT						0x80000041
//////////////////////////////////////////////////////
#define WISP_WM_UPDATE						0x80000100
#define WISP_WM_UPDATE_BORDER				0x80000101
#define WISP_WM_UPDATE_CAPTION				0x80000102
#define WISP_WM_UPDATE_CLIENT				0x80000103
#define WISP_WM_UPDATE_CARET				0x80000104
#define WISP_WM_UPDATE_HORZ_SCROLL			0x80000105
#define WISP_WM_UPDATE_VERT_SCROLL			0x80000106
//////////////////////////////////////////////////////
#define WISP_WM_BEGIN_MOVE					0x80000120
#define WISP_WM_END_MOVE					0x80000121
#define WISP_WM_MOVE						0x80000122
#define WISP_WM_MOVING						0x80000123
#define WISP_WM_SIZE						0x80000124
#define WISP_WM_SIZING						0x80000125
#define WISP_WM_RECALCLAYOUT				0x80000126
#define WISP_WM_PARENT_RESIZE				0x80000127
//////////////////////////////////////////////////////
#define WISP_WM_CHAR						0x80000140
//////////////////////////////////////////////////////
#define WISP_WM_SCROLL_EVENT				0x80000150

#define WISP_WM_VERT_SCROLL_MOVE			0x80000152
#define WISP_WM_HORZ_SCROLL_MOVE			0x80000153

//////////////////////////////////////////////////////
#define WISP_WM_TIMER						0x80000161
//////////////////////////////////////////////////////
#define WISP_WM_GET_FOCUS					0x80000170
#define WISP_WM_LOST_FOCUS					0x80000171
//////////////////////////////////////////////////////
#define WISP_WM_HIT_TEST					0x80000180
//////////////////////////////////////////////////////
#define WISP_WM_BEGIN_DRAG					0x80000190
#define WISP_WM_DRAG_MOVE					0x80000191
#define WISP_WM_END_DRAG					0x80000192
//////////////////////////////////////////////////////
//消息映射宏
//////////////////////////////////////////////////////
#define DECLARE_WISP_MSG_MAP				virtual bool MsgProc(IN WISP_MSG*pMsg);
#define DECLARE_WISP_MSG(FuncName)			bool FuncName(IN WISP_MSG*pMsg);
#define WISP_MSG_MAP_BEGIN(ClassName)		bool ClassName::MsgProc(IN WISP_MSG*pMsg)\
											{\
												switch(pMsg->Msg)\
												{\
													case WISP_INVALID_MSG:	\
														return false;
#define WISP_MSG_MAP_ON_COMMAND						case WISP_WM_COMMAND:\
														if(OnCommand(pMsg)==false)\
															return false;\
														break;
#define WISP_MSG_MAP_ON_EVENT						case WISP_WM_EVENT:\
														if(OnEvent(pMsg)==false)\
															return false;\
														break;
#define WISP_MSG_MAP(Msg,OnMsgProc)					case Msg:\
														if(OnMsgProc(pMsg)==false)\
															return false;\
														break;
#define WISP_MSG_MAP_END(BaseClassName)				default:\
														break;\
													}\
													return BaseClassName::MsgProc(pMsg);\
												}
#define WISP_BASE_WND_MSG_MAP_END					default:\
														break;\
													}\
													return true;\
												}
#define WISP_MSG_MAP_DEFAULT_END(OnMsgProc,BaseClassName)	default:\
																return OnMsgProc(pMsg);\
															}\
															return BaseClassName::MsgProc(pMsg);\
														}
////////////////////////////////////////////////////////////////////////////////////////////
//Command映射宏
////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_WISP_MSG_CMD_MAP			bool OnCommand(IN WISP_MSG*pMsg);
#define DECLARE_WISP_MSG_CMD(FuncName)		bool FuncName(IN WISP_MSG*pMsg);
#define WISP_MSG_CMD_MAP_BEGIN(ClassName)	bool ClassName::OnCommand(IN WISP_MSG*pMsg)\
											{\
												switch(pMsg->Command.CmdID)\
												{\
													case WISP_ID_NULL:\
														return true;
#define WISP_MSG_CMD_MAP(CmdID,OnMsgProc)			case CmdID:\
														if(OnMsgProc(pMsg)==false)\
															return false;\
														break;
#define WISP_MSG_CMD_MAP_END						default:\
														break;\
												}\
												return true;\
											}
#define WISP_MSG_CMD_MAP_DEFAULT_END(OnMsgProc)		default:\
														return OnMsgProc(pMsg);\
												}\
												return true;\
											}

////////////////////////////////////////////////////////////////////////////////////////////
//Event映射宏
////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_WISP_MSG_EVENT_MAP			bool OnEvent(IN WISP_MSG*pMsg);
#define DECLARE_WISP_MSG_EVENT(FuncName)	bool FuncName(IN WISP_MSG*pMsg);
#define WISP_MSG_EVENT_MAP_BEGIN(ClassName)	bool ClassName::OnEvent(IN WISP_MSG*pMsg)\
											{\
												switch(pMsg->Command.CmdID)\
												{\
													case WISP_ID_NULL:\
														return false;
#define WISP_MSG_EVENT_MAP(CmdID,OnMsgProc)			case CmdID:\
														if(OnMsgProc(pMsg)==false)\
															return false;\
														break;
#define WISP_MSG_EVENT_MAP_END						default:\
														break;\
												}\
												return true;\
											}
#define WISP_MSG_EVENT_MAP_DEFAULT_END(OnMsgProc)	default:\
														return OnMsgProc(pMsg);\
												}\
												return true;\
											}
#endif

