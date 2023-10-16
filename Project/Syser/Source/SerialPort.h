#ifndef _SERIALPORT_H_
#define _SERIALPORT_H_

#include "InputDriver.h"
#include "SyserConnect.h"

class CSerialPortConnect : public CSyserConnect
{
public:
	CSerialPortConnect();
	~CSerialPortConnect();
public:
	bool	Init();
	void	Release();
	int		RecvData(void*Buffer,int BufSize);
	int		SendData(void*Buffer,int BufSize);
private:
	HANDLE	m_hSerialPortDevice;
	WORD	m_ComPort;
};


extern DWORD	gHardInt4Vector;
extern DWORD	gHardInt3Vector;
extern ST_DESC* Com1Com3Desc;
extern ST_DESC* Com2Com4Desc;
extern VADDR32 gOldCom1Com3Proc;
extern VADDR32 gOldCom2Com4Proc;
extern DWORD dwSerialCom1Com3Counter;
extern DWORD dwSerialCom2Com4Counter; 

#ifdef __cplusplus
extern "C" {
#endif

VOID	SyserSerialCom1Com3Proc(VOID);
VOID	SyserSerialCom2Com4Proc(VOID);
VOID	SyserInterrupt_0xFB_Com1_Com3_Service(VOID);
VOID	SyserInterrupt_0xFC_Com2_Com4_Service(VOID);
#define SYSER_APIC_COM1_INTERRUPT_VECTOR	(0xfb)
#define SYSER_APIC_COM2_INTERRUPT_VECTOR	(0xfc)

#ifdef __cplusplus
}; // extern "C"
#endif

#endif /* _SERIALPORT_H_ */

