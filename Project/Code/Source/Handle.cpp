#include "StdAfx.h" 
#include "Handle.h" 

NAME_SPACE_BEGIN

CHandle::CHandle()
{
	ZeroMemory(m_RegisterType,sizeof(m_RegisterType));
	ZeroMemory(m_HandleInfoDir,sizeof(m_HandleInfoDir));
}

void CHandle::Reset()
{
	CloseAllHandle();
	ZeroMemory(m_RegisterType,sizeof(m_RegisterType));
	ZeroMemory(m_HandleInfoDir,sizeof(m_HandleInfoDir));
}

HANDLE_TYPE CHandle::CreateHandle(void* HandleInfo,DWORD Type)
{
	HANDLE_TYPE Result;
	DWORD nDir,nSlot;
	HANDLE_INFO*pFreeSlot=NULL;
	for(nDir=0;nDir<HANDLE_DIR_COUNT;nDir++)
	{
		if(m_HandleInfoDir[nDir]==NULL)
		{
			m_HandleInfoDir[nDir]=new HANDLE_INFO[HANDLE_SLOT_COUNT];
			ZeroMemory(m_HandleInfoDir[nDir],sizeof(HANDLE_INFO)*HANDLE_SLOT_COUNT);
		}
		for(nSlot=0;nSlot<HANDLE_SLOT_COUNT;nSlot++)
		{
			if(m_HandleInfoDir[nDir][nSlot].Attribute == 0)
			{
				pFreeSlot=&m_HandleInfoDir[nDir][nSlot];
				break;
			}
		}
		if(pFreeSlot)
			break;
	}
	if(pFreeSlot==NULL)
		return INVALID_HANDLE;
	Result = MAKE_DWORD(Type,(nDir<<10)|nSlot);
	pFreeSlot->HandleInfo = HandleInfo;
	pFreeSlot->Attribute = MAKE_DWORD(Type,HANDLE_EXIST);
	return Result;
}

bool CHandle::CloseHandle(HANDLE_TYPE Handle)
{
	HANDLE_INFO*pHandleInfo;
	DWORD nDir,nSlot,m;
	DWORD Type;
	Type  = HIGH_WORD(Handle);
	nSlot = Handle&0x03FF;
	nDir  = (Handle>>10)&0x3F;
	if(	m_HandleInfoDir[nDir] == NULL ||
		(m_HandleInfoDir[nDir][nSlot].Attribute&HANDLE_EXIST)==0 ||
		HIGH_WORD(m_HandleInfoDir[nDir][nSlot].Attribute)!=Type)
		return false;
	if(Type >= MAX_HANDLE_TYPE || m_RegisterType[Type].bExist==false)
		return false;
	pHandleInfo = &m_HandleInfoDir[nDir][nSlot];
	if(m_RegisterType[Type].RelHIFunc)
		m_RegisterType[Type].RelHIFunc(m_RegisterType[Type].Param,pHandleInfo->HandleInfo);
	else
		delete (BYTE*)pHandleInfo->HandleInfo;
	pHandleInfo->HandleInfo = NULL;
	pHandleInfo->Attribute = 0;
	pHandleInfo = m_HandleInfoDir[nDir];
	for(m=0;m<HANDLE_SLOT_COUNT;m++)
	{
		if(pHandleInfo[m].Attribute & HANDLE_EXIST)
			break;
	}
	if(m>=HANDLE_SLOT_COUNT)
	{
		delete m_HandleInfoDir[nDir];
		m_HandleInfoDir[nDir] = NULL;
	}
	return true;
}

void CHandle::CloseAllHandle()
{
	DWORD  Type;
	HANDLE_INFO*HandleInfoAry;
	for(int n=0;n<HANDLE_DIR_COUNT;n++)
	{
		HandleInfoAry = m_HandleInfoDir[n];
		if(HandleInfoAry)
		{
			for(int m=0;m<HANDLE_SLOT_COUNT;m++)
			{
				Type = HIGH_WORD(HandleInfoAry[m].Attribute);
				if(Type >= MAX_HANDLE_TYPE || m_RegisterType[Type].bExist==false)
					continue;
				if(HandleInfoAry[m].Attribute & HANDLE_EXIST)
				{
					if(m_RegisterType[Type].RelHIFunc)
						m_RegisterType[Type].RelHIFunc(m_RegisterType[Type].Param,HandleInfoAry[m].HandleInfo);
					else
						delete (BYTE*)HandleInfoAry[m].HandleInfo;
				}
			}
			delete HandleInfoAry;
			m_HandleInfoDir[n]=NULL;
		}
	}
}

