#include "StdAfx.h"
#include "DbgModule.h"
 
CSymbolModule::CSymbolModule()
{
	m_ReferenceCount = 0;
	m_ModuleName = NULL;
	m_pParam = NULL;
	m_ModuleID = 0;
	m_ModuleBase = 0;
	m_ModuleSize = 0;
}

bool CSymbolModule::InsertSymbol(IN ULPOS Offset,IN PCSYMSTR szSym)
{
	return  m_SymbolMap.InsertUnique(Offset,szSym)!=m_SymbolMap.End();
}

bool CSymbolModule::SetSymbol(IN ULPOS Offset,IN PCSYMSTR szSym)
{
	CSymbolMap::IT Iter = m_SymbolMap.Find(Offset);
	if(Iter!=m_SymbolMap.End())
	{
		if(*Iter == szSym)
			return false;
		*Iter = szSym;
		return true;
	}
	return m_SymbolMap.InsertUnique(Offset,szSym)!=m_SymbolMap.End();
}

bool CSymbolModule::RemoveSymbol(IN ULPOS Offset)
{
	return m_SymbolMap.Remove(Offset)>0;
}

bool CSymbolModule::RemoveSymbol(IN PCSYMSTR szSym)
{
	int Count = 0;
	CSymbolMap::IT RemovIter,Iter = m_SymbolMap.Begin();
	while(Iter!=m_SymbolMap.End())
	{
		if(TStrICmp((PCSYMSTR)(*Iter),szSym)==0)
		{
			RemovIter = Iter;
			Iter++;
			Count++;
			m_SymbolMap.Remove(RemovIter);
		}
		else
			Iter++;
	}
	return Count>0;
}

bool CSymbolModule::GetAddress(IN PCSYMSTR szSym,OUT ULPOS*pAddress)
{
	if(m_ModuleBase==0)
		return false;
	for(CSymbolMap::IT Iter = m_SymbolMap.Begin();Iter.IsExist();Iter++)
	{
		if(*Iter==szSym)
		{
			if(pAddress)
				*pAddress = Iter.Key()+m_ModuleBase;
			return true;
		}
	}
	return false;
}

CCommentModule::CCommentModule()
{
	m_ReferenceCount = 0;
	m_ModuleName = NULL;
	m_pParam = NULL;
}

bool CCommentModule::InsertComment(IN ULPOS Offset,IN PCCMTSTR szComment)
{
	return m_CommentMap.InsertUnique(Offset,szComment)!=m_CommentMap.End();
}

bool CCommentModule::SetComment(IN ULPOS Offset,IN PCCMTSTR szComment)
{
	CCommentMap::IT Iter = m_CommentMap.Find(Offset);
	if(Iter!=m_CommentMap.End())
	{
		if(*Iter==szComment)
			return false;
		*Iter = szComment;
		return true;
	}
	return m_CommentMap.InsertUnique(Offset,szComment)!=m_CommentMap.End();
}

bool CCommentModule::RemoveComment(IN ULPOS Offset)
{
	return m_CommentMap.Remove(Offset)>0;
}

CSymbolModule*CSymbolContainer::GetSymbolModule(MODULE_ID MID)
{
	TMap<MODULE_ID,CSymbolModule>::IT Iter = Find(MID);
	if(Iter.IsExist())
		return &(*Iter);
	return NULL;
}

CSymbolModule*CSymbolContainer::InsertSymbolModule(MODULE_ID MID)
{
	TMap<MODULE_ID,CSymbolModule>::IT Iter = InsertUnique(MID);
	if(Iter.IsExist()==false)
		return NULL;
	Iter->m_ModuleID = MID;
	return &(*Iter);
}

bool CSymbolContainer::RemoveSymbolModule(MODULE_ID MID)
{
	return Remove(MID)>0;
}

void CSymbolContainer::RemoveUnusedSymbolModule()
{
	TMap<MODULE_ID,CSymbolModule>::IT RemoveIter,Iter = Begin();
	while(Iter.IsExist())
	{
		if(Iter->m_ReferenceCount<=0)
		{
			RemoveIter = Iter;
			Iter++;
			Remove(RemoveIter);
		}
		else
		{
			Iter++;
		}
	}
}

bool CSymbolContainer::GetFullSymbol(IN ULPOS Address,OUT PSYMSTR SymbolName,int MaxLength)
{
	int Len;
	ULPOS Offset;
	for(CSymbolContainer::IT SymModIter=Begin();SymModIter.IsExist();SymModIter++)
	{
		if(SymModIter->m_ModuleBase==0 || Address<SymModIter->m_ModuleBase || Address>=SymModIter->m_ModuleBase+SymModIter->m_ModuleSize)
			continue;
		Offset = Address-SymModIter->m_ModuleBase;
		CSymbolMap::IT Iter = SymModIter->m_SymbolMap.Find(Offset);
		if(Iter.IsExist()==false)
			continue;
		Len = TGetFileTitle((PCSYMSTR)SymModIter->m_ModuleName,SymbolName);
		Len+=TStrCpy(&SymbolName[Len],CDbgModule::m_SplitStr);
		TStrCpyLimit(&SymbolName[Len],(PCSYMSTR)*Iter,MaxLength-Len);
		return true;
	}
	return false;
}

