#include "StdAfx.h"
#include "WispCalcWnd.h"
//extern item_contents	display_data;
//extern bool				display_error;

item_contents 	display_data;
bool display_error	= false;
bool percent_mode	= false;

stack_ptr	top_of_stack = NULL;
stack_ptr	top_type_stack[2] = { NULL, NULL };
int 		stack_next, stack_last;
stack_item	process_stack[STACK_SIZE];


#define PRINT_FLOAT		"%d"
#define PRINT_LONG_BIG	"%d"
#define PRINT_LONG		"%d"


#define PRINT_OCTAL	"%I64o"
#define PRINT_HEX	"%I64X"


int precedence[14] = { 0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 6 };

int adjust_op[14][3] =
{
	{FUNC_NULL,     FUNC_NULL,     FUNC_NULL},
	{FUNC_OR,       FUNC_OR,       FUNC_XOR },
	{FUNC_XOR,      FUNC_XOR,      FUNC_XOR },
	{FUNC_AND,      FUNC_AND,      FUNC_AND },
	{FUNC_LSH,      FUNC_LSH,      FUNC_RSH },
	{FUNC_RSH,      FUNC_RSH,      FUNC_RSH },
	{FUNC_ADD,      FUNC_ADD,      FUNC_ADD },
	{FUNC_SUBTRACT, FUNC_SUBTRACT, FUNC_SUBTRACT},
	{FUNC_MULTIPLY, FUNC_MULTIPLY, FUNC_MULTIPLY},
	{FUNC_DIVIDE,   FUNC_DIVIDE,   FUNC_DIVIDE},
	{FUNC_MOD,      FUNC_MOD,      FUNC_INTDIV },
	{FUNC_POWER,    FUNC_POWER,    FUNC_PWR_ROOT},
	{FUNC_PWR_ROOT, FUNC_PWR_ROOT, FUNC_PWR_ROOT},
	{FUNC_INTDIV,   FUNC_INTDIV,   FUNC_INTDIV},
};

Arith Arith_ops[14] =
{
	NULL,
		CWispCalcWnd::ExecOr,
		CWispCalcWnd::ExecXor,
		CWispCalcWnd::ExecAnd,
		CWispCalcWnd::ExecLsh,
		CWispCalcWnd::ExecRsh,
		CWispCalcWnd::ExecAdd,
		CWispCalcWnd::ExecSubtract,
		CWispCalcWnd::ExecMultiply,
		CWispCalcWnd::ExecDivide,
		CWispCalcWnd::ExecMod,
		CWispCalcWnd::ExecPower,
		CWispCalcWnd::ExecPwrRoot,
		CWispCalcWnd::ExecIntDiv
};

Prcnt Prcnt_ops[14] =
{
	NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		CWispCalcWnd::ExecAddP,
		CWispCalcWnd::ExecSubP,
		CWispCalcWnd::ExecMultiplyP,
		CWispCalcWnd::ExecDivideP,
		NULL,
		NULL,
		NULL,
		NULL
};
const CALCAMNT CWispCalcWnd::pi = 3;

WISP_MSG_MAP_BEGIN(CWispCalcWnd)
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestory)
	WISP_MSG_MAP(WISP_WM_UPDATE_CLIENT,OnUpdateClient)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
WISP_MSG_MAP_END(CWispWnd)

CWispCalcWnd::CWispCalcWnd(void)
{	
	inverse=false;	
	refresh_display=false;
	display_size=DEC_SIZE;
	m_NumberBitWdith=ANG_DEGREE;
	input_limit=0;
	input_count=0;
	decimal_point=0;
	precedence_base=0;
	current_base=NB_DECIMAL;
	memory_num=0;
	last_input=DIGIT;
	history_index=0;
	key_pressed=false;
	mInternalSpacing=4;
}

bool CWispCalcWnd::OnKeyEvent(IN WISP_MSG *pMsg)
{
	if(pMsg->KeyEvent.bKeyDown)
		OnKeyDown(pMsg);
	Update();
	return true;
}

bool CWispCalcWnd::OnDestory(IN WISP_MSG*pMsg)
{
	pbA->Destroy();
	delete pbA;
	pbMR->Destroy();
	delete pbMR;
	pbMplusminus->Destroy();
	delete pbMplusminus;
	pbMC->Destroy();
	delete pbMC;
	pbClear->Destroy();
	delete pbClear;
	pbAC->Destroy();
	delete pbAC;
	pbRsh->Destroy();
	delete pbRsh;
	pbplusminus->Destroy();
	delete pbplusminus;
	pbB->Destroy();
	delete pbB;
	pb7->Destroy();
	delete pb7;
	pb8->Destroy();
	delete pb8;
	pb9->Destroy();
	delete pb9;
	pbparenopen->Destroy();
	delete pbparenopen;
	pbparenclose->Destroy();
	delete pbparenclose;
	pband->Destroy();
	delete pband;
	pbXor->Destroy();
	delete pbXor;
	pbC->Destroy();
	delete pbC;
	pb4->Destroy();
	delete pb4;
	pb5->Destroy();
	delete pb5;
	pb6->Destroy();
	delete pb6;
	pbX->Destroy();
	delete pbX;
	pbdivision->Destroy();
	delete pbdivision;
	pbor->Destroy();
	delete pbor;	
	pbfactorial->Destroy();
	delete pbfactorial;
	pbD->Destroy();
	delete pbD;
	pb1->Destroy();
	delete pb1;
	pb2->Destroy();
	delete pb2;
	pb3->Destroy();
	delete pb3;
	pbplus->Destroy();
	delete pbplus;
	pbminus->Destroy();
	delete pbminus;
	pbshift->Destroy();
	delete pbshift;
	pbsquare->Destroy();
	delete pbsquare;
	pbE->Destroy();
	delete pbE;
	pb0->Destroy();
	delete pb0;
	pbequal->Destroy();
	delete pbequal;
	pbnegate->Destroy();
	delete pbnegate;
	pbmod->Destroy();
	delete pbmod;
	pbpower->Destroy();
	delete pbpower;
	pbF->Destroy();
	delete pbF;
	for(int i =0; i < 4;i++)
	{
		anglebutton[i]->Destroy();
		delete anglebutton[i];
		basebutton[i]->Destroy();
		delete basebutton[i];
	}
	
	return true;
}

void CWispCalcWnd::Popup()
{
	if(IsWindow())
	{
		Show();
	}
	else
	{
		Create(0,0);
		Center();
	}
}

bool CWispCalcWnd::Create(int x,int y,CWispBaseWnd*pParentWnd,UINT CmdID)
{
	return CWispWnd::Create(WISP_STR("Calc"),x,y,500,204,pParentWnd,CmdID,WISP_WS_CAPTION|WISP_WS_BORDER|WISP_WS_BT_CLOSE,WISP_SH_NORMAL);
}

