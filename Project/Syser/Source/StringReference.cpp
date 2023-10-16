#include "stdafx.h"
#include "StringReference.h"
#include "Syser.h"
CFindString::CFindString()
{

}
CFindString::~CFindString()
{

}

bool CFindString::IsPrint(const BYTE cChar)
{
	if (cChar<0x20 || cChar==0xff)
		return false;
	return true;
}

bool CFindString::IsAlpha(const BYTE cChar)
{
	return (cChar>=0x20 && cChar <=0x7f)? true:false;
}
/////////////////////////////////////////////////////////
//    区名    码位范围   码位数  字符数 字符类型
// 双字节2区  B0A1—F7FE   6768    6763    汉字
/////////////////////////////////////////////////////////
bool CFindString::IsSimplified(const WORD wChar)
{
	BYTE LowByte,HighByte;

	HighByte = wChar & 0x00ff;
	LowByte  = wChar >> 8;

	if ((HighByte >= 0xb0 && HighByte <= 0xf7) && (LowByte  >= 0xa1 && LowByte <= 0xfe))	
		return true;
	return false;
}
/////////////////////////////////////////////////////////
//    区名    码位范围   码位数  字符数  字符类型
// 双字节5区  A840—A9A0    192     166  图形符号
// 双字节1区  A1A1—A9FE    846     718  图形符号
/////////////////////////////////////////////////////////
bool CFindString::IsGraphic(const WORD wChar)
{
	BYTE LowByte,HighByte;
	
	HighByte = wChar & 0x00ff;
	LowByte  = wChar >>8;
	
	if((LowByte >= 0xa1 && LowByte <= 0xfe) && (HighByte >= 0xa1 && HighByte <= 0xa9))
		return true;	
	if((LowByte  >= 0x40 && LowByte  <= 0xa0) && (HighByte >= 0xa8 && HighByte <= 0xa9))
		return true;
	return false;
}
bool CFindString::SearchImageMemory(DWORD Address)
{
	CMemPEFile MemPEFile;
	int i;
	DWORD BaseAddress;
	CDbgModule*pDbgModule;
#ifdef CODE_OS_NT_DRV
	pDbgModule = gpSyser->m_pSysDebugger->m_ModuleList.GetModule(Address);
	if(pDbgModule==NULL)
#endif
		pDbgModule = gpSyser->m_pDebugger->m_ModuleList.GetModule(Address);
	if(pDbgModule==NULL)
		return false;
	
	BaseAddress = pDbgModule->m_ModuleBase;
	if(BaseAddress==0)
		BaseAddress+=0x400000;
	if(MemPEFile.Open(BaseAddress,PE_OPEN_NO_IMPORT|PE_OPEN_NO_EXPORT,CDebugger::ReadMemory,gpSyser->m_pDebugger)==false)
		return false;
	for(i = 0 ; i < MemPEFile.m_SectCount;i++)
	{
		if(MemPEFile.m_Section[i].Characteristics & IMAGE_SCN_MEM_EXECUTE)
		{
			SearchSectionMemory(MemPEFile.m_Section[i].VirtualAddress+BaseAddress,MemPEFile.m_Section[i].VirtualSize,MemPEFile.m_ImageBase,MemPEFile.m_ImageSize);
		}
	}	
	MemPEFile.Close();
	return true;
}
#define  SHOW_HEX 0

