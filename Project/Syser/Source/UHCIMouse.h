#ifndef _UHCIMOUSE_H_
#define _UHCIMOUSE_H_


extern  char cFirstData,cXOffset,cYOffset,cZOffset;
extern  char cPrevFirstData,cPrevXOffset,cPrevYOffset,cPrevZOffset;
void	UsbMouseService();
void	InstallUsbMouseQueue();
void	UninstallUsbMouseQueue();

#endif //_UHCIMOUSE_H_