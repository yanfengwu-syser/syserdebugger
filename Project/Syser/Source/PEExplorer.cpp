#include "StdAfx.h"
#include "Syser.h"
#include "PEExplorer.h"


char* TimeDateStampToString(DWORD TimeDateStamp,char* TimeString)
{
	DWORD val= TimeDateStamp;
	DWORD dat =val/86400;
	DWORD dat1 =val%86400;
	DWORD hour=dat1/3600;
	DWORD hour1=dat1%3600;
	DWORD minute=hour1/60;
	DWORD minute1=hour1%60;
	DWORD second=minute1;
	DWORD year=dat/365+1970;
	DWORD year1=dat%365,i;
	DWORD dat2 = (year/4 - 1970/4) - (year/100 - 1970/100) + (year/400-1970/400);
	WORD wDayOfWeek=(WORD)((dat+1)%7);
	if(((year%4)==0&& (year%100)!=0) || ((year %400)==0))    
		dat2--;
	DWORD month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	if(year1<dat2)
	{
		year--;
	}
	dat2 = (year-1970)*365+(year/4 - 1970/4) - (year/100 - 1970/100) + (year/400-1970/400);
	if(((year%4)==0&& (year%100)!=0) || ((year %400)==0))    
		dat2--,month[1]++;;
	dat -= dat2;

	for(i=0;i<12;i++)
	{
		if(dat>=month[i])
			dat-=month[i];
		else
			break;
	}
	dat++;	
	WORD wYear=(WORD)year;
	WORD wMonth=(WORD)i+1;
	WORD wDay=(WORD)dat;
	WORD wHour=(WORD)hour;
	WORD wMinute=(WORD)minute;
	WORD wSecond=(WORD)second;
	TSPrintf(TimeString,"%02d/%02d/%d %02d:%02d:%02d",wDay,wMonth,wYear,wHour,wMinute,wSecond);
	return TimeString;
}

DWORD GetModuleBaseByName(char* FileName)
{
	DWORD BaseAddress=0;
	CDbgModuleMap::IT Iter = gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();

	while(Iter.IsExist())
	{
		if(TStrICmp(Iter->m_ModuleName,FileName)==0)
		{
			BaseAddress = Iter->m_ModuleBase;
			break;
		}
		Iter++;
	}	
	return BaseAddress;
}

enum {
	CMD_ID_PEHEADER_1=WISP_ID_USER_START+0x100,
	CMD_ID_PEHEADER_2,
	CMD_ID_IMPORT_LIST1,
	CMD_ID_IMPORT_LIST2,
	CMD_ID_WND_DATA_DIRECTORY,

};
enum CPEExplorerForm::WISP_FORM_ID
{	
	CMD_ID_BT_EDIT = WISP_ID_USER_START,
	CMD_ID_MAIN_TAB,
	CMD_ID_COMBOBOX_MODULE,
	CMD_ID_WND_PE_HEADER,	
	CMD_ID_WND_RELOCATIONS,
	CMD_ID_WND_IMPORT,
	CMD_ID_WND_EXPORT,
	CMD_ID_BP_DATA_LIST,
};

WISP_FORM_RES_ITEM CPEExplorerForm::m_FormRes[]=
{
	{
		WISP_CTRL_FORM,
		{0,0,780,390},
		WISP_ID_NULL,
		WISP_WS_CAPTION|WISP_WS_BT_CLOSE|WISP_WS_BORDER,
		WSTR("PE Explorer"),
		"\\SyserIcon\\Syser.ico",
	},
	{
		WISP_CTRL_COMBO_BOX,
		{5,5,135,20},
		CMD_ID_COMBOBOX_MODULE,
		WISP_ES_EDIT_NORMAL|WISP_ES_READONLY,
		NULL,
		NULL,
	},
	{
		WISP_CTRL_TAB,
		{5,30,765,330},
		CMD_ID_MAIN_TAB,
		WISP_WS_THIN_BORDER,
		NULL,
	},		
	{WISP_CTRL_NULL}
};


WISP_MSG_MAP_BEGIN(CPEExplorerForm)
	WISP_MSG_MAP_ON_EVENT
	WISP_MSG_MAP_ON_COMMAND
	WISP_MSG_MAP(WISP_WM_FORM_CREATE,OnFormCreate)
WISP_MSG_MAP_END(CWispForm)

WISP_MSG_CMD_MAP_BEGIN(CPEExplorerForm)
	WISP_MSG_CMD_MAP(CMD_ID_COMBOBOX_MODULE,OnModuleSelectComboxCmd)
WISP_MSG_CMD_MAP_END

WISP_MSG_EVENT_MAP_BEGIN(CPEExplorerForm)


WISP_MSG_EVENT_MAP_END

CPEExplorerForm::CPEExplorerForm()
{
	m_pFormRes = m_FormRes;	
	m_pMainTab=NULL;
	m_PEHeaderWnd=NULL;
	m_PERelcationWnd=NULL;
	m_PEImportWnd=NULL;
	m_PEExportWnd=NULL;
}