PCSYMSTR CSymbolContainer::GetSymbol(IN ULPOS Address)
{
	for(CSymbolContainer::IT SymModIter=Begin();SymModIter.IsExist();SymModIter++)
	{
		if(SymModIter->m_ModuleBase==0 || Address<SymModIter->m_ModuleBase || Address>=SymModIter->m_ModuleBase+SymModIter->m_ModuleSize)
			continue;
		CSymbolMap::IT Iter = SymModIter->m_SymbolMap.Find(Address-SymModIter->m_ModuleBase);
		if(Iter.IsExist()==false)
			continue;
		return *Iter;
	}
	return NULL;
}

CCommentModule*CCommentContainer::GetCommentModule(MODULE_ID MID)
{
	TMap<MODULE_ID,CCommentModule>::IT Iter = Find(MID);
	if(Iter.IsExist())
		return &(*Iter);
	return NULL;
}

CCommentModule*CCommentContainer::InsertCommentModule(MODULE_ID MID)
{
	TMap<MODULE_ID,CCommentModule>::IT Iter = InsertUnique(MID);
	if(Iter.IsExist()==false)
		return NULL;
	Iter->m_ModuleID = MID;
	return &(*Iter);
}

bool CCommentContainer::RemoveCommentModule(MODULE_ID MID)
{
	return Remove(MID)>0;
}

void CCommentContainer::RemoveUnusedCommentModule()
{
	TMap<MODULE_ID,CCommentModule>::IT Iter,RemoveIter;
	Iter = Begin();
	while(Iter.IsExist())
	{
		if(Iter->m_ReferenceCount<=0)
		{
			RemoveIter = Iter;
			Iter++;
			Remove(RemoveIter);
		}
		else
		{
			Iter++;
		}
	}
}


PCSYMSTR CDbgModule::m_SplitStr = "_";

CDbgModule::CDbgModule()
{
	m_ModuleID=0;
	m_ModuleBase = 0;
	m_ModuleSize = 0;
	m_pParam = NULL;
	m_pSymbolModule = NULL;
	m_pCommentModule = NULL;
}

bool CDbgModule::GetOffset(IN PCSYMSTR szSym,INOUT ULPOS*pOffset)
{
	if(m_pSymbolModule==NULL)
		return false;
	for(CSymbolMap::IT Iter = m_pSymbolModule->m_SymbolMap.Begin();Iter!=m_pSymbolModule->m_SymbolMap.End();Iter++)
	{
		if(*Iter==szSym)
		{
			if(pOffset)
				*pOffset = Iter.Key();
			return true;
		}
	}
	return false;
}

bool CDbgModule::GetAddress(IN PCSYMSTR szSym,INOUT ULPOS*pAddress)
{
	if(GetOffset(szSym,pAddress)==false)
		return false;
	if(pAddress)
		*pAddress+=m_ModuleBase;
	return true;
}

bool CDbgModule::GetFullSymbol(IN ULPOS Address,INOUT PSYMSTR szSym,int MaxLength)
{
	int Len;
	ULPOS Offset;
	if(m_pSymbolModule==NULL)
		return false;
	Offset = Address-m_ModuleBase;
	CSymbolMap::IT Iter = m_pSymbolModule->m_SymbolMap.Find(Offset);
	if(Iter==m_pSymbolModule->m_SymbolMap.End())
		return false;
	Len = TStrCpyLimit(szSym,(PCSYMSTR)m_ModuleTitle,MaxLength);
	szSym += Len;
	MaxLength -= Len;
	if(MaxLength<=0)
		return false;
	if(m_ModuleTitle.Length())
	{
		Len = TStrCpyLimit(szSym,m_SplitStr,MaxLength);
		szSym += Len;
		MaxLength -= Len;
		if(MaxLength<=0)
			return false;
	}
	TStrCpyLimit(szSym,(PCSYMSTR)(*Iter),MaxLength);
	return true;
}

PCSYMSTR CDbgModule::GetSymbol(IN ULPOS Address)
{
	if(m_pSymbolModule==NULL)
		return NULL;
	ULPOS Offset = Address-m_ModuleBase;
	CSymbolMap::IT Iter = m_pSymbolModule->m_SymbolMap.Find(Offset);
	if(Iter==m_pSymbolModule->m_SymbolMap.End())
		return NULL;
	return (PCSYMSTR)(*Iter);
}