bool CWispCalcWnd::OnCreate(IN WISP_MSG*pMsg)
{
	CWispRect rc;
	int NormalWidth=40,NormalHeight=16;
	int xdelt=4;
	int ydelt=4;
	pbA = new CWispButton;
	pbMR = new CWispButton;
	pbMplusminus = new CWispButton;
	pbMC = new CWispButton;
	pbClear = new CWispButton;
	pbAC = new CWispButton;
	pbRsh = new CWispButton;
	pbplusminus = new CWispButton;
	pbB = new CWispButton;
	pb7 = new CWispButton;
	pb8 = new CWispButton;
	pb9 = new CWispButton;
	pbparenopen = new CWispButton;
	pbparenclose = new CWispButton;
	pband = new CWispButton;
	pbXor = new CWispButton;
	pbC = new CWispButton;
	pb4 = new CWispButton;
	pb5 = new CWispButton;
	pb6 = new CWispButton;
	pbX = new CWispButton;
	pbdivision = new CWispButton;
	pbor = new CWispButton;

	pbfactorial = new CWispButton;
	pbD = new CWispButton;
	pb1 = new CWispButton;
	pb2 = new CWispButton;
	pb3 = new CWispButton;
	pbplus = new CWispButton;
	pbminus = new CWispButton;
	pbshift = new CWispButton;

	pbsquare = new CWispButton;
	pbE = new CWispButton;
	pb0 = new CWispButton;
	pbequal = new CWispButton;
	pbnegate = new CWispButton;
	pbmod = new CWispButton;
	pbpower = new CWispButton;
	pbF = new CWispButton;
	
	for(int i = 0; i < 4;i++)
	{
		anglebutton[i] = new CWispRadioBox;
		basebutton[i]=new CWispRadioBox;
	}
	NormalHeight=25;
	rc.x = 15,rc.y=33,rc.cx=40,rc.cy=16; 
	basebutton[0]->Create(WSTR("Hex"),rc,this,CHECKBOX_HEX,WISP_RBS_FLAT|WISP_WS_BACK_TRANS,WISP_SH_NORMAL);
	rc.x = 15,rc.y+=(NormalHeight+ydelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	basebutton[1]->Create(WSTR("Dec"),rc,this,CHECKBOX_DEC,WISP_RBS_FLAT|WISP_WS_BACK_TRANS,WISP_SH_NORMAL);
	rc.x = 15,rc.y+=(NormalHeight+ydelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	basebutton[2]->Create(WSTR("Oct"),rc,this,CHECKBOX_OCT,WISP_RBS_FLAT|WISP_WS_BACK_TRANS,WISP_SH_NORMAL);
	rc.x = 15,rc.y+=(NormalHeight+ydelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	basebutton[3]->Create(WSTR("Bin"),rc,this,CHECKBOX_BIN,WISP_RBS_FLAT|WISP_WS_BACK_TRANS,WISP_SH_NORMAL);

	rc.x = 90,rc.y=33,rc.cx=58,rc.cy=16;
	anglebutton[0]->Create(WSTR("64 Bit"),rc,this,CHECKBOX_8BYTE,WISP_RBS_FLAT|WISP_WS_BACK_TRANS,WISP_SH_NORMAL);
	rc.x = 90,rc.y+=(NormalHeight+ydelt),rc.cx=58,rc.cy=NormalHeight;
	anglebutton[1]->Create(WSTR("32 Bit"),rc,this,CHECKBOX_4BYTE,WISP_RBS_FLAT|WISP_WS_BACK_TRANS,WISP_SH_NORMAL);
	rc.x = 90,rc.y+=(NormalHeight+ydelt),rc.cx=58,rc.cy=NormalHeight;
	anglebutton[2]->Create(WSTR("16 Bit"),rc,this,CHECKBOX_2BYTE,WISP_RBS_FLAT|WISP_WS_BACK_TRANS,WISP_SH_NORMAL);
	rc.x = 90,rc.y+=(NormalHeight+ydelt),rc.cx=58,rc.cy=NormalHeight;
	anglebutton[3]->Create(WSTR(" 8 Bit"),rc,this,CHECKBOX_1BYTE,WISP_RBS_FLAT|WISP_WS_BACK_TRANS,WISP_SH_NORMAL);

	anglebutton[0]->Check(false);
	anglebutton[1]->Check(true);
	anglebutton[2]->Check(false);
	anglebutton[3]->Check(false);
	basebutton[0]->Check(true);
	basebutton[1]->Check(false);	
	basebutton[2]->Check(false);
	basebutton[3]->Check(false);
#define HIGH_ITEM 24

	NormalWidth=40;NormalHeight=16;
	rc.x = 303-35,rc.y=32,rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbMR->Create(WISP_STR("MR"),&rc,this,BUTTON_MR,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.y=32,rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbMplusminus->Create(WISP_STR("M+-"),&rc,this,BUTTON_MOTHER,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.y=32,rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbMC->Create(WISP_STR("MC"),&rc,this,BUTTON_MC,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.y=32,rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbClear->Create(WISP_STR("C"),&rc,this,BUTTON_AFUNCTION,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.y=32,rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbAC->Create(WISP_STR("AC"),&rc,this,BUTTON_AC,WISP_BS_NORMAL,WISP_SH_NORMAL);
#define HIGH_2 89

	rc.x = 171-35, rc.y+=(NormalHeight+ydelt),rc.cx=NormalWidth,rc.cy=NormalHeight;	
	rc.x += (NormalWidth+xdelt);
	pbplusminus->Create(WISP_STR("+/-"),&rc,this,BUTTON_PLUSMINUS,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pb7->Create(WISP_STR("7"),&rc,this,BUTTON_7,WISP_BS_NORMAL,WISP_SH_NORMAL);//13521866678
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pb8->Create(WISP_STR("8"),&rc,this,BUTTON_8,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pb9->Create(WISP_STR("9"),&rc,this,BUTTON_9,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbparenopen->Create(WISP_STR("("),&rc,this,BUTTON_LBRACKET,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbparenclose->Create(WISP_STR(")"),&rc,this,BUTTON_RBRACKET,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pband->Create(WISP_STR("And"),&rc,this,BUTTON_AND,WISP_BS_NORMAL,WISP_SH_NORMAL);
#define HIGH_3 117

	rc.x = 171-35, rc.y+=(NormalHeight+ydelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	
	rc.x += (NormalWidth+xdelt);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pb4->Create(WISP_STR("4"),&rc,this,BUTTON_4,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pb5->Create(WISP_STR("5"),&rc,this,BUTTON_5,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pb6->Create(WISP_STR("6"),&rc,this,BUTTON_6,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbX->Create(WISP_STR("X"),&rc,this,BUTTON_MULTIPLYSIGN,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbdivision->Create(WISP_STR("/"),&rc,this,BUTTON_DIVESIONSIGN,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbor->Create(WISP_STR("Or"),&rc,this,BUTTON_OR,WISP_BS_NORMAL,WISP_SH_NORMAL);

#define HIGH_4 145	
	rc.x = 62+153-35,rc.y+=(NormalHeight+ydelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbfactorial->Create(WISP_STR("x!"),&rc,this,BUTTON_FACTORIAL,WISP_BS_NORMAL,WISP_SH_NORMAL);

	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pb1->Create(WISP_STR("1"),&rc,this,BUTTON_1,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pb2->Create(WISP_STR("2"),&rc,this,BUTTON_2,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pb3->Create(WISP_STR("3"),&rc,this,BUTTON_3,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbplus->Create(WISP_STR("+"),&rc,this,BUTTON_ADDSIGN,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbminus->Create(WISP_STR("-"),&rc,this,BUTTON_SUBSIGN,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbshift->Create(WISP_STR("Lsh"),&rc,this,BUTTON_LSH,WISP_BS_NORMAL,WISP_SH_NORMAL);
//13504330378//13180887271
#define HIGH_5 173
	
	rc.x = 62+153-35,rc.y+=(NormalHeight+ydelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbsquare->Create(WISP_STR("x^2"),&rc,this,BUTTON_SQUARE,WISP_BS_NORMAL,WISP_SH_NORMAL);			
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pb0->Create(WISP_STR("0"),&rc,this,BUTTON_0,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbequal->Create(WISP_STR("="),&rc,this,BUTTON_EQUALSIGN,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbnegate->Create(WISP_STR("Not"),&rc,this,BUTTON_CMP,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbmod->Create(WISP_STR("Mod"),&rc,this,BUTTON_MOD,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbRsh->Create(WISP_STR("Rsh"),&rc,this,BUTTON_RSH,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbXor->Create(WISP_STR("Cos"),&rc,this,BUTTON_COS,WISP_BS_NORMAL,WISP_SH_NORMAL);		
#define HIGH_6 (201)
	rc.x = 62+153-35,rc.y+=(NormalHeight+ydelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbpower->Create(WISP_STR("x^y"),&rc,this,BUTTON_POWER,WISP_BS_NORMAL,WISP_SH_NORMAL);	
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbA->Create(WISP_STR("A"),&rc,this,BUTTON_A,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbB->Create(WISP_STR("B"),&rc,this,BUTTON_B,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbC->Create(WISP_STR("C"),&rc,this,BUTTON_C,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbD->Create(WISP_STR("D"),&rc,this,BUTTON_D,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbE->Create(WISP_STR("E"),&rc,this,BUTTON_E,WISP_BS_NORMAL,WISP_SH_NORMAL);
	rc.x += (NormalWidth+xdelt),rc.cx=NormalWidth,rc.cy=NormalHeight;
	pbF->Create(WISP_STR("F"),&rc,this,BUTTON_F,WISP_BS_NORMAL,WISP_SH_NORMAL);

	readSettings();
	set_precision();
	set_style();
	Base_Selected(0);
	InitializeCalculator();
	LoadTitleDIB("\\WispApp\\Calc\\Calc.bmp");
	m_pTitleDIB->SetType(WISP_DIB_TK);
	m_pTitleDIB->SetColorKey(0);
	return true;
}

bool CWispCalcWnd::OnCommand(IN WISP_MSG*pMsg)
{
	if(pMsg->Command.CtrlType==WISP_CTRL_RADIO_BOX)
	{
		switch(pMsg->Command.CmdID)
		{
		case CHECKBOX_HEX:
			Hex_Selected();
			break;
		case CHECKBOX_DEC:
			Dec_Selected();
			break;
		case CHECKBOX_OCT:
			Oct_Selected();
			break;
		case CHECKBOX_BIN:
			Bin_Selected();
			break;
		case CHECKBOX_8BYTE:
			Qword_Selected();
			break;
		case CHECKBOX_4BYTE:
			Dword_Selected();
			break;
		case CHECKBOX_2BYTE:
			Word_Selected();
			break;
		case CHECKBOX_1BYTE:
			Byte_Selected();
			break;
		}
	}
	if(pMsg->Command.CtrlType==WISP_CTRL_BUTTON)
	{	if(pMsg->Command.CmdMsg==WISP_CMD_BT_UP)
		switch(pMsg->Command.CmdID) {
			case BUTTON_CONFIG:				
				break;
			case BUTTON_HELP:
				break;
			case EDIT_DISPLAY:
				break;			
			case BUTTON_HYP:	
				pbhyptoggled(true);
				break;
			case BUTTON_INV:
				pbinvtoggled(true);
				break;
			case BUTTON_A:
				pbAtoggled(true);
				break;
			case BUTTON_EE:	
				EEtoggled(true);
				break;
			case BUTTON_MR:
				pbMRtoggled(true);
				break;
			case BUTTON_MOTHER:
				pbMplusminustoggled(true);
				break;
			case BUTTON_MC:
				pbMCtoggled(true);
				break;
			case BUTTON_AFUNCTION:		
				pbCleartoggled(true);
				break;
			case BUTTON_AC:
				pbACtoggled(true);
				break;
			case BUTTON_RSH:
				pbRshtoggled(true);
				break;
			case BUTTON_PLUSMINUS:
				pbplusminustoggled(true);				
				break;
			case BUTTON_B:
				pbBtoggled(true);
				break;
			case BUTTON_7:
				pb7toggled(true);
				break;
			case BUTTON_8:
				pb8toggled(true);
				break;
			case BUTTON_9:
				pb9toggled(true);
				break;
			case BUTTON_LBRACKET:
				pbparenopentoggled(true);
				break;
			case BUTTON_RBRACKET:
				pbparenclosetoggled(true);
				break;
			case BUTTON_AND:
				pbandtoggled(true);
				break;
			case BUTTON_COS:
				pbXortoggled(true);
				break;
			case BUTTON_RECIPROCAL:
				pbrecitoggled(true);
				break;
			case BUTTON_C:
				pbCtoggled(true);
				break;
			case BUTTON_4:
				pb4toggled(true);
				break;
			case BUTTON_5:
				pb5toggled(true);
				break;
			case BUTTON_6:
				pb6toggled(true);
				break;
			case BUTTON_MULTIPLYSIGN:
				pbXtoggled(true);
				break;
			case BUTTON_DIVESIONSIGN:
				pbdivisiontoggled(true);
				break;
			case BUTTON_OR:
				pbortoggled(true);
				break;
			case BUTTON_TAN:
				pbTantoggled(true);
				break;
			case BUTTON_FACTORIAL:
				pbfactorialtoggled(true);
				break;
			case BUTTON_D:
				pbDtoggled(true);
				break;
			case BUTTON_1:
				pb1toggled(true);
				break;
			case BUTTON_2:
				pb2toggled(true);
				break;
			case BUTTON_3:
				pb3toggled(true);
				break;
			case BUTTON_ADDSIGN:
				pbplustoggled(true);
				break;
			case BUTTON_SUBSIGN:
				pbminustoggled(true);
				break;
			case BUTTON_LSH:
				pbshifttoggled(true);
				break;
			case BUTTON_LOG:
				pblogtoggled(true);
				break;
			case BUTTON_SQUARE:
				pbsquaretoggled(true);
				break;
			case BUTTON_E:
				pbEtoggled(true);
				break;
			case BUTTON_DECIMAL:
				pbperiodtoggled(true);
				break;
			case BUTTON_0:
				pb0toggled(true);
				break;
			case BUTTON_EQUALSIGN:
				pbequaltoggled(true);
				break;
			case BUTTON_PERCENTSIGN:
				pbpercenttoggled(true);
				break;
			case BUTTON_CMP:
				pbnegatetoggled(true);
				break;
			case BUTTON_MOD:
				pbmodtoggled(true);
				break;
			case BUTTON_LN:
				pblntoggled(true);
				break;
			case BUTTON_POWER:
				pbpowertoggled(true);
				break;
			case BUTTON_F:
				pbFtoggled(true);
				break;
		default:
			break;
		}
	}
	return true;
}

bool CWispCalcWnd::OnUpdateClient(IN WISP_MSG*pMsg)
{
#define STAT_Y_VALUE 156
	WISP_RECT rc;
	WISP_CHAR DisplayOut[100];
	CWispWnd::OnUpdateClient(pMsg);
	rc.x = 5, rc.y=31,rc.cx=64,rc.cy=117;
	m_ClientDC.DrawRect(&rc,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_RED]);
	rc.x = 85,rc.y=31,rc.cx=66,rc.cy=117;
	m_ClientDC.DrawRect(&rc,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_RED]);
	rc.x = 5,rc.y=STAT_Y_VALUE,rc.cx=49,rc.cy=17;
	m_ClientDC.DrawFrameRect(&rc,false);	
	m_ClientDC.DrawString(WISP_STR("NORM"),&rc,WISP_DT_VCENTER|WISP_DT_CENTER);	
	rc.x = 58,rc.y=STAT_Y_VALUE,rc.cx=49,rc.cy=17;
	m_ClientDC.DrawFrameRect(&rc,false);
	m_ClientDC.DrawString(WISP_STR(""),&rc,WISP_DT_VCENTER|WISP_DT_CENTER);
	rc.x = 111,rc.y=STAT_Y_VALUE,rc.cx=218+156,rc.cy=17;
	m_ClientDC.DrawFrameRect(&rc,false);

	rc.x = 5, rc.y=4,rc.cx=329+150,rc.cy=22;	
	m_ClientDC.DrawFullRect(&rc,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_WHITE]);
	m_ClientDC.DrawRect(&rc,m_pWispBase->m_pCurDrawObj->m_crSystem[SC_BLACK]);
	rc.cx-=4;
	TStrToStr(display_str,DisplayOut);
	m_ClientDC.DrawString(DisplayOut,&rc,WISP_DT_VCENTER|WISP_DT_RIGHT);
	return false;
}
//-------------------------------------------------------------------------
// Name: Base_Selected()
//-------------------------------------------------------------------------
void CWispCalcWnd::Base_Selected(int base)
{	
	pbA->EnableWindow(base==0);
	pbB->EnableWindow(base==0);
	pbC->EnableWindow(base==0);
	pbD->EnableWindow(base==0);
	pbE->EnableWindow(base==0);
	pbF->EnableWindow(base==0);
	pb9->EnableWindow(base<=1);
	pb8->EnableWindow(base<=1);
	pb7->EnableWindow(base <= 2);
	pb6->EnableWindow(base <= 2);
	pb5->EnableWindow(base <= 2);
	pb4->EnableWindow(base <= 2);
	pb3->EnableWindow(base <= 2);
	pb2->EnableWindow(base <= 2);	
	base_selected(base);
}

//-------------------------------------------------------------------------
// Name: Hex_Selected()
//-------------------------------------------------------------------------
void CWispCalcWnd::Hex_Selected()
{
	basebutton[0]->Check(true);
	basebutton[1]->Check(false);
	basebutton[2]->Check(false);
	basebutton[3]->Check(false);
	Base_Selected(0);
}

//-------------------------------------------------------------------------
// Name: Dec_Selected()
//-------------------------------------------------------------------------
void CWispCalcWnd::Dec_Selected()
{
	basebutton[0]->Check(false);
	basebutton[1]->Check(true);
	basebutton[2]->Check(false);
	basebutton[3]->Check(false);
	Base_Selected(1);
}

//-------------------------------------------------------------------------
// Name: Oct_Selected()
//-------------------------------------------------------------------------
void CWispCalcWnd::Oct_Selected()
{
	basebutton[0]->Check(false);
	basebutton[1]->Check(false);
	basebutton[2]->Check(true);
	basebutton[3]->Check(false);
	Base_Selected(2);
}

//-------------------------------------------------------------------------
// Name: Bin_Selected()
//-------------------------------------------------------------------------
void CWispCalcWnd::Bin_Selected()
{
	basebutton[0]->Check(false);
	basebutton[1]->Check(false);
	basebutton[2]->Check(false);
	basebutton[3]->Check(true);
	Base_Selected(3);
}

//-------------------------------------------------------------------------
// Name: Deg_Selected()
//-------------------------------------------------------------------------
void CWispCalcWnd::Qword_Selected()
{
	anglebutton[0]->Check(true);
	anglebutton[1]->Check(false);
	anglebutton[2]->Check(false);
	anglebutton[3]->Check(false);
	angle_selected(0);
}

//-------------------------------------------------------------------------
// Name: Rad_Selected()
//-------------------------------------------------------------------------
void CWispCalcWnd::Dword_Selected()
{
	anglebutton[0]->Check(false);
	anglebutton[1]->Check(true);
	anglebutton[2]->Check(false);
	anglebutton[3]->Check(false);
	angle_selected(1);
}

//-------------------------------------------------------------------------
// Name: Gra_Selected()
//-------------------------------------------------------------------------
void CWispCalcWnd::Word_Selected()
{
	anglebutton[0]->Check(false);
	anglebutton[1]->Check(false);
	anglebutton[2]->Check(true);
	anglebutton[3]->Check(false);
	angle_selected(2);
}

void CWispCalcWnd::Byte_Selected()
{
	anglebutton[0]->Check(false);
	anglebutton[1]->Check(false);	
	anglebutton[2]->Check(false);
	anglebutton[3]->Check(true);
	angle_selected(3);
}

//-------------------------------------------------------------------------
// Name: keyPressEvent(QKeyEvent *e)
//-------------------------------------------------------------------------
bool CWispCalcWnd::OnKeyDown(IN WISP_MSG *pMsg)
{
	switch (pMsg->KeyEvent.KeyType)
	{
	case WISP_VK_F1:		
		break;
	case WISP_VK_F2:		
		break;
	case WISP_VK_F3:
		if(kcalcdefaults.style == 0)
			kcalcdefaults.style = 1;
		else
			kcalcdefaults.style = 0;
		set_style();
		break;
	case WISP_VK_UP:
		history_prev();
		break;
	case WISP_VK_DOWN:
		history_next();
		break;
	case WISP_VK_PAGE_DOWN:
		key_pressed = true;
		pbACtoggled(true);
		break;
	case WISP_VK_PAGE_UP:
		key_pressed = true;
		pbCleartoggled(true);
		break;
	case WISP_VK_H:
		key_pressed = true;
		pbhyptoggled(true);
		break;
	case WISP_VK_I:
		key_pressed = true;
		pbinvtoggled(true);
		break;
	case WISP_VK_A:
		key_pressed = true;
		pbAtoggled(true);
		break;
	case WISP_VK_E:
		key_pressed = true;
		if (current_base == NB_HEX)
			pbEtoggled(true);
		else
			EEtoggled(true);
		break;
	case WISP_VK_ESCAPE:
		key_pressed = true;
		pbCleartoggled(true);
		break;
	case WISP_VK_DELETE:
		key_pressed = true;
		pbACtoggled(true);
		break;
	case WISP_VK_S:
		key_pressed = true;
		pbRshtoggled(true);
		break;
	case WISP_VK_OEM_5:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbortoggled(true);
		else			
			pbplusminustoggled(true);
		break;
	case WISP_VK_B:
		key_pressed = true;
		pbBtoggled(true);
		break;
	case WISP_VK_7:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbandtoggled(true);
		else
			pb7toggled(true);
		break;
	case WISP_VK_8:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbXtoggled(true);
		else
			pb8toggled(true);
		break;
	case WISP_VK_9:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbparenopentoggled(true);
		else
			pb9toggled(true);
		break;
								
	case WISP_VK_C:
		key_pressed = true;
		if (current_base == NB_HEX)
			pbCtoggled(true);
		else
			pbXortoggled(true);
		break;
	case WISP_VK_4:
		key_pressed = true;
		pb4toggled(true);
		break;
	case WISP_VK_5:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbpercenttoggled(true);
		else
			pb5toggled(true);
		break;
	case WISP_VK_6:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbpowertoggled(true);
		else
			pb6toggled(true);
		break;
	case WISP_VK_X:		
		key_pressed = true;
		pbXtoggled(true);
		break;		
	case WISP_VK_DIVIDE:
		key_pressed = true;
		pbdivisiontoggled(true);
		break;
	case WISP_VK_O:
		key_pressed = true;
		pbortoggled(true);
		break;
	case WISP_VK_T:
		key_pressed = true;
		pbTantoggled(true);
		break;		
	case WISP_VK_D:
		key_pressed = true;
		//if(kcalcdefaults.style == 0)
				pbDtoggled(true);
		//else
			//	pblog->setOn(true); // stat mode
		break;
	case WISP_VK_1:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbfactorialtoggled(true);
		else
			pb1toggled(true);
		break;
	case WISP_VK_2:
		key_pressed = true;
		pb2toggled(true);
		break;
	case WISP_VK_3:
		key_pressed = true;
		pb3toggled(true);
		break;
	case WISP_VK_OEM_PLUS:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbplustoggled(true);
		else
			pbequaltoggled(true);
		break;
	case WISP_VK_OEM_MINUS:
		key_pressed = true;
			pbminustoggled(true);					
		break;
	case WISP_VK_N:
		key_pressed = true;
		pblntoggled(true);
		break;
	case WISP_VK_L:
		key_pressed = true;
		pblogtoggled(true);
		break;		
	case WISP_VK_F:
		key_pressed = true;
		pbFtoggled(true);
		break;
	case WISP_VK_OEM_PERIOD:
		key_pressed = true;
		pbperiodtoggled(true);
		break;
	case WISP_VK_OEM_COMMA:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbshifttoggled(true);
		else			
			pbperiodtoggled(true);
		break;
	case WISP_VK_0:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbparenclosetoggled(true);
		else
			pb0toggled(true);;		
		break;		
	case WISP_VK_RETURN:
		key_pressed = true;
		pbequaltoggled(true);
		break;				
		
	case WISP_VK_OEM_3:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbnegatetoggled(true);
		break;
	case WISP_VK_SEMI:
		key_pressed = true;
		if(m_pWispBase->m_KeyMap[WISP_VK_SHIFT])
			pbmodtoggled(true);
		break;
	case WISP_VK_LSQUARE_BRACKET:		
		key_pressed = true;
		pbsquaretoggled(true);
		break;
	case WISP_VK_BACK:
		SubtractDigit();
		key_pressed = true;
		pbACtoggled(true);
		break;
	case WISP_VK_R:
		key_pressed = true;
		pbrecitoggled(true);
		break;
	}
	return true;
}

//-------------------------------------------------------------------------
// Name: keyReleaseEvent(QKeyEvent *e)
//-------------------------------------------------------------------------
bool CWispCalcWnd::OnKeyUp(IN WISP_MSG *pMsg)
{
	bool oldKey = key_pressed;
	key_pressed = false;

	switch (pMsg->KeyEvent.KeyType)
	{
		//	case Key_Next:
		//pbAC->setOn(false);
		break;
		//	case Key_Prior:
		//pbClear->setOn(false);
		break;
	case WISP_VK_H:
		//pbhyp->setOn(false);
		break;
	case WISP_VK_I:
		//pbinv->setOn(false);
		break;
	case WISP_VK_A:
		//pbA->setOn(false);
		break;
	case WISP_VK_E:
		if (current_base == NB_HEX)
			;//	pbE->setOn(false);
		else
			;//	pbEE->setOn(false);
		break;
	case WISP_VK_ESCAPE:
		//pbClear->setOn(false);
		break;
	case WISP_VK_DELETE:
		//pbAC->setOn(false);
		break;
	case WISP_VK_S:
		//pbSin->setOn(false);
		break;
		//	case Key_Backslash:
		//pbplusminus->setOn(false);
		break;
	case WISP_VK_B:
		//pbB->setOn(false);
		break;
	case WISP_VK_7:
		//pb7->setOn(false);
		break;
	case WISP_VK_8:
		//pb8->setOn(false);
		break;
	case WISP_VK_9:
		//pb9->setOn(false);
		break;
		//	case Key_ParenLeft:
		//pbparenopen->setOn(false);
		break;
		//	case Key_ParenRight:
		//pbparenclose->setOn(false);
		break;
		//	case Key_Ampersand:
		//pband->setOn(false);
		break;
	case WISP_VK_C:
		if (current_base == NB_HEX)
			;//	pbC->setOn(false);
		else
			;//	pbCos->setOn(false);
		break;
	case WISP_VK_4:
		//pb4->setOn(false);
		break;
	case WISP_VK_5:
		//pb5->setOn(false);
		break;
	case WISP_VK_6:
		//pb6->setOn(false);
		break;
		//	case Key_Asterisk:
		//pbX->setOn(false);
		break;
		//	case Key_Slash:
		//pbdivision->setOn(false);
		break;
	case WISP_VK_O:
		//pbor->setOn(false);
		break;
	case WISP_VK_T:
		//pbTan->setOn(false);
		break;
		//	case Key_Exclam:
		//pbfactorial->setOn(false);
		break;
	case WISP_VK_D:
		if(kcalcdefaults.style == 0)
			;//	pbD->setOn(false);		// trig mode
		else
			;//	pblog->setOn(false);	// stat mode
		break;
	case WISP_VK_1:
		//pb1->setOn(false);
		break;
	case WISP_VK_2:
		//pb2->setOn(false);
		break;
	case WISP_VK_3:
		//pb3->setOn(false);
		break;
	case WISP_VK_ADD:
		///pbplus->setOn(false);
		break;
	case WISP_VK_SUBTRACT:
		//pbminus->setOn(false);
		break;
		//	case Key_Less:
		//pbshift->setOn(false);
		break;
	case WISP_VK_N:
		//pbln->setOn(false);
		break;
	case WISP_VK_L:
		key_pressed = false;
		//pblog->setOn(false);
		break;
		//	case Key_AsciiCircum:
		//pbpower->setOn(false);
		break;
	case WISP_VK_F:
		//pbF->setOn(false);
		break;
	case WISP_VK_OEM_PERIOD:
		//pbperiod->setOn(false);
		break;
	case WISP_VK_OEM_COMMA:
		//pbperiod->setOn(false);
		break;
	case WISP_VK_0:
		//pb0->setOn(false);
		break;
		//	case Key_Equal:
		//pbequal->setOn(false);
		break;
		//	case Key_Return:
		//pbequal->setOn(false);
		break;
		//	case Key_Enter:
		//pbequal->setOn(false);
		break;
		//	case Key_Percent:
		key_pressed = false;
		//pbpercent->setOn(false);
		break;
		//	case Key_AsciiTilde:
		//pbnegate->setOn(false);
		break;
		//	case Key_Colon:
		//pbmod->setOn(false);
		break;
		//	case Key_BracketLeft:
		//pbsquare->setOn(false);
		break;
		//	case Key_Backspace:
		//pbAC->setOn(false);
		break;
	case WISP_VK_R:
		//pbreci->setOn(false);
		break;
	default:
		key_pressed = oldKey;
	}

	clear_buttons();
	return true;
}

//-------------------------------------------------------------------------
// Name: clear_buttons()
//-------------------------------------------------------------------------
void CWispCalcWnd::clear_buttons()
{
	//TODO: does this do anything?
}

//-------------------------------------------------------------------------
// Name: EEtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::EEtoggled(bool myboolean)
{
	if(!display_error)
	{
		if(myboolean)
			EE();		
	}
}

//-------------------------------------------------------------------------
// Name: pbinvtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbinvtoggled(bool myboolean)
{
	if(myboolean)
		SetInverse();
}

//-------------------------------------------------------------------------
// Name: pbhyptoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbhyptoggled(bool myboolean)
{
	if(myboolean)
		EnterHyp();	
}

//-------------------------------------------------------------------------
// Name: pbMRtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbMRtoggled(bool myboolean)
{
	if(myboolean)
		MR();	
}

//-------------------------------------------------------------------------
// Name: pbAtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbAtoggled(bool myboolean)
{
	if(myboolean)
		buttonA();	
}

//-------------------------------------------------------------------------
// Name: pbSintoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbRshtoggled(bool myboolean)
{
	if(myboolean)
		Rshift();
		//ExecSin();	
}

//-------------------------------------------------------------------------
// Name: pbplusminustoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbplusminustoggled(bool myboolean)
{
	if(myboolean)
		EnterNegate();	
}

//-------------------------------------------------------------------------
// Name: pbMplusminustoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbMplusminustoggled(bool myboolean)
{
	if(myboolean)
		Mplusminus();	
}

//-------------------------------------------------------------------------
// Name: pbBtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbBtoggled(bool myboolean)
{
	if(myboolean)
		buttonB();	
}

//-------------------------------------------------------------------------
// Name: pbCostoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbXortoggled(bool myboolean)
{
	if(myboolean)
		Xor();
}

//-------------------------------------------------------------------------
// Name: pbrecitoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbrecitoggled(bool myboolean)
{
	if(myboolean)
		EnterRecip();	
}

//-------------------------------------------------------------------------
// Name: pbCtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbCtoggled(bool myboolean)
{
	if(myboolean)
		buttonC();	
}

//-------------------------------------------------------------------------
// Name: pbTantoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbTantoggled(bool myboolean)
{
	if(myboolean)
		ExecTan();	
}

//-------------------------------------------------------------------------
// Name: pbfactorialtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbfactorialtoggled(bool myboolean)
{
	if(myboolean)
		EnterFactorial();	
}

//-------------------------------------------------------------------------
// Name: pbDtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbDtoggled(bool myboolean)
{
	if(myboolean)
		buttonD();	
}

//-------------------------------------------------------------------------
// Name: pblogtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pblogtoggled(bool myboolean)
{
	if(myboolean)
		EnterLogr();
}

//-------------------------------------------------------------------------
// Name: pbsquaretoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbsquaretoggled(bool myboolean)
{
	if(myboolean)
		EnterSquare();
}

//-------------------------------------------------------------------------
// Name: pbEtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbEtoggled(bool myboolean)
{
	if(!display_error)
	{
		if(myboolean)
			buttonE();
	}
}

//-------------------------------------------------------------------------
// Name: pblntoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pblntoggled(bool myboolean)
{
	if(myboolean)
		EnterLogn();	
}

//-------------------------------------------------------------------------
// Name: pbpowertoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbpowertoggled(bool myboolean)
{
	if(myboolean)
		Power();	
}

//-------------------------------------------------------------------------
// Name: pbFtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbFtoggled(bool myboolean)
{
	if(myboolean)
		buttonF();	
}

//-------------------------------------------------------------------------
// Name: pbMCtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbMCtoggled(bool myboolean)
{
	if(myboolean)
		MC();	
}

//-------------------------------------------------------------------------
// Name: pbCleartoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbCleartoggled(bool myboolean)
{
	if(myboolean)
		Clear();	
}

//-------------------------------------------------------------------------
// Name: pbACtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbACtoggled(bool myboolean)
{
	if(myboolean)
		ClearAll();	
}

//-------------------------------------------------------------------------
// Name: pb7toggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pb7toggled(bool myboolean)
{
	if(myboolean)
		button7();	
}

//-------------------------------------------------------------------------
// Name: pb8toggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pb8toggled(bool myboolean)
{
	if(myboolean)
		button8();	
}

//-------------------------------------------------------------------------
// Name: pb9toggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pb9toggled(bool myboolean)
{
	if(myboolean)
		button9();	
}

//-------------------------------------------------------------------------
// Name: pbparenopentoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbparenopentoggled(bool myboolean)
{
	if(myboolean)
		EnterOpenParen();	
}

//-------------------------------------------------------------------------
// Name: pbparenclosetoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbparenclosetoggled(bool myboolean)
{
	if(myboolean)
		EnterCloseParen();	
}

//-------------------------------------------------------------------------
// Name: pbandtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbandtoggled(bool myboolean)
{
	if(myboolean)
		And();	
}

//-------------------------------------------------------------------------
// Name: pb4toggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pb4toggled(bool myboolean)
{
	if(myboolean)
		button4();
}

//-------------------------------------------------------------------------
// Name: pb5toggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pb5toggled(bool myboolean)
{
	if(myboolean)
		button5();
}

//-------------------------------------------------------------------------
// Name: pb6toggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pb6toggled(bool myboolean)
{
	if(myboolean)
		button6();
}

//-------------------------------------------------------------------------
// Name: pbXtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbXtoggled(bool myboolean)
{
	if(myboolean)
		Multiply();
}

//-------------------------------------------------------------------------
// Name:
//-------------------------------------------------------------------------
void CWispCalcWnd::pbdivisiontoggled(bool myboolean)
{
	if(myboolean)
		Divide();
}

//-------------------------------------------------------------------------
// Name: pbortoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbortoggled(bool myboolean)
{
	if(myboolean)
		Or();
}

//-------------------------------------------------------------------------
// Name: pb1toggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pb1toggled(bool myboolean)
{
	if(myboolean)
		button1();
}

//-------------------------------------------------------------------------
// Name: pb2toggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pb2toggled(bool myboolean)
{
	if(myboolean)
		button2();
}

//-------------------------------------------------------------------------
// Name: pb3toggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pb3toggled(bool myboolean)
{
	if(myboolean)
		button3();
}

//-------------------------------------------------------------------------
// Name: pbplustoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbplustoggled(bool myboolean)
{
	if(myboolean)
		Plus();
}

//-------------------------------------------------------------------------
// Name: pbminustoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbminustoggled(bool myboolean)
{
	if(myboolean)
		Minus();
}

//-------------------------------------------------------------------------
// Name: pbshifttoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbshifttoggled(bool myboolean)
{
	if(myboolean)
		Shift();
}

//-------------------------------------------------------------------------
// Name: pbperiodtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbperiodtoggled(bool myboolean)
{
	//if(myboolean)
	//	EnterDecimal();
}

//-------------------------------------------------------------------------
// Name: pb0toggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pb0toggled(bool myboolean)
{
	if(myboolean)
		button0();
}

//-------------------------------------------------------------------------
// Name: pbequaltoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbequaltoggled(bool myboolean)
{
	if(myboolean)
		EnterEqual();
}

//-------------------------------------------------------------------------
// Name: pbpercenttoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbpercenttoggled(bool myboolean)
{
	if(myboolean)
		EnterPercent();
}

//-------------------------------------------------------------------------
// Name: pbnegatetoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbnegatetoggled(bool myboolean)
{
	if(myboolean)
		EnterNotCmp();

}

//-------------------------------------------------------------------------
// Name: pbmodtoggled(bool myboolean)
//-------------------------------------------------------------------------
void CWispCalcWnd::pbmodtoggled(bool myboolean)
{
	if(myboolean)
		Mod();

}

//-------------------------------------------------------------------------
// Name: set_style()
//-------------------------------------------------------------------------
void CWispCalcWnd::set_style()
{
	switch(kcalcdefaults.style)
	{
	case  0:
//		pbhyp->SetWindowText(WSTR("Hyp"));
		pbRsh->SetWindowText(WSTR("Rsh"));
		pbXor->SetWindowText(WSTR("Xor"));
//		pbTan->SetWindowText(WSTR("Tan"));		
//		pblog->SetWindowText(WSTR("Log"));		
//		pbln ->SetWindowText(WSTR("Ln"));		
		break;

	case 1:
//		pbhyp->SetWindowText(WSTR("N"));
		pbRsh->SetWindowText(WSTR("Mea"));
		pbXor->SetWindowText(WSTR("Xor"));		
//		pbTan->SetWindowText(WSTR("Med"));		
//		pblog->SetWindowText(WSTR("Dat"));		
//		pbln ->SetWindowText(WSTR("CSt"));				
		break;

	default:
		break;
	}

	//angle_group->setEnabled(kcalcdefaults.style == 0);
}

//-------------------------------------------------------------------------
// Name: readSettings()
//-------------------------------------------------------------------------
void CWispCalcWnd::readSettings()
{

#ifdef HAVE_LONG_DOUBLE
	kcalcdefaults.precision	= 14;
#else
	kcalcdefaults.precision	= 10;
#endif

	kcalcdefaults.fixedprecision =2;		
	kcalcdefaults.fixed = false;	
	kcalcdefaults.style	= 0;
	kcalcdefaults.beep	= true;
}

//-------------------------------------------------------------------------
// Name: writeSettings()
//-------------------------------------------------------------------------
void CWispCalcWnd::writeSettings()
{	
}


//-------------------------------------------------------------------------
// Name: set_precision()
//-------------------------------------------------------------------------
void CWispCalcWnd::set_precision()
{
	// TODO: make this do somthing!!
	UpdateDisplay();
}


//-------------------------------------------------------------------------
// Name: history_next()
//-------------------------------------------------------------------------
void CWispCalcWnd::history_next()
{
	if(history_list.Count()<=0 || (history_index <= 0))
	{
		return;
	}
	last_input = RECALL;
	DISPLAY_AMOUNT = *history_list[--history_index];
	UpdateDisplay();
}

//-------------------------------------------------------------------------
// Name: history_prev()
//-------------------------------------------------------------------------
void CWispCalcWnd::history_prev()
{
	if(history_list.Count() <=0 || history_index >= history_list.Count() - 1)
	{
		return;
	}

	last_input = RECALL;
	DISPLAY_AMOUNT = *history_list[++history_index];
	UpdateDisplay();
}


//-------------------------------------------------------------------------
// Name: button0()
//-------------------------------------------------------------------------
void CWispCalcWnd::button0()
{
	EnterDigit(0x0);
}

//-------------------------------------------------------------------------
// Name: button1()
//-------------------------------------------------------------------------
void CWispCalcWnd::button1()
{
	EnterDigit(0x1);
}

//-------------------------------------------------------------------------
// Name: button2()
//-------------------------------------------------------------------------
void CWispCalcWnd::button2()
{
	if (current_base != NB_BINARY)
		EnterDigit(0x2);
}

//-------------------------------------------------------------------------
// Name: button3()
//-------------------------------------------------------------------------
void CWispCalcWnd::button3()
{
	if (current_base != NB_BINARY)
		EnterDigit(0x3);
}

//-------------------------------------------------------------------------
// Name: button4()
//-------------------------------------------------------------------------
void CWispCalcWnd::button4()
{
	if (current_base != NB_BINARY)
		EnterDigit(0x4);
}

//-------------------------------------------------------------------------
// Name: button5()
//-------------------------------------------------------------------------
void CWispCalcWnd::button5()
{
	if (current_base != NB_BINARY)
		EnterDigit(0x5);
}

//-------------------------------------------------------------------------
// Name: button6()
//-------------------------------------------------------------------------
void CWispCalcWnd::button6()
{
	if (current_base != NB_BINARY)
		EnterDigit(0x6);
}

//-------------------------------------------------------------------------
// Name: button7()
//-------------------------------------------------------------------------
void CWispCalcWnd::button7()
{
	if (current_base != NB_BINARY)
		EnterDigit(0x7);
}

//-------------------------------------------------------------------------
// Name: button8()
//-------------------------------------------------------------------------
void CWispCalcWnd::button8()
{
	if ((current_base != NB_BINARY) && (current_base != NB_OCTAL))
		EnterDigit(0x8);
}

//-------------------------------------------------------------------------
// Name: button9()
//-------------------------------------------------------------------------
void CWispCalcWnd::button9()
{
	if ((current_base != NB_BINARY) && (current_base != NB_OCTAL))
		EnterDigit(0x9);
}

//-------------------------------------------------------------------------
// Name: buttonA()
//-------------------------------------------------------------------------
void CWispCalcWnd::buttonA()
{
	if ((current_base != NB_BINARY) && (current_base != NB_OCTAL) &&
		(current_base != NB_DECIMAL))
		EnterDigit(0xA);
}

//-------------------------------------------------------------------------
// Name: buttonB()
//-------------------------------------------------------------------------
void CWispCalcWnd::buttonB()
{
	if ((current_base != NB_BINARY) && (current_base != NB_OCTAL) &&
		(current_base != NB_DECIMAL))
		EnterDigit(0xB);
}

//-------------------------------------------------------------------------
// Name: buttonC()
//-------------------------------------------------------------------------
void CWispCalcWnd::buttonC()
{
	if ((current_base != NB_BINARY) && (current_base != NB_OCTAL) &&
		(current_base != NB_DECIMAL))
		EnterDigit(0xC);
}

//-------------------------------------------------------------------------
// Name: buttonD()
//-------------------------------------------------------------------------
void CWispCalcWnd::buttonD()
{
	if ((current_base != NB_BINARY) && (current_base != NB_OCTAL) &&
		(current_base != NB_DECIMAL))
		EnterDigit(0xD);
}

//-------------------------------------------------------------------------
// Name: buttonE()
//-------------------------------------------------------------------------
void CWispCalcWnd::buttonE()
{
	if ((current_base != NB_BINARY) && (current_base != NB_OCTAL) &&
		(current_base != NB_DECIMAL))
		EnterDigit(0xE);
}

//-------------------------------------------------------------------------
// Name: buttonF()
//-------------------------------------------------------------------------
void CWispCalcWnd::buttonF()
{
	if ((current_base != NB_BINARY) && (current_base != NB_OCTAL) &&
		(current_base != NB_DECIMAL))
		EnterDigit(0xF);
}

//-------------------------------------------------------------------------
// Name: InitializeCalculator()
//-------------------------------------------------------------------------
void CWispCalcWnd::InitializeCalculator()
{
	//
	// Basic initialization involves initializing the calcultion
	// stack, forcing the display to refresh to zero, and setting
	// up the floating point excetion signal handler to trap the
	// errors that the code can/has not been written to trap.
	//
	display_data.s_item_type = ITEM_AMOUNT;
	display_data.s_item_data.item_amount = 0;
	display_data.s_item_data.item_func_data.item_function = 0;
	display_data.s_item_data.item_func_data.item_precedence = 0;
	RefreshCalculator();

}


//-------------------------------------------------------------------------
// Name: (int fpe_parm)
//-------------------------------------------------------------------------



//-------------------------------------------------------------------------
// Name: RefreshCalculator()
//-------------------------------------------------------------------------
void CWispCalcWnd::RefreshCalculator()
{
	InitStack();
	display_error = false;
	DISPLAY_AMOUNT = 0L;
	inverse = false;
	decimal_point = 0;
	input_count = 0;
	UpdateDisplay();
	last_input = DIGIT; // must set last to DIGIT after Update Display in order
	// not to get a display holding e.g. 0.000
}

//-------------------------------------------------------------------------
// Name: EnterDigit(int data)
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterDigit(int data)
{	

	last_input = DIGIT;

	if (refresh_display) {
		DISPLAY_AMOUNT = 0L;
		decimal_point = 0;
		refresh_display = false;
		input_count = 0;
	}

	if (!(input_limit && input_count >= input_limit)) {
		if (DISPLAY_AMOUNT < 0) {
			DISPLAY_AMOUNT =(current_base * DISPLAY_AMOUNT) - data;
		} else {
			DISPLAY_AMOUNT =(current_base * DISPLAY_AMOUNT) + data;
		}
	}

	if (decimal_point) {
		input_count ++;
	}

	UpdateDisplay();
}
//-------------------------------------------------------------------------
// Name: SubtractDigit()
//-------------------------------------------------------------------------
void CWispCalcWnd::SubtractDigit()
{
	// This function could be better, possibly, but am I glad to see it!
	
	
}

//-------------------------------------------------------------------------
// Name: EnterDecimal()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterDecimal()
{
	// exit if we aren't in decimla mode
	if (current_base != NB_DECIMAL)
		return;
	
	if (refresh_display)
	{
		DISPLAY_AMOUNT = 0L;
		refresh_display = false;
		input_count = 0;
	}

	if(last_input == DIGIT)
	{
		if (decimal_point==0)  //strpbrk() doesn't work in fixed precision mode
		{
			// if the last input was a DIGIT and we don't
			// have already a period in our
			// display string then display a period
			if (strlen(display_str) >= DSP_SIZE)
				return;

			if (!kcalcdefaults.fixed)
				strcat(display_str, ".");
			decimal_point = 1;
		}
	}
	else
	{
		// the last input wasn't a DIGIT so we are about to
		// input a new number in particular we need to display a "0.".

		if (decimal_point==0)  //strpbrk() doesn't work in fixed precision mode
		{

			DISPLAY_AMOUNT = 0L;
			refresh_display = false;
			decimal_point = 1;

			if (!kcalcdefaults.fixed)
				strcpy(display_str, "0.");			
		}
	}
}

//-------------------------------------------------------------------------
// Name: Or()
//-------------------------------------------------------------------------
void CWispCalcWnd::Or()
{	
	
	EnterStackFunction(1);   // OR
	last_input = OPERATION;
}
void CWispCalcWnd::Xor()
{
	EnterStackFunction(2);   // XOR
	last_input = OPERATION;
}

//-------------------------------------------------------------------------
// Name: And()
//-------------------------------------------------------------------------
void CWispCalcWnd::And()
{	
	last_input = OPERATION;
	EnterStackFunction(3);
}


//-------------------------------------------------------------------------
// Name: Shift()
//-------------------------------------------------------------------------
void CWispCalcWnd::Shift()
{	
	last_input = OPERATION;
	if (inverse)
	{
		EnterStackFunction(5);   // Rsh
		inverse = false;
	}
	else
		EnterStackFunction(4);   // Lsh
}
void CWispCalcWnd::Lshift()
{
	last_input = OPERATION;
	EnterStackFunction(4);   // Lsh
}
void CWispCalcWnd::Rshift()
{
	last_input = OPERATION;
	EnterStackFunction(5);   // Rsh
}
//-------------------------------------------------------------------------
// Name: Plus()
//-------------------------------------------------------------------------
void CWispCalcWnd::Plus()
{	
	last_input = OPERATION;
	EnterStackFunction(6);
}

//-------------------------------------------------------------------------
// Name: Minus()
//-------------------------------------------------------------------------
void CWispCalcWnd::Minus()
{	
	last_input = OPERATION;
	EnterStackFunction(7);
}

//-------------------------------------------------------------------------
// Name: Multiply()
//-------------------------------------------------------------------------
void CWispCalcWnd::Multiply()
{	
	last_input = OPERATION;
	EnterStackFunction(8);
}

//-------------------------------------------------------------------------
// Name: Divide()
//-------------------------------------------------------------------------
void CWispCalcWnd::Divide()
{	
	last_input = OPERATION;
	EnterStackFunction(9);
}

//-------------------------------------------------------------------------
// Name: Mod()
//-------------------------------------------------------------------------
void CWispCalcWnd::Mod()
{	
	last_input = OPERATION;
	if (inverse)
	{
		EnterStackFunction(13);   // InvMod
		inverse = false;
	}
	else
	{
		EnterStackFunction(10);   // Mod
	}
}

//-------------------------------------------------------------------------
// Name: Power()
//-------------------------------------------------------------------------
void CWispCalcWnd::Power()
{	
	last_input = OPERATION;
	if (inverse)
	{
		EnterStackFunction(12);   // InvPower
		inverse = false;
	}
	else
	{
		EnterStackFunction(11);   // Power
	}
}


//-------------------------------------------------------------------------
// Name: EnterStackFunction(int data)
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterStackFunction(int data)
{
	item_contents 	new_item;
	int new_precedence;
	int dummy = 0;



	data = adjust_op[data][dummy];

	PushStack(&display_data);

	new_item.s_item_type = ITEM_FUNCTION;
	new_item.s_item_data.item_func_data.item_function = data;
	new_item.s_item_data.item_func_data.item_precedence =
	new_precedence = precedence[data] + precedence_base;

	refresh_display = true;
	if (UpdateStack(new_precedence)) {
		UpdateDisplay();
	}

	PushStack(&new_item);
}

//-------------------------------------------------------------------------
// Name: EnterNegate()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterNegate()
{
	
	{		
		if (DISPLAY_AMOUNT != 0)
		{
			DISPLAY_AMOUNT *= -1;
			UpdateDisplay();
		}
	}

	last_input = DIGIT;
}

//-------------------------------------------------------------------------
// Name: EnterOpenParen()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterOpenParen()
{
	
	last_input = OPERATION;
	precedence_base += PRECEDENCE_INCR;
	refresh_display = true;
}

//-------------------------------------------------------------------------
// Name: EnterCloseParen()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterCloseParen()
{
	
	last_input = OPERATION;
	PushStack(&display_data);
	refresh_display = true;

	if (UpdateStack(precedence_base))
		UpdateDisplay();

	if ((precedence_base -= PRECEDENCE_INCR) < 0)
		precedence_base = 0;
}

//-------------------------------------------------------------------------
// Name: EnterRecip()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterRecip()
{
	/*
	last_input = OPERATION;
	DISPLAY_AMOUNT = 1 / DISPLAY_AMOUNT;
	refresh_display = true;
	UpdateDisplay();
	*/
}

//-------------------------------------------------------------------------
// Name: EnterInt()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterInt()
{
	
	CALCAMNT work_amount1 = 0;
	CALCAMNT work_amount2 = 0;

	last_input = OPERATION;

	if (!inverse)
	{
		work_amount2 = 0;//MODF(DISPLAY_AMOUNT, &work_amount1);
		DISPLAY_AMOUNT = work_amount2 ;
	}
	else
	{
		DISPLAY_AMOUNT = work_amount1;
		inverse = false;
	}

	refresh_display = true;
	UpdateDisplay();

}

//-------------------------------------------------------------------------
// Name: EnterFactorial()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterFactorial()
{
	
	CALCAMNT work_amount1;
	CALCAMNT work_amount2;
	int incr;

	//MODF(DISPLAY_AMOUNT, &work_amount1);
	work_amount1 = DISPLAY_AMOUNT;
	incr = work_amount1 < 0 ? -1 : 1;

	work_amount2 = work_amount1 - incr;

	while (work_amount1 != 0 && work_amount2 != 0 && !display_error)
	{
		work_amount1 *= work_amount2;
		work_amount2 -= incr;		
	}

	if(work_amount1 == 0)
		work_amount1 = 1;

	DISPLAY_AMOUNT = work_amount1;
	refresh_display = true;
	last_input = OPERATION;
	UpdateDisplay();
}

//-------------------------------------------------------------------------
// Name: EnterSquare()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterSquare()
{
	
	
	DISPLAY_AMOUNT *= DISPLAY_AMOUNT;
	

	refresh_display = true;
	inverse = false;
	last_input = OPERATION;
	UpdateDisplay();
	

}

//-------------------------------------------------------------------------
// Name: EnterNotCmp()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterNotCmp()
{
	
	CALCAMNT boh_work_d;
	KCALC_LONG boh_work;

	//MODF(DISPLAY_AMOUNT, &boh_work_d);
	boh_work_d = DISPLAY_AMOUNT;
	if (ABS(boh_work_d) > KCALC_LONG_MAX)
		display_error = true;
	else
	{
		boh_work = (KCALC_LONG)boh_work_d;
		DISPLAY_AMOUNT = ~boh_work;
	}

	refresh_display = true;
	last_input = OPERATION;
	UpdateDisplay();
}

//-------------------------------------------------------------------------
// Name: EnterHyp()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterHyp()
{
	
}

//-------------------------------------------------------------------------
// Name: ExecSin()
//-------------------------------------------------------------------------
void CWispCalcWnd::ExecSin()
{
	
}

//-------------------------------------------------------------------------
// Name: ComputeMean()
//-------------------------------------------------------------------------
void CWispCalcWnd::ComputeMean()
{
	
}

//-------------------------------------------------------------------------
// Name: ComputeSin()
//-------------------------------------------------------------------------
void CWispCalcWnd::ComputeSin()
{
}

//-------------------------------------------------------------------------
// Name: ExecCos()
//-------------------------------------------------------------------------
void CWispCalcWnd::ExecCos()
{
	
}

//-------------------------------------------------------------------------
// Name: ComputeStd()
//-------------------------------------------------------------------------
void CWispCalcWnd::ComputeStd()
{
	
}

//-------------------------------------------------------------------------
// Name: ComputeCos()
//-------------------------------------------------------------------------
void CWispCalcWnd::ComputeCos()
{

}

//-------------------------------------------------------------------------
// Name: ComputeMedean()
//-------------------------------------------------------------------------
void CWispCalcWnd::ComputeMedean()
{
	
}

//-------------------------------------------------------------------------
// Name: ComputeTan()
//-------------------------------------------------------------------------
void CWispCalcWnd::ComputeTan()
{
}

//-------------------------------------------------------------------------
// Name: ExecTan()
//-------------------------------------------------------------------------
void CWispCalcWnd::ExecTan()
{
	
}

//-------------------------------------------------------------------------
// Name: EnterPercent()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterPercent()
{
	
	last_input		= OPERATION;
	percent_mode	= true;
	EnterEqual();
	percent_mode	= false;

}

//-------------------------------------------------------------------------
// Name: EnterLogr()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterLogr()
{
}

//-------------------------------------------------------------------------
// Name: EnterLogn()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterLogn()
{	
}

//-------------------------------------------------------------------------
// Name: base_selected(int number)
//-------------------------------------------------------------------------
void CWispCalcWnd::base_selected(int number)
{
	switch(number)
	{
	case 0:
		current_base	= NB_HEX;
		display_size	= HEX_SIZE;
		decimal_point	= 0;
		input_limit		= sizeof(KCALC_LONG)*2;
		break;
	case 1:
		current_base	= NB_DECIMAL;
		display_size	= DEC_SIZE;
		input_limit		= 0;
		break;
	case 2:
		current_base	= NB_OCTAL;
		display_size	= OCT_SIZE;
		decimal_point	= 0;
		input_limit		= 11;
		break;
	case 3:
		current_base	= NB_BINARY;
		display_size	= BIN_SIZE;
		decimal_point	= 0;
		input_limit		= 32;
		break;
	default: // we shouldn't ever end up here
		current_base	= NB_DECIMAL;
		display_size	= DEC_SIZE;
		input_limit		= 0;
	}

	UpdateDisplay();
}


//-------------------------------------------------------------------------
// Name: angle_selected(int number)
//-------------------------------------------------------------------------
void CWispCalcWnd::angle_selected(int number)
{
	switch(number)
	{
	case 0:
		m_NumberBitWdith = ANG_DEGREE;
		break;
	case 1:
		m_NumberBitWdith = ANG_RADIAN;
		break;
	case 2:
		m_NumberBitWdith = ANG_GRADIENT;
		break;
	case 3:
		m_NumberBitWdith=ANG_RADIAN;
	default: // we shouldn't ever end up here
		m_NumberBitWdith = ANG_RADIAN;
	}
}

//-------------------------------------------------------------------------
// Name: SetInverse()
//-------------------------------------------------------------------------
void CWispCalcWnd::SetInverse()
{
	inverse = ! inverse;
}

//-------------------------------------------------------------------------
// Name: EE()
//-------------------------------------------------------------------------
void CWispCalcWnd::EE()
{

}

//-------------------------------------------------------------------------
// Name: MR()
//-------------------------------------------------------------------------
void CWispCalcWnd::MR()
{
	
	last_input		= OPERATION;
	DISPLAY_AMOUNT	= memory_num;
	refresh_display	= true;

	UpdateDisplay();

}

//-------------------------------------------------------------------------
// Name: Mplusminus()
//-------------------------------------------------------------------------
void CWispCalcWnd::Mplusminus()
{
	
	EnterEqual();

	if (!inverse)	memory_num += DISPLAY_AMOUNT;
	else 			memory_num -= DISPLAY_AMOUNT;

	inverse = false;
}

//-------------------------------------------------------------------------
// Name: MC()
//-------------------------------------------------------------------------
void CWispCalcWnd::MC()
{
	memory_num		= 0;
	refresh_display	= true;
}

//-------------------------------------------------------------------------
// Name: EnterEqual()
//-------------------------------------------------------------------------
void CWispCalcWnd::EnterEqual()
{
	
	last_input	= OPERATION;

	PushStack(&display_data);

	refresh_display = true;

	//if (UpdateStack(0))
	UpdateStack(0);

	UpdateDisplay();
	precedence_base = 0;

	// add this latest value to our history
	history_list.InsertBefore(history_list.Begin(), DISPLAY_AMOUNT);
}

//-------------------------------------------------------------------------
// Name: Clear()
//-------------------------------------------------------------------------
void CWispCalcWnd::Clear()
{

	
	input_count		= 0;
	decimal_point	= 0;


	if (last_input == OPERATION)
	{
		PopStack();
		last_input = DIGIT;
	}

	if(display_error)
	{
		display_error	= false;
		refresh_display	= false;
	}

	if (!refresh_display)
	{
		DISPLAY_AMOUNT = 0L;
		UpdateDisplay();
	}

	//RefreshCalculator();
}

//-------------------------------------------------------------------------
// Name: ClearAll()
//-------------------------------------------------------------------------
void CWispCalcWnd::ClearAll()
{
	

	// last_input = OPERATION;
	last_input = DIGIT;

	RefreshCalculator();
	refresh_display = true;
}


//-------------------------------------------------------------------------
// Name: UpdateDisplay()
//-------------------------------------------------------------------------
void CWispCalcWnd::UpdateDisplay()
{;
	// this needs to be rewritten based on whether we are currently
	// inputting a number so that the period and the 0 after a period
	// are correctly displayed.

	CALCAMNT	boh_work_d;
	KCALC_LONG	boh_work = 0;
	int		str_size = 0;
	
	if (current_base != NB_DECIMAL)
	{
		//MODF(DISPLAY_AMOUNT, &boh_work_d);		
		//
		int mm=100;
		boh_work_d = DISPLAY_AMOUNT;
		//KCALC_LONG tmpminlong = KCALC_LONG_MIN;
#ifdef CODE_OS_UNIX
		KCALC_LONG tmpminlong = (-9223372036854775807LL - 1);
		KCALC_LONG tmpmaxlong = 0xffffffffffffffffULL;
if(boh_work_d<(-9223372036854775807LL - 1))
			mm-=100;
		if(boh_work_d>0xffffffffffffffffULL)
			mm+=100;

#else
		KCALC_LONG tmpminlong = (-9223372036854775807i64 - 1);
		KCALC_LONG tmpmaxlong = 0xffffffffffffffffui64;
		if(boh_work_d<(-9223372036854775807i64 - 1))
			mm-=100;
		if(boh_work_d>0xffffffffffffffffui64)
			mm+=100;

#endif
		//KCALC_LONG tmpmaxlong = KCALC_ULONG_MAX;

		if(boh_work_d	< tmpminlong ||boh_work_d > KCALC_ULONG_MAX)
		{
			display_error = true;
		
		//
		// We may be in that never-never land where boh numbers
		// turn from positive to negative - if so then we do
		// just that, allowing boh negative numbers to be entered
		// as read (from dumps and the like!)
		//
		}
		else if (boh_work_d > KCALC_LONG_MAX)
		{
			DISPLAY_AMOUNT = KCALC_LONG_MIN + (boh_work_d - KCALC_LONG_MAX - 1);
			boh_work = (KCALC_LONG)DISPLAY_AMOUNT;
		}
		else
		{
			DISPLAY_AMOUNT = boh_work_d;
			boh_work = (KCALC_LONG)boh_work_d;
		}
	}

	if (!display_error)
	{
		switch(current_base)
		{
		case NB_BINARY:
			str_size = cvb(display_str, boh_work, BIN_SIZE);
			break;

		case NB_OCTAL:
			str_size = sprintf(display_str, PRINT_OCTAL, boh_work);
			break;

		case NB_HEX:
			str_size = sprintf(display_str, PRINT_HEX, boh_work);
			break;

		case NB_DECIMAL:
			if (kcalcdefaults.fixed) {
				str_size = sprintf(display_str, 
					PRINT_FLOAT,					
					DISPLAY_AMOUNT);
			} else if(last_input == DIGIT) {
			
				str_size = sprintf(display_str, 
					PRINT_LONG_BIG,					
					DISPLAY_AMOUNT);
			} else {
				str_size = sprintf(display_str,  PRINT_LONG, DISPLAY_AMOUNT);
			}

			if (input_count > 0 &&last_input == DIGIT )
			{
				str_size = sprintf(display_str, 
					PRINT_FLOAT,			
			  DISPLAY_AMOUNT);
			}
			break;

		default:
			display_error = true;
			break;
		}
	}
	if (display_error || str_size < 0)
	{
		display_error = true;
	}
	Update();
}

//-------------------------------------------------------------------------
// Name: cvb(char *out_str, KCALC_LONG amount, int max_digits)
//-------------------------------------------------------------------------
int CWispCalcWnd::cvb(char *out_str, KCALC_LONG amount, int max_digits)
{
	/*
	* A routine that converts a long int to
	* binary display format
	*/

	char *strPtr	= out_str;
	bool hitOne		= false;
	unsigned KCALC_LONG bit_mask =
		((unsigned KCALC_LONG) 1 << (BIN_SIZE - 1));
	unsigned KCALC_LONG bit_mask_mask = bit_mask - 1;
	unsigned int count = 0 ;

	while(bit_mask != 0 && max_digits > 0)
	{
		char tmp = (bit_mask & amount) ? '1' : '0';

		if (hitOne && (count%4==0))
			*strPtr++ = ' ';
		count++;

		if(!hitOne && tmp == '1')
			hitOne = true;

		if(hitOne)
			*strPtr++ = tmp;

		bit_mask >>= 1;

		// this will fix a prob with some processors using an
		// arithmetic right shift (which would maintain sign on
		// negative numbers and cause a loop that's too long)
		bit_mask &= bit_mask_mask; //Sven: Uwe's Alpha adition

		max_digits--;
	}

	if(amount == 0)
		*strPtr++ = '0';

	*strPtr = '\0';

	return (int)strlen(out_str);
}

//-------------------------------------------------------------------------
// Name: UpdateStack(int run_precedence)
//-------------------------------------------------------------------------
int CWispCalcWnd::UpdateStack(int run_precedence)
{
	item_contents new_item;
	item_contents *top_item;
	item_contents *top_function;

	CALCAMNT left_op	= 0;
	CALCAMNT right_op 	= 0;
	int op_function		= 0;
	int return_value	= 0;

	new_item.s_item_type = ITEM_AMOUNT;

	while ((top_function = TopTypeStack(ITEM_FUNCTION)) &&
		top_function->s_item_data.item_func_data.item_precedence >=
		run_precedence)
	{
		return_value = 1;
		top_item = PopStack();
		right_op = top_item->s_item_data.item_amount;
		top_item = PopStack();
		op_function = top_item->s_item_data.item_func_data.item_function;
		top_item = PopStack();
		left_op = top_item->s_item_data.item_amount;

		if ( ! percent_mode || Prcnt_ops[op_function] == NULL )
		{
			new_item.s_item_data.item_amount =
				(Arith_ops[op_function])(left_op, right_op);
		}
		else
		{
			new_item.s_item_data.item_amount =
				(Prcnt_ops[op_function])(left_op, right_op);
			percent_mode = false;
		};

		PushStack(&new_item);
	}

	if (return_value)
		DISPLAY_AMOUNT = new_item.s_item_data.item_amount;

	decimal_point=1;
	return return_value;
}

//-------------------------------------------------------------------------
// Name: isoddint(CALCAMNT input)
//-------------------------------------------------------------------------
int isoddint(CALCAMNT input)
{
	return (input % 2)==1;
}

//-------------------------------------------------------------------------
// Name: ExecOr(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecOr(CALCAMNT left_op, CALCAMNT right_op)
{
	// printf("ExecOr\n");
	CALCAMNT	boh_work_d;
	KCALC_LONG	boh_work_l;
	KCALC_LONG	boh_work_r;

	//MODF(left_op, &boh_work_d);
	boh_work_d = left_op;
	if (ABS(boh_work_d) > KCALC_LONG_MAX)
	{
		display_error = true;
		return 0;
	}

	boh_work_l = (KCALC_LONG)boh_work_d;
	//MODF(right_op, &boh_work_d);
	boh_work_d = right_op;
	if (ABS(boh_work_d) > KCALC_LONG_MAX)
	{
		display_error = true;
		return 0;
	}

	boh_work_r = (KCALC_LONG) boh_work_d;
	return (boh_work_l | boh_work_r);
}

//-------------------------------------------------------------------------
// Name: ExecXor(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecXor(CALCAMNT left_op, CALCAMNT right_op)
{
	// printf("ExecXOr\n");
	CALCAMNT	boh_work_d;
	KCALC_LONG	boh_work_l;
	KCALC_LONG	boh_work_r;

	//MODF(left_op, &boh_work_d);
	boh_work_d = left_op;
	if (ABS(boh_work_d) > KCALC_LONG_MAX)
	{
		display_error = true;
		return 0;
	}

	boh_work_l = (KCALC_LONG)boh_work_d;
	//MODF(right_op, &boh_work_d);
	boh_work_d=right_op;
	if (ABS(boh_work_d) > KCALC_LONG_MAX)
	{
		display_error = true;
		return 0;
	}

	boh_work_r = (KCALC_LONG)boh_work_d;
	return (boh_work_l ^ boh_work_r);
}

//-------------------------------------------------------------------------
// Name: ExecAnd(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecAnd(CALCAMNT left_op, CALCAMNT right_op)
{
	// printf("ExecAnd\n");
	CALCAMNT	boh_work_d;
	KCALC_LONG	boh_work_l;
	KCALC_LONG	boh_work_r;

	//MODF(left_op, &boh_work_d);
	boh_work_d=left_op;
	if (ABS(boh_work_d) > KCALC_LONG_MAX)
	{
		display_error = true;
		return 0;
	}

	boh_work_l = (KCALC_LONG)boh_work_d;
	//MODF(right_op, &boh_work_d);
	boh_work_d=right_op;
	if (ABS(boh_work_d) > KCALC_LONG_MAX)
	{
		display_error = true;
		return 0;
	}

	boh_work_r = (KCALC_LONG)boh_work_d;
	return (boh_work_l & boh_work_r);
}

//-------------------------------------------------------------------------
// Name: ExecLsh(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecLsh(CALCAMNT left_op, CALCAMNT right_op)
{
	// printf("ExecLsh\n");
	CALCAMNT	boh_work_d;
	KCALC_LONG	boh_work_l;
	KCALC_LONG	boh_work_r;

	//MODF(left_op, &boh_work_d);
	boh_work_d=left_op;
	if (ABS(boh_work_d) > KCALC_LONG_MAX)
	{
		display_error = true;
		return 0;
	}

	boh_work_l = (KCALC_LONG) boh_work_d;
	//MODF(right_op, &boh_work_d);
	boh_work_d=right_op;
	if (ABS(boh_work_d) > KCALC_LONG_MAX)
	{
		display_error = true;
		return 0;
	}

	boh_work_r = (KCALC_LONG) boh_work_d;
	return (boh_work_l << boh_work_r);
}

//-------------------------------------------------------------------------
// Name: ExecRsh(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecRsh(CALCAMNT left_op, CALCAMNT right_op)
{
	// printf("ExecRsh\n");
	CALCAMNT	boh_work_d;
	KCALC_LONG	boh_work_l;
	KCALC_LONG	boh_work_r;

	//MODF(left_op, &boh_work_d);
	boh_work_d=left_op;
	if (ABS(boh_work_d) > KCALC_LONG_MAX)
	{
		display_error = true;
		return 0;
	}

	boh_work_l = (KCALC_LONG)boh_work_d;
	//MODF(right_op, &boh_work_d);
	boh_work_d=right_op;
	if (ABS(boh_work_d) > KCALC_LONG_MAX)
	{
		display_error = true;
		return 0;
	}

	boh_work_r = (KCALC_LONG)boh_work_d;
	return (boh_work_l >> boh_work_r);
}

//-------------------------------------------------------------------------
// Name: ExecAdd(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecAdd(CALCAMNT left_op, CALCAMNT right_op)
{	
	return left_op + right_op;
}

//-------------------------------------------------------------------------
// Name: ExecSubtract(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecSubtract(CALCAMNT left_op, CALCAMNT right_op)
{
	// printf("ExecSubtract\n");
	return left_op - right_op;
}

//-------------------------------------------------------------------------
// Name: ExecMultiply(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecMultiply(CALCAMNT left_op, CALCAMNT right_op)
{
	// printf("ExecMulti\n");
	return left_op * right_op;
}

//-------------------------------------------------------------------------
// Name: ExecMod(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecDivide(CALCAMNT left_op, CALCAMNT right_op)
{
	// printf("ExecDivide\n");
	if (right_op == 0)
	{
		display_error = true;
		return 0L;
	}
	else
		return left_op / right_op;
}

//-------------------------------------------------------------------------
// Name: QExecMod(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecMod(CALCAMNT left_op, CALCAMNT right_op)
{
	// printf("ExecMod\n");
	CALCAMNT temp = 0;

	if (right_op == 0)
	{
		display_error = true;
		return 0L;
	}
	else
	{
		// x mod y should be the same as x mod -y, thus:
		right_op = ABS(right_op);
		
		temp = left_op%right_op;//FMOD(left_op, right_op);
 
		// let's make sure that -7 mod 3 = 2 and NOT -1.
		// In other words we wand x mod 3 to be a _positive_ number
		// that is 0,1 or 2.
		if( temp < 0 )
			temp = right_op + temp;

		return ABS(temp);
	}
}

//-------------------------------------------------------------------------
// Name: ExecIntDiv(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecIntDiv(CALCAMNT left_op, CALCAMNT right_op)
{
	// printf("IndDiv\n");
	if (right_op == 0)
	{
		display_error = true;
		return 0L;
	}
	else
	{
		//MODF(left_op / right_op, &left_op);
		left_op=left_op / right_op;
		return left_op;
	}
}

//-------------------------------------------------------------------------
// Name: ExecPower(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecPower(CALCAMNT left_op, CALCAMNT right_op)
{
	int i;
	CALCAMNT ret;
	ret = left_op;
	if (right_op == 0)
		return 1L;
	for(i = 1; i < right_op;i++)
		ret = ret * left_op;
	if (left_op < 0 && isoddint(right_op))
		left_op = -1 * left_op;
	

		return ret;
}

//-------------------------------------------------------------------------
// Name: ExecPwrRoot(CALCAMNT left_op, CALCAMNT right_op)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecPwrRoot(CALCAMNT left_op, CALCAMNT right_op)
{
		return left_op;
}

//-------------------------------------------------------------------------
// Name: ExecAddSubP(CALCAMNT left_op, CALCAMNT right_op, CALCAMNT result)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecAddP(CALCAMNT left_op, CALCAMNT right_op)
{
	return (left_op + left_op * right_op/100 );
}

//-------------------------------------------------------------------------
// Name: ExecAddSubP(CALCAMNT left_op, CALCAMNT right_op, CALCAMNT result)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecSubP(CALCAMNT left_op, CALCAMNT right_op)
{
	return (left_op - left_op * right_op/100 );
}

//-------------------------------------------------------------------------
// Name: ExecMultiplyP(CALCAMNT left_op, CALCAMNT right_op, CALCAMNT result)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecMultiplyP(CALCAMNT left_op, CALCAMNT right_op)
{
	return left_op*right_op/100;
}

//-------------------------------------------------------------------------
// Name: ExecPowerP(CALCAMNT left_op, CALCAMNT right_op, CALCAMNT result)
//-------------------------------------------------------------------------
CALCAMNT CWispCalcWnd::ExecDivideP(CALCAMNT left_op, CALCAMNT right_op)
{
	return left_op*100/right_op;
}

//-------------------------------------------------------------------------
// Name: AllocStackItem()
//-------------------------------------------------------------------------
stack_ptr AllocStackItem()
{
	CODE_ASSERT(stack_next <= stack_last);
	process_stack[stack_next].prior_item = NULL;
	process_stack[stack_next].prior_type = NULL;
	return (process_stack + (stack_next++));
}

//-------------------------------------------------------------------------
// Name: UnAllocStackItem(stack_ptr return_item)
//-------------------------------------------------------------------------
void UnAllocStackItem(stack_ptr return_item)
{
	if (return_item != (process_stack + (--stack_next))) {
		CODE_ASSERT(false); // stack error
	}
}

//-------------------------------------------------------------------------
// Name: PushStack(item_contents *add_item)
//-------------------------------------------------------------------------
void PushStack(item_contents *add_item)
{
	// Add an item to the stack

	stack_ptr new_item = top_of_stack;

	if (!(new_item &&
		new_item->item_value.s_item_type == add_item->s_item_type))
	{
		new_item = AllocStackItem();	// Get a new item

		// Chain new item to existing stacks


		new_item->prior_item = top_of_stack;
		top_of_stack	     = new_item;
		new_item->prior_type = top_type_stack[add_item->s_item_type];
		top_type_stack[add_item->s_item_type] = new_item;
	}

	new_item->item_value  = *add_item;	// assign contents

}

//-------------------------------------------------------------------------
// Name: PopStack()
//-------------------------------------------------------------------------
item_contents *PopStack()
{
	// Remove and return the top item in the stack

	static item_contents return_item;

	item_contents *return_item_ptr = NULL;
	stack_ptr return_stack_ptr;

	if ((return_stack_ptr = top_of_stack))
	{
		return_item = top_of_stack->item_value;

		top_type_stack[return_item.s_item_type] =
			top_of_stack->prior_type;

		top_of_stack = top_of_stack->prior_item;

		UnAllocStackItem(return_stack_ptr);

		return_item_ptr = &return_item;
	}

	return return_item_ptr;
}

//-------------------------------------------------------------------------
// Name: TopTypeStack(item_type rqstd_type)
//-------------------------------------------------------------------------
item_contents *TopTypeStack(item_type rqstd_type)
{
	// Return the top item in the stack without removing

	item_contents *return_item_ptr = NULL;

	if (top_type_stack[rqstd_type])
		return_item_ptr = &(top_type_stack[rqstd_type]->item_value);

	return return_item_ptr;
}


/*
* Stack storage management Data and Functions
*/

//-------------------------------------------------------------------------
// Name: InitStack()
//-------------------------------------------------------------------------
void InitStack()
{
	stack_next = 0;
	stack_last = STACK_SIZE - 1;
	top_of_stack = top_type_stack[0] = top_type_stack[1] = NULL;
}
