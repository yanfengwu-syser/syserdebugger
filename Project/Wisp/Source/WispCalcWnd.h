#ifndef _WISPCALCWND_H_
#define _WISPCALCWND_H_
#include "WispDefine.h"
#include "WispMsgDefine.h"
#include "WispButton.h"
#include "WispRadioBox.h"


#ifndef CODE_OS_UNIX 
	#define _I64_MIN    (-9223372036854775807i64 - 1)
	#define _I64_MAX      9223372036854775807i64
	#define _UI64_MAX     0xffffffffffffffffui64
	typedef __int64 CALCAMNT;
	#define KCALC_LONG_MIN	_I64_MIN
	#define KCALC_LONG_MAX	_I64_MAX
	#define KCALC_ULONG_MAX	_UI64_MAX
	#define KCALC_LONG	__int64 
	#define HAVE_LONG_LONG
	#define HAVE_LONG_DOUBLE
#else

	#define LONG_MIN    (-2147483647L - 1)
	#define LONG_MAX      2147483647L
	#define ULONG_MAX     0xffffffffUL
	typedef long CALCAMNT;
	#define KCALC_LONG_MIN	LONG_MIN
	#define KCALC_LONG_MAX	LONG_MAX
	#define KCALC_ULONG_MAX	ULONG_MAX
	#define KCALC_LONG	long 
	#define HAVE_LONG_LONG
	#define HAVE_LONG_DOUBLE
#endif

#define UNUSED(x) ((void)(x))

enum {
	BUTTON_CONFIG,
	BUTTON_HELP,
	EDIT_DISPLAY,

	CHECKBOX_HEX,
	CHECKBOX_DEC,
	CHECKBOX_OCT,
	CHECKBOX_BIN,
	CHECKBOX_8BYTE,
	CHECKBOX_4BYTE,
	CHECKBOX_2BYTE,
	CHECKBOX_1BYTE,

	BUTTON_HYP,
	BUTTON_INV,
	BUTTON_A,
	BUTTON_EE,
	BUTTON_MR,
	BUTTON_MOTHER,
	BUTTON_MC,
	BUTTON_AFUNCTION,
	BUTTON_AC,

	BUTTON_RSH,
	BUTTON_PLUSMINUS,
	BUTTON_B,
	BUTTON_7,
	BUTTON_8,
	BUTTON_9,
	BUTTON_LBRACKET,
	BUTTON_RBRACKET,
	BUTTON_AND,

	BUTTON_COS,
	BUTTON_RECIPROCAL,
	BUTTON_C,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6,
	BUTTON_MULTIPLYSIGN,
	BUTTON_DIVESIONSIGN,
	BUTTON_OR,

	BUTTON_TAN,
	BUTTON_FACTORIAL,
	BUTTON_D,
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_ADDSIGN,
	BUTTON_SUBSIGN,
	BUTTON_LSH,


	BUTTON_LOG,
	BUTTON_SQUARE,
	BUTTON_E,
	BUTTON_DECIMAL,
	BUTTON_0,
	BUTTON_EQUALSIGN,
	BUTTON_PERCENTSIGN,
	BUTTON_CMP,
	BUTTON_MOD,

	BUTTON_LN,
	BUTTON_POWER,
	BUTTON_F,

	CONTROL_MAXNUM,
};


#define STACK_SIZE	100
#define PRECEDENCE_INCR	20

#define FUNC_NULL		0
#define FUNC_OR			1
#define FUNC_XOR		2
#define FUNC_AND		3
#define FUNC_LSH		4
#define FUNC_RSH		5
#define FUNC_ADD		6
#define FUNC_SUBTRACT	7
#define FUNC_MULTIPLY	8
#define FUNC_DIVIDE		9
#define FUNC_MOD		10
#define FUNC_POWER		11
#define FUNC_PWR_ROOT	12
#define FUNC_INTDIV		13

#define		HEX_SIZE	sizeof(KCALC_LONG)*2
#define		OCT_SIZE	22
#define		DEC_SIZE	20
#define		BIN_SIZE	64

#define		DSP_SIZE	65 // 25

#define		POS_ZERO	 1e-19L	 /* What we consider zero is */
#define		NEG_ZERO	-1e-19L	 /* anything between these two */

#define DISPLAY_AMOUNT display_data.s_item_data.item_amount


typedef	CALCAMNT	(*Arith)(CALCAMNT, CALCAMNT);
typedef	CALCAMNT	(*Prcnt)(CALCAMNT, CALCAMNT);
typedef	CALCAMNT	(*Trig)(CALCAMNT);

typedef enum _last_input_type
{
	DIGIT = 1,
	OPERATION = 2,
	RECALL = 3,
	PASTE = 4
} last_input_type;

typedef enum _num_base
{
	NB_BINARY = 2,
	NB_OCTAL = 8,
	NB_DECIMAL = 10,
	NB_HEX = 16
} num_base;

typedef enum _angle_type
{
	ANG_DEGREE = 0,
	ANG_RADIAN = 1,
	ANG_GRADIENT = 2
} angle_type;

typedef enum _item_type
{
	ITEM_FUNCTION,
	ITEM_AMOUNT
} item_type;

typedef struct _func_data
{
	int item_function;
	int item_precedence;
} func_data;

typedef	union  _item_data
{
	CALCAMNT	item_amount;	// an amount
	func_data	item_func_data;	// or a function
} item_data;

typedef struct _item_contents
{
	item_type	s_item_type;	// a type flag
	item_data	s_item_data; 	// and data
} item_contents;

typedef struct stack_item *stack_ptr;

typedef struct stack_item
{
	// Contents of an item on the input stack

	stack_ptr prior_item;		// Pointer to prior item
	stack_ptr prior_type;		// Pointer to prior type
	item_contents item_value;	// The value of the item
} stack_item;


void 	InitStack();
void 	PushStack(item_contents *add_item);
int		UpdateStack(int run_precedence);
item_contents	*PopStack();
item_contents	*TopOfStack();
item_contents	*TopTypeStack(item_type rqstd_type);


typedef struct _DefStruct
{
	COLORREF forecolor;
	COLORREF backcolor;
	COLORREF numberButtonColor;
	COLORREF functionButtonColor;
	COLORREF hexButtonColor;
	COLORREF memoryButtonColor;
	COLORREF operationButtonColor;

	int precision;
	int fixedprecision;
	int style;
	bool fixed;
	bool beep;
	CWispFont font;
} DefStruct;


class CWispCalcWnd :public CWispWnd
{
public:
	CWispCalcWnd(void);
	void Popup();
	bool Create(int x=0,int y=0,CWispBaseWnd*pParentWnd = NULL,UINT CmdID = 0);
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnCommand);
	DECLARE_WISP_MSG(OnDestory);
	DECLARE_WISP_MSG(OnUpdateClient);
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG(OnKeyDown);
	DECLARE_WISP_MSG(OnKeyUp);
	CWispRadioBox*	anglebutton[4];
	CWispRadioBox*	basebutton[4];

	CWispButton* pbA;	
	CWispButton* pbMR;
	CWispButton* pbMplusminus;
	CWispButton* pbMC;
	CWispButton* pbClear;
	CWispButton* pbAC;

	CWispButton* pbRsh;
	CWispButton* pbplusminus;
	CWispButton* pbB;
	CWispButton* pb7;
	CWispButton* pb8;
	CWispButton* pb9;
	CWispButton* pbparenopen;
	CWispButton* pbparenclose;
	CWispButton* pband;
	
	CWispButton* pbXor;
	CWispButton* pbC;
	CWispButton* pb4;
	CWispButton* pb5;
	CWispButton* pb6;
	CWispButton* pbX;
	CWispButton* pbdivision;
	CWispButton* pbor;
	
	CWispButton* pbfactorial;
	CWispButton* pbD;
	CWispButton* pb1;
	CWispButton* pb2;
	CWispButton* pb3;
	CWispButton* pbplus;
	CWispButton* pbminus;
	CWispButton* pbshift;

	CWispButton* pbsquare;
	CWispButton* pbE;	
	CWispButton* pb0;
	CWispButton* pbequal;	
	CWispButton* pbnegate;
	CWispButton* pbmod;	
	CWispButton* pbpower;
	CWispButton* pbF;
		
	void writeSettings();
	void readSettings();
	void set_precision();
	void set_style();
	void history_next();
	void history_prev();
	void ComputeMean();
	void ComputeSin();
	void ComputeStd();
	void ComputeCos();
	void ComputeMedean();
	void ComputeTan();

	int UpdateStack(int run_precedence);
protected :	
	void display_selected();
	void selection_timed_out();
	void clear_buttons();		
	void EnterDigit(int data);
	void SubtractDigit();
	void EnterDecimal();
	void EnterStackFunction(int data);
	void EnterNegate();
	void EnterOpenParen();
	void EnterCloseParen();
	void EnterRecip();
	void EnterInt();
	void EnterFactorial();
	void EnterSquare();
	void EnterNotCmp();
	void EnterHyp();
	void EnterPercent();
	void EnterLogr();
	void EnterLogn();
	void Qword_Selected();
	void Dword_Selected();
	void Word_Selected();
	void Byte_Selected();
	void Base_Selected(int number);
	void Hex_Selected();
	void Dec_Selected();
	void Oct_Selected();
	void Bin_Selected();
	void SetInverse();
	void EnterEqual();
	void Clear();
	void ClearAll();
	void RefreshCalculator();
	void InitializeCalculator();
	void UpdateDisplay();
	void ExecSin();
	void ExecCos();
	void ExecTan();
	void button0();
	void button1();
	void button2();
	void button3();
	void button4();
	void button5();
	void button6();
	void button7();
	void button8();
	void button9();
	void buttonA();
	void buttonB();
	void buttonC();
	void buttonD();
	void buttonE();
	void buttonF();
	void base_selected(int number);
	void angle_selected(int number);
	void Or();
	void Xor();
	void And();
	void Shift();
	void Lshift();
	void Rshift();
	void Plus();
	void Minus();
	void Multiply();
	void Divide();
	void Mod();
	void Power();
	void EE();
	void MR();
	void Mplusminus();
	void MC();
	void EEtoggled(bool myboolean);
	void pbinvtoggled(bool myboolean);
	void pbMRtoggled(bool myboolean);
	void pbAtoggled(bool myboolean);
	void pbRshtoggled(bool myboolean);
	void pbplusminustoggled(bool myboolean);
	void pbMplusminustoggled(bool myboolean);
	void pbBtoggled(bool myboolean);
	void pbXortoggled(bool myboolean);
	void pbrecitoggled(bool myboolean);
	void pbCtoggled(bool myboolean);
	void pbTantoggled(bool myboolean);
	void pbfactorialtoggled(bool myboolean);
	void pbDtoggled(bool myboolean);
	void pblogtoggled(bool myboolean);
	void pbsquaretoggled(bool myboolean);
	void pbEtoggled(bool myboolean);
	void pblntoggled(bool myboolean);
	void pbpowertoggled(bool myboolean);
	void pbFtoggled(bool myboolean);
	void pbMCtoggled(bool myboolean);
	void pbCleartoggled(bool myboolean);
	void pbACtoggled(bool myboolean);
	void pb7toggled(bool myboolean);
	void pb8toggled(bool myboolean);
	void pb9toggled(bool myboolean);
	void pbparenopentoggled(bool myboolean);
	void pbparenclosetoggled(bool myboolean);
	void pbandtoggled(bool myprivateboolean);
	void pb4toggled(bool myboolean);
	void pb5toggled(bool myboolean);
	void pb6toggled(bool myboolean);
	void pbXtoggled(bool myboolean);
	void pbdivisiontoggled(bool myboolean);
	void pbortoggled(bool myboolean);
	void pb1toggled(bool myboolean);
	void pb2toggled(bool myboolean);
	void pb3toggled(bool myboolean);
	void pbplustoggled(bool myboolean);
	void pbminustoggled(bool myboolean);
	void pbshifttoggled(bool privatemyboolean);
	void pbperiodtoggled(bool myboolean);
	void pb0toggled(bool myboolean);
	void pbequaltoggled(bool myboolean);
	void pbpercenttoggled(bool myboolean);
	void pbnegatetoggled(bool myboolean);
	void pbmodtoggled(bool myboolean);
	void pbhyptoggled(bool myboolean);	

private:
	DefStruct kcalcdefaults;
	void setStatusLabel();
private:
	static int cvb(char *out_str, KCALC_LONG amount, int max_digits);

public:
	static CALCAMNT ExecOr(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecXor(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecAnd(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecLsh(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecRsh(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecAdd(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecSubtract(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecMultiply(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecDivide(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecMod(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecPower(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecPwrRoot(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecIntDiv(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecAddP(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecSubP(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecMultiplyP(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecDivideP(CALCAMNT left_op, CALCAMNT right_op);
	static CALCAMNT ExecFunction(CALCAMNT left_op, int function, CALCAMNT right_op);
	
private:
	bool inverse;	
	bool refresh_display;
	int	display_size;
	int	m_NumberBitWdith;
	int input_limit;
	int input_count;
	int decimal_point;
	int precedence_base;
	num_base current_base;
	CALCAMNT memory_num;
	last_input_type last_input;

public:
	static const CALCAMNT pi;

private:
	char display_str[DSP_SIZE + 1];

private:
	TList<CALCAMNT> history_list;
	int history_index;
	bool key_pressed;
	int mInternalSpacing;

};
#endif /* _WISPCALCWND_H_ */

