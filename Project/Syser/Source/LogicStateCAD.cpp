#include "StdAfx.h"
#include "LogicStateCAD.h"

CLogicStateCAD::CLogicStateCAD()
{
}

CLogicStateCAD::~CLogicStateCAD()
{

}

bool CLogicStateCAD::LoadRecord(PCSTR FileName)
{
	if(m_FileStream.Open(FileName)==false)
		return false;
	STStatePathEntry::Load(m_FileStream,&m_StateRoot,sizeof(STStatePathEntry));
	m_FileStream.Close();
	return true;
}

void CLogicStateCAD::ClearRecord()
{
	m_StateRoot.NextEntry.Clear();
}

bool CLogicStateCAD::InsertRecord(const STReportInfo&ReportInfo,const TList<STRecogCode>&RecogCodeList,const TList<STPathMethod>&PathMethodList)
{
	TList<STRecogCode>::IT RecogCodeIter;
	TList<STPathMethod>::IT PathMethodIter;
	TStatePathEntrySet::IT SPEIter;
	STStatePathEntry Entry,*pParentEntry;
	CODE_ASSERT(RecogCodeList.Count()==PathMethodList.Count()+1);
	pParentEntry = &m_StateRoot;
	RecogCodeIter = RecogCodeList.Begin();
	PathMethodIter = PathMethodList.Begin();
	while(RecogCodeIter!=RecogCodeList.End())
	{
		Entry.RecogCode = *RecogCodeIter;
		if(RecogCodeIter->CodeType == STRecogCode::IGNORE_ENTRY)
		{
			if(pParentEntry->NextEntry.Count()>1)
				return false;
		}
		else
			SPEIter = pParentEntry->NextEntry.Insert(Entry);
		if(SPEIter == pParentEntry->NextEntry.End())
			SPEIter = pParentEntry->NextEntry.Find(Entry);
		CODE_ASSERT(SPEIter != m_StateRoot.NextEntry.End());
		pParentEntry = &(*SPEIter);
		if(PathMethodIter==PathMethodList.End())
			pParentEntry->ReportInfo = ReportInfo;
		else
			pParentEntry->PathMethod = *PathMethodIter;
		RecogCodeIter++;
		PathMethodIter++;
	}
	return true;
}