bool CFindString::SearchSectionMemory(DWORD Address,DWORD dwSize,DWORD ImageBase,DWORD ImageSize)
{
	DWORD i,Length;
	BYTE CodeBuffer[MAX_INSTR_LEN];
	char DisBuffer[256];
	char DisBuffer2[256];
	BYTE OutBuffer[512];
	int OutputLen;
	WCHAR wBuffer[256];
	bool bIsUnicode=true;
	CInstrSym InstrSym;
	INSTRUCTION_INFORMATION InstInfo;
	DWORD InstLen;
	ULONGLONG Value;
	InstInfo.CodeMode=1;
	InstInfo.CodeBuff=CodeBuffer;
	InstInfo.pasm=DisBuffer2;
	CodeBuffer[0]=0;
	DWORD Count=0;
	for(i=0;i<dwSize;i+=Length)
	{

		Length=gpSyser->m_pDebugger->ReadMemory(Address+i,CodeBuffer,MAX_INSTR_LEN);
		if(Length==0)
		{
			Address = ((Address+i)&0xfffff000) + 0x1000;
			Length = 0x1000-((Address+i)%0xfff);
			continue;
		}
		InstInfo.eip=Address+i;	
		InstLen = InstrSym.Disassembler(&InstInfo);
		if(InstLen==0)
		{
			Length+=1;
			continue;
		}
		Length=InstLen;

		if(TStrICmp(InstInfo.Name,"mov")==0)
		{
			if(InstInfo.op[1].mode==mode_address)
				goto local_001;
			if(InstInfo.op[1].mode==mode_immed &&InstInfo.op[1].opersize==4)
			{				
				if(InstInfo.op[1].immed.immed_value>ImageBase && InstInfo.op[1].immed.immed_value<ImageBase+ImageSize)
				{
					
					if(gpSyser->m_pDebugger->ReadMemory((ULPOS)InstInfo.op[1].immed.immed_value,DisBuffer,sizeof(DisBuffer))==sizeof(DisBuffer))
					{
						if(GetString((BYTE*)DisBuffer,sizeof(DisBuffer),OutBuffer,sizeof(OutBuffer),&OutputLen)==true)
						{
							if(OutputLen ==2)
							{
								if(GetUnicodeString((BYTE*)DisBuffer,sizeof(DisBuffer),OutBuffer,sizeof(OutBuffer),&OutputLen))
								{
									Value =OutputLen/sizeof(WCHAR);
									Value|=0x80000000;
									Value<<=32;
									Value|=InstInfo.op[1].immed.immed_value;
									gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.InsertUnique(Address+i,Value);
								}
							}
							else
							{
								TStrCpy(wBuffer,InstInfo.pasm);
								
								{
									Value =OutputLen;
									Value<<=32;
									Value|=InstInfo.op[1].immed.immed_value;
									gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.InsertUnique(Address+i,Value);
								}
								
								
								
								TStrCpy(wBuffer,OutBuffer);
								AnsiToUnicode((const char*)OutBuffer,wBuffer,256);
							
	#if SHOW_HEX
								if(OutputLen>3)
								{
									for(int k = 0;k<OutputLen;k++)
										OUTPUT(WSTR("%02x "),OutBuffer[k]);
									OUTPUT(WSTR("\n"));
								}
	#endif
								
								Count++;
							}

						}
					}					
				}
				
			}
		}
		else
		{
			if(TStrICmp(InstInfo.Name,"lea")==0)
			{
local_001:
				if(InstInfo.op[1].mode==mode_immed && InstInfo.op[1].opersize==4)
				{
					
					if(InstInfo.op[1].addr.displacement >ImageBase && InstInfo.op[1].addr.displacement<ImageBase+ImageSize)
					{
						
						if(gpSyser->m_pDebugger->ReadMemory((ULPOS)InstInfo.op[1].addr.displacement,DisBuffer,sizeof(DisBuffer))==sizeof(DisBuffer))
						{
							if(GetString((BYTE*)DisBuffer,sizeof(DisBuffer),OutBuffer,sizeof(OutBuffer),&OutputLen))
							{
								TStrCpy(wBuffer,InstInfo.pasm);

								if(OutputLen ==2)
								{
									if(GetUnicodeString((BYTE*)DisBuffer,sizeof(DisBuffer),OutBuffer,sizeof(OutBuffer),&OutputLen))
									{
										Value =OutputLen/sizeof(WCHAR);
										Value|=0x80000000;
										Value<<=32;
										Value|=InstInfo.op[1].addr.displacement;
										gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.InsertUnique(Address+i,Value);
									}
								}
								else
								{
									
									{
										Value =OutputLen;
										Value<<=32;
										Value|=InstInfo.op[1].addr.displacement;
										gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.InsertUnique(Address+i,Value);
										
									}
									TStrCpy(wBuffer,OutBuffer);
									AnsiToUnicode((const char*)OutBuffer,wBuffer,256);
									
		#if SHOW_HEX
									if(OutputLen>3)
									{
										for(int k = 0;k<OutputLen;k++)
											OUTPUT(WSTR("%02x "),OutBuffer[k]);
										OUTPUT(WSTR("\n"));
									}
		#endif
									
									Count++;
								}

							}
						}
						
					}		
						
				}
			}
			else
			if(TStrICmp(InstInfo.Name,"push")==0)
			{
				if(InstInfo.op[0].immed.immed_value>ImageBase && InstInfo.op[0].immed.immed_value<ImageBase+ImageSize)
				{
					if(gpSyser->m_pDebugger->ReadMemory((ULPOS)InstInfo.op[0].immed.immed_value,DisBuffer,sizeof(DisBuffer))==sizeof(DisBuffer))
					{
						if(GetString((BYTE*)DisBuffer,sizeof(DisBuffer),OutBuffer,sizeof(OutBuffer),&OutputLen))
						{
							if(OutputLen ==2)
							{
								if(GetUnicodeString((BYTE*)DisBuffer,sizeof(DisBuffer),OutBuffer,sizeof(OutBuffer),&OutputLen))
								{
									Value =OutputLen/sizeof(WCHAR);
									Value|=0x80000000;
									Value<<=32;
									Value|=InstInfo.op[0].immed.immed_value;
									gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.InsertUnique(Address+i,Value);
								}
							}
							else
							{
								
								{
									Value =OutputLen;
									Value<<=32;
									Value|=InstInfo.op[0].immed.immed_value;
									gpSyser->m_MainFrame.m_SystemExplorer.m_StrReferenceMap.InsertUnique(Address+i,Value);
									
								}
								
								TStrCpy(wBuffer,OutBuffer);
								AnsiToUnicode((const char*)OutBuffer,wBuffer,256);
							
								
			#if SHOW_HEX
								if(OutputLen>3)
								{
									for(int k = 0;k<OutputLen;k++)
										OUTPUT(WSTR("%02x "),OutBuffer[k]);
									OUTPUT(WSTR("\n"));
								}
			#endif
								
								Count++;
							}
							
						}
					}				
				}			
					
			}
		}

	}
	return true;
}
bool CFindString::GetString(IN const BYTE *InputBuffer,IN int InputBufferLen,IN OUT BYTE *OutputBuffer,IN int OutputBufferLen,OUT int *OutputLen)
{
	bool bFound = true;
	int nLen = 0,i=0;
	OutputBuffer[0]=0;
	while (i < InputBufferLen && nLen<OutputBufferLen-2)
	{		
		if ('\0' == InputBuffer[i])
			break;				
		if ('\r' == InputBuffer[i])
		{
			*OutputBuffer++ = '\\';
			*OutputBuffer++ = 'r';
			nLen += 2;
		}
		else if ('\n' == InputBuffer[i])
		{
			*OutputBuffer++ = '\\';
			*OutputBuffer++ = 'n';
			nLen += 2;
		}
		else if ('\t' == InputBuffer[i])
		{
			*OutputBuffer++ = '\\';
			*OutputBuffer++ = 't';
			nLen += 2;
		}
		else if (IsAlpha(InputBuffer[i]))
		{
			*OutputBuffer++ = InputBuffer[i];
			++nLen;			
		}
		else if (IsGraphic(	*(WORD *)&InputBuffer[i]) || IsSimplified(*(WORD *)&InputBuffer[i]))
		{
			*OutputBuffer++ = InputBuffer[i];
			++i;
			*OutputBuffer++ = InputBuffer[i];
			nLen += 2;
		}
		else 
		{
			bFound = FALSE;
			break;
		}
		++i;
	}

	if (0 == nLen)
		bFound = FALSE;

	*OutputBuffer = '\0';

	if (bFound)
	{
		if (i >= InputBufferLen)
		{
			TStrCpy((char *)&OutputBuffer[InputBufferLen - 4], " ...");
			nLen = InputBufferLen; 
		}
		else
			nLen+=1;
	}

	if (OutputLen)
		*OutputLen = nLen;

	return bFound;
}
bool CFindString::GetUnicodeString(IN const BYTE *InputBuffer,IN int InputBufferLen,IN OUT BYTE *OutputBuffer,IN int OutputBufferLen,OUT int *OutputLen)
{
	bool bFound = true;
	int nLen = 0,i=0;

	while (i < InputBufferLen && nLen<OutputBufferLen-2)
	{
		
		if ('\0' == InputBuffer[i] && '\0' == InputBuffer[i + 1])
			break;
		
		if ('\r' == InputBuffer[i])
		{
			*OutputBuffer++ = '\\';
			*OutputBuffer++='\0';
			*OutputBuffer++ = 'r';
			*OutputBuffer++='\0';
			nLen += 4;
		}
		else if ('\n' == InputBuffer[i])
		{
			*OutputBuffer++ = '\\';
			*OutputBuffer++='\0';
			*OutputBuffer++ = 'n';
			*OutputBuffer++='\0';
			nLen += 4;
		}
		else if ('\t' == InputBuffer[i])
		{
			*OutputBuffer++ = '\\';
			*OutputBuffer++='\0';
			*OutputBuffer++ = 't';
			*OutputBuffer++='\0';
			nLen += 4;
		}
		else if (IsAlpha(InputBuffer[i]))
		{
			*OutputBuffer++ = InputBuffer[i];
			if(InputBuffer[i+1]!=0)
			{
				bFound = FALSE;
				break;
			}
			*OutputBuffer++='\0';
			nLen+=2;
		}
		else if (IsGraphic(	*(WORD *)&InputBuffer[i]) || IsSimplified(*(WORD *)&InputBuffer[i]))
		{
			*OutputBuffer++ = InputBuffer[i];
			++i;
			*OutputBuffer++ = InputBuffer[i];
			nLen += 2;
		}
		else
		{
			bFound = FALSE;
			break;
		}
		i+=2;
	}

	if (0 == nLen)
		bFound = FALSE;

	*OutputBuffer++ = '\0';
	*OutputBuffer++ = '\0';
	if (bFound)
	{
		if (i >= InputBufferLen)
		{
			TStrCpy((char *)&OutputBuffer[InputBufferLen - 4], " ...");
			nLen = InputBufferLen; 
		}
		else
			nLen+=2;
	}

	if (OutputLen)
		*OutputLen = nLen;

	return bFound;
}