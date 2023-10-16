#ifndef _PROMPTQUIT_H_
#define _PROMPTQUIT_H_
void DisplayTextString(char* DisplayString,int x,int y,BYTE* VideoBuffer);
int PromptQuit(char* DisplayString,LONG TimeOut=-10000);
extern "C"
{
	__declspec(dllimport ) void	VidSolidColorFill(int x,int y,int x1,int y1,int TextColor);
	__declspec(dllimport) void VidDisplayStringXY(char* pStr,int x,int y,int TextColor);
	__declspec(dllimport) void VidBitBlt(unsigned char* colorbuf,int x,int y);
}
#endif //_PROMPTQUIT_H_