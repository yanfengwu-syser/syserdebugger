#ifndef _SD_DEFINE_H_
#define _SD_DEFINE_H_

#define SD_CMD_SIGN			0x53434453 //SDCS
#define SD_RES_SIGN			0x53524453 //SDRS
#define SD_MAX_LENGTH		0x00010000

struct SD_PACKET
{
	DWORD	Sign;
	DWORD	CRCCode;
	int		Length;
	union
	{
		WCHAR szCmd[1];
		DCHAR CSStream[1];
	}Data;
};


#endif