PCCMTSTR CDbgModule::GetComment(IN ULPOS Address)
{
	if(m_pCommentModule==NULL)
		return NULL;
	ULPOS Offset = Address-m_ModuleBase;
	CCommentMap::IT Iter = m_pCommentModule->m_CommentMap.Find(Offset);
	if(Iter==m_pCommentModule->m_CommentMap.End())
		return NULL;
	return (PCCMTSTR)(*Iter);	
}

bool CDbgModule::GetNearbySymbolAddrress(INOUT ULPOS*pAddress)
{
	if(m_pSymbolModule==NULL)
		return false;
	ULPOS Offset = *pAddress-m_ModuleBase;
	CSymbolMap::IT Iter = m_pSymbolModule->m_SymbolMap.FindAlmost(Offset);
	if(Iter==m_pSymbolModule->m_SymbolMap.End())
		return false;
	*pAddress = Iter.Key() + m_ModuleBase;
	return true;
}

void CDbgModule::AttachSymbolModule(CSymbolModule*pSymbolModule)
{
	m_pSymbolModule = pSymbolModule;
	if(m_pSymbolModule)
		m_pSymbolModule->m_ReferenceCount++;
}

void CDbgModule::DetachSymbolModule(CSymbolContainer*pSymContainer)
{
	if(m_pSymbolModule==NULL)
		return;
	m_pSymbolModule->m_ReferenceCount--;
	if(pSymContainer && m_pSymbolModule->m_ReferenceCount<=0)
		pSymContainer->RemoveSymbolModule(m_pSymbolModule->m_ModuleID);
	m_pSymbolModule=NULL;
}

void CDbgModule::AttachCommentModule(CCommentModule*pCommentModule)
{
	m_pCommentModule = pCommentModule;
	if(m_pCommentModule)
		m_pCommentModule->m_ReferenceCount++;	
}

void CDbgModule::DetachCommentModule(CCommentContainer*pCmtContainer)
{
	if(m_pCommentModule==NULL)
		return;
	m_pCommentModule->m_ReferenceCount--;
	if(pCmtContainer && m_pCommentModule->m_ReferenceCount<=0)
		pCmtContainer->RemoveCommentModule(m_pCommentModule->m_ModuleID);
	m_pCommentModule=NULL;
}

bool CDbgModuleList::GetFullSymbol(IN ULPOS Address,INOUT PSYMSTR szSym,int MaxLength)
{
	CDbgModuleMap::IT ModuleIter = m_DbgModuleMap.Find(Address);
	if(ModuleIter==m_DbgModuleMap.End())
		return false;
	return ModuleIter->GetFullSymbol(Address,szSym,MaxLength);
}

PCSYMSTR CDbgModuleList::GetSymbol(IN ULPOS Address)
{
	CDbgModuleMap::IT ModuleIter = m_DbgModuleMap.Find(Address);
	if(ModuleIter==m_DbgModuleMap.End())
		return NULL;
	return ModuleIter->GetSymbol(Address);
}

CDbgModule*CDbgModuleList::GetModule(IN PCSYMSTR szModule)
{
	PCSYMSTR pStr;
	for(CDbgModuleMap::IT Iter=m_DbgModuleMap.Begin();Iter!=m_DbgModuleMap.End();Iter++)
	{
		if(TCmpModuleName((PCSYMSTR)Iter->m_ModuleFullName,szModule))
			return &(*Iter);
	}
	pStr = TStrRChr(szModule,'\\');
	if(pStr)
	{
		pStr++;
		for(CDbgModuleMap::IT Iter=m_DbgModuleMap.Begin();Iter!=m_DbgModuleMap.End();Iter++)
		{
			if(TCmpModuleName((PCSYMSTR)Iter->m_ModuleFullName,pStr))
				return &(*Iter);
		}
	}
	return NULL;
}

CDbgModule*CDbgModuleList::GetModule(IN ULPOS Address)
{
	CDbgModuleMap::IT Iter = m_DbgModuleMap.Find(Address);
	if(Iter==m_DbgModuleMap.End())
		return NULL;
	return &(*Iter);
}

CDbgModule*	CDbgModuleList::GetModuleByID(IN MODULE_ID ModuleID)
{
	for(CDbgModuleMap::IT Iter=m_DbgModuleMap.Begin();Iter!=m_DbgModuleMap.End();Iter++)
	{
		if(Iter->m_ModuleID==ModuleID)
			return &(*Iter);
	}
	return NULL;
}