CPEExplorerForm::~CPEExplorerForm()
{
	if(m_MemPEFile.IsOpened())
		m_MemPEFile.Close();
}
void CPEExplorerForm::UpdateContext(DWORD ModuleBase)
{
	if(!IsWindow())
		return;
	if(SetPEModuleBase(ModuleBase)==false)
		return;
	ChangeModule(ModuleBase);
	m_PEHeaderWnd->LoadPEFile(&m_MemPEFile);
	m_PERelcationWnd->LoadPEFile(&m_MemPEFile);
	m_PEImportWnd->LoadPEFile(&m_MemPEFile);
	m_PEExportWnd->LoadPEFile(&m_MemPEFile);
	m_DataDirectoryWnd->LoadPEFile(&m_MemPEFile);
}


bool CPEExplorerForm::SetPEModuleBase(DWORD ModuleBase)
{
	if(m_MemPEFile.IsOpened())
	{
		m_MemPEFile.Close();	
	}
	return m_MemPEFile.Open(ModuleBase,PE_OPEN_ALL,CDebugger::ReadMemory,gpSyser->m_pDebugger);		
}
void CPEExplorerForm::Popup()
{
	if(IsWindow())
	{
		Show();
	}
	else
	{
		CreateForm(NULL);
	}
}
bool CPEExplorerForm::OnModuleSelectComboxCmd(IN WISP_MSG* pMsg)
{
	NUM_PTR ItemData;
	if(pMsg->Command.CmdMsg == WISP_CMD_COMBOX_SELCHANGE)
	{
		ItemData = m_ModuleSelectList->m_ComboList.GetItemData((HANDLE)pMsg->Command.Param2);
		UpdateContext((DWORD)ItemData);
	}
	return true;
}
bool CPEExplorerForm::ChangeModule(DWORD BaseAddress)
{
	HANDLE hItem=NULL;
	DWORD Index=0,Count;
	NUM_PTR ItemData;

	Count = m_ModuleSelectList->m_ComboList.GetItemCount();
	do 
	{
		hItem = m_ModuleSelectList->m_ComboList.GetItem(Index);
		if(hItem==NULL)
			break;
		ItemData = m_ModuleSelectList->m_ComboList.GetItemData(hItem);
		if(BaseAddress==(DWORD)ItemData)
		{
			m_ModuleSelectList->SelectItem(Index);
			break;
		}
		Index++;
	} while(Index < Count);
	return true;
}
bool CPEExplorerForm::OnFormCreate(WISP_MSG*pMsg)
{
	m_pMainTab = (CWispTabWnd*) GetFormItem(CMD_ID_MAIN_TAB);
	m_PEHeaderWnd = new CPEHeaderWnd;
	m_PEHeaderWnd->Create(NULL,0,0,0,0,m_pMainTab,CMD_ID_WND_PE_HEADER,WISP_WS_NULL);
	m_PEHeaderWnd->SetOwner(this);
	m_pMainTab->InsertWnd(WSTR("PE Header"),m_PEHeaderWnd);
	m_PEHeaderWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
	m_ModuleSelectList = (CWispComboBox*)GetFormItem(CMD_ID_COMBOBOX_MODULE);

	CDbgModuleMap::IT Iter = gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();
	while(Iter.IsExist())
	{		
		HANDLE hListItem = m_ModuleSelectList->m_ComboList.InsertItemA(Iter->m_ModuleName);
		m_ModuleSelectList->m_ComboList.SetItemData(hListItem,0,Iter->m_ModuleBase);	
		Iter++;
	}		
	m_ModuleSelectList->SelectItem(0);
	m_DataDirectoryWnd = new CPEDataDirectoryWnd;
	m_DataDirectoryWnd->Create(NULL,0,0,0,0,m_pMainTab,CMD_ID_WND_DATA_DIRECTORY,WISP_WS_NULL);
	m_DataDirectoryWnd->SetOwner(this);
	m_pMainTab->InsertWnd(WSTR("Data Directories"),m_DataDirectoryWnd);
	m_DataDirectoryWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);

	m_PERelcationWnd = new CPERelcationWnd;
	m_PERelcationWnd->Create(NULL,0,0,0,0,m_pMainTab,CMD_ID_WND_RELOCATIONS,WISP_WS_NULL);
	m_PERelcationWnd->SetOwner(this);
	m_pMainTab->InsertWnd(WSTR("Relocations"),m_PERelcationWnd);
	m_PERelcationWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);
	
	m_PEImportWnd = new CPEImportWnd;
	m_PEImportWnd->Create(NULL,0,0,0,0,m_pMainTab,CMD_ID_WND_IMPORT,WISP_WS_NULL);
	m_PEImportWnd->SetOwner(this);
	m_pMainTab->InsertWnd(WSTR("Imports"),m_PEImportWnd);
	m_PEImportWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);

	m_PEExportWnd = new CPEExportWnd;
	m_PEExportWnd->Create(NULL,0,0,0,0,m_pMainTab,CMD_ID_WND_EXPORT,WISP_WS_NULL);
	m_PEExportWnd->SetOwner(this);
	m_pMainTab->InsertWnd(WSTR("Exports"),m_PEExportWnd);
	m_PEExportWnd->AddAdvStyle(WISP_WAS_AUTO_DELETE);

	return true;
}


