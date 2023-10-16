#ifndef _PROMPTQUIT_H_
#define _PROMPTQUIT_H_
void DisplayTextString(char* DisplayString,int x,int y,BYTE* VideoBuffer);
int PromptQuit(char* DisplayString,LONG TimeOut=-10000);
#endif //_PROMPTQUIT_H_