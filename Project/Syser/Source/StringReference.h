#ifndef _STRINGREFERENCE_H_
#define _STRINGREFERENCE_H_

class CFindString
{
public:
	bool IsPrint(const BYTE cChar);
	bool IsAlpha(const BYTE cChar);
	bool IsSimplified(const WORD wChar);
	bool IsGraphic(const WORD wChar);
	bool SearchImageMemory(DWORD Address);
	bool SearchSectionMemory(DWORD Address,DWORD dwSize,DWORD ImageBase,DWORD ImageSize);
public:
	CFindString();
	~CFindString();
	bool GetString(IN const BYTE *InputBuffer,IN int InputBufferLen,IN OUT BYTE *OutputBuffer,IN int OutputBufferLen,OUT int *OutputLen);
	bool GetUnicodeString(IN const BYTE *InputBuffer,IN int InputBufferLen,IN OUT BYTE *OutputBuffer,IN int OutputBufferLen,OUT int *OutputLen);

};

#endif //_STRINGREFERENCE_H_