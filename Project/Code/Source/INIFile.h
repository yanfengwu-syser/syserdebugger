#ifndef _INIFILE_H_
#define _INIFILE_H_
#include "Define.h"
#include "TXTFile.h"

NAME_SPACE_BEGIN
typedef TList<char*> CommentSeparatorList;

class CINIFile:public CTXTFile
{
	CommentSeparatorList m_CommentSeparatorStrList;
	TList<char*> m_SectionList;
public:
	CINIFile();
	~CINIFile();
	bool GetString(IN char* lpSectionName,IN char*lpKeyName,OUT char *lpString);
	bool SetString(IN char* lpSectionName,IN char*lpKeyName,IN char*lpString);
	bool IsSectionExist(IN char* lpSectionName);
	bool IsKeyExist(IN char* lpSectionName,IN char*lpKeyName);
	bool CreateSection(IN char* lpSectionName);
	bool DeleteSection(IN char* lpSectionName);
	void AddCommentSeparatorStr(IN char* SeparatorStr);
	void DelCommentSeparatorStr(IN char* SeparatorStr);
};
bool FindKey(const char*pLine,const char* KeyName,char** pDestKeyName=NULL,DWORD* dwDestKeyNameLen=NULL);
bool FindSection(const char* pLine,const char* SectionName,char** pDestSectionName=NULL,DWORD* dwDestSectionNameLen=NULL);
bool CodeWritePrivateProfileString(
							   IN LPCSTR lpAppName,
							   IN LPCSTR lpKeyName,
							   IN LPCSTR lpString,
							   IN LPCSTR lpFileName
							   );
bool CodeGetPrivateProfileString(
							 IN LPCSTR lpAppName,
							 IN LPCSTR lpKeyName,
							 IN LPCSTR lpDefault,
							 OUT LPSTR lpReturnedString,
							 IN DWORD nSize,
							 IN LPCSTR lpFileName
							 );
NAME_SPACE_END
#endif // _INIFILE_H_