CPEHeaderWnd::CPEHeaderWnd()
{

}
CPEHeaderWnd::~CPEHeaderWnd()
{

}
WISP_MSG_MAP_BEGIN(CPEHeaderWnd)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP_END(CWispWnd)
WISP_MSG_EVENT_MAP_BEGIN(CPEHeaderWnd)

WISP_MSG_EVENT_MAP_END
bool CPEHeaderWnd::OnCreate(WISP_MSG*pMsg)
{
	m_pPEHeaderList1.Create(NULL,5,5,372,294,this,CMD_ID_PEHEADER_1,		WISP_WS_THIN_BORDER|WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WLS_VERT_LINE|WISP_WLS_HORZ_LINE);
	m_pPEHeaderList2.Create(NULL,385,5,372,294,this,CMD_ID_PEHEADER_2,		WISP_WS_THIN_BORDER|WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WLS_VERT_LINE|WISP_WLS_HORZ_LINE);
	InitPEHeaderList();
	return true;
}
bool CPEHeaderWnd::LoadPEFile(CMemPEFile* pMemPEFile)
{
	char TimeString[50];
	
	TimeDateStampToString(pMemPEFile->m_PEHead.TimeDateStamp-gpSyser->m_TimeZoneBias,TimeString);
	m_pPEHeaderList1.SetItemNum(m_Item[0],1,pMemPEFile->m_PEHead.Machine,WSTR("0x%04x"));
	m_pPEHeaderList1.SetItemNum(m_Item[1],1,pMemPEFile->m_PEHead.NumberOfSections,WSTR("0x%04x"));
	m_pPEHeaderList1.SetItemNum(m_Item[2],1,pMemPEFile->m_PEHead.TimeDateStamp,WSTR("0x%08x"));
	m_pPEHeaderList1.SetItemTextA(m_Item[2],2,TimeString);
	m_pPEHeaderList1.SetItemNum(m_Item[3],1,pMemPEFile->m_PEHead.PointerToSymbolTable,WSTR("0x%08x"));
	m_pPEHeaderList1.SetItemNum(m_Item[4],1,pMemPEFile->m_PEHead.NumberOfSymbols,WSTR("0x%08x"));
	m_pPEHeaderList1.SetItemNum(m_Item[5],1,pMemPEFile->m_PEHead.SizeOfOptionalHeader,WSTR("0x%04x"));
	m_pPEHeaderList1.SetItemNum(m_Item[6],1,pMemPEFile->m_PEHead.Characteristics,WSTR("0x%08x"));
	m_pPEHeaderList1.SetItemNum(m_Item[7],1,pMemPEFile->m_PEHead.Magic,WSTR("0x%08x"));
	m_pPEHeaderList1.SetItemNum(m_Item[8],1,(pMemPEFile->m_PEHead.MinorLinkerVersion << 8) | pMemPEFile->m_PEHead.MajorLinkerVersion,WSTR("0x%04x"));
	TSPrintf(TimeString,"%d.%d",pMemPEFile->m_PEHead.MajorLinkerVersion,pMemPEFile->m_PEHead.MinorLinkerVersion);
	m_pPEHeaderList1.SetItemTextA(m_Item[8],2,TimeString);
	m_pPEHeaderList1.SetItemNum(m_Item[9],1,pMemPEFile->m_PEHead.SizeOfCode,WSTR("0x%08x"));
	m_pPEHeaderList1.SetItemNum(m_Item[10],1,pMemPEFile->m_PEHead.SizeOfInitializedData,WSTR("0x%08x"));
	m_pPEHeaderList1.SetItemNum(m_Item[11],1,pMemPEFile->m_PEHead.SizeOfUninitializedData,WSTR("0x%08x"));
	m_pPEHeaderList1.SetItemNum(m_Item[12],1,pMemPEFile->m_PEHead.AddressOfEntryPoint,WSTR("0x%08x"));
	m_pPEHeaderList1.SetItemNum(m_Item[13],1,pMemPEFile->m_PEHead.BaseOfCode,WSTR("0x%08x"));
	m_pPEHeaderList1.SetItemNum(m_Item[14],1,pMemPEFile->m_PEHead.BaseOfData,WSTR("0x%08x"));
	m_pPEHeaderList1.SetItemNum(m_Item[15],1,pMemPEFile->m_PEHead.ImageBase,WSTR("0x%08x"));

	m_pPEHeaderList2.SetItemNum(m_HItem[0],1,pMemPEFile->m_PEHead.SectionAlignment,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[1],1,pMemPEFile->m_PEHead.FileAlignment,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[2],1,(pMemPEFile->m_PEHead.MinorOperatingSystemVersion <<16)| pMemPEFile->m_PEHead.MajorOperatingSystemVersion,WSTR("0x%08x"));
	TSPrintf(TimeString,"%d.%d",pMemPEFile->m_PEHead.MajorOperatingSystemVersion,pMemPEFile->m_PEHead.MinorOperatingSystemVersion);
	m_pPEHeaderList1.SetItemTextA(m_HItem[2],2,TimeString);
	m_pPEHeaderList2.SetItemNum(m_HItem[3],1,(pMemPEFile->m_PEHead.MinorImageVersion<<16)|pMemPEFile->m_PEHead.MajorImageVersion,WSTR("0x%08x"));
	TSPrintf(TimeString,"%d.%d",pMemPEFile->m_PEHead.MajorImageVersion,pMemPEFile->m_PEHead.MinorImageVersion);
	m_pPEHeaderList1.SetItemTextA(m_HItem[3],2,TimeString);
	m_pPEHeaderList2.SetItemNum(m_HItem[4],1,(pMemPEFile->m_PEHead.MinorSubsystemVersion<<16)|pMemPEFile->m_PEHead.MajorSubsystemVersion,WSTR("0x%08x"));
	TSPrintf(TimeString,"%d.%d",pMemPEFile->m_PEHead.MajorSubsystemVersion,pMemPEFile->m_PEHead.MinorSubsystemVersion);
	m_pPEHeaderList1.SetItemTextA(m_HItem[4],2,TimeString);
	m_pPEHeaderList2.SetItemNum(m_HItem[5],1,pMemPEFile->m_PEHead.Win32VersionValue,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[6],1,pMemPEFile->m_PEHead.SizeOfImage,WSTR("0x%08x"));
	TSPrintf(TimeString,"%d bytes",pMemPEFile->m_PEHead.SizeOfImage);
	m_pPEHeaderList2.SetItemTextA(m_HItem[6],2,TimeString);
	m_pPEHeaderList2.SetItemNum(m_HItem[7],1,pMemPEFile->m_PEHead.SizeOfHeaders,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[8],1,pMemPEFile->m_PEHead.CheckSum,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[9],1,pMemPEFile->m_PEHead.Subsystem,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[10],1,pMemPEFile->m_PEHead.DllCharacteristics,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[11],1,pMemPEFile->m_PEHead.SizeOfStackReserve,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[12],1,pMemPEFile->m_PEHead.SizeOfStackCommit,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[13],1,pMemPEFile->m_PEHead.SizeOfHeapReserve,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[14],1,pMemPEFile->m_PEHead.SizeOfHeapCommit,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[15],1,pMemPEFile->m_PEHead.LoaderFlags,WSTR("0x%08x"));
	m_pPEHeaderList2.SetItemNum(m_HItem[16],1,pMemPEFile->m_PEHead.NumberOfRvaAndSizes,WSTR("0x%08x"));
	return true;
}
bool CPEHeaderWnd::InitPEHeaderList()
{		
	m_pPEHeaderList1.InsertColumn(WSTR("Field Name"),165);
	m_pPEHeaderList1.InsertColumn(WSTR("Date Value"),80);
	m_pPEHeaderList1.InsertColumn(WSTR("Description"),120);
	m_Item[0]=m_pPEHeaderList1.InsertItem(WSTR("Machine"));
	m_Item[1]=m_pPEHeaderList1.InsertItem(WSTR("Number of Sections"));
	m_Item[2]=m_pPEHeaderList1.InsertItem(WSTR("Time Date Stamp"));
	m_Item[3]=m_pPEHeaderList1.InsertItem(WSTR("Pointer to Symbol Table"));
	m_Item[4]=m_pPEHeaderList1.InsertItem(WSTR("Number of Symbols"));
	m_Item[5]=m_pPEHeaderList1.InsertItem(WSTR("Size of Optional Header"));
	m_Item[6]=m_pPEHeaderList1.InsertItem(WSTR("Characteristics"));
	m_Item[7]=m_pPEHeaderList1.InsertItem(WSTR("Magic"));
	m_Item[8]=m_pPEHeaderList1.InsertItem(WSTR("Linker Version"));
	m_Item[9]=m_pPEHeaderList1.InsertItem(WSTR("Size of code"));
	m_Item[10]=m_pPEHeaderList1.InsertItem(WSTR("Size of Initialized Data"));
	m_Item[11]=m_pPEHeaderList1.InsertItem(WSTR("Size of Uninitialized Data"));
	m_Item[12]=m_pPEHeaderList1.InsertItem(WSTR("Address of entry Point"));
	m_Item[13]=m_pPEHeaderList1.InsertItem(WSTR("Base of code"));
	m_Item[14]=m_pPEHeaderList1.InsertItem(WSTR("Base of data"));
	m_Item[15]=m_pPEHeaderList1.InsertItem(WSTR("Image Base"));	
	m_pPEHeaderList2.InsertColumn(WSTR("Field Name"),165);
	m_pPEHeaderList2.InsertColumn(WSTR("Date Value"),90);
	m_pPEHeaderList2.InsertColumn(WSTR("Description"),110);



	m_HItem[0]=m_pPEHeaderList2.InsertItem(WSTR("Section Alignment"));
	m_HItem[1]=m_pPEHeaderList2.InsertItem(WSTR("File Alignment"));
	m_HItem[2]=m_pPEHeaderList2.InsertItem(WSTR("Operating System Version"));
	m_HItem[3]=m_pPEHeaderList2.InsertItem(WSTR("Image Version"));
	m_HItem[4]=m_pPEHeaderList2.InsertItem(WSTR("Subsystem Version"));
	m_HItem[5]=m_pPEHeaderList2.InsertItem(WSTR("Win32 Version Value"));
	m_HItem[6]=m_pPEHeaderList2.InsertItem(WSTR("Size of Image"));
	m_HItem[7]=m_pPEHeaderList2.InsertItem(WSTR("Size of Headers"));
	m_HItem[8]=m_pPEHeaderList2.InsertItem(WSTR("Checksum"));
	m_HItem[9]=m_pPEHeaderList2.InsertItem(WSTR("Subsystem"));
	m_HItem[10]=m_pPEHeaderList2.InsertItem(WSTR("Dll Characteristics"));
	m_HItem[11]=m_pPEHeaderList2.InsertItem(WSTR("Size of Stack Reserve"));
	m_HItem[12]=m_pPEHeaderList2.InsertItem(WSTR("Size of Stack Commit"));
	m_HItem[13]=m_pPEHeaderList2.InsertItem(WSTR("Size of Heap Reserve"));
	m_HItem[14]=m_pPEHeaderList2.InsertItem(WSTR("Size of Heap Commit"));
	m_HItem[15]=m_pPEHeaderList2.InsertItem(WSTR("Loader Flags"));
	m_HItem[16]=m_pPEHeaderList2.InsertItem(WSTR("Number of Data Directories"));
	return true;
}

CPERelcationWnd::CPERelcationWnd()
{

}
CPERelcationWnd::~CPERelcationWnd()
{

}
WISP_MSG_MAP_BEGIN(CPERelcationWnd)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP_END(CWispWnd)
WISP_MSG_EVENT_MAP_BEGIN(CPERelcationWnd)

WISP_MSG_EVENT_MAP_END
bool CPERelcationWnd::OnCreate(WISP_MSG*pMsg)
{
	m_RelPageList.Create(NULL,5,5,372,294,this,CMD_ID_PEHEADER_1,		WISP_WS_THIN_BORDER|WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WLS_VERT_LINE|WISP_WLS_HORZ_LINE);
	m_RelEntryList.Create(NULL,385,5,372,294,this,CMD_ID_PEHEADER_2,		WISP_WS_THIN_BORDER|WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WLS_VERT_LINE|WISP_WLS_HORZ_LINE);
	InitList();
	return true;
}
bool CPERelcationWnd::LoadPEFile(CMemPEFile* pMemPEFile)
{
	return true;
}
bool CPERelcationWnd::InitList()
{		
	m_RelPageList.InsertColumn(WSTR("RVA"),165);
	m_RelPageList.InsertColumn(WSTR("Items"),90);
	m_RelPageList.InsertColumn(WSTR("Owner"),110);
	m_RelEntryList.InsertColumn(WSTR("Offset"),165);
	m_RelEntryList.InsertColumn(WSTR("Types"),90);
	return true;
}


CPEImportWnd::CPEImportWnd()
{

}
CPEImportWnd::~CPEImportWnd()
{

}
WISP_MSG_MAP_BEGIN(CPEImportWnd)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_ON_COMMAND
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP_END(CWispWnd)

WISP_MSG_EVENT_MAP_BEGIN(CPEImportWnd)

WISP_MSG_EVENT_MAP_END

WISP_MSG_CMD_MAP_BEGIN(CPEImportWnd)
WISP_MSG_CMD_MAP(CMD_ID_IMPORT_LIST1,OnModuleSelected)
WISP_MSG_CMD_MAP_END
DWORD CPEImportWnd::GetModuleBaseByName(char* FileName)
{
	DWORD BaseAddress=0;
	CDbgModuleMap::IT Iter = gpSyser->m_pDebugger->m_ModuleList.m_DbgModuleMap.Begin();

	while(Iter.IsExist())
	{
		if(TStrICmp(Iter->m_ModuleName,FileName)==0)
		{
			BaseAddress = Iter->m_ModuleBase;
			break;
		}
		Iter++;
	}	
	return BaseAddress;
}
bool CPEImportWnd::OnModuleSelected(WISP_MSG*pMsg)
{
	CMemPEFile ImportPEFile;
	bool bImportOpen=false;
	DWORD FunAddress;
	int Index;
	DWORD ImportModuleBase=0;
	if(pMsg->Command.CmdMsg!=WISP_CMD_ITEM_SELECTED)	
		return true;
	if(gpSyser->m_pDebugger==NULL)
		return true;	
	m_ImportEntryList.ClearChildItem();
	HANDLE hItem = m_ImportModuleList.GetNextItem(NULL,WISP_WLIS_SELECTED);
	NUM_PTR ItemData;
	ItemData = m_ImportModuleList.GetItemData(hItem);
	int i = (int)ItemData,j,k;
	if(i >= m_pMemPEFile->m_ImportModuleCount)
		return true;
	k = m_pMemPEFile->m_ImportModule[i].FuncCount;
	IMPORT_FUNC* pFunc=	m_pMemPEFile->m_ImportModule[i].FuncList;
	
	ImportModuleBase = GetModuleBaseByName(m_pMemPEFile->m_ImportModule[i].FileName);
	if(ImportModuleBase)
	{
		bImportOpen = ImportPEFile.Open(ImportModuleBase,PE_OPEN_ALL|PE_OPEN_NO_IMPORT,CDebugger::ReadMemory,gpSyser->m_pDebugger);				
	}
	for(j=0;j<k;j++)
	{
		hItem = m_ImportEntryList.InsertItem(pFunc[j].ThunkAddr,NULL,WSTR("0x%08X"));
		m_ImportEntryList.SetItemData(hItem,0,pFunc[j].ThunkAddr);
		if(bImportOpen)
		{
			FunAddress = ImportPEFile.GetExportFunc(pFunc[j].FuncName,&Index);
			m_ImportEntryList.SetItemNum(hItem,1,Index,WSTR("0x%04X"));	
			m_ImportEntryList.SetItemNum(hItem,2,FunAddress,WSTR("0x%08X"));
			m_ImportEntryList.SetItemData(hItem,2,FunAddress);
		}		
		m_ImportEntryList.SetItemTextA(hItem,3,pFunc[j].FuncName);
	}
	if(bImportOpen)
		ImportPEFile.Close();
	return true;
}