bool CHandle::IsHandleExist(HANDLE_TYPE Handle)
{
	DWORD nDir,nSlot;
	DWORD Type;
	Type  = HIGH_WORD(Handle);
	nSlot = Handle&0x03FF;
	nDir  = (Handle>>10)&0x3F;
	if( m_HandleInfoDir[nDir] == NULL || 
		(m_HandleInfoDir[nDir][nSlot].Attribute&HANDLE_EXIST)==0 ||
		HIGH_WORD(m_HandleInfoDir[nDir][nSlot].Attribute)!=Type)
		return false;
	return true;
}

void* CHandle::GetHandleInfo(HANDLE_TYPE Handle)
{
	DWORD nDir,nSlot;
	DWORD Type;
	Type  = HIGH_WORD(Handle);
	nSlot = Handle&0x03FF;
	nDir  = (Handle>>10)&0x3F;
	if(Type >= MAX_HANDLE_TYPE || m_RegisterType[Type].bExist==false)
		return false;
	if(	m_HandleInfoDir[nDir] == NULL ||
		(m_HandleInfoDir[nDir][nSlot].Attribute&HANDLE_EXIST)==0 ||
		HIGH_WORD(m_HandleInfoDir[nDir][nSlot].Attribute)!=Type)
		return NULL;
	return m_HandleInfoDir[nDir][nSlot].HandleInfo;
}

DWORD CHandle::GetHandleType(HANDLE_TYPE Handle)
{
	return HIGH_WORD(Handle);
}

HANDLE_TYPE CHandle::GetFirstHandle(DWORD Type)
{
	DWORD nDir,nSlot;	
	nSlot = 0;
	nDir  = 0;
	if(Type >= MAX_HANDLE_TYPE || m_RegisterType[Type].bExist==false)
		return false;
	for(DWORD n=nDir;n<HANDLE_DIR_COUNT;n++)
	{
		if(m_HandleInfoDir[n])
		{
			for(DWORD s=nSlot;s<HANDLE_SLOT_COUNT;s++)
			{
				if( HIGH_WORD(m_HandleInfoDir[n][s].Attribute)==Type && 
					(m_HandleInfoDir[nDir][nSlot].Attribute&HANDLE_EXIST))
					return (HANDLE_TYPE)((Type<<16)+(n<<10)+s);
			}
		}
		nSlot=0;
	}
	return INVALID_HANDLE;
}

HANDLE_TYPE  CHandle::GetNextHandle(HANDLE_TYPE Handle)
{
	DWORD nDir,nSlot;
	DWORD Type;
	Type  = HIGH_WORD(Handle);
	nSlot = Handle&0x03FF;
	nDir  = (Handle>>10)&0x3F;
	if(Type >= MAX_HANDLE_TYPE || m_RegisterType[Type].bExist==false)
		return false;
	nSlot++;
	for(DWORD n=nDir;n<HANDLE_DIR_COUNT;n++)
	{
		if(m_HandleInfoDir[n])
		{
			for(DWORD s=nSlot;s<HANDLE_SLOT_COUNT;s++)
			{
				if( HIGH_WORD(m_HandleInfoDir[n][s].Attribute)==Type && 
					(m_HandleInfoDir[nDir][nSlot].Attribute&HANDLE_EXIST)
					)
					return (HANDLE_TYPE)((Type<<16)+(n<<10)+s);
			}
		}
		nSlot=0;
	}
	return INVALID_HANDLE;
}

DWORD CHandle::Register(REL_HI_FUNC RelHIFunc,void* Param)
{	
	for(DWORD Type=1;Type<MAX_HANDLE_TYPE;Type++)
	{
		if(m_RegisterType[Type].bExist==false)
		{
			m_RegisterType[Type].RelHIFunc=RelHIFunc;
			m_RegisterType[Type].Param=Param;
			m_RegisterType[Type].bExist=true;
			return Type;
		}
	}
	return INVALID_HANDLE_TYPE;
}

bool CHandle::Unregister(DWORD Type)
{
	if(Type >= MAX_HANDLE_TYPE || m_RegisterType[Type].bExist==false)
		return false;
	m_RegisterType[Type].RelHIFunc=NULL;
	m_RegisterType[Type].Param=NULL;
	m_RegisterType[Type].bExist=false;
	return true;
}

NAME_SPACE_END

