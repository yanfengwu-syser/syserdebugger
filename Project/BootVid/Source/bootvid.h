#ifndef _BOOTVID_H_
#define _BOOTVID_H_

extern "C" DECLSPEC_IMPORT void VidSolidColorFill(int x,int y,int x1,int y1,int TextColor);
extern "C" DECLSPEC_IMPORT void VidDisplayStringXY(char* pStr,int x,int y,int TextColor);
extern "C" DECLSPEC_IMPORT void VidBitBlt(unsigned char* colorbuf,int x,int y);
extern "C" DECLSPEC_IMPORT int VidScreenToBufferBlt(char* buffer,int x,int y,int width,int heigh,int linedistance);
extern "C" DECLSPEC_IMPORT int VidBufferToScreenBlt(char* buffer,int x,int y,int width,int height,int neg_linedistance);
extern "C" DECLSPEC_IMPORT int VidSetTextColor(int NewTextColor);
extern "C" DECLSPEC_IMPORT int VidCleanUp();
extern "C" DECLSPEC_IMPORT int VidInitialize(int mode);
extern "C" DECLSPEC_IMPORT int VidDisplayString(char* pStr);
extern "C" DECLSPEC_IMPORT int VidSetScrollRegion(int,int,int,int);
extern "C" DECLSPEC_IMPORT int VidResetDisplay(int);

#endif //_BOOTVID_H_
