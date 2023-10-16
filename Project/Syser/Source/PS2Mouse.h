#ifndef _PS2MOUSE_H_
#define _PS2MOUSE_H_

#ifdef __cplusplus
extern "C" {
#endif

DWORD CalcMouseBeginIndex();
void MouseInterruptService();
VOID SyserInterrupt_0xF9_Mouse_Service(VOID);
extern DWORD gPS2MouseInterruptNum;
void PS2MouseOperation();

#ifdef __cplusplus
}; // extern "C"
#endif

#endif //_PS2MOUSE_H_