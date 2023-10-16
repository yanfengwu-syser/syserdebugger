#ifndef _VMWARE_SUPPORT_H_
#define _VMWARE_SUPPORT_H_

#ifdef __cplusplus
extern "C" {
#endif


//     Vmware 后门是 vmware 和 vmware tools 通信的一个接口。
//     这个后门开在 IO 端口 0x5658。利用这个后门时，必需：
//     EAX = 0x564D5868 ( “VMXh” )
//     ECX 低 16 位为功能号。其实是一个函数数组的索引。
//     ECX 的高 16 位为功能参数。
//     EDX = 0x5658 ( “VX” )，为 IO 端口号。
//
//     0xa   得到 vmware 版本
//
//     感谢许继彬提供的详细资料
typedef struct _VMVWARE_CALL{
	unsigned long     Return_Status;    //vm_eax  
	unsigned long     Exist_flag;       //vm_ebx
	unsigned long     Func_num;         //vm_ecx
	unsigned long     Port;				//vm_edx
	unsigned long     Trans_Src;		//vm_esi
	unsigned long     Trans_Dest;		//vm_edi
}VMVWARE_CALL,*PVMVWARE_CALL;
void FlushVedioBuffer(int x,int y,int width,int heigh,int command = 0);
extern bool gInVMWARE;
extern bool gIsSupportVMMouse;
bool VMWareTest();
DWORD __stdcall SyserVMWareCall(PVMVWARE_CALL pVMCParam);
bool IsSupportVMMouse();
typedef struct _TRANS_MOUSEDATA{
	USHORT    Priority_flag;
	USHORT    ButtonStatus;
	DWORD   DeltaX;
	DWORD   DeltaY;
	DWORD   DeltaWheel;
}TRANS_MOUSEDATA,*PTRANS_MOUSEDATA;
bool GetVMMouseData(PTRANS_MOUSEDATA pTranMouseData);
#define VMWARESET_CURSOR_POINT_FLAG			0x18
#define VMWARESET_CURSOR_POINT_X			0x19
#define VMWARESET_CURSOR_POINT_Y			0x1a
#define VMWARESET_ACCESS_FLAG               0x1B
void SetVMWareMousePos(DWORD CommandPort,DWORD DataPort,DWORD mousex,DWORD mousey);
void GetVMWareMousePos(DWORD* mousex,DWORD* mousey);

#ifdef __cplusplus
}; // extern "C"
#endif

#endif