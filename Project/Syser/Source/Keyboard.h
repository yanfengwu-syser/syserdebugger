#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

struct USB_MOD_TRANS
{
	UINT	KeyType;
	WORD	Mask;
};

extern	UINT USBKeyTransTable[256];
extern	USB_MOD_TRANS USBModKeyTransTable[];
void	TranslateUSBKey(BYTE*pPrevData,BYTE*pNewData);


struct USB_HOOK_PARAM
{
	PUSAGE_AND_PAGE  ChangedUsageList;
	ULONG  UsageListLength;
	HIDP_KEYBOARD_DIRECTION  KeyAction;
	PHIDP_KEYBOARD_MODIFIER_STATE  ModifierState;
	PHIDP_INSERT_SCANCODES  InsertCodesProcedure;
	PVOID  InsertCodesContext;
};

extern bool gUsbRightControl;
extern bool gbUsbKeyboardActive;
#endif