CDbgModule*CDbgModuleList::InsertModule(IN PCSYMSTR szModuleFullName,ULPOS Address,ULSIZE Size,MODULE_ID ModuleID)
{
	SYMCHAR szFileNameTitle[MAX_FN_LEN];
	CDbgModuleMap::IT Iter = m_DbgModuleMap.InsertUnique(CDbgModuleMap::RANGE(Address,Address+Size-1));
	if(Iter==m_DbgModuleMap.End())
		return NULL;
	Iter->m_ModuleBase = Address;
	Iter->m_ModuleSize = Size;
	Iter->m_ModuleFullName = szModuleFullName;
	Iter->m_ModuleID = ModuleID;
	TGetFileTitle(szModuleFullName,szFileNameTitle);
	Iter->m_ModuleTitle = szFileNameTitle;
	Iter->m_ModuleName = TGetFileName((PCSYMSTR)Iter->m_ModuleFullName);
	return &(*Iter);
}

bool CDbgModuleList::RemoveModule(IN ULPOS Address)
{
	CDbgModuleMap::IT Iter = m_DbgModuleMap.Find(Address);
	if(Iter==m_DbgModuleMap.End())
		return false;
	if(Iter->m_pSymbolModule)
		Iter->m_pSymbolModule->m_ReferenceCount--;
	m_DbgModuleMap.Remove(Iter);
	return true;
}

bool CDbgModuleList::GetNearbySymbolAddrress(INOUT ULPOS*pAddress)
{
	CDbgModuleMap::IT ModuleIter = m_DbgModuleMap.Find(*pAddress);
	if(ModuleIter==m_DbgModuleMap.End())
		return false;
	return ModuleIter->GetNearbySymbolAddrress(pAddress);
}

PCCMTSTR CDbgModuleList::GetComment(IN ULPOS Address)
{
	CDbgModuleMap::IT ModuleIter = m_DbgModuleMap.Find(Address);
	if(ModuleIter==m_DbgModuleMap.End())
		return NULL;
	return ModuleIter->GetComment(Address);
}

int	CCommentModule::Save(ALTFileStream&Stream)
{
	ULPOS Address;
	int	Length = m_ModuleName.Save(Stream);
	Length+=Stream.Puts(&m_CommentMap.m_Count,sizeof(m_CommentMap.m_Count));
	for(CCommentMap::IT Iter = m_CommentMap.Begin();Iter!=m_CommentMap.End();Iter++)
	{
		Address = Iter.Key();
		Length += Stream.Puts(&Address,sizeof(Address));
		Length += Iter->Save(Stream);
	}
	return Length;
}

int	CCommentModule::Load(ALTFileStream&Stream)
{
	ULPOS Address;
	int Count,Length,TotalLength;	
	Length = m_ModuleName.Load(Stream);
	if(Length==0)
		return 0;
	TotalLength=Length;
	Length = Stream.Gets(&Count,sizeof(Count));
	if(Length==0 || Count > 0x1000)
		return 0;
	TotalLength+=Length;
	CCommentMap::IT Iter;
	CSymStr Str;
	while(Count)
	{
		TotalLength += Stream.Gets(&Address,sizeof(Address));
		Iter=m_CommentMap.InsertUnique(Address);
		if(Iter==m_CommentMap.End())
			return 0;
		Length=Iter->Load(Stream);
		if(Length==0)
		{
			m_CommentMap.Remove(Iter);
			return 0;
		}
		TotalLength+=Length;
		Count--;
	}
	return TotalLength;
}

int	CCommentContainer::Save(ALTFileStream&Stream)
{
	int Length;
	DWORD Ver = CMT_MODULE_VER;
	Length =  Stream.Puts(&Ver,sizeof(Ver));
	Length += Stream.Puts(&m_Count,sizeof(m_Count));
	for(CCommentContainer::IT Iter = Begin();Iter!=End();Iter++)
	{
		Length += Stream.Puts(&Iter.Key(),sizeof(MODULE_ID));
		Length += Iter->Save(Stream);
	}
	return Length;
}

int	CCommentContainer::Load(ALTFileStream&Stream)
{
	DWORD Ver;
	int Count,Length,TotalLength;
	TotalLength = 0;
	Length =  Stream.Gets(&Ver,sizeof(Ver));
	if(Length!=sizeof(Ver) || Ver!=CMT_MODULE_VER)
		return 0;
	TotalLength+=Length;
	Length = Stream.Gets(&Count,sizeof(Count));
	if(Length==0 || Count > 0x10000)
		return 0;
	TotalLength+=Length;
	TMap<MODULE_ID,CCommentModule>::IT Iter;
	MODULE_ID MID;
	while(Count)
	{
		Length = Stream.Gets(&MID,sizeof(MID));
		if(Length==0)
			return 0;
		TotalLength+=Length;
		Iter=InsertUnique(MID);
		if(Iter.IsExist()==false)
			return 0;
		Iter->m_ModuleID = MID;
		Length = Iter->Load(Stream);
		if(Length==0)
		{
			Remove(Iter);
			return 0;
		}
		TotalLength+=Length;
		Count--;
	}
	return TotalLength;
}