bool CPEImportWnd::OnCreate(WISP_MSG*pMsg)
{
	m_ImportModuleList.Create(NULL,5,5,225,294,this,CMD_ID_IMPORT_LIST1,		WISP_WS_THIN_BORDER|WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WLS_VERT_LINE|WISP_WLS_HORZ_LINE);
	m_ImportEntryList.Create(NULL,240,5,510,294,this,CMD_ID_IMPORT_LIST2,		WISP_WS_THIN_BORDER|WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WLS_VERT_LINE|WISP_WLS_HORZ_LINE);
	InitList();
	return true;
}
bool CPEImportWnd::LoadPEFile(CMemPEFile* pMemPEFile)
{
	int i,j;
	HANDLE hItem;
	DWORD ImportModuleBase;
	m_pMemPEFile=pMemPEFile;
	j=pMemPEFile->m_ImportModuleCount;
	m_ImportModuleList.ClearChildItem();
	for(i=0;i<j;i++)
	{		
		hItem = m_ImportModuleList.InsertItem(pMemPEFile->m_ImportModule[i].Address,NULL,WSTR("0x%08X"));
		m_ImportModuleList.SetItemData(hItem,2,pMemPEFile->m_ImportModule[i].Address);
		m_ImportModuleList.SetItemTextA(hItem,1,pMemPEFile->m_ImportModule[i].FileName);
		m_ImportModuleList.SetItemData(hItem,0,i);
		ImportModuleBase = GetModuleBaseByName(pMemPEFile->m_ImportModule[i].FileName);
		m_ImportModuleList.SetItemData(hItem,1,ImportModuleBase);
		m_ImportModuleList.SetItemNum(hItem,2,pMemPEFile->m_ImportModule[i].FuncCount,WSTR("%d"));		
	}
	return true;
}
bool CPEImportWnd::InitList()
{		
	m_ImportModuleList.InsertColumn(WSTR("RVA"),70);
	m_ImportModuleList.InsertColumn(WSTR("Name"),100);
	m_ImportModuleList.InsertColumn(WSTR("Count"),40);
	m_ImportEntryList.InsertColumn(WSTR("RVA"),70);
	m_ImportEntryList.InsertColumn(WSTR("Hint"),50);
	m_ImportEntryList.InsertColumn(WSTR("Entry Point"),70);
	m_ImportEntryList.InsertColumn(WSTR("Name"),270);
	return true;
}

CPEExportWnd::CPEExportWnd()
{

}
CPEExportWnd::~CPEExportWnd()
{

}
WISP_MSG_MAP_BEGIN(CPEExportWnd)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP_END(CWispWnd)
WISP_MSG_EVENT_MAP_BEGIN(CPEExportWnd)

WISP_MSG_EVENT_MAP_END
bool CPEExportWnd::OnCreate(WISP_MSG*pMsg)
{
	m_ExportEntryList.Create(NULL,5,5,736,294,this,CMD_ID_PEHEADER_1,		WISP_WS_THIN_BORDER|WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WLS_VERT_LINE|WISP_WLS_HORZ_LINE);
	InitList();
	return true;
}
bool CPEExportWnd::LoadPEFile(CMemPEFile* pMemPEFile)
{
	int i = 0,j; 
	HANDLE hItem;
	m_ExportEntryList.ClearChildItem();
	j = pMemPEFile->m_ExportFuncCount;
	for(i=0;i<j;i++)
	{		
		hItem = m_ExportEntryList.InsertItem(pMemPEFile->m_ExportFunc[i].Address,NULL,WSTR("0x%08X"));
		m_ExportEntryList.SetItemData(hItem,0,pMemPEFile->m_ExportFunc[i].Address);
		m_ExportEntryList.SetItemNum(hItem,1,pMemPEFile->m_ExportFunc[i].FuncOrd,WSTR("%d"));
		m_ExportEntryList.SetItemNum(hItem,2,pMemPEFile->m_ExportFunc[i].ThunkAddr,WSTR("0x%08X"));
		m_ExportEntryList.SetItemData(hItem,2,pMemPEFile->m_ExportFunc[i].ThunkAddr);
		m_ExportEntryList.SetItemTextA(hItem,3,pMemPEFile->m_ExportFunc[i].FuncName);		
	}
	return true;
}
bool CPEExportWnd::InitList()
{		
	m_ExportEntryList.InsertColumn(WSTR("Entry Point"),80);
	m_ExportEntryList.InsertColumn(WSTR("Ord"),50);
	m_ExportEntryList.InsertColumn(WSTR("Thunk"),80);
	m_ExportEntryList.InsertColumn(WSTR("Name"),490);	
	return true;
}
CPEExportList::CPEExportList()
{

}

CPEExportList::~CPEExportList()
{

}

WISP_MSG_MAP_BEGIN(CPEExportList) 
	WISP_MSG_MAP(WISP_WM_MOUSE_DBCLICK,OnMouseDBClick)
WISP_MSG_MAP_END(CWispList)


bool CPEExportList::OnMouseDBClick(IN WISP_MSG*pMsg)
{
	WISP_RECT CellRC;
	HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	NUM_PTR ItemData;
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON)
	{
		GetItemCellRect(hItem,2,&CellRC);
		if(pMsg->MsgMouseWndPT.x >= CellRC.x && pMsg->MsgMouseWndPT.x<=CellRC.x+CellRC.cx)
		{
			ItemData = GetItemData(hItem,2);
			VIEW_DATA((DWORD)ItemData);
		}
		else
		{
			ItemData = GetItemData(hItem,0);
			VIEW_CODE((DWORD)ItemData,true);
		}
	}	
	return true;
}

CPEImportModuleList::CPEImportModuleList()
{

}

CPEImportModuleList::~CPEImportModuleList()
{

}

WISP_MSG_MAP_BEGIN(CPEImportModuleList) 
WISP_MSG_MAP(WISP_WM_MOUSE_DBCLICK,OnMouseDBClick)
WISP_MSG_MAP_END(CWispList)


bool CPEImportModuleList::OnMouseDBClick(IN WISP_MSG*pMsg)
{
	WISP_RECT CellRC;
	HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	NUM_PTR ItemData;
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON)
	{
		GetItemCellRect(hItem,0,&CellRC);
		if(pMsg->MsgMouseWndPT.x >= CellRC.x && pMsg->MsgMouseWndPT.x<=CellRC.x+CellRC.cx)
		{
			ItemData = GetItemData(hItem,2);
			VIEW_DATA((DWORD)ItemData);
		}
		else
		{
			ItemData = GetItemData(hItem,1);
			VIEW_DATA((DWORD)ItemData);
		}
	}	
	return true;
}

CPEImportEntryList::CPEImportEntryList()
{

}

CPEImportEntryList::~CPEImportEntryList()
{

}

WISP_MSG_MAP_BEGIN(CPEImportEntryList) 
WISP_MSG_MAP(WISP_WM_MOUSE_DBCLICK,OnMouseDBClick)
WISP_MSG_MAP_END(CWispList)


bool CPEImportEntryList::OnMouseDBClick(IN WISP_MSG*pMsg)
{
	WISP_RECT CellRC;
	HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	NUM_PTR ItemData;
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON)
	{
		GetItemCellRect(hItem,0,&CellRC);
		if(pMsg->MsgMouseWndPT.x >= CellRC.x && pMsg->MsgMouseWndPT.x<=CellRC.x+CellRC.cx)
		{
			ItemData = GetItemData(hItem,0);
			VIEW_DATA((DWORD)ItemData);
		}
		else
		{
			ItemData = GetItemData(hItem,2);
			VIEW_CODE((DWORD)ItemData,true);
		}
	}	
	return true;
}

CPEDataDirectoryWnd::CPEDataDirectoryWnd()
{

}
CPEDataDirectoryWnd::~CPEDataDirectoryWnd()
{

}
WISP_MSG_MAP_BEGIN(CPEDataDirectoryWnd)
WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
WISP_MSG_MAP_END(CWispWnd)
WISP_MSG_EVENT_MAP_BEGIN(CPEDataDirectoryWnd)

WISP_MSG_EVENT_MAP_END
bool CPEDataDirectoryWnd::OnCreate(WISP_MSG*pMsg)
{
	m_DataDirectoryList.Create(NULL,5,5,450,278,this,CMD_ID_WND_DATA_DIRECTORY,WISP_WS_THIN_BORDER|WISP_WLS_COLUMN_TITLE|WISP_WLS_SELECTED_ALWAYS|WISP_WLS_VERT_LINE|WISP_WLS_HORZ_LINE);
	InitList();
	return true;
}
bool CPEDataDirectoryWnd::LoadPEFile(CMemPEFile* pMemPEFile)
{
	DWORD i,Address;
	for(i=0;i<pMemPEFile->m_PEHead.NumberOfRvaAndSizes;i++)
	{
		Address=pMemPEFile->m_PEHead.DataDirectory[i].VirtualAddress;
		if(Address)
			Address+=pMemPEFile->m_ImageBase;
		m_DataDirectoryList.SetItemNum(m_DataDirectoryItem[i],1,Address,WSTR("0x%08X"));
		m_DataDirectoryList.SetItemData(m_DataDirectoryItem[i],1,Address);
		m_DataDirectoryList.SetItemNum(m_DataDirectoryItem[i],2,pMemPEFile->m_PEHead.DataDirectory[i].Size,WSTR("0x%08X"));
	}
	return true;
}
bool CPEDataDirectoryWnd::InitList()
{		
	m_DataDirectoryList.InsertColumn(WSTR("Directory Name"),205);
	m_DataDirectoryList.InsertColumn(WSTR("Virtual Address"),90);
	m_DataDirectoryList.InsertColumn(WSTR("Size"),90);
	m_DataDirectoryItem[0]=m_DataDirectoryList.InsertItem(WSTR("Export Table"));
	m_DataDirectoryItem[1]=m_DataDirectoryList.InsertItem(WSTR("Import Table"));
	m_DataDirectoryItem[2]=m_DataDirectoryList.InsertItem(WSTR("Resource Table"));
	m_DataDirectoryItem[3]=m_DataDirectoryList.InsertItem(WSTR("Exception Table"));
	m_DataDirectoryItem[4]=m_DataDirectoryList.InsertItem(WSTR("Certificate Table"));
	m_DataDirectoryItem[5]=m_DataDirectoryList.InsertItem(WSTR("Relocation Table"));
	m_DataDirectoryItem[6]=m_DataDirectoryList.InsertItem(WSTR("Debug Data"));
	m_DataDirectoryItem[7]=m_DataDirectoryList.InsertItem(WSTR("Architecture-specific data"));
	m_DataDirectoryItem[8]=m_DataDirectoryList.InsertItem(WSTR("Machine Value (MIPS GP)"));
	m_DataDirectoryItem[9]=m_DataDirectoryList.InsertItem(WSTR("TLS Table"));
	m_DataDirectoryItem[10]=m_DataDirectoryList.InsertItem(WSTR("Load Configuration Table"));
	m_DataDirectoryItem[11]=m_DataDirectoryList.InsertItem(WSTR("Bound Import Table"));
	m_DataDirectoryItem[12]=m_DataDirectoryList.InsertItem(WSTR("Import Address Table"));
	m_DataDirectoryItem[13]=m_DataDirectoryList.InsertItem(WSTR("Delay Import Descriptor"));
	m_DataDirectoryItem[14]=m_DataDirectoryList.InsertItem(WSTR("COM+ Runtime Header"));
	m_DataDirectoryItem[15]=m_DataDirectoryList.InsertItem(WSTR("(15) Reserved"));
	return true;
}

CPEDataDirectoryList::CPEDataDirectoryList()
{

}

CPEDataDirectoryList::~CPEDataDirectoryList()
{

}

WISP_MSG_MAP_BEGIN(CPEDataDirectoryList) 
WISP_MSG_MAP(WISP_WM_MOUSE_DBCLICK,OnMouseDBClick)
WISP_MSG_MAP_END(CWispList)


bool CPEDataDirectoryList::OnMouseDBClick(IN WISP_MSG*pMsg)
{
	HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	NUM_PTR ItemData;
	if(pMsg->KeyEvent.KeyType == WISP_VK_LBUTTON)
	{		
		ItemData = GetItemData(hItem,1);
		VIEW_DATA((DWORD)ItemData);		
	}	
	return true;
}