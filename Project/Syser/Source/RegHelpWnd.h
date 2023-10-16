#ifndef _REGHELPWND_H_
#define _REGHELPWND_H_ 


enum{
	CONTROL_REGISTER,
	DEBUG_REGISTER,
	SEGMENT_DESCRIPTOR_REGISTER,
	FLAGS_REGISTER,
	PAGEDIRENTRY4M_REGISTER,
	PAGEDIRENTRY4K_REGISTER,
	MAX_REGISTER_GROUP_INDEX,
};

typedef struct stRegisterBitName
{
	WISP_CHAR *RegName;
	int BeginBitIndex;
	int BitLen;
	WISP_CHAR *Descriptor;
}REGISTERBITNAME;

class CRegHelpWnd :	public CWispWnd
{
	int m_RegisterGroup;
public:
	CRegHelpWnd();
	~CRegHelpWnd();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnUpdateClient)
	bool	DrawRegister(int x, int y,unsigned int NumberMask,unsigned int  ReservedMask,unsigned int LineMask,unsigned int OtherMask, CWispDC DrawDC,REGISTERBITNAME *RegBitName=NULL,WISP_CHAR *RegisterName=NULL);	
	int		SetRegisterGroup(int index);
};
#endif /* _REGHELPWND_H_ */

