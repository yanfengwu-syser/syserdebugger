#include "StdAfx.h"
#include "ColorOption.h"


int ColorOptionRef = 0;

COLOR_OPTION OrgColorOption=
{
	0,//CRCCode
	WISP_RGB(0,0,0),		//clrBackground
	WISP_RGB(255,255,255),	//clrText
	WISP_RGB(80,176,255),	//clrSelectedFrame
	WISP_RGB(88,88,127),	//clrLostFocusSelFrame
	WISP_RGB(255,0,0),		//clrChgText
	WISP_RGB(128,196,255),	//clrSpeicalText
//////////////////////////////////////////////////////////////////////////
//Code View
	WISP_RGB(0,0,0),		//clrCVBK
	WISP_RGB(80,176,255),	//clrCVSelectedFrame
	WISP_RGB(88,88,127),	//clrCVLostFocusSelFrame
	WISP_RGB(255,255,255),	//clrCVAddr
	WISP_RGB(255,255,255),	//clrCVPrefix;
	WISP_RGB(255,255,255),	//clrCVOpCode;
	WISP_RGB(0,255,255),	//clrCVReg;
	WISP_RGB(0,192,192),	//clrCVSegReg;
	WISP_RGB(0,255,128),	//clrCVImmed;
	WISP_RGB(255,255,255),	//clrCVOptr;
	WISP_RGB(255,255,0),	//clrCVSymbol;
	WISP_RGB(255,255,0),	//clrCVComment;
	WISP_RGB(255,255,255),	//clrCVKeyword;
	WISP_RGB(255,255,0),	//clrCVStr;
	WISP_RGB(255,0,0),		//clrCVBPXStrip;
	WISP_RGB(128,128,128),	//clrCVEIPStrip;
	WISP_RGB(255,128,0),	//clrCVBPXEIPStrip;
	WISP_RGB(255,128,0),	//clrCVAPIName;
	WISP_RGB(255,125,125),	//clrCVAPIParamType;
	WISP_RGB(192,192,192),	//clrCVAPIParamName;
	WISP_RGB(255,255,255),	//clrCVJmpLine
	WISP_RGB(255,255,0),	//clrCVActivedJmpLine
	WISP_RGB(0x68,0x38,0xc6),	//clrCVPrefixByte
	WISP_RGB(0x99,0x16,0x22),	//clrCVOpcodeByte
	WISP_RGB(0x1a,0x33,0xe4),	//clrCVRegRMByte;
	WISP_RGB(0x39,0xef,0x04),	//clrCVSIBByte
	WISP_RGB(0xd0,0x1f,0xdf),	//clrCVOtherOpcodeByte
	WISP_RGB(0x70,0x70,0x70),	//clrCV3DNowByte
//Code View
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//Source Debug
	WISP_RGB(0,0,0),		//clrSDBK;
	WISP_RGB(80,176,255),	//clrSDSelectedFrame;
	WISP_RGB(88,88,127),	//clrSDLostFocusSelFrame
	WISP_RGB(255,255,255),	//clrSDKeyword;
	WISP_RGB(192,192,192),	//clrSDId;
	WISP_RGB(64,128,255),	//clrSDPrekeyWord;
	WISP_RGB(128,128,128),	//clrSDCmtBlock;
	WISP_RGB(128,128,128),	//clrSDCmtLine;
	WISP_RGB(255,255,0),	//clrSDString;
	WISP_RGB(0,255,128),	//clrSDNum;
	WISP_RGB(255,255,255),	//clrSDOperation;
	WISP_RGB(225,125,125),	//clrSDClassName;
	WISP_RGB(225,125,125),	//clrSDStructName;
	WISP_RGB(225,125,125),	//clrSDUnionName;
	WISP_RGB(225,125,125),	//clrSDTypedefName;
	WISP_RGB(255,128,0),	//clrSDFunctionName;
	WISP_RGB(123,123,123),	//clrSDUnknown;
//Source Debug
//////////////////////////////////////////////////////////////////////////
};


COLOR_OPTION ColorOption;