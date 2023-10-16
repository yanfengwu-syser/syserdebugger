#include "stdafx.h"
#include "TypeViewerWnd.h"
#include "SyserSymAnalyzer.h"
#include "Syser.h"

#define NORMAL_TEXT_COLOR WISP_RGB(255,255,255)
#define CHANGE_TEXT_COLOR WISP_RGB(255,0,0)

WISP_MENU_RES_ITEM TypeViewerMenu[]=
{
	{WSTR("Delete Watch"),EVENT_ID_TYPEVIEWERWND_DELETE_WATCH,12*16+10},
	{WSTR("Hexadecimal Display"),EVENT_ID_TYPEVIEWERWND_HEX_DISPLAY,0*16+13},
	WISP_MENU_RES_END
};

enum CTypeViewerWnd::CHILD_CMD_ID
{
	CHILD_CMD_TYPELIST=WISP_ID_USER_START,
};

WISP_MSG_MAP_BEGIN(CTypeViewerWnd)
	WISP_MSG_MAP(WISP_WM_KEY_EVENT,OnKeyEvent)
	WISP_MSG_MAP(WISP_WM_CREATE,OnCreate)
	WISP_MSG_MAP(WISP_WM_DESTROY,OnDestroy)
	WISP_MSG_MAP_ON_EVENT
WISP_MSG_MAP_END(CWispList) 

WISP_MSG_EVENT_MAP_BEGIN(CTypeViewerWnd)
	WISP_MSG_EVENT_MAP(EVENT_ID_TYPEVIEWERWND_HEX_DISPLAY,OnHexDisplayEvent)
	WISP_MSG_EVENT_MAP(EVENT_ID_TYPEVIEWERWND_DELETE_WATCH,OnDeleteWatchEvent)
WISP_MSG_EVENT_MAP_END

bool CTypeViewerWnd::OnHexDisplayEvent(IN WISP_MSG* pMsg)
{	
	TYPE_VALUE_ATTR ValueAttr;	
	HANDLE hItem,hNextItem,hSelectItem;
	CWispString* str;
	WCHAR ValueBuf[512];
	hItem = GetNextListItem(NULL,WISP_WLIS_SELECTED);	
	if(hItem==NULL)
		return true;
	if(hItem)
		hNextItem=GetNextItem(hItem);
	hSelectItem=hItem;
	while(hItem)
	{
		ValueAttr.ItemData = GetItemData(hItem,LIST_COLUMN_VALUE);	
		ValueAttr.Attr.Attribute^=ITEM_ATTRIBUTE_HEX;		
		SetItemData(hItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);
		str =&GetItemText(hItem);
		hItem = GetNextListItem(hItem);
		if(hItem==hNextItem)
			break;
	}
	UpdateItemContext(hSelectItem,ValueBuf,sizeof(ValueBuf)/sizeof(ValueBuf[0]));
	//UpdateDisplay(hSelectItem);
	return true;
}

PSDTYPE_INFILE CTypeViewerWnd::GetTypeByDataIndex(CSDSModule* pSDSModule,DWORD DataIndex)
{	
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUDTDataItem;
	PSDREFERENCETYPE pReferenceType;
	pUDTDataItem = pSDSModule->GetDataSymbol(DataIndex);
	if(pUDTDataItem==NULL)
		return NULL;
	pType = pSDSModule->GetTypeSymbol(pUDTDataItem->TypeId);
	if(pType!=NULL)
	{
		if(pType->Type==SD_REFERENCE)
		{
			pReferenceType = (PSDREFERENCETYPE)&pType[1];
			pType = pSDSModule->GetTypeSymbol(pReferenceType->TypeID);
		}
	}
	return pType;
}

bool CTypeViewerWnd::UpdateItemContext(HANDLE hItem,WCHAR* ValueBuf,DWORD ValueBufLen,DWORD Address)
{
	WATCH_DATA WatchData;
	PSDTYPE_INFILE pType,pTmpType;
	PSDREFERENCETYPE pReferenceType;
	DWORD TypeIndex;
	CSDSModule* pSDSModule;
	DWORD ReadWriteLen,Attribute;
	VALUEUNION ValueUnion;
	PSDPOINTERTYPE pSDPointerType;
	PSDUDTDATAITEM pUDTDataItem;
	PSDENUMERATIONTYPE pEnumType;
	char *EnumElementName=NULL;
	char* pStr=(char*)&ValueBuf[0];
	bool bOK;
	memset(&WatchData,0,sizeof(WatchData));
	bOK = GetItemDataAll(hItem,&WatchData);
	if(bOK==false)
		return false;
	if(Address==0)
		Address=WatchData.Value.Attr.Address;
	WatchData.Value.Attr.Address=Address;
	SetItemData(hItem,LIST_COLUMN_VALUE,WatchData.Value.ItemData);
	if(WatchData.Value.Attr.Attribute&ITEM_ATTRIBUTE_UNINITIALIZE)
		return true;
	Attribute = WatchData.Value.Attr.Attribute;	
	pSDSModule = WatchData.Name.Attr.pSDSModule;
	TypeIndex = WatchData.Name.Attr.TypeIndex;	
	if(pSDSModule==NULL)return false;
	if(Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUDTDataItem=pSDSModule->GetDataSymbol(TypeIndex);
		if(pUDTDataItem==NULL)
			return false;
		TypeIndex=pUDTDataItem->TypeId;
	}
	pType=pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return false;
	switch(pType->Type)
	{
	case SD_ARRAY:		
		TSPrintf(ValueBuf,WSTR("0x%08x"),Address);
		SetItemText(hItem,LIST_COLUMN_VALUE,ValueBuf);
		UpdateItemContextArray(hItem,ValueBuf,ValueBufLen,Address);
		break;
	case SD_BASIC:
		GetBasicTypeValue(pSDSModule,pType,Address,Attribute,ValueBuf,&ValueUnion);
		SetItemTextColor(hItem,LIST_COLUMN_VALUE,NORMAL_TEXT_COLOR);
		if(WatchData.Type.ValueUnion.uint64value!=ValueUnion.uint64value)
		{			
			SetItemTextColor(hItem,LIST_COLUMN_VALUE,CHANGE_TEXT_COLOR);
		}
		SetItemText(hItem,LIST_COLUMN_VALUE,ValueBuf);
		WatchData.Type.ValueUnion = ValueUnion;
		SetItemData(hItem,LIST_COLUMN_TYPE,WatchData.Type.ItemData);
		break;
	case SD_POINTER:
		{
			memset(&ValueUnion,0,sizeof(VALUEUNION));
			ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(Address,&ValueUnion,pType->TypeSize);
			if(ReadWriteLen!=pType->TypeSize)
				break;						
			TSPrintf(ValueBuf,WSTR("0x%08x "),ValueUnion.uintvalue);
			SetItemTextColor(hItem,LIST_COLUMN_VALUE,NORMAL_TEXT_COLOR);
			if(WatchData.Type.ValueUnion.uint64value!=ValueUnion.uint64value)
			{			
				SetItemTextColor(hItem,LIST_COLUMN_VALUE,CHANGE_TEXT_COLOR);
			}
			SetItemText(hItem,LIST_COLUMN_VALUE,ValueBuf);
			pSDPointerType=(PSDPOINTERTYPE)&pType[1];
			if(pSDPointerType->PointerDepth==1)
			{
				pTmpType=pSDSModule->GetTypeSymbol(pSDPointerType->TypeID);
				if(pTmpType==NULL)break;
				if(pTmpType->Type==SD_CLASS || pTmpType->Type==SD_STRUCT || pTmpType->Type==SD_UNION)
				{
					UpdateItemContextUDTPointer(hItem,ValueBuf,ValueBufLen,ValueUnion.uintvalue);
				}				
				else if(pTmpType->Type==SD_BASIC)
				{					
					if(pTmpType->TypeSize==1)
					{
						TSPrintf(pStr,"0x%08x \"",ValueUnion.uintvalue);
						ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(ValueUnion.uintvalue,&pStr[12],ValueBufLen*sizeof(WCHAR)-15);
						for(DWORD i=0;i < ReadWriteLen ;i++)
						{
							if(pStr[i+12]!=0)continue;		
							pStr[i+12]='"';pStr[i+13]=0;
							SetItemTextA(hItem,LIST_COLUMN_VALUE,pStr);
							break;							
						}
					}
					
					HANDLE hNextItem = GetNextListItem(hItem);
					TYPE_VALUE_ATTR ValueAttr;
					if(hNextItem!=NULL)
					{
						ValueAttr.ItemData = GetItemData(hNextItem,LIST_COLUMN_VALUE);
						ValueAttr.Attr.Address = ValueUnion.uintvalue;
						SetItemData(hNextItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);
						GetBasicTypeValue(pSDSModule,pTmpType,ValueUnion.uintvalue,Attribute,ValueBuf,&ValueUnion);
						SetItemText(hNextItem,LIST_COLUMN_VALUE,ValueBuf);
					}															
				}				
			}
		}		
		break;
	case SD_REFERENCE:
		{
			memset(&ValueUnion,0,sizeof(VALUEUNION));
			ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(Address,&ValueUnion,4);
			if(ReadWriteLen!=4)
				break;						
			TSPrintf(ValueBuf,WSTR("0x%08x"),ValueUnion.uintvalue);
			SetItemText(hItem,LIST_COLUMN_VALUE,ValueBuf);
			pReferenceType=(PSDREFERENCETYPE)&pType[1];			
			pTmpType=pSDSModule->GetTypeSymbol(pReferenceType->TypeID);		
			if(pTmpType==NULL)break;
			if(pTmpType->Type==SD_CLASS || pTmpType->Type==SD_STRUCT || pTmpType->Type==SD_UNION)
			{
				UpdateItemContextUDTReference(hItem,ValueBuf,ValueBufLen,ValueUnion.uintvalue);
			}
			else if(pTmpType->Type==SD_BASIC)
			{
				TYPE_VALUE_ATTR ValueAttr;

				ValueAttr.ItemData = GetItemData(hItem,LIST_COLUMN_VALUE);
				ValueAttr.Attr.Address = ValueUnion.uintvalue;
				SetItemData(hItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);
				GetBasicTypeValue(pSDSModule,pTmpType,ValueUnion.uintvalue,Attribute,ValueBuf,&ValueUnion);
				SetItemText(hItem,LIST_COLUMN_VALUE,ValueBuf);													
			}			
		}		
		break;
	case SD_ENUMERATION:
		pEnumType=(PSDENUMERATIONTYPE)&pType[1];
		pTmpType = pSDSModule->GetTypeSymbol(pEnumType->TypeID);
		if(GetBasicTypeValue(pSDSModule,pTmpType,Address,Attribute,ValueBuf,&ValueUnion))
		{
			EnumElementName = pSDSModule->GetEnumerationByValue(TypeIndex,ValueUnion.uint64value);		
		}
		if(EnumElementName)
			SetItemTextA(hItem,LIST_COLUMN_VALUE,EnumElementName);
		else
			SetItemText(hItem,LIST_COLUMN_VALUE,ValueBuf);
		break;
	case SD_CLASS:
	case SD_STRUCT:
	case SD_UNION:
		UpdateItemContextUDT(hItem,ValueBuf,ValueBufLen,Address);
		break;
	}
	return true;
}
//显示一个UDT类型数据的前3项的值
bool CTypeViewerWnd::UpdateItemContextUDT(HANDLE hItem,WCHAR* ValueBuf,DWORD ValueBufLen,DWORD BaseAddress)
{
	WATCH_DATA WatchData;
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	HANDLE hSubItem;
	DWORD Address;
	DWORD TypeIndex;
	CSDSModule* pSDSModule ;
	if(hItem==NULL)
		return false;		
	ChangeUDTBaseClassAddressByUDT(hItem,BaseAddress);
	hSubItem = GetNextListItem(hItem);
	for(;hSubItem;hSubItem = GetNextItem(hSubItem))
	{
		GetItemText(hSubItem,LIST_COLUMN_NAME,ValueBuf,ValueBufLen);
		if(GetItemDataAll(hSubItem,&WatchData)==false)
			continue;
		Address=WatchData.Value.Attr.Address;
		TypeIndex = WatchData.Name.Attr.TypeIndex;
		pSDSModule = WatchData.Name.Attr.pSDSModule;
		if(WatchData.Value.Attr.Attribute&ITEM_ATTRIBUTE_UNINITIALIZE || pSDSModule==NULL || TypeIndex==0)
			continue;
		if(WatchData.Value.Attr.Attribute&ITEM_ATTRIBUTE_DATA)
		{
			pUdtDataItem = WatchData.Name.Attr.pSDSModule->GetDataSymbol(TypeIndex);
			if(pUdtDataItem==NULL)
				continue;
			TypeIndex = pUdtDataItem->TypeId;	
			if(pUdtDataItem->Location == LocIsThisRel) 
			{
				Address = BaseAddress+ pUdtDataItem->u.LOCISTHISREL.Offset;
			}
		}
		pType=WatchData.Name.Attr.pSDSModule->GetTypeSymbol(TypeIndex);
		if(pType==NULL)
			continue;		
		UpdateItemContext(hSubItem,ValueBuf,ValueBufLen,Address);
	}
	return true;
}
bool CTypeViewerWnd::ChangeUDTBaseClassAddress(HANDLE hItem,DWORD TypeIndex,DWORD Address)
{
	HANDLE hSubItem;
	WATCH_DATA WatchData;
	WCHAR ValueBuf[256];
	bool bOK=false;
	hSubItem = GetNextListItem(hItem);
	//hNextItem = GetListItem(hItem);
	for(;hSubItem;hSubItem = GetNextItem(hSubItem))
	{		
		if(GetItemDataAll(hSubItem,&WatchData)==false)
			continue;
		if(WatchData.Name.Attr.TypeIndex==TypeIndex && (WatchData.Value.Attr.Attribute&ITEM_ATTRIBUTE_TYPE))
		{
			GetItemText(hSubItem,LIST_COLUMN_NAME,ValueBuf,256);
			WatchData.Value.Attr.Address=Address;
			SetItemData(hSubItem,LIST_COLUMN_VALUE,WatchData.Value.ItemData);
			bOK=true;
			break;
		}
	}
	return bOK;
}
bool CTypeViewerWnd::ChangeUDTBaseClassAddressPointer(HANDLE hItem,DWORD BaseAddress)
{
	WATCH_DATA WatchData;
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	CSDSModule* pSDSModule;
	DWORD Address,Attribute;
	DWORD TypeIndex;
	PSDTYPE_INFILE pBaseClassType;
	PSDUDTBASECLASS pUdtBaseClassType;
	PSDPOINTERTYPE pPointerType;
	DWORD *pBaseClassIndex;
	PSDUDTTYPE pUdtType;
	DWORD i;
	if(GetItemDataAll(hItem,&WatchData)==false)
		return false;
	Attribute = WatchData.Value.Attr.Attribute;
	TypeIndex=WatchData.Name.Attr.TypeIndex;
	pSDSModule=WatchData.Name.Attr.pSDSModule;
	if(pSDSModule==NULL || TypeIndex == 0)
		return false;
	if(Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUdtDataItem=pSDSModule->GetDataSymbol(TypeIndex);
		if(pUdtDataItem==NULL)
			return false;
		TypeIndex=pUdtDataItem->TypeId;
	}
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return false;
	if(pType->Type!=SD_POINTER)
		return false;
	pPointerType =(PSDPOINTERTYPE) &pType[1];
	if(pPointerType->PointerDepth!=1)
		return false;
	pType = pSDSModule->GetTypeSymbol(pPointerType->TypeID);
	if(pType==NULL)
		return false;
	if(pType->Type!=SD_CLASS && pType->Type!=SD_STRUCT && pType->Type!=SD_UNION)
		return false;

	pUdtType = (PSDUDTTYPE)&pType[1];
	pBaseClassIndex = pUdtType->pBaseClass.pBaseClassMember;
	for(i = 0; i < pUdtType->BaseClassCounter;i++)
	{
		pBaseClassType = pSDSModule->GetTypeSymbol(pBaseClassIndex[i]);
		pUdtBaseClassType = (PSDUDTBASECLASS)&pBaseClassType[1];
		Address = BaseAddress+pUdtBaseClassType->Offset;
		ChangeUDTBaseClassAddress(hItem,pUdtBaseClassType->TypeID,Address);		
	}
	return true;
}

bool CTypeViewerWnd::ChangeUDTBaseClassAddressByUDT(HANDLE hItem,DWORD BaseAddress)
{
	WATCH_DATA WatchData;
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	CSDSModule* pSDSModule;
	DWORD Address,Attribute;
	DWORD TypeIndex;
	PSDTYPE_INFILE pBaseClassType;
	PSDUDTBASECLASS pUdtBaseClassType;
	DWORD *pBaseClassIndex;
	PSDUDTTYPE pUdtType;
	DWORD i;
	if(GetItemDataAll(hItem,&WatchData)==false)
		return false;
	Attribute = WatchData.Value.Attr.Attribute;
	TypeIndex=WatchData.Name.Attr.TypeIndex;
	pSDSModule=WatchData.Name.Attr.pSDSModule;
	if(pSDSModule==NULL || TypeIndex == 0)
		return false;
	if(Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUdtDataItem=pSDSModule->GetDataSymbol(TypeIndex);
		if(pUdtDataItem==NULL)
			return false;
		TypeIndex=pUdtDataItem->TypeId;
	}
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return false;
	
	if(pType->Type!=SD_CLASS && pType->Type!=SD_STRUCT && pType->Type!=SD_UNION)
		return false;

	pUdtType = (PSDUDTTYPE)&pType[1];
	pBaseClassIndex = pUdtType->pBaseClass.pBaseClassMember;
	for(i = 0; i < pUdtType->BaseClassCounter;i++)
	{
		pBaseClassType = pSDSModule->GetTypeSymbol(pBaseClassIndex[i]);
		pUdtBaseClassType = (PSDUDTBASECLASS)&pBaseClassType[1];
		Address = BaseAddress+pUdtBaseClassType->Offset;
		ChangeUDTBaseClassAddress(hItem,pUdtBaseClassType->TypeID,Address);		
	}
	return true;
}
bool CTypeViewerWnd::UpdateItemContextArray(HANDLE hItem,WCHAR* ValueBuf,DWORD ValueBufLen,DWORD BaseAddress)
{	
	PSDTYPE_INFILE pType,pArrayElementType;
	DWORD Attribute,Address;
	CSDSModule* pSDSModule;
	DWORD TypeIndex,i;
	WATCH_DATA WatchData;
	PSDUDTDATAITEM pUDTDataItem;
	PSDARRAYTYPE pArrayType;
	HANDLE hSubItem;
	if(hItem==NULL)
		return false;
	if(GetItemDataAll(hItem,&WatchData)==false)
		return false;
	pSDSModule = WatchData.Name.Attr.pSDSModule;
	TypeIndex  = WatchData.Name.Attr.TypeIndex;
	Attribute = WatchData.Value.Attr.Attribute;
	Address = BaseAddress;
	if(pSDSModule==NULL||TypeIndex==0)
		return false;
	if(Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUDTDataItem = pSDSModule->GetDataSymbol(TypeIndex);
		if(pUDTDataItem==NULL)
			return false;
		TypeIndex=pUDTDataItem->TypeId;
	}
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return false;
	pArrayType = (PSDARRAYTYPE)&pType[1];
	if(pArrayType->DimensionsSize==1)
	{
		hSubItem = GetNextListItem(hItem);
		pArrayElementType=pSDSModule->GetTypeSymbol(pArrayType->TypeIDElement);
		for(i = 0; i < pArrayType->Dimensions[0].Size && hSubItem!=NULL;i++)
		{
			UpdateItemContext(hSubItem,ValueBuf,ValueBufLen,Address);
			Address+=pArrayElementType->TypeSize;
			hSubItem = GetNextItem(hSubItem);
		}
	}
	return true;
}
bool CTypeViewerWnd::UpdateItemContextUDTPointer(HANDLE hItem,WCHAR* ValueBuf,DWORD ValueBufLen,DWORD BaseAddress)
{
	WATCH_DATA WatchData;
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	CSDSModule* pSDSModule;
	DWORD Address,Attribute;
	HANDLE hSubItem;
	DWORD TypeIndex;

	if(hItem==NULL)
		return false;	
	ChangeUDTBaseClassAddressPointer(hItem,BaseAddress);
	hSubItem = GetNextListItem(hItem);

	for(;hSubItem;hSubItem = GetNextItem(hSubItem))
	{
		GetItemText(hSubItem,LIST_COLUMN_NAME,ValueBuf,ValueBufLen);
		Address=0;
		if(GetItemDataAll(hSubItem,&WatchData)==false)
			continue;
		TypeIndex = WatchData.Name.Attr.TypeIndex;
		Attribute=WatchData.Value.Attr.Attribute;
		pSDSModule=WatchData.Name.Attr.pSDSModule;
		if(Attribute&ITEM_ATTRIBUTE_UNINITIALIZE || pSDSModule==NULL || TypeIndex==0)
			continue;
		if(Attribute&ITEM_ATTRIBUTE_DATA)
		{
			pUdtDataItem = pSDSModule->GetDataSymbol(TypeIndex);
			if(pUdtDataItem==NULL)
				continue;
			TypeIndex = pUdtDataItem->TypeId;
			if(pUdtDataItem->Location == LocIsThisRel) 
			{
				Address = BaseAddress+ pUdtDataItem->u.LOCISTHISREL.Offset;
			}
		}
		pType=pSDSModule->GetTypeSymbol(TypeIndex);
		if(pType==NULL)
			continue;		
		UpdateItemContext(hSubItem,ValueBuf,ValueBufLen,Address);
	}
	return true;
}
bool CTypeViewerWnd::UpdateItemContextUDTReference(HANDLE hItem,WCHAR* ValueBuf,DWORD ValueBufLen,DWORD BaseAddress)
{
	WATCH_DATA WatchData;
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	DWORD Address;
	HANDLE hSubItem;
	DWORD TypeIndex;
	if(hItem==NULL)
		return false;	

	hSubItem = GetNextListItem(hItem);
	for(;hSubItem;hSubItem = GetNextItem(hSubItem))
	{
		GetItemText(hSubItem,LIST_COLUMN_NAME,ValueBuf,ValueBufLen);
		Address=0;
		if(GetItemDataAll(hSubItem,&WatchData)==false)
			continue;
		TypeIndex = WatchData.Name.Attr.TypeIndex;
		if(WatchData.Value.Attr.Attribute&ITEM_ATTRIBUTE_UNINITIALIZE || WatchData.Name.Attr.pSDSModule==NULL || TypeIndex==0)
			continue;
		if(WatchData.Value.Attr.Attribute&ITEM_ATTRIBUTE_DATA)
		{
			pUdtDataItem = WatchData.Name.Attr.pSDSModule->GetDataSymbol(TypeIndex);
			if(pUdtDataItem==NULL)
				continue;
			TypeIndex = pUdtDataItem->TypeId;
			if(pUdtDataItem->Location == LocIsThisRel) 
			{
				Address = BaseAddress+ pUdtDataItem->u.LOCISTHISREL.Offset;
			}
		}
		pType=WatchData.Name.Attr.pSDSModule->GetTypeSymbol(TypeIndex);
		if(pType==NULL)
			continue;		
		UpdateItemContext(hSubItem,ValueBuf,ValueBufLen,Address);
	}
	return true;
}

bool CTypeViewerWnd::OnDeleteWatchEvent(IN WISP_MSG* pMsg)
{	
	HANDLE hFirstItem;
	HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
	hFirstItem = GetItem(0);
	if(GetParentItem(hItem)!=GetParentItem(hFirstItem))
		return false;
	if(hItem && hItem!=m_hLastItem)
		RemoveItem(hItem);
	return true;
}

bool CTypeViewerWnd::OnKeyEvent(IN WISP_MSG* pMsg)
{
	if(pMsg->KeyEvent.bKeyDown && pMsg->KeyEvent.KeyType == WISP_VK_F2)
	{
		HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
		if(hItem)
			BeginEditItem(hItem,0);
		return true;
	}
	if(pMsg->KeyEvent.bKeyDown==false)
	{
		if(pMsg->KeyEvent.KeyType == (WISP_MOD_CTRL| WISP_VK_H))
			m_PopupMenu.Popup();
		if(pMsg->KeyEvent.KeyType == WISP_VK_RBUTTON)
		{
			HANDLE hItem = GetNextItem(NULL,WISP_WLIS_SELECTED);
			m_PopupMenu.EnableItem(m_hRemoveItem,hItem!=NULL && hItem!=m_hLastItem);
			m_PopupMenu.Popup();
		}
	}
	return true;
}

bool CTypeViewerWnd::BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	bool bOK;
	TYPE_NAME_ATTR NameAttr;
	TYPE_VALUE_ATTR ValueAttr;
	TYPE_TYPE_ATTR TypeAttr;
	PSDREFERENCETYPE pReferenceType;
	TYPE_ADDRESS_ATTR AddressAttr;
	CSDSModule* pSdsModule;
	PSDTYPE_INFILE pType,pSubType;	
	HANDLE hFirstItem;
	DWORD TypeIndex;

	if(hItem==NULL)
		return false;
	bOK = GetItemDataAll(hItem,&NameAttr,&ValueAttr,&TypeAttr,&AddressAttr);
	if(bOK==false)
		return false;
	TypeIndex=NameAttr.Attr.TypeIndex;
	switch(Col) 
	{
	case LIST_COLUMN_VALUE:
		if(ValueAttr.Attr.Attribute&ITEM_ATTRIBUTE_UNINITIALIZE)
			return false;
		if(NameAttr.Attr.pSDSModule==NULL)
			return false;
		pSdsModule=NameAttr.Attr.pSDSModule;
		if((ValueAttr.Attr.Attribute&ITEM_ATTRIBUTE_TYPE)&&(ValueAttr.Attr.Attribute&ITEM_ATTRIBUTE_VFTABLE))
			return false;
		if(ValueAttr.Attr.Attribute&ITEM_ATTRIBUTE_DATA)
		{
			PSDUDTDATAITEM pUdtDataItem;
			pUdtDataItem=pSdsModule->GetDataSymbol(NameAttr.Attr.TypeIndex);
			if(pUdtDataItem==NULL)
				return false;
			TypeIndex = pUdtDataItem->TypeId;
		}
		pType = pSdsModule->GetTypeSymbol(TypeIndex);
		if(pType==NULL)
			return false;
		if(pType->Type==SD_REFERENCE)
		{
			pReferenceType = (PSDREFERENCETYPE)&pType[1];
			pSubType= pSdsModule->GetTypeSymbol(pReferenceType->TypeID);
			if(pSubType==NULL)
				return false;
			pType = pSubType;
		}
		return pType->Type==SD_BASIC || pType->Type==SD_POINTER;
	case LIST_COLUMN_NAME:
		hFirstItem = GetItem(0);
		if(GetParentItem(hItem)!=GetParentItem(hFirstItem))
			return false;
		break;
	}
	return true;
}
bool CTypeViewerWnd::ChangeValueBoolAndBitField1(DWORD Address,CSDSModule* pSDSModule,DWORD DataIndex,WCHAR* ValueBuf)
{
	PSDUDTDATAITEM pUdtDataItem;
	PSDTYPE_INFILE pType;
	VALUEUNION ValueUnion;
	DWORD ReadWriteLen,BaseTypeID;
	if(pSDSModule==NULL)
		return false;
	pUdtDataItem=pSDSModule->GetDataSymbol(DataIndex);
	if(pUdtDataItem==NULL)
		return false;
	pType = pSDSModule->GetTypeSymbol(pUdtDataItem->TypeId);
	if(pType==NULL)
		return false;
	if(pType->Type==SD_BASIC)
	{
		BaseTypeID = GetBaseTypeIdByName(pType->uName.Name);
		ReadWriteLen=0;
		if(pType->TypeSize>0 && pType->TypeSize<=sizeof(VALUEUNION))
			ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(Address,&ValueUnion,pType->TypeSize);
		if(ReadWriteLen!=pType->TypeSize)
			return false;
		switch(BaseTypeID)
		{
		case btBool:
			if(ValueUnion.boolvalue)
			{
				ValueUnion.boolvalue=false;
				TStrCpy(ValueBuf,"false");
			}
			else
			{
				ValueUnion.boolvalue=true;
				TStrCpy(ValueBuf,"true");
			}
			ReadWriteLen = gpSyser->m_pDebugger->WriteMemory(Address,&ValueUnion,pType->TypeSize);
			return true;
		case btInt1:
		case btInt2:
		case btInt4:
		case btLong:
		case btInt8:
		case btUint1:
		case btUint2:
		case btUint4:
		case btULong:
		case btUint8:
			if(pUdtDataItem->Location==LocIsBitField)
			{
				if(pUdtDataItem->u.LOCISBITFIELD.Size!=1)
					break;				
				ULONGLONG BitMask=1;
				BitMask<<=pUdtDataItem->u.LOCISBITFIELD.Position;
				ValueUnion.uint64value^=BitMask;
				ReadWriteLen = gpSyser->m_pDebugger->WriteMemory(Address,&ValueUnion,pType->TypeSize);
				if(ValueUnion.uint64value&BitMask)
					TStrCpy(ValueBuf,"1");
				else
					TStrCpy(ValueBuf,"0");
				return true;
			}
		}
	}
	return false;
}


CTypeViewerWnd::CTypeViewerWnd()
{
	m_hLastItem=NULL;
}

CTypeViewerWnd::~CTypeViewerWnd()
{
}

bool CTypeViewerWnd::OnCreate(IN WISP_MSG* pMsg)
{
	//Create(NULL,m_ClientRect,this,CHILD_CMD_TYPELIST,WISP_WLS_COLUMN_TITLE|WISP_WS_THIN_BORDER|WISP_WLS_TREE);
	InsertColumn(WSTR("Name F2"),100,WISP_WLCS_EDITABLE);
	InsertColumn(WSTR("Value"),400,WISP_WLCS_EDITABLE);
	InsertColumn(WSTR("Type"),100);
	InsertColumn(WSTR("Offset"),90);
	m_SelectBKColor = ColorOption.clrSelectedFrame;
	SetDefaultTextColor(ColorOption.clrText);
	SetBGColor(ColorOption.clrBackground);

	m_PopupMenu.CreatePopupMenu(TypeViewerMenu,this,WispTKDIBList("\\Toolbar.bmp",16,16));
	m_hRemoveItem = m_PopupMenu.GetItem(EVENT_ID_TYPEVIEWERWND_DELETE_WATCH);
	ResetContext();
	return true;
}

bool CTypeViewerWnd::OnDestroy(IN WISP_MSG* pMsg)
{
	m_PopupMenu.Destroy();
	return true;
}

void CTypeViewerWnd::ExpandArrayType(HANDLE hItem,bool bIsData)
{
	DWORD Attribute;
	DWORD TypeIndex;
	DWORD Address;
	bool bOK;
	TYPE_NAME_ATTR NameAttr;
	TYPE_VALUE_ATTR ValueAttr;
	TYPE_TYPE_ATTR TypeAttr;
	TYPE_ADDRESS_ATTR AddressAttr;
	PSDUDTDATAITEM pUdtDataItem;
	CSDSModule* pSDSModule;
	PSDTYPE_INFILE pType;
	PSDTYPE_INFILE pArrayElementType;
	PSDARRAYTYPE pArrayType;
	char Name[20];
	DWORD MemoryAddress;
	DWORD i;
	if(hItem==NULL)
		return;
	bOK = GetItemDataAll(hItem,&NameAttr,&ValueAttr,&TypeAttr,&AddressAttr);
	if(bOK==false)
		return;
	Attribute = ValueAttr.Attr.Attribute;
	pSDSModule = NameAttr.Attr.pSDSModule;
	TypeIndex = NameAttr.Attr.TypeIndex;
	Address = ValueAttr.Attr.Address;
	MemoryAddress=Address;
	if(pSDSModule==NULL||TypeIndex==0)
		return;
	if(Attribute&ITEM_ATTRIBUTE_UNINITIALIZE)
		return;
	if(Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUdtDataItem = pSDSModule->GetDataSymbol(TypeIndex);
		if(pUdtDataItem==NULL)
			return;
		TypeIndex=pUdtDataItem->TypeId;
	}	
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL||pType->Type!=SD_ARRAY)
		return;
	pArrayType=(PSDARRAYTYPE)&pType[1];
	if(pArrayType->DimensionsSize>1)
	{
		pArrayElementType=pSDSModule->GetTypeSymbol(pArrayType->NextArrayID);
	}	
	else
	{
		pArrayElementType=pSDSModule->GetTypeSymbol(pArrayType->TypeIDElement);
		Attribute &= ITEM_ATTRIBUTE_TYPEDATA_MASK;
		Attribute |= ITEM_ATTRIBUTE_TYPE;
		for(i = 0; i < pArrayType->Dimensions[0].Size;i++)
		{
			TSPrintf(Name,"[%d]",i);
			WatchType(pSDSModule,pArrayElementType->Id,MemoryAddress,Attribute,hItem,Name);
			MemoryAddress+=pArrayElementType->TypeSize;
		}
	}	
}
void CTypeViewerWnd::AddArrayTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName,bool bIsData)
{
	WCHAR ValueBuf[30];
	WCHAR UndefineValue[]=WSTR("????????");
	NUM_PTR NumPtr;
	DWORD *TmpPtr=(DWORD*)&NumPtr,DataIndex=TypeIndex;
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	char NameBuf[512]={0};
	int NameBufLen=sizeof(NameBuf);
	CWispDIB*pIcon=WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);

	if(pSDSModule==NULL)
		return;
	if(bIsData)
	{
		DataIndex=TypeIndex;
		pUdtDataItem=pSDSModule->GetDataSymbol(DataIndex);
		if(pUdtDataItem==NULL)
			return;
		switch(pUdtDataItem->Access)
		{

		case CV_private:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+15);
			break;
		case CV_protected:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+14);
			break;
		case CV_public:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);
			break;
		}
		TypeIndex=pUdtDataItem->TypeId;
	}
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return;
	TSPrintf(ValueBuf,WSTR("0x%08x"),Address);
	pSDSModule->GetSDSymbolName(pType,NameBuf,&NameBufLen);
	if(DataMemberName)
		hItem = InsertItemA(DataMemberName,hItem,WISP_WLIS_NORMAL,pIcon);
	else
		hItem = InsertItemA(NameBuf,hItem,WISP_WLIS_NORMAL,pIcon);
	SetItemTextA(hItem,LIST_COLUMN_TYPE,NameBuf);
	TmpPtr[0]=bIsData?DataIndex:TypeIndex;
	TmpPtr[1]=*(DWORD*)&pSDSModule;
	SetItemData(hItem,LIST_COLUMN_NAME,NumPtr);
	SetItemText(hItem,LIST_COLUMN_VALUE,ValueBuf);

	TmpPtr[0]=Address;
	TmpPtr[1]=Attribute&ITEM_ATTRIBUTE_TYPEDATA_MASK;
	TmpPtr[1]|=(bIsData?ITEM_ATTRIBUTE_DATA:ITEM_ATTRIBUTE_TYPE);
	SetItemData(hItem,LIST_COLUMN_VALUE,NumPtr);	
	SetItemNum(hItem,LIST_COLUMN_ADDRESS,Address,WSTR("0x%08x"));
	TmpPtr[0]=TypeIndex;
	TmpPtr[1]=0;
	SetItemData(hItem,LIST_COLUMN_TYPE,NumPtr);	
	hItem = InsertItem(WSTR(".."),hItem);
	TmpPtr[1]|=ITEM_ATTRIBUTE_UNINITIALIZE;
	SetItemData(hItem,LIST_COLUMN_VALUE,NumPtr);	
}
void CTypeViewerWnd::ExpendVirtualFunctionTable(HANDLE hItem,PWATCH_DATA pWatchData)
{
	WATCH_DATA WatchData;;
	DWORD Attribute;
	DWORD TypeIndex;
	char NameBuffer[256];
	char FuncNameBuffer[256];
	DWORD Address;
	const char*Name;
	PSDUDTDATAITEM pUdtDataItem;
	CSDSModule* pSDSModule;
	PSDTYPE_INFILE pType,pSubType;
	PSDUDTTYPE pUdtType;
	HANDLE hSubItem;
	PSDUDTVIRTUALTABLE pVTable;
	DWORD ReadWriteLen;
	DWORD i,j;
	BYTE CodeBuf[0x10];
	CWispDIB* pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);
	Attribute = pWatchData->Value.Attr.Attribute;
	pSDSModule = pWatchData->Name.Attr.pSDSModule;
	TypeIndex = pWatchData->Name.Attr.TypeIndex;
	Address = pWatchData->Value.Attr.Address;
	if(pSDSModule==NULL || TypeIndex==0)
		return;
	if(Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUdtDataItem =pSDSModule->GetDataSymbol(TypeIndex);
		if(pUdtDataItem==NULL)
			return;
		TypeIndex=pUdtDataItem->TypeId;
	}
	pSubType = pSDSModule->GetSymbolByName("unsigned int");
	if(pSubType==NULL)
		return;
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	pUdtType = (PSDUDTTYPE)&pType[1];
	pVTable=pUdtType->pVTable.pVTableMember;
	if(pVTable==NULL)
		return;
	memset(&WatchData,0,sizeof(WatchData));
	for(i = 0; i < pUdtType->VTableCount;i++)
	{
		if(pVTable[i].VTBaseClassTypeID==TypeIndex)
		{
			CWispListItemCell*   ListItemCell;
			DWORD dwVTBaseAddress= pSDSModule->m_pCurDbgModule->m_ModuleBase+pVTable[i].VTableRVA;;
			DWORD dwVFAddr;
			HANDLE hChildItem;
			hSubItem=InsertItemA("__vfptr",hItem,WISP_WLIS_NORMAL,pIcon);
			ListItemCell = GetItemCell(hSubItem,LIST_COLUMN_TYPE);				
			Name = pSDSModule->m_pCurDbgModule->GetSymbol(dwVTBaseAddress);			
			WatchData.Name.Attr.TypeIndex=pSubType->Id;
			WatchData.Name.Attr.pSDSModule=pSDSModule;
			WatchData.Value.Attr.Address=(DWORD)&ListItemCell->Data;//  pSDSModule->m_pCurDbgModule->m_ModuleBase+pVTable[i].VTableRVA;
			WatchData.Value.Attr.Attribute |= ITEM_ATTRIBUTE_TYPE;
			WatchData.Value.Attr.Attribute |= ITEM_ATTRIBUTE_VFTABLE;
			WatchData.Type.VFTable.Address=dwVTBaseAddress;
			TSPrintf(NameBuffer,"0x%08x  %s",dwVTBaseAddress,Name==NULL?"":Name);
			SetItemTextA(hSubItem,LIST_COLUMN_VALUE,NameBuffer);
			SetItemData(hSubItem,LIST_COLUMN_NAME,WatchData.Name.ItemData);
			SetItemData(hSubItem,LIST_COLUMN_VALUE,WatchData.Value.ItemData);
			SetItemData(hSubItem,LIST_COLUMN_TYPE,WatchData.Type.ItemData);
			SetItemTextA(hSubItem,LIST_COLUMN_TYPE,"*");
			
			for(j=0;j<pVTable[i].VTableSize / sizeof(DWORD);j++,dwVTBaseAddress+=4)
			{
				ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(dwVTBaseAddress,&dwVFAddr,4);
				if(ReadWriteLen!=4)
					break;
				if(dwVFAddr==0)
					break;
				TSPrintf(NameBuffer,"[0x%x]",j);
				hChildItem = InsertItemA(NameBuffer,hSubItem,WISP_WLIS_NORMAL,WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*18));
				
				ListItemCell = GetItemCell(hChildItem,LIST_COLUMN_TYPE);				
				Name = pSDSModule->m_pCurDbgModule->GetSymbol(dwVFAddr);	
				if(Name==NULL)
				{
					ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(dwVFAddr,CodeBuf,5);
					if(ReadWriteLen==5)
					{
						if(CodeBuf[0]==0xe9)
						{
							DWORD dwDestAddr;
							dwDestAddr=dwVFAddr+ *(DWORD*)&CodeBuf[1]+5-pSDSModule->m_pCurDbgModule->m_ModuleBase;
							PSDFUNCTIONITEM pFuncItem= pSDSModule->GetFunctionFromRav(dwDestAddr);
							NameBuffer[0]=0;
							int NameLen=sizeof(FuncNameBuffer);
							if(pFuncItem)
							{	
								Name = pSDSModule->GetFunctionName(pFuncItem,FuncNameBuffer,&NameLen);								
							}
							//Name=pSDSModule->GetFuncNameByRva(dwDestAddr);
							//Name = pSDSModule->m_pCurDbgModule->GetSymbol(dwDestAddr);
						}
					}
				}
				WatchData.Name.Attr.TypeIndex=pSubType->Id;
				WatchData.Name.Attr.pSDSModule=pSDSModule;
				WatchData.Value.Attr.Address=(DWORD)&ListItemCell->Data;
				WatchData.Value.Attr.Attribute |= ITEM_ATTRIBUTE_TYPE;
				WatchData.Value.Attr.Attribute |= ITEM_ATTRIBUTE_VFTABLE;
				WatchData.Type.VFTable.Address=dwVFAddr;
				TSPrintf(NameBuffer,"0x%08x  %s",WatchData.Type.VFTable.Address,Name==NULL?"":Name);
				SetItemTextA(hChildItem,LIST_COLUMN_VALUE,NameBuffer);
				SetItemData(hChildItem,LIST_COLUMN_NAME,WatchData.Name.ItemData);
				SetItemData(hChildItem,LIST_COLUMN_VALUE,WatchData.Value.ItemData);
				SetItemData(hChildItem,LIST_COLUMN_TYPE,WatchData.Type.ItemData);
				SetItemTextA(hChildItem,LIST_COLUMN_TYPE,"*");

			}
			break;
		}
	}

}
void CTypeViewerWnd::AddClassVFPTRWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName)
{
	WCHAR ValueBuf[30];
	WCHAR UndefineValue[]=WSTR("????????");
	NUM_PTR NumPtr;
	DWORD *TmpPtr=(DWORD*)&NumPtr,DataIndex=TypeIndex;
	PSDTYPE_INFILE pType;
	WATCH_DATA WatchData;
//	PSDUDTDATAITEM pUdtDataItem;
	HANDLE hParent,hNext;
	TYPE_NAME_ATTR NameAttr;
	char NameBuf[512]={0};
	int NameBufLen=sizeof(NameBuf);
	if(pSDSModule==NULL)
		return;
	
	hParent = hNext = hItem;
	while(hParent!=NULL)
	{
		hParent = GetParentItem(hNext);
		if(hParent==NULL)
			break;
		hNext = hParent;
	}
	if(hNext==NULL)
		return;
	NameAttr.ItemData = GetItemData(hNext);
	memset(&WatchData,0,sizeof(WatchData));
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return;
	TSPrintf(ValueBuf,WSTR("0x%08x"),Address);
	pSDSModule->GetSDSymbolName(pType,NameBuf,&NameBufLen);
	if(DataMemberName)
		hItem = InsertItemA(DataMemberName,hItem);
	else
		hItem = InsertItemA(NameBuf,hItem);
	SetItemTextA(hItem,LIST_COLUMN_TYPE,NameBuf);
	TmpPtr[0]=TypeIndex;
	TmpPtr[1]=*(DWORD*)&pSDSModule;
	SetItemData(hItem,LIST_COLUMN_NAME,NumPtr);
	SetItemText(hItem,LIST_COLUMN_VALUE,ValueBuf);
	TmpPtr[0]=Address;TmpPtr[1]=Attribute|ITEM_ATTRIBUTE_TYPE;
	TmpPtr[1]&=(~ITEM_ATTRIBUTE_DATA);
	SetItemData(hItem,LIST_COLUMN_VALUE,NumPtr);	
	SetItemNum(hItem,LIST_COLUMN_ADDRESS,Address,WSTR("0x%08x"));
	TmpPtr[0]=TypeIndex;
	TmpPtr[1]=0;
	SetItemData(hItem,LIST_COLUMN_TYPE,NumPtr);	
	hItem = InsertItem(WSTR(".."),hItem);
	TmpPtr[1]|=ITEM_ATTRIBUTE_UNINITIALIZE;
	SetItemData(hItem,LIST_COLUMN_VALUE,NumPtr);	
}

void CTypeViewerWnd::AddEnumerationTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName,bool bIsData)
{
	VALUEUNION ValueUnion;
	WCHAR ValueBuf[30]={0};
	WCHAR UndefineValue[]=WSTR("????????");
	NUM_PTR NumPtr;
	DWORD *TmpPtr=(DWORD*)&NumPtr,DataIndex=TypeIndex;
	PSDTYPE_INFILE pType,pTmpType;
	PSDUDTDATAITEM pUdtDataItem;
	PSDENUMERATIONTYPE pEnumType;
	char NameBuf[512]={0};
	char* EnumElementName=NULL;
	int NameBufLen=sizeof(NameBuf);
	if(pSDSModule==NULL)
		return;
	if(bIsData)
	{
		DataIndex=TypeIndex;
		pUdtDataItem=pSDSModule->GetDataSymbol(DataIndex);
		if(pUdtDataItem==NULL)
			return;
		TypeIndex=pUdtDataItem->TypeId;
	}
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL||pType->Type!=SD_ENUMERATION)
		return;
	pEnumType=(PSDENUMERATIONTYPE)&pType[1];
	
	TSPrintf(ValueBuf,WSTR("%08x"),Address);
	pSDSModule->GetSDSymbolName(pType,NameBuf,&NameBufLen);
	if(DataMemberName)
		hItem = InsertItemA(DataMemberName,hItem);
	else
		hItem = InsertItemA(NameBuf,hItem);
	TmpPtr[0]=bIsData?DataIndex:TypeIndex;
	TmpPtr[1]=*(DWORD*)&pSDSModule;
	SetItemData(hItem,LIST_COLUMN_NAME,NumPtr);
	//SetItemText(hItem,LIST_COLUMN_VALUE,ValueBuf);
	if(bIsData)
	{
		TmpPtr[0]=Address;TmpPtr[1]=Attribute|ITEM_ATTRIBUTE_TYPE;
		TmpPtr[1]&=(~ITEM_ATTRIBUTE_DATA);
	}
	else
	{
		TmpPtr[0]=Address;TmpPtr[1]=Attribute|ITEM_ATTRIBUTE_DATA;
		TmpPtr[1]&=(~ITEM_ATTRIBUTE_TYPE);
	}
	SetItemData(hItem,LIST_COLUMN_VALUE,NumPtr);
	TmpPtr[0]=TypeIndex;
	TmpPtr[1]=0;
	SetItemData(hItem,LIST_COLUMN_TYPE,NumPtr);
	SetItemTextA(hItem,LIST_COLUMN_TYPE,NameBuf);
	pTmpType = pSDSModule->GetTypeSymbol(pEnumType->TypeID);
	
	if(GetBasicTypeValue(pSDSModule,pTmpType,Address,Attribute,ValueBuf,&ValueUnion))
	{
		EnumElementName = pSDSModule->GetEnumerationByValue(TypeIndex,ValueUnion.uint64value);		
	}
	if(EnumElementName)
		SetItemTextA(hItem,LIST_COLUMN_VALUE,EnumElementName);
	else
		SetItemText(hItem,LIST_COLUMN_VALUE,ValueBuf);
	SetItemNum(hItem,LIST_COLUMN_ADDRESS,Address);

}
void CTypeViewerWnd::AddPointerTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName,bool bIsData)
{
	WCHAR ValueBuf[30];
	WCHAR UndefineValue[]=WSTR("????????");
	VALUEUNION ValueUnion;
	NUM_PTR NumPtr;
	DWORD *TmpPtr,ReadWriteLen;
	PSDTYPE_INFILE pType,pElementType;
	PSDPOINTERTYPE pPointerType;
	TYPE_TYPE_ATTR TypeAddr;
	bool voidpointer=false;
	DWORD DataIndex;
	PSDUDTDATAITEM pUdtDataItem;
	char NameBuf[512]={0};
	int NameBufLen=sizeof(NameBuf);
	CWispDIB*pIcon=WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);

	TypeAddr.ItemData=0;
	if(pSDSModule==NULL)
		return;
	if(bIsData)
	{
		DataIndex=TypeIndex;
		pUdtDataItem=pSDSModule->GetDataSymbol(DataIndex);
		if(pUdtDataItem==NULL)
			return;
		switch(pUdtDataItem->Access)
		{

		case CV_private:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+15);
			break;
		case CV_protected:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+14);
			break;
		case CV_public:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);
			break;
		}
		TypeIndex=pUdtDataItem->TypeId;
	}
	
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL||pType->Type!=SD_POINTER)
		return;
	pPointerType = (PSDPOINTERTYPE)&pType[1];
	if(pType->TypeSize>0 && pType->TypeSize<=sizeof(VALUEUNION))
		ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(Address,&ValueUnion,pType->TypeSize);
	if(ReadWriteLen==pType->TypeSize &&ReadWriteLen)
		TSPrintf(ValueBuf,WSTR("0x%08x"),ValueUnion.uintvalue);
	else
		TStrCpy(ValueBuf,UndefineValue);

	pElementType = pSDSModule->GetTypeSymbol(pPointerType->TypeID);
	pSDSModule->GetSDSymbolName(pType,NameBuf,&NameBufLen);
	voidpointer = (TStrCmp(NameBuf,"void*")==0);
	if(pElementType->Type==SD_FUNCTIONTYPE)
		voidpointer=true;
	NameBuf[0]=0;
	pSDSModule->GetSDSymbolName(pType,NameBuf,&NameBufLen);
	if(DataMemberName)
		hItem = InsertItemA(DataMemberName,hItem,WISP_WLIS_NORMAL,pIcon);
	else
		hItem = InsertItemA(NameBuf,hItem,WISP_WLIS_NORMAL,pIcon);
	SetItemTextA(hItem,LIST_COLUMN_TYPE,NameBuf);
	TypeAddr.ValueUnion = ValueUnion;
	SetItemData(hItem,LIST_COLUMN_TYPE,TypeAddr.ItemData);
	TmpPtr = (DWORD*)&NumPtr;
	TmpPtr[0] = bIsData?DataIndex:TypeIndex;
	TmpPtr[1]=*(DWORD*)&pSDSModule;
	SetItemData(hItem,LIST_COLUMN_NAME,NumPtr);
	SetItemText(hItem,LIST_COLUMN_VALUE,ValueBuf);
	TmpPtr[0]=Address;
	TmpPtr[1]=Attribute& ITEM_ATTRIBUTE_TYPEDATA_MASK;
	TmpPtr[1]|=(bIsData?ITEM_ATTRIBUTE_DATA:ITEM_ATTRIBUTE_TYPE);
	SetItemData(hItem,LIST_COLUMN_VALUE,NumPtr);
	
	SetItemNum(hItem,LIST_COLUMN_ADDRESS,Address,WSTR("0x%08x "));
	TypeAddr.ItemData=0;
	SetItemData(hItem,LIST_COLUMN_TYPE,TypeAddr.ItemData);
	if(pElementType->Type==SD_BASIC && pElementType->TypeSize == 1)
	{
		TSPrintf(NameBuf,"0x%08x \"",ValueUnion.uintvalue);
		ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(ValueUnion.uintvalue,&NameBuf[12],sizeof(NameBuf)-15);
		for(DWORD i = 0; i < ReadWriteLen;i++)
		{
			if(NameBuf[i+12]!=0)continue;	
			NameBuf[i+12]='"';NameBuf[i+13]=0;
			SetItemTextA(hItem,LIST_COLUMN_VALUE,NameBuf);
			break;
		}
	}
	if(voidpointer==false)
	{
		hItem = InsertItem(WSTR(".."),hItem);
		TmpPtr[1]|=ITEM_ATTRIBUTE_UNINITIALIZE;
		SetItemData(hItem,LIST_COLUMN_VALUE,NumPtr);
	}

	SetItemTextA(hItem,LIST_COLUMN_TYPE,NameBuf);
	TmpPtr[0]=TypeIndex;
	TmpPtr[1]=0;
	SetItemData(hItem,LIST_COLUMN_TYPE,NumPtr);
}

void CTypeViewerWnd::WatchType(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName)
{
	NUM_PTR NumPtr;
	DWORD *TmpPtr=(DWORD*)&NumPtr;
	PSDTYPE_INFILE pType;
	bool bInsertItem=true;
	if(pSDSModule==NULL)
		return;
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return;
	if(hItem==NULL)
	{
		RemoveItem(m_hLastItem);
		m_hLastItem=NULL;
	}
	switch(pType->Type) {
	case SD_STRUCT:
	case SD_UNION:
	case SD_CLASS:
		AddUdtTypeWatch(pSDSModule,TypeIndex,Address,Attribute,hItem,DataMemberName);
		break;
	case SD_BASIC:
		AddBasicTypeWatch(pSDSModule,TypeIndex,Address,Attribute,hItem,DataMemberName);
		break;
	case SD_POINTER:
		AddPointerTypeWatch(pSDSModule,TypeIndex,Address,Attribute,hItem,DataMemberName);
		break;
	case SD_ARRAY:
		AddArrayTypeWatch(pSDSModule,TypeIndex,Address,Attribute,hItem,DataMemberName);
		break;
	case SD_ENUMERATION:
		AddEnumerationTypeWatch(pSDSModule,TypeIndex,Address,Attribute,hItem,DataMemberName);
		break;
	}	
}
void CTypeViewerWnd::AddBaseClassTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName,bool bIsData)
{
	char Buf[256];
	char* pStr=Buf;
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	DWORD Len,DataIndex;
	WATCH_DATA WatchData;
	TYPE_VALUE_ATTR ValueAttr;
	DWORD OldAttribute=Attribute;
	CWispDIB*pIcon=WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);

	if(bIsData)
	{
		DataIndex=TypeIndex;
		pUdtDataItem = pSDSModule->GetDataSymbol(DataIndex);
		if(pUdtDataItem==NULL)
			return;
		switch(pUdtDataItem->Access)
		{

		case CV_private:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+15);
			break;
		case CV_protected:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+14);
			break;
		case CV_public:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);
			break;
		}
		TypeIndex = pUdtDataItem->TypeId;
		if(DataMemberName==NULL)
			DataMemberName=pUdtDataItem->uName.Name;
	}
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return;
	if(pType->Type!=SD_CLASS&&pType->Type!=SD_STRUCT&&pType->Type!=SD_CLASS)
		return;
	Len = TStrLen(pType->uName.Name)+9;
	if(Len > sizeof(Buf)/sizeof(Buf[0]))
		pStr=new char[Len];
	pStr[0]=0;
	switch(pType->Type) {
		case SD_CLASS:
			TSPrintf(pStr,"class %s",pType->uName.Name);
			break;
		case SD_STRUCT:
			TSPrintf(pStr,"struct %s",pType->uName.Name);
			break;
		case SD_UNION:
			TSPrintf(pStr,"union %s",pType->uName.Name);
			break;
	}
	hItem = InsertItemA(pType->uName.Name,hItem);
	SetItemTextA(hItem,LIST_COLUMN_TYPE,pType->uName.Name);
	if(DataMemberName)
		SetItemTextA(hItem,LIST_COLUMN_NAME,DataMemberName);
	WatchData.Name.Attr.pSDSModule = pSDSModule;
	WatchData.Name.Attr.TypeIndex = bIsData ? DataIndex:TypeIndex;	
	SetItemData(hItem,LIST_COLUMN_NAME,WatchData.Name.ItemData);
	SetItemText(hItem,LIST_COLUMN_VALUE,WSTR("{...}"));
	WatchData.Type.ItemData=0;
	SetItemData(hItem,LIST_COLUMN_TYPE,WatchData.Type.ItemData);
	WatchData.Value.Attr.Address = Address;
	Attribute = Attribute & ITEM_ATTRIBUTE_TYPEDATA_MASK;
	Attribute |= bIsData ? ITEM_ATTRIBUTE_DATA : ITEM_ATTRIBUTE_TYPE;	
	WatchData.Value.Attr.Attribute=Attribute;
	SetItemData(hItem,LIST_COLUMN_VALUE,WatchData.Value.ItemData);
	SetItemNum(hItem,LIST_COLUMN_ADDRESS,Address,WSTR("0x%08x"));
	hItem = InsertItem(WSTR(".."),hItem);
	ValueAttr.Attr.Address=0;
	ValueAttr.Attr.Attribute = OldAttribute | ITEM_ATTRIBUTE_UNINITIALIZE;
	SetItemData(hItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);
	if(pStr!=Buf)
		delete pStr;
}
void CTypeViewerWnd::AddUdtTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName,bool bIsData)
{
	char Buf[256];
	char* pStr=Buf;
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	DWORD Len,DataIndex;
	WATCH_DATA WatchData;
	TYPE_VALUE_ATTR ValueAttr;
	DWORD OldAttribute=Attribute;
	CWispDIB*pIcon=WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);

	if(bIsData)
	{
		DataIndex=TypeIndex;
		pUdtDataItem = pSDSModule->GetDataSymbol(DataIndex);
		if(pUdtDataItem==NULL)
			return;
		switch(pUdtDataItem->Access)
		{
		case CV_private:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+15);
			break;
		case CV_protected:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+14);
			break;
		case CV_public:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);
			break;
		}
		TypeIndex = pUdtDataItem->TypeId;
		if(DataMemberName==NULL)
			DataMemberName=pUdtDataItem->uName.Name;
	}
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return;
	if(pType->Type!=SD_CLASS&&pType->Type!=SD_STRUCT&&pType->Type!=SD_CLASS)
		return;
	Len = TStrLen(pType->uName.Name)+9;
	if(Len > sizeof(Buf)/sizeof(Buf[0]))
		pStr=new char[Len];
	pStr[0]=0;
	switch(pType->Type) {
		case SD_CLASS:
			TSPrintf(pStr,"class %s",pType->uName.Name);
			break;
		case SD_STRUCT:
			TSPrintf(pStr,"struct %s",pType->uName.Name);
			break;
		case SD_UNION:
			TSPrintf(pStr,"union %s",pType->uName.Name);
			break;
	}
	hItem = InsertItemA(pType->uName.Name,hItem);
	SetItemTextA(hItem,LIST_COLUMN_TYPE,pType->uName.Name);
	if(DataMemberName)
		SetItemTextA(hItem,LIST_COLUMN_NAME,DataMemberName);
	WatchData.Name.Attr.pSDSModule = pSDSModule;
	WatchData.Name.Attr.TypeIndex = bIsData ? DataIndex:TypeIndex;	
	SetItemData(hItem,LIST_COLUMN_NAME,WatchData.Name.ItemData);
	SetItemText(hItem,LIST_COLUMN_VALUE,WSTR("{...}"));
	WatchData.Type.ItemData=0;
	SetItemData(hItem,LIST_COLUMN_TYPE,WatchData.Type.ItemData);
	WatchData.Value.Attr.Address = Address;
	Attribute = Attribute & ITEM_ATTRIBUTE_TYPEDATA_MASK;
	Attribute |= bIsData ? ITEM_ATTRIBUTE_DATA : ITEM_ATTRIBUTE_TYPE;	
	WatchData.Value.Attr.Attribute=Attribute;
	SetItemData(hItem,LIST_COLUMN_VALUE,WatchData.Value.ItemData);
	SetItemNum(hItem,LIST_COLUMN_ADDRESS,Address,WSTR("0x%08x"));
	hItem = InsertItem(WSTR(".."),hItem);
	ValueAttr.Attr.Address=0;
	ValueAttr.Attr.Attribute = OldAttribute | ITEM_ATTRIBUTE_UNINITIALIZE;
	SetItemData(hItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);
	if(pStr!=Buf)
		delete pStr;
}
void CTypeViewerWnd::RemoveTypeAttachByAddress(DWORD Address)
{

}
void CTypeViewerWnd::ModifyTypeAttachAddress(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address)
{

}
bool CTypeViewerWnd::ChangeValue(HANDLE hItem)
{	
	VALUEUNION ValueUnion;
	PVALUEUNION pValue;
	WCHAR UndefineValue[]=WSTR("????????");
	CSDSModule* pSDSModule;
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	PSDREFERENCETYPE pReferenceType;
	DWORD BaseTypeID,ReadWriteLen,TypeIndex;
	NUM_PTR NumPtr;
	WATCH_DATA WatchData;
	DWORD Attribute;
	DWORD Address,i;
	bool bOK=false;
	DWORD *TmpPtr=(DWORD*)&NumPtr;
	WCHAR* szText;
	memset(&WatchData,0,sizeof(WatchData));
	if(GetItemDataAll(hItem,&WatchData)==false)
		return false;
	TypeIndex = WatchData.Name.Attr.TypeIndex;
	pSDSModule = WatchData.Name.Attr.pSDSModule;
	Attribute = WatchData.Value.Attr.Attribute;
	Address = WatchData.Value.Attr.Address;	
	if(pSDSModule==NULL || Attribute&ITEM_ATTRIBUTE_UNINITIALIZE)
		return false;
	if(Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUdtDataItem=pSDSModule->GetDataSymbol(TypeIndex);
		if(pUdtDataItem==NULL)
			return false;
		TypeIndex=pUdtDataItem->TypeId;
	}
	szText=GetItemText(hItem,LIST_COLUMN_VALUE);	
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return false;
	memset(&ValueUnion,0,sizeof(ValueUnion));
	if(pType->Type==SD_BASIC)
	{
local_001:
		BaseTypeID = GetBaseTypeIdByName(pType->uName.Name);
		ReadWriteLen=0;
		
		switch(BaseTypeID)
		{
		case btBool:
		case btInt1:
		case btInt2:
		case btInt4:
		case btLong:
		case btInt8:
			if(Attribute&ITEM_ATTRIBUTE_HEX)
				bOK = SHexStrToNum(szText,&ValueUnion.int64value);
			else
				bOK = SDecStrToNum(szText,&ValueUnion.int64value);
			break;
		case btUint1:
		case btUint2:
		case btUint4:
		case btULong:
		case btUint8:
			if(Attribute&ITEM_ATTRIBUTE_HEX)
				bOK = SHexStrToNum(szText,&ValueUnion.uint64value);
			else
				bOK = SDecStrToNum(szText,&ValueUnion.uint64value);
			break;
		}
		pValue=bOK?&ValueUnion:NULL;
		if(bOK)
		{			
			ModifyDataValue(Address,pSDSModule,TypeIndex,ValueUnion);			
		}
	}
	else if(pType->Type==SD_POINTER)
	{		
		for(i=0; szText[i];i++)
		{
			if(szText[i]=='x' || szText[i]=='X')
			{
				i++;
				szText+=i;
				break;
			}
		}
		bOK = SHexStrToNum(szText,&ValueUnion.uint64value);
		if(bOK)
			ModifyDataValue(Address,pSDSModule,TypeIndex,ValueUnion);
	}
	else if(pType->Type==SD_REFERENCE)
	{
		PSDTYPE_INFILE pSubType;
		DWORD dwAddress  ;
		pReferenceType = (PSDREFERENCETYPE)&pType[1];
		pSubType = pSDSModule->GetTypeSymbol(pReferenceType->TypeID);
		if(pSubType)
		{
			if(pSubType->Type==SD_BASIC)
			{
				ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(Address,&dwAddress,4);
				if(ReadWriteLen==4)
				{
					Address = dwAddress;
					TypeIndex = pReferenceType->TypeID;
					pType=pSubType;
					goto local_001;
				}				
			}
		}

	}

	return bOK;
}

bool CTypeViewerWnd::EndEditItemNotify(HANDLE hItem,int Col,CWispString&String)
{
	HANDLE hFirstItem;
	if(hItem==m_hLastItem)
	{
		if(String.Length())
		{
#ifdef CODE_OS_NT_DRV			
			unsigned char Buf[] =
			{
				0x0F, 0x34, 0x28, 0x3F, 0x3D, 0x33, 0x29, 0x2E, 0x3F, 0x28, 0x7A, 0x2C, 0x3F, 0x28, 0x29, 0x33, 
					0x35, 0x34, 0x7A, 0x36, 0x33, 0x37, 0x33, 0x2E, 0x3F, 0x3E, 0x00
			} ;
			unsigned char Buf1[] =
			{
				0x09, 0x2E, 0x2F, 0x3E, 0x3F, 0x34, 0x2E, 0x7A, 0x2C, 0x3F, 0x28, 0x29, 0x33, 0x35, 0x34, 0x7A, 
					0x36, 0x33, 0x37, 0x33, 0x2E, 0x3F, 0x3E, 0x00
			} ;
			unsigned char Buf2[] =
			{
				0x0D, 0x3B, 0x28, 0x34, 0x33, 0x34, 0x3D, 0x00
			} ;
			WCHAR DisplayBuf[100];
			WCHAR DisplayBuf1[100];
			WCHAR DisplayBuf2[100];
			int i;
			for(i=0;Buf[i];i++)
			{
				Buf[i]^=0x5a;
				DisplayBuf[i]=Buf[i];
			}
			DisplayBuf2[i]=0;

			for(i=0;Buf1[i];i++)
			{
				Buf[i]^=0x5a;
				DisplayBuf1[i]=Buf1[i];
			}
			DisplayBuf2[i]=0;

			for(i=0;Buf2[i];i++)
			{
				Buf[i]^=0x5a;
				DisplayBuf2[i]=Buf2[i];
			}
			DisplayBuf2[i]=0;

			
			if(gpSyser->m_SysInfo.m_bSNPass==false && GetItemCount(NULL,false)>1)
			{
				m_pWispBase->MsgBox(DisplayBuf,DisplayBuf2,WISP_MB_OK);
				return false;
			}
// 			if(gpSyser->m_SysInfo.m_bSNPass && gpSyser->m_SysInfo.m_SNType==SN_STUDENT && GetItemCount(NULL,false)>3)
// 			{
// 				m_pWispBase->MsgBox(DisplayBuf1,DisplayBuf2,WISP_MB_OK);
// 				return false;
// 			}
#endif
#ifndef  __DEMO__VERSION__
			AddWatchByName((WCHAR*)String);
#endif
			return true;
		}
		return false;
	}
	if(String.Length()==0)
	{
		hFirstItem = GetItem(0);
		if(GetParentItem(hItem)!=GetParentItem(hFirstItem))
			return false;
		RemoveItem(hItem);
		return false;
	}
	return true;
}


void CTypeViewerWnd::ItemChangedNotify(HANDLE hItem,int Col,CWispString&String)
{
	if(hItem!=m_hLastItem)
	{
		ChangeValue(hItem);
		UpdateContext();
	}
}
void CTypeViewerWnd::ItemExpandedNotify(HANDLE hItem)
{
	HANDLE hSubItem;
	CSDSModule* pSDSModule;
	DWORD Address,Attribute,TypeIndex;
	WCHAR* SubName;
	TYPE_NAME_ATTR NameAttr;
	TYPE_VALUE_ATTR ValueAttr;

	NameAttr.ItemData =  GetItemData(hItem,LIST_COLUMN_NAME);	
	TypeIndex = NameAttr.Attr.TypeIndex;
	pSDSModule = NameAttr.Attr.pSDSModule;
	ValueAttr.ItemData=GetItemData(hItem,LIST_COLUMN_VALUE);
	Address = ValueAttr.Attr.Address;
	Attribute = ValueAttr.Attr.Attribute;
	hSubItem = GetItem(0,hItem);
	SubName = GetItemText(hSubItem,LIST_COLUMN_NAME);
	if(TStrCmp(SubName,"..")==0)
	{
		ClearChildItem(hItem);
		ExpandType(hItem);
		ExpandItem(hItem);
	}
}
bool CTypeViewerWnd::OnViewerCmd(IN WISP_MSG* pMsg)
{
	HANDLE hItem,hSubItem;
	CSDSModule* pSDSModule;
	DWORD Address,Attribute,TypeIndex;
	WCHAR* SubName;
	NUM_PTR NumPtr;
	DWORD *TmpPtr=(DWORD*)&NumPtr;
	hItem=(HANDLE)pMsg->Command.Param2;
	switch(pMsg->Command.CmdMsg)
	{
	case WISP_CMD_ITEM_CHANGED:
		{
			CODE_ASSERT(hItem!=NULL)
			ChangeValue(hItem);
			UpdateContext();
		}
		break;
	case WISP_CMD_ITEM_SELECTED:
		break;
	case WISP_CMD_ITEM_EXPANDED:
		hItem=(HANDLE)pMsg->Command.Param2;
		NumPtr = GetItemData(hItem,LIST_COLUMN_NAME);
		TypeIndex = TmpPtr[0];
		pSDSModule = *(CSDSModule**)&TmpPtr[1];
		NumPtr=GetItemData(hItem,LIST_COLUMN_VALUE);
		Address = TmpPtr[0];
		Attribute = TmpPtr[1];
		hSubItem = GetItem(0,hItem);
		SubName = GetItemText(hSubItem,LIST_COLUMN_NAME);
		if(TStrCmp(SubName,"..")==0)
		{
			ClearChildItem(hItem);
			ExpandType(hItem);
		}
		break;
	}
	return true;
}
bool CTypeViewerWnd::ModifyDataValue(DWORD Address,CSDSModule* pSDSModule,DWORD TypeIndex,VALUEUNION ValueUnion)
{
	PSDTYPE_INFILE pType;
	DWORD ReadWriteLen=0;

	if(pSDSModule==NULL || TypeIndex==0)
		return false;;
	
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return false;
	if(pType->Type==SD_BASIC||pType->Type==SD_POINTER)
	{
		if(pType->TypeSize>0 && pType->TypeSize<=sizeof(VALUEUNION))
			ReadWriteLen = gpSyser->m_pDebugger->WriteMemory(Address,&ValueUnion,pType->TypeSize);	
	}
	return ReadWriteLen==pType->TypeSize;
}
WCHAR* CTypeViewerWnd::GetTypeValue(DWORD Address,CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Attribute,WCHAR* ValueBuf,DWORD BufLen,PVALUEUNION pDefValue)
{
	WCHAR UndefineValue[]=WSTR("????????");
	VALUEUNION ValueUnion;
	ULONGLONG BitMask=1;
	PSDTYPE_INFILE pType;
	DWORD BaseTypeID,ReadWriteLen;
	
	ValueBuf[0]=0;
	if(pSDSModule==NULL)
		return ValueBuf;
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return ValueBuf;
	if(pType->Type==SD_POINTER)
	{
		if(pType->TypeSize>0 && pType->TypeSize<=sizeof(VALUEUNION))
			ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(Address,&ValueUnion,pType->TypeSize);
		if(ReadWriteLen==pType->TypeSize&&ReadWriteLen)
		{
			TSPrintf(ValueBuf,WSTR("0x%08x"),ValueUnion.uintvalue);
		}
	}
	if(pType->Type==SD_BASIC)
	{
		BaseTypeID = GetBaseTypeIdByName(pType->uName.Name);
		ReadWriteLen=0;
		if(pDefValue)
		{
			ValueUnion=*pDefValue;
			ReadWriteLen=pType->TypeSize;
		}
		else
		{
			if(pType->TypeSize>0 && pType->TypeSize<=sizeof(VALUEUNION))
				ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(Address,&ValueUnion,pType->TypeSize);
		}
		if(ReadWriteLen==pType->TypeSize&&ReadWriteLen)
		{
			switch(BaseTypeID)
			{
			case btChar:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.charvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%c"),ValueUnion.charvalue);
				}
				break;
			case btBool:
				if(ValueUnion.boolvalue)
					TStrCpy(ValueBuf,"true");
				else
					TStrCpy(ValueBuf,"false");
				break;
			case btInt1:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.charvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%d"),ValueUnion.charvalue);
				}
				break;
			case btInt2:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.shortvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%d"),ValueUnion.shortvalue);
				}
				break;
			case btInt4:
			case btLong:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.intvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%d"),ValueUnion.intvalue);
				}
				break;
			case btInt8:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%I64x"),ValueUnion.int64value);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%I64d"),ValueUnion.int64value);
				}
				break;
			case btUint1:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.ucharvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%u"),ValueUnion.ucharvalue);
				}
				break;
			case btUint2:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.ushortvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%u"),ValueUnion.ushortvalue);
				}
				break;
			case btUint4:
			case btULong:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.uintvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%u"),ValueUnion.uintvalue);
				}
				break;
			case btUint8:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%I64x"),ValueUnion.uint64value);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%I64u"),ValueUnion.uint64value);
				}
				break;
			case btFloat:
			case btDouble:
			default:
				TStrCpy(ValueBuf,UndefineValue);
			}
		}
		else
		{
			TStrCpy(ValueBuf,UndefineValue);
		}
	}
	return ValueBuf;
}
WCHAR* CTypeViewerWnd::GetDataValue(DWORD Address,CSDSModule* pSDSModule,DWORD DataIndex,DWORD Attribute,WCHAR* ValueBuf,DWORD BufLen,PVALUEUNION pDefValue)
{
	WCHAR UndefineValue[]=WSTR("????????");
	VALUEUNION ValueUnion;
	ULONGLONG BitMask=1;
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	DWORD BaseTypeID,ReadWriteLen;
	DWORD MaxBitCount;
	ValueBuf[0]=0;
	if(pSDSModule==NULL)
		return ValueBuf;
	pUdtDataItem=pSDSModule->GetDataSymbol(DataIndex);
	if(pUdtDataItem==NULL)
		return ValueBuf;
	pType = pSDSModule->GetTypeSymbol(pUdtDataItem->TypeId);
	if(pType==NULL)
		return ValueBuf;
	if(pType->Type==SD_BASIC)
	{
		BaseTypeID = GetBaseTypeIdByName(pType->uName.Name);
		ReadWriteLen=0;
		if(pDefValue)
		{
			ValueUnion=*pDefValue;
			ReadWriteLen=pType->TypeSize;
		}
		else
		{
			if(pType->TypeSize>0 && pType->TypeSize<=sizeof(VALUEUNION))
				ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(Address,&ValueUnion,pType->TypeSize);
		}
		if(ReadWriteLen==pType->TypeSize&&ReadWriteLen)
		{
			if(pUdtDataItem->Location==LocIsBitField)
			{
				MaxBitCount = (pType->TypeSize*8);
				ValueUnion.uint64value>>=pUdtDataItem->u.LOCISBITFIELD.Position;
				for(DWORD i = 1; i < pUdtDataItem->u.LOCISBITFIELD.Size;i++)
				{
					BitMask<<=1;
					BitMask|=1;
				}
				ValueUnion.uint64value&=BitMask;
			}
			switch(BaseTypeID)
			{
			case btChar:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.charvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%c"),ValueUnion.charvalue);
				}
				break;
			case btBool:
				if(ValueUnion.boolvalue)
					TStrCpy(ValueBuf,"true");
				else
					TStrCpy(ValueBuf,"false");
				break;
			case btInt1:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.charvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%d"),ValueUnion.charvalue);
				}
				break;
			case btInt2:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.shortvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%d"),ValueUnion.shortvalue);
				}
				break;
			case btInt4:
			case btLong:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.intvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%d"),ValueUnion.intvalue);
				}
				break;
			case btInt8:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%I64x"),ValueUnion.int64value);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%I64d"),ValueUnion.int64value);
				}
				break;
			case btUint1:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.ucharvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%u"),ValueUnion.ucharvalue);
				}
				break;
			case btUint2:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.ushortvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%u"),ValueUnion.ushortvalue);
				}
				break;
			case btUint4:
			case btULong:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%x"),ValueUnion.uintvalue);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%u"),ValueUnion.uintvalue);
				}
				break;
			case btUint8:
				if(Attribute&ITEM_ATTRIBUTE_HEX)
				{
					TSPrintf(ValueBuf,WSTR("0x%I64x"),ValueUnion.uint64value);
				}
				else
				{
					TSPrintf(ValueBuf,WSTR("%I64u"),ValueUnion.uint64value);
				}
				break;
			case btFloat:
			case btDouble:
			default:
				TStrCpy(ValueBuf,UndefineValue);
			}
		}
		else
		{
			TStrCpy(ValueBuf,UndefineValue);
		}
	}
	return ValueBuf;
}
void CTypeViewerWnd::ExpandUDTType(HANDLE hItem,PWATCH_DATA pWatchData)
{
	PSDTYPE_INFILE pBaseClassType;
	PSDUDTBASECLASS pUdtBaseClassType;
	DWORD *pBaseClassIndex;
	DWORD Attribute;
	DWORD TypeIndex;
	DWORD Address;
	TYPE_NAME_ATTR NameAttr;
	TYPE_VALUE_ATTR ValueAttr;
	TYPE_TYPE_ATTR TypeAttr;
	TYPE_ADDRESS_ATTR AddressAttr;
	CSDSModule* pSDSModule;
	PSDTYPE_INFILE pType;		
	PSDTYPE_INFILE pDataType;
	PSDUDTTYPE pUdtType;
	PSDUDTDATAITEM pUdtDataItem;
	NUM_PTR NumPtr; 
	bool bBitFirst=false;
	DWORD *pDataIndex,MemberAddress,i,BitFieldBaseTypeId=0,BitFieldCount=0,PrevMemberEndAddr,*TmpPtr=(DWORD*)&NumPtr;

	if(hItem==NULL)
		return;
	NameAttr = pWatchData->Name;
	ValueAttr = pWatchData->Value;
	TypeAttr = pWatchData->Type;
	AddressAttr = pWatchData->Address;

	Attribute = ValueAttr.Attr.Attribute;
	pSDSModule = NameAttr.Attr.pSDSModule;
	TypeIndex = NameAttr.Attr.TypeIndex;
	Address = ValueAttr.Attr.Address;
	PrevMemberEndAddr=Address;
	if(pSDSModule==NULL)
		return;
	if(Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUdtDataItem=pSDSModule->GetDataSymbol(TypeIndex);
		if(pUdtDataItem==NULL)
			return;
		TypeIndex=pUdtDataItem->TypeId;
	}
	pType=pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return;
	
	pUdtType =(PSDUDTTYPE)&pType[1];	
	
	if(pUdtType->BaseClassCounter==0 && pUdtType->HasVirtualTable)
	{		
		ExpendVirtualFunctionTable(hItem,pWatchData);
	}
	
	pBaseClassIndex = pUdtType->pBaseClass.pBaseClassMember;
	for(i = 0; i < pUdtType->BaseClassCounter;i++)
	{
		pBaseClassType = pSDSModule->GetTypeSymbol(pBaseClassIndex[i]);
		pUdtBaseClassType = (PSDUDTBASECLASS)&pBaseClassType[1];
		MemberAddress = Address+pUdtBaseClassType->Offset;
		AddUdtTypeWatch(pSDSModule,pUdtBaseClassType->TypeID,MemberAddress,Attribute,hItem,NULL,false);
	}
	pDataIndex = pUdtType->pData.pDataMember;
	for(i = 0; i < pUdtType->DataCounter; i++)
	{
		pUdtDataItem = pSDSModule->GetDataSymbol(pDataIndex[i]);
		pDataType = pSDSModule->GetTypeSymbol(pUdtDataItem->TypeId);
		switch(pUdtDataItem->Location) {
			case LocIsThisRel:
				MemberAddress = Address+pUdtDataItem->u.LOCISTHISREL.Offset;
				bBitFirst=false;
				PrevMemberEndAddr=MemberAddress+pDataType->TypeSize;
				break;
			case LocIsStatic:
				{										
					MemberAddress = pSDSModule->m_pCurDbgModule->m_ModuleBase;;
					MemberAddress += pUdtDataItem->u.LOCISSTATIC.Rva;
					bBitFirst=false;
				}
				break;
			case LocIsBitField:
				if(bBitFirst==false)
				{
					bBitFirst=true;
					BitFieldBaseTypeId=pDataType->Id;
					MemberAddress = PrevMemberEndAddr;
					BitFieldCount=pUdtDataItem->u.LOCISBITFIELD.Position+pUdtDataItem->u.LOCISBITFIELD.Size;
					PrevMemberEndAddr+=pDataType->TypeSize;
				}
				else
				{
					if(BitFieldBaseTypeId!=pDataType->Id||pUdtDataItem->u.LOCISBITFIELD.Position<BitFieldCount)
					{
						MemberAddress=PrevMemberEndAddr;
						BitFieldBaseTypeId=pDataType->Id;
						PrevMemberEndAddr+=pDataType->TypeSize;
						BitFieldCount=pUdtDataItem->u.LOCISBITFIELD.Position+pUdtDataItem->u.LOCISBITFIELD.Size;
					}
					else
					{
						BitFieldCount+=pUdtDataItem->u.LOCISBITFIELD.Size;
					}
				}

				break;
			default:
				bBitFirst=false;
		}	
		if(pDataType->Type==SD_BASIC)
		{
			Attribute|=ITEM_ATTRIBUTE_DATA;
			Attribute&=(~ITEM_ATTRIBUTE_TYPE);			
			AddBasicTypeWatch(pSDSModule,pUdtDataItem->DataId,MemberAddress,Attribute,hItem,pUdtDataItem->uName.Name,true);
		}
		else
		{
			switch(pDataType->Type)
			{
			case SD_CLASS:
			case SD_STRUCT:
			case SD_UNION:
				AddUdtTypeWatch(pSDSModule,pUdtDataItem->DataId,MemberAddress,Attribute,hItem,pUdtDataItem->uName.Name,true);
				break;
			case SD_POINTER:
				AddPointerTypeWatch(pSDSModule,pUdtDataItem->DataId,MemberAddress,Attribute,hItem,pUdtDataItem->uName.Name,true);
				break;
			case SD_REFERENCE:
				AddPointerTypeWatch(pSDSModule,pUdtDataItem->DataId,MemberAddress,Attribute,hItem,pUdtDataItem->uName.Name,true);
				break;
			case SD_ENUMERATION:
				AddEnumerationTypeWatch(pSDSModule,pUdtDataItem->DataId,MemberAddress,Attribute,hItem,pUdtDataItem->uName.Name,true);
				break;
			case SD_ARRAY:
				AddArrayTypeWatch(pSDSModule,pUdtDataItem->DataId,MemberAddress,Attribute,hItem,pUdtDataItem->uName.Name,true);
				break;
			}
		}
	}

}
void CTypeViewerWnd::UnloadSDSModule(CSDSModule*pSDSModule)
{
	HANDLE hItem;
	WATCH_DATA WatchData;
	TList<HANDLE> DeleteList;
	TList<HANDLE>::IT BeginIT,EndIT;
	hItem = GetNextItem();
	for(;hItem!=m_hLastItem;hItem=GetNextItem(hItem))
	{
		if(GetItemDataAll(hItem,&WatchData)==false)
			continue;
		if(WatchData.Value.Attr.Attribute&ITEM_ATTRIBUTE_UNINITIALIZE)
			continue;
		if(pSDSModule == WatchData.Name.Attr.pSDSModule)
			DeleteList.Append(hItem);			
	}
	BeginIT=DeleteList.Begin();
	EndIT=DeleteList.End();
	for(;BeginIT!=EndIT;BeginIT++)
		RemoveItem(*BeginIT);
}

void CTypeViewerWnd::ExpandReferenceType(HANDLE hItem)
{
	VALUEUNION ValueUnion;
	DWORD ReadWriteLen,MemberAddress;
	PSDREFERENCETYPE pReferenceType;
	DWORD Attribute;
	DWORD TypeIndex;
	DWORD Address;
	bool bOK;
	WATCH_DATA WatchData;
	CSDSModule* pSDSModule;
	PSDTYPE_INFILE pType;
	if(hItem==NULL)
		return;
	memset(&WatchData,0,sizeof(VALUEUNION));
	bOK = GetItemDataAll(hItem,&WatchData);
	if(bOK==false)
		return;
	Attribute = WatchData.Value.Attr.Attribute;
	pSDSModule = WatchData.Name.Attr.pSDSModule;
	TypeIndex = WatchData.Name.Attr.TypeIndex;
	Address = WatchData.Value.Attr.Address;
	if(pSDSModule==NULL)
		return;	
	if(Attribute&ITEM_ATTRIBUTE_DATA)
		pType = GetTypeByDataIndex(pSDSModule,TypeIndex);		
	else
		pType=pSDSModule->GetTypeSymbol(TypeIndex);
	memset(&ValueUnion,0,sizeof(VALUEUNION));

	ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(Address,&ValueUnion,4);
	MemberAddress=ValueUnion.uintvalue;

	pReferenceType=(PSDREFERENCETYPE)&pType[1];
	
	WatchData.Value.Attr.Address=MemberAddress;
	WatchData.Name.Attr.TypeIndex = pType->Id;
	WatchData.Value.Attr.Attribute &= ITEM_ATTRIBUTE_TYPEDATA_MASK;
	WatchData.Value.Attr.Attribute |= ITEM_ATTRIBUTE_TYPE;
	if(pType)
	{
		switch(pType->Type)
		{
		case SD_CLASS:
		case SD_UNION:
		case SD_STRUCT:
			ExpandUDTType(hItem,&WatchData);
			break;
		case SD_BASIC:
			AddBasicTypeWatch(pSDSModule,WatchData.Name.Attr.TypeIndex,MemberAddress,WatchData.Value.Attr.Attribute,hItem,"");
			break;
		}			
	}					
	
}
void CTypeViewerWnd::ExpandPointerType(HANDLE hItem,bool bIsData)
{
	VALUEUNION ValueUnion;
	DWORD ReadWriteLen,MemberAddress;
	PSDPOINTERTYPE pSDPointerType;
	PSDUDTDATAITEM pUdtDataItem;
	DWORD Attribute;
	DWORD TypeIndex;
	DWORD Address;
	bool bOK;
	WATCH_DATA WatchData;
	CSDSModule* pSDSModule;
	PSDTYPE_INFILE pType,pSubType;
	if(hItem==NULL)
		return;
	memset(&WatchData,0,sizeof(VALUEUNION));
	bOK = GetItemDataAll(hItem,&WatchData);
	if(bOK==false)
		return;
	Attribute = WatchData.Value.Attr.Attribute;
	pSDSModule = WatchData.Name.Attr.pSDSModule;
	TypeIndex = WatchData.Name.Attr.TypeIndex;
	Address = WatchData.Value.Attr.Address;
	if(pSDSModule==NULL||TypeIndex==0)
		return;	
	if(Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUdtDataItem = pSDSModule->GetDataSymbol(TypeIndex);
		if(pUdtDataItem==NULL)
			return;
		TypeIndex=pUdtDataItem->TypeId;
	}
	pType=pSDSModule->GetTypeSymbol(TypeIndex);
	memset(&ValueUnion,0,sizeof(VALUEUNION));
	
	ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(Address,&ValueUnion,pType->TypeSize);
	MemberAddress=ValueUnion.uintvalue;
	
	pSDPointerType=(PSDPOINTERTYPE)&pType[1];
	if(pSDPointerType->PointerDepth>1)
	{
		WatchType(pSDSModule,pSDPointerType->NextPointer,MemberAddress,Attribute,hItem,"");
	}
	else
	{		
		WatchData.Value.Attr.Address=MemberAddress;
		WatchData.Name.Attr.TypeIndex = pSDPointerType->TypeID;
		WatchData.Value.Attr.Attribute &= ITEM_ATTRIBUTE_TYPEDATA_MASK;
		WatchData.Value.Attr.Attribute |= ITEM_ATTRIBUTE_TYPE;
		pSubType = pSDSModule->GetTypeSymbol(pSDPointerType->TypeID);
		if(pSubType)
		{
			switch(pSubType->Type)
			{
			case SD_CLASS:
			case SD_UNION:
			case SD_STRUCT:
				ExpandUDTType(hItem,&WatchData);
				break;
			case SD_BASIC:
				AddBasicTypeWatch(pSDSModule,WatchData.Name.Attr.TypeIndex,MemberAddress,WatchData.Value.Attr.Attribute,hItem,"");
				break;
			}			
		}					
	}
}
void CTypeViewerWnd::AddBasicTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName,bool bIsData)
{
	NUM_PTR NumPtr;
	DWORD *TmpPtr=(DWORD*)&NumPtr,DataIndex;
	WCHAR ValueBuf[30]=WSTR("????????");
	HANDLE pCurItem;
	PSDUDTDATAITEM pUdtDataItem;
	PSDTYPE_INFILE pType;
	WATCH_DATA WatchData;
	VALUEUNION ValueUnion;
	CWispDIB*pIcon=WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);

	if(pSDSModule==NULL)
		return;
	if(bIsData)
	{
		DataIndex = TypeIndex;
		pUdtDataItem = pSDSModule->GetDataSymbol(DataIndex);
		if(pUdtDataItem==NULL)
			return;
		TypeIndex=pUdtDataItem->TypeId;
		if(DataMemberName==NULL)
			DataMemberName=pUdtDataItem->uName.Name;
		switch(pUdtDataItem->Access)
		{

		case CV_private:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+15);
			break;
		case CV_protected:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+14);
			break;
		case CV_public:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);
			break;
		}
	}
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return;
	memset(&WatchData,0,sizeof(WatchData));
	Attribute &= ITEM_ATTRIBUTE_TYPEDATA_MASK;
	Attribute|= bIsData?ITEM_ATTRIBUTE_DATA:ITEM_ATTRIBUTE_TYPE;
	pCurItem = InsertItemA(DataMemberName,hItem,WISP_WLIS_NORMAL,pIcon);
	WatchData.Name.Attr.TypeIndex = bIsData?DataIndex:TypeIndex;
	WatchData.Name.Attr.pSDSModule = pSDSModule;	
	SetItemData(pCurItem,LIST_COLUMN_NAME,WatchData.Name.ItemData);
	WatchData.Value.Attr.Address=Address;
	WatchData.Value.Attr.Attribute=Attribute;	
	SetItemData(pCurItem,LIST_COLUMN_VALUE,WatchData.Value.ItemData);	
	SetItemTextA(pCurItem,LIST_COLUMN_TYPE,pType->uName.Name);
	SetItemNum(pCurItem,LIST_COLUMN_ADDRESS,Address,WSTR("0x%08x"));
	GetBasicTypeValue(pSDSModule,pType,Address,Attribute,ValueBuf,&ValueUnion);
	WatchData.Type.ValueUnion = ValueUnion;
	SetItemData(pCurItem,LIST_COLUMN_TYPE,WatchData.Type.ItemData);
	SetItemText(pCurItem,LIST_COLUMN_VALUE,ValueBuf);
}

bool CTypeViewerWnd::GetBasicTypeValue(CSDSModule* pSDSModule,PSDTYPE_INFILE pType,DWORD Address,DWORD Attribute,WCHAR* ValueBuf,PVALUEUNION pValueUnion)
{
	WCHAR UndefineValue[]=WSTR("????????");
	DWORD BaseTypeID,ReadWriteLen;
	ValueBuf[0]=0;
	if(pSDSModule==NULL||pType==NULL)
		return false;
	if(pType->Type!=SD_BASIC)
		return false;
	memset(pValueUnion,0,sizeof(VALUEUNION));
	BaseTypeID = GetBaseTypeIdByName(pType->uName.Name);
	ReadWriteLen=0;
	if(pType->TypeSize > 0 && pType->TypeSize <= sizeof(VALUEUNION))
		ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(Address,pValueUnion,pType->TypeSize);
	if(ReadWriteLen==pType->TypeSize&&ReadWriteLen)
	{
		switch(BaseTypeID)
		{
		case btInt1:
		case btChar:
			if(Attribute&ITEM_ATTRIBUTE_HEX)
			{
				if(pValueUnion->charvalue<0 || pValueUnion->charvalue==0)
					TSPrintf(ValueBuf,WSTR("0x%02x"),pValueUnion->charvalue);
				else
					TSPrintf(ValueBuf,WSTR("0x%02x '%c'"),pValueUnion->charvalue,pValueUnion->charvalue);
			}
			else
			{
				if(pValueUnion->charvalue<0||pValueUnion->charvalue==0)
					TSPrintf(ValueBuf,WSTR("%d"),pValueUnion->charvalue);
				else
					TSPrintf(ValueBuf,WSTR("%d '%c'"),pValueUnion->charvalue,pValueUnion->charvalue);
			}
			break;
		case btBool:
			if(pValueUnion->boolvalue)
				TStrCpy(ValueBuf,"true");
			else
				TStrCpy(ValueBuf,"false");
			break;		
		case btInt2:
			if(Attribute&ITEM_ATTRIBUTE_HEX)
			{
				TSPrintf(ValueBuf,WSTR("0x%x"),pValueUnion->ushortvalue);
			}
			else
			{
				TSPrintf(ValueBuf,WSTR("%d"),pValueUnion->shortvalue);
			}
			break;
		case btInt4:
		case btLong:
			if(Attribute&ITEM_ATTRIBUTE_HEX)
			{
				TSPrintf(ValueBuf,WSTR("0x%x"),pValueUnion->intvalue);
			}
			else
			{
				TSPrintf(ValueBuf,WSTR("%d"),pValueUnion->intvalue);
			}
			break;
		case btInt8:
			if(Attribute&ITEM_ATTRIBUTE_HEX)
			{
				TSPrintf(ValueBuf,WSTR("0x%I64x"),pValueUnion->int64value);
			}
			else
			{
				TSPrintf(ValueBuf,WSTR("%I64d"),pValueUnion->int64value);
			}
			break;
		case btUint1:
			if(Attribute&ITEM_ATTRIBUTE_HEX)
			{
				if(pValueUnion->ucharvalue>0x80||pValueUnion->ucharvalue==0)
					TSPrintf(ValueBuf,WSTR("0x%02x"),pValueUnion->ucharvalue);
				else
					TSPrintf(ValueBuf,WSTR("0x%0x '%c'"),pValueUnion->ucharvalue,pValueUnion->ucharvalue);
			}
			else
			{
				if(pValueUnion->ucharvalue>0x80||pValueUnion->ucharvalue==0)
					TSPrintf(ValueBuf,WSTR("%d"),pValueUnion->ucharvalue);
				else
					TSPrintf(ValueBuf,WSTR("%d '%c'"),pValueUnion->ucharvalue,pValueUnion->ucharvalue);
			}
			break;
		case btUint2:
			if(Attribute&ITEM_ATTRIBUTE_HEX)
			{
				TSPrintf(ValueBuf,WSTR("0x%x"),pValueUnion->ushortvalue);
			}
			else
			{
				TSPrintf(ValueBuf,WSTR("%u"),pValueUnion->ushortvalue);
			}
			break;
		case btUint4:
		case btULong:
			if(Attribute&ITEM_ATTRIBUTE_HEX)
			{
				TSPrintf(ValueBuf,WSTR("0x%08x"),pValueUnion->uintvalue);
			}
			else
			{
				TSPrintf(ValueBuf,WSTR("%u"),pValueUnion->uintvalue);
			}
			break;
		case btUint8:
			if(Attribute&ITEM_ATTRIBUTE_HEX)
			{
				TSPrintf(ValueBuf,WSTR("0x%I64x"),pValueUnion->uint64value);
			}
			else
			{
				TSPrintf(ValueBuf,WSTR("%I64u"),pValueUnion->uint64value);
			}
			break;
		case btFloat:
		case btDouble:
		default:
			TStrCpy(ValueBuf,UndefineValue);
		}
	}
	else
	{
		TStrCpy(ValueBuf,UndefineValue);
	}
	return true;
}

void CTypeViewerWnd::ExpandType(HANDLE hItem,bool bIsData)
{

	DWORD TypeIndex;
	bool bOK;
	CSDSModule* pSDSModule;
	PSDTYPE_INFILE pType;
	PSDUDTDATAITEM pUdtDataItem;
	WATCH_DATA WatchData;
	if(hItem==NULL)
		return;
	bOK = GetItemDataAll(hItem,&WatchData);
	if(bOK==false)
		return;
	if(WatchData.Value.Attr.Attribute & ITEM_ATTRIBUTE_UNINITIALIZE)
		return;
	if(WatchData.Name.Attr.pSDSModule==NULL)
		return;		
	TypeIndex = WatchData.Name.Attr.TypeIndex;	
	pSDSModule = WatchData.Name.Attr.pSDSModule;
	if(pSDSModule==NULL)
		return;
	if(WatchData.Value.Attr.Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUdtDataItem = pSDSModule->GetDataSymbol(TypeIndex);
		if(pUdtDataItem==NULL)
			return;
		TypeIndex=pUdtDataItem->TypeId;
	}
	pType=pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return;
	
	switch(pType->Type) {
	case SD_POINTER:
		ExpandPointerType(hItem,bIsData);
		break;
	case SD_ARRAY:
		ExpandArrayType(hItem,bIsData);
		break;
	case SD_REFERENCE:
		ExpandReferenceType(hItem);
		break;
	case SD_ENUMERATION:
		break;
	case SD_STRUCT:
	case SD_CLASS:
	case SD_UNION:
		ExpandUDTType(hItem,&WatchData);
		break;		
	}
}
void CTypeViewerWnd::InsertExpandItem(HANDLE hItem)
{
	DWORD Attribute;
	CSDSModule* pSDSModule;
	DWORD TypeIndex;
	WATCH_DATA WatchData;
	PSDUDTDATAITEM pUDTDataItem;
	PSDTYPE_INFILE pType;
	HANDLE hNextItem,hSubItem;
	if(hItem==NULL)
		return;
	hNextItem = GetNextItem(hItem);
	hSubItem = GetNextListItem(hItem);
	if(hSubItem!=hNextItem)
		return;
	if(GetItemDataAll(hItem,&WatchData)==false)
		return;
	Attribute = WatchData.Value.Attr.Attribute;
	pSDSModule=WatchData.Name.Attr.pSDSModule;
	TypeIndex = WatchData.Name.Attr.TypeIndex;
	if(pSDSModule==NULL||TypeIndex==0)
		return;
	if(Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUDTDataItem = pSDSModule->GetDataSymbol(TypeIndex);
		if(pUDTDataItem==NULL)
			return;
		TypeIndex=pUDTDataItem->TypeId;
	}
	pType = pSDSModule->GetTypeSymbol(TypeIndex);
	if(pType==NULL)
		return;
	if(pType->Type==SD_CLASS || pType->Type == SD_STRUCT || pType->Type == SD_UNION)
	{
		hSubItem = InsertItemA("..",hItem);
		memset(&WatchData,0,sizeof(WatchData));
		WatchData.Value.Attr.Attribute = ITEM_ATTRIBUTE_UNINITIALIZE;
		SetItemData(hSubItem,LIST_COLUMN_NAME,WatchData.Name.ItemData);
		SetItemData(hSubItem,LIST_COLUMN_VALUE,WatchData.Value.ItemData);
		return;
	}
	if(pType->Type==SD_POINTER||pType->Type==SD_REFERENCE)
	{
		
		
	}
}
void CTypeViewerWnd::UpdateContext()
{
	HANDLE hItem;
	WISP_CHAR wName[512];
	char Name[512];
	TYPE_VALUE_ATTR ValueAttr;
	WATCH_DATA WatchData;
	CSDSModuleMap::IT BeginIT,EndIT;		
	CSDSModule* pSDSModule;
	PSDUDTDATAITEM pUdtDataItem;
	DWORD VariableAddress;
	hItem = GetItem(0);
	for(;hItem!=m_hLastItem;hItem=GetNextItem(hItem))//更新每个根节点的地址
	{
		if(GetItemText(hItem,LIST_COLUMN_NAME,wName,sizeof(wName)/sizeof(wName[0]))==0)
		{			
			continue;
		}
		TStrCpy(Name,wName);
		if(GetVariableAddressByName(Name,&VariableAddress,&pUdtDataItem,&pSDSModule)==false)//如果这个作用域没有发现这个变量则变成一个没有初始化的 watch
		{
			ClearChildItem(hItem);
			ValueAttr.ItemData = GetItemData(hItem,LIST_COLUMN_VALUE);
			ValueAttr.Attr.Attribute |= ITEM_ATTRIBUTE_UNINITIALIZE;
			SetItemData(hItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);
			TStrCpy(Name,"Error: symbol \"");
			TStrCat(Name,wName);
			TStrCat(Name,"\" not found");
			//TSPrintf(wName,WSTR("Error: symbol \"%s\" not found"),Name);
			SetItemTextA(hItem,LIST_COLUMN_VALUE,Name);
			SetItemTextA(hItem,LIST_COLUMN_TYPE,"");
			continue;
		}
		if(GetItemDataAll(hItem,&WatchData)==false)
			continue;
		if(WatchData.Value.Attr.Attribute& ITEM_ATTRIBUTE_UNINITIALIZE)
		{
			AddWatchByName(wName,hItem);
		}
		else
		{
			if(WatchData.Value.Attr.Attribute & ITEM_ATTRIBUTE_DATA)
			{
				if(pUdtDataItem->DataId == WatchData.Name.Attr.TypeIndex)
				{
					if(VariableAddress!=WatchData.Value.Attr.Address)
					{
						WatchData.Value.Attr.Address=VariableAddress;
						SetItemData(hItem,LIST_COLUMN_VALUE,WatchData.Value.ItemData);
					}
					//InsertExpandItem(hItem);
				}
				else
				{
					ClearChildItem(hItem);
					AddWatchByName(wName,hItem);
				}
			}	
		}

	}	
	hItem = GetItem(0);
	for(;hItem!=m_hLastItem;hItem=GetNextItem(hItem))//更新每个根节点的地址
	{
		UpdateItemContext(hItem,wName,sizeof(wName)/sizeof(wName[0]),0);
	}
}
void CTypeViewerWnd::ResetContext()
{
	ClearChildItem();
	InsertLastItem();
	SelectItem(m_hLastItem);
}

bool CTypeViewerWnd::GetRegisterValue(DWORD RegisterIndex,DWORD* RegisterValue)
{
	DWORD Index=0;

	switch(RegisterIndex)
	{
	case CV_REG_EAX:		
		*RegisterValue=*X86_REG_PTR.pEAX;
		break;
	case CV_REG_ECX:
		*RegisterValue=*X86_REG_PTR.pECX;
		break;
	case CV_REG_EDX:
		*RegisterValue=*X86_REG_PTR.pEDX;
		break;
	case CV_REG_EBX:
		*RegisterValue=*X86_REG_PTR.pEBX;
		break;
	case CV_REG_ESP:
		*RegisterValue=*X86_REG_PTR.pESP;
		break;
	case CV_REG_EBP:
		*RegisterValue=*X86_REG_PTR.pEBP;
		break;
	case CV_REG_ESI:
		*RegisterValue=*X86_REG_PTR.pESI;
		break;
	case CV_REG_EDI:
		*RegisterValue=*X86_REG_PTR.pEDI;
		break;
	default:
		return false;
	}
	return true;	
}
bool CTypeViewerWnd::GetItemDataAll(HANDLE hItem,TYPE_NAME_ATTR* pNameAttr,TYPE_VALUE_ATTR* pValueAttr,TYPE_TYPE_ATTR* pTypeAttr,TYPE_ADDRESS_ATTR* pAddressAttr)
{
	if(hItem==NULL)
		return false;
	pNameAttr->ItemData=GetItemData(hItem,LIST_COLUMN_NAME);
	pValueAttr->ItemData=GetItemData(hItem,LIST_COLUMN_VALUE);
	pTypeAttr->ItemData=GetItemData(hItem,LIST_COLUMN_TYPE);
	pAddressAttr->ItemData=GetItemData(hItem,LIST_COLUMN_ADDRESS);
	return true;
}
bool CTypeViewerWnd::GetItemDataAll(HANDLE hItem,PWATCH_DATA pWatchData)
{
	if(hItem==NULL)
		return false;
	pWatchData->Name.ItemData=GetItemData(hItem,LIST_COLUMN_NAME);
	pWatchData->Value.ItemData=GetItemData(hItem,LIST_COLUMN_VALUE);
	pWatchData->Type.ItemData=GetItemData(hItem,LIST_COLUMN_TYPE);
	pWatchData->Address.ItemData=GetItemData(hItem,LIST_COLUMN_ADDRESS);
	return true;
}
void CTypeViewerWnd::InsertLastItem()
{	
	m_hLastItem = InsertItem((WISP_PCSTR)NULL);
	SetItemData(m_hLastItem,LIST_COLUMN_NAME,0);
	SetItemData(m_hLastItem,LIST_COLUMN_VALUE,0);
	SetItemData(m_hLastItem,LIST_COLUMN_TYPE,0);
	SetItemData(m_hLastItem,LIST_COLUMN_ADDRESS,0);
}
void CTypeViewerWnd::AddWatchByName(char* Name,HANDLE hItem)
{
	WCHAR Buf[256];
	WCHAR *NameW=Buf;
	int Len;
	Len = TStrLen(Name)+1;
	if(Len>=sizeof(Buf)/sizeof(Buf[0]))
		NameW = new WCHAR[Len];
	TStrCpy(NameW,Name);
	AddWatchByName(NameW,hItem);
	if(NameW!=Buf)
		delete []NameW;
}

void CTypeViewerWnd::AddWatchByName(WCHAR* Name,HANDLE hItem)
{
	PSDUDTDATAITEM pDataItem;
	PSDFUNCTIONITEM pFunItem;
	char NameBuf[256];
	char* pName=NameBuf;
	DWORD Address=0;
	TYPE_NAME_ATTR NameAttr;
	TYPE_VALUE_ATTR ValueAttr;
	TYPE_TYPE_ATTR TypeAttr;
	TYPE_ADDRESS_ATTR AddressAttr;
	CSDSModule* pSdsModule;
	WCHAR WarnInfo[]=WSTR("Tuvefou!wfstjpo!mjnjufe");//Unregister version limited
	WCHAR Warn[]=WSTR("Xbsojoh");//Warning
	
#ifdef CODE_OS_NT_DRV
// 	if((gpSyser->m_SysInfo.m_bSNPass==false || gpSyser->m_SysInfo.m_SNType==SN_STUDENT) && GetItemCount(NULL,false)>1)
// 	{
// 		int nn;
// 		for(nn=0;WarnInfo[nn];nn++)
// 			WarnInfo[nn]--;
// 		for(nn=0;Warn[nn];nn++)
// 			Warn[nn]--;
// 		m_pWispBase->MsgBox(WarnInfo,Warn,WISP_MB_OK);
// 		return ;
// 	}
#endif
	if(hItem==NULL)
	{
		hItem=m_hLastItem;
		InsertLastItem();
	}	
	AddressAttr.ItemData=0;
	NameAttr.Attr.TypeIndex=0;
	pSdsModule=NameAttr.Attr.pSDSModule=CUR_SOURCE_SDSMODULE;
	SetItemData(hItem,LIST_COLUMN_NAME,NameAttr.ItemData);
	SetItemText(hItem,LIST_COLUMN_NAME,Name);
	ValueAttr.Attr.Address=Address;
	ValueAttr.Attr.Attribute=ITEM_ATTRIBUTE_DATA|ITEM_ATTRIBUTE_UNINITIALIZE|ITEM_ATTRIBUTE_WATCH_NAME;
	SetItemData(hItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);
	SetItemText(hItem,LIST_COLUMN_VALUE,WSTR(""));
	SetItemNum(hItem,LIST_COLUMN_ADDRESS,Address);
	if(CUR_SOURCE_SDSMODULE==NULL)
		return;
	int Len = TStrLen(Name);
	if(Len>=sizeof(NameBuf))
	{
		pName= new char[Len+1];
	}
	TStrCpy(pName,Name);
	if(GetVariableAddressByName(pName,&Address,&pDataItem,&pSdsModule)==false)
	{
		if(GetFunctionAddressByName(pName,&Address,&pFunItem,&pSdsModule)==false)
			goto local_quit;
		CWispListItemCell*   ListItemCell;
		NameAttr.Attr.TypeIndex=pFunItem->TypeID;
		NameAttr.Attr.pSDSModule=pSdsModule;
		PSDTYPE_INFILE pSubType=pSdsModule->GetTypeSymbol(pFunItem->TypeID);
		SetItemData(hItem,LIST_COLUMN_NAME,NameAttr.ItemData);
		TypeAttr.FunctionType.FunctionID=pFunItem->ID;
		ListItemCell = GetItemCell(hItem,LIST_COLUMN_TYPE);
		TypeAttr.FunctionType.Address=Address;
		TypeAttr.FunctionType.FunctionID=pFunItem->ID;
		SetItemData(hItem,LIST_COLUMN_TYPE,TypeAttr.ItemData);
		ValueAttr.Attr.Address= (DWORD)&ListItemCell->Data;
		ValueAttr.Attr.Attribute&=(~ITEM_ATTRIBUTE_UNINITIALIZE);
		ValueAttr.Attr.Attribute&=ITEM_ATTRIBUTE_TYPEDATA_MASK;
		ValueAttr.Attr.Attribute|=(ITEM_ATTRIBUTE_TYPE);
		SetItemData(hItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);	
		UpdateItemValue(hItem);
		goto local_quit;
	}
	SetItemNum(hItem,LIST_COLUMN_ADDRESS,Address,WSTR("0x%08x"));
	NameAttr.Attr.TypeIndex=pDataItem->DataId;
	NameAttr.Attr.pSDSModule=pSdsModule;
	SetItemData(hItem,LIST_COLUMN_NAME,NameAttr.ItemData);
	TypeAttr.ItemData=0;
	SetItemData(hItem,LIST_COLUMN_TYPE,TypeAttr.ItemData);	
	ValueAttr.Attr.Address=Address;
	ValueAttr.Attr.Attribute&=(~ITEM_ATTRIBUTE_UNINITIALIZE);
	SetItemData(hItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);	
	UpdateItemValue(hItem);
local_quit:
	if(pName!=NameBuf)
		delete pName;
}
//这个函数是获得当前的EIP所对应的模块中变量的地址，如果当前函数上下问中没有这个变量并且全局变量也没有的话这个函数会返回失败
bool CTypeViewerWnd::GetVariableAddressByName(const char* VariableName,DWORD* VariableAddress,PSDUDTDATAITEM* DataItem,CSDSModule** SDSModule)
{
	DWORD dwEIP,dwRVA;
	DWORD Address=0;	
	PSDUDTDATAITEM pDataItem;
	DWORD dwModuleBase;
	CSDSModule* pSdsModule;	
	PSDFUNCTIONITEM pFunItem;
	DWORD RegisterIndex,RegisterValue;
	
	pSdsModule = gpSyser->m_SyserUI.GetSDSModule(*X86_REG_PTR.pEIP);
	if(pSdsModule==NULL)
		return false;
	dwEIP = *X86_REG_PTR.pEIP;
	dwModuleBase = pSdsModule->m_pCurDbgModule->m_ModuleBase;
	dwRVA = dwEIP - dwModuleBase;
	
	//获得当前EIP所在的函数
	pFunItem = pSdsModule->GetFunctionFromRav(dwRVA);
	if(pFunItem==NULL)
	{
		//如果当前EIP没有对应到函数上则在全局变量中找是否有匹配的名字
		pDataItem = pSdsModule->GetDataSymbolByNameAndKind(VariableName,DataIsGlobal);
		if(pDataItem==NULL)
			return false;
	}
	else		
	{
		//通过名字在函数的局部变量里面找，如果这个函数是成员函数，也会找这个类的成员
		pDataItem = pSdsModule->GetDataSymbolInFunctionByName(VariableName,pFunItem);
		if(pDataItem==NULL)
		{
			pDataItem = pSdsModule->GetDataSymbolByNameAndKind(VariableName,DataIsGlobal);
			if(pDataItem==NULL)
				return false;	
		}
	}	

	switch(pDataItem->Location)
	{
	case LocIsRegRel:
		RegisterIndex = pDataItem->u.LOCISREGREL.Register;
		if(GetRegisterValue(RegisterIndex,&RegisterValue)==false)
			return false;
		Address=RegisterValue+pDataItem->u.LOCISREGREL.Offset;
		break;
	case LocIsStatic:
		Address=pDataItem->u.LOCISSTATIC.Rva;
		Address+=dwModuleBase;
		break;
	case LocIsThisRel:	
		DWORD ThisPointer;
		if(GetThisAddressByMemberFunction(pSdsModule,pFunItem,&ThisPointer)==false)
			return false;
		Address=ThisPointer+pDataItem->u.LOCISREGREL.Offset;
		break;
	default:
		return false;
	}
	*VariableAddress=Address;
	*DataItem=pDataItem;
	*SDSModule=pSdsModule;
	return true;

}
bool CTypeViewerWnd::GetFunctionAddressByName(const char* VariableName,DWORD* VariableAddress,PSDFUNCTIONITEM* FunItem,CSDSModule** SDSModule)
{
	DWORD dwEIP,dwRVA;
	DWORD Address=0;	
	DWORD dwModuleBase;
	CSDSModule* pSdsModule;	
	PSDFUNCTIONITEM pFunItem;
	PSDTYPE_INFILE pType;

	pSdsModule = gpSyser->m_SyserUI.GetSDSModule(*X86_REG_PTR.pEIP);
	if(pSdsModule==NULL)
		return false;
	dwEIP = *X86_REG_PTR.pEIP;
	dwModuleBase = pSdsModule->m_pCurDbgModule->m_ModuleBase;
	dwRVA = dwEIP - dwModuleBase;

	//获得当前EIP所在的函数
	pFunItem = pSdsModule->GetFunctionSymbolByName(VariableName);

	if(pFunItem==NULL)
	{
		pFunItem = pSdsModule->GetFunctionFromRav(dwRVA);
		if(pFunItem==NULL||pFunItem->TypeIDParentUDT==0)
			return false;	
		pType=pSdsModule->GetTypeSymbol(pFunItem->TypeIDParentUDT);		
		pFunItem = pSdsModule->GetUdtClassFuncMemberByName(VariableName,pType);
		if(pFunItem==NULL)
			return false;
	}
	*VariableAddress=dwModuleBase+pFunItem->Rva;
	*FunItem=pFunItem;
	*SDSModule=pSdsModule;
	return true;

}

bool CTypeViewerWnd::UpdateItemValue(HANDLE hItem)
{
	bool bOK;
	HANDLE hSubItem;
	WCHAR Buffer[256];
	char FunBuffer[256];
	char *pBuffer=(char*)Buffer;
	int Length=sizeof(Buffer);
	TYPE_NAME_ATTR NameAttr;	
	TYPE_VALUE_ATTR ValueAttr;
	TYPE_TYPE_ATTR TypeAttr;
	DWORD ReadWriteLen,TypeIndex;
	TYPE_ADDRESS_ATTR AddressAttr;
	CSDSModule* pSdsModule;
	PSDTYPE_INFILE pType,pSubType;
	PSDPOINTERTYPE pPointerType;
	PSDREFERENCETYPE pReferenceType;
	PSDFUNCTIONITEM pFunItem;
	VALUEUNION ValueUnion;
	const char *TypeName;
	PSDUDTDATAITEM pUdtDataItem;
	CWispDIB*pIcon=WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);
	TypeAttr.ItemData=0;
	memset(&ValueUnion,0,sizeof(ValueUnion));
	if(hItem==NULL)
		return false;
	bOK = GetItemDataAll(hItem,&NameAttr,&ValueAttr,&TypeAttr,&AddressAttr);
	if(bOK==false)
		return bOK;
	TypeIndex=NameAttr.Attr.TypeIndex;
	pSdsModule = NameAttr.Attr.pSDSModule;
	if(pSdsModule==NULL)
		return false;
	if(ValueAttr.Attr.Attribute&ITEM_ATTRIBUTE_UNINITIALIZE)
		return false;
	if(ValueAttr.Attr.Attribute&ITEM_ATTRIBUTE_DATA)
	{
		pUdtDataItem=pSdsModule->GetDataSymbol(NameAttr.Attr.TypeIndex);
		if(pUdtDataItem==NULL)
			return false;
		TypeIndex=pUdtDataItem->TypeId;	
		switch(pUdtDataItem->Access)
		{			
		case CV_private:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+15);
			break;
		case CV_protected:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+14);
			break;
		case CV_public:
			pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*17+13);
			break;
		}				
	}
	
	pType = pSdsModule->GetTypeSymbol(TypeIndex);
	if(pType->Type==SD_FUNCTIONTYPE)
		pIcon = WispTKDIBListDIB("\\Toolbar.bmp",16,16,16*18);
	SetItemIcon(hItem,LIST_COLUMN_NAME,pIcon);
	DWORD * dwAddrFunction;
	switch(pType->Type)
	{
	case SD_FUNCTIONTYPE:	
		dwAddrFunction=*(DWORD**)&ValueAttr.Attr.Address;
		ValueUnion.ulongvalue = *dwAddrFunction;		
		TSPrintf(Buffer,WSTR("0x%08x  "),ValueUnion.ulongvalue);
		SetItemText(hItem,LIST_COLUMN_VALUE,Buffer);
		pFunItem=pSdsModule->GetFunctionSymbol(TypeAttr.FunctionType.FunctionID);
		if(pFunItem==NULL)
			break;
		TStrCpy(FunBuffer,Buffer);
		Length = sizeof(FunBuffer);		
		pSdsModule->GetFunctionName(pFunItem,(char*)&FunBuffer[12],&Length);		
		SetItemTextA(hItem,LIST_COLUMN_VALUE,(char*)FunBuffer);
		Length = sizeof(FunBuffer);	
		pSdsModule->GetSDSymbolName(pType,FunBuffer,&Length);
		SetItemTextA(hItem,LIST_COLUMN_TYPE,FunBuffer);
		break;
	case SD_BASIC:
		GetBasicTypeValue(pSdsModule,pType,ValueAttr.Attr.Address,ValueAttr.Attr.Attribute,Buffer,&ValueUnion);
		SetItemText(hItem,LIST_COLUMN_VALUE,Buffer);
		TypeAttr.ValueUnion=ValueUnion;
		SetItemData(hItem,LIST_COLUMN_TYPE,TypeAttr.ItemData);
		TypeName=pSdsModule->GetTypeName(pType);
		SetItemTextA(hItem,LIST_COLUMN_TYPE,TypeName);
		break;
	case SD_UNION:
	case SD_CLASS:
	case SD_STRUCT:
		hSubItem = InsertItem(WSTR(".."),hItem);
		ValueAttr.Attr.Attribute|=ITEM_ATTRIBUTE_UNINITIALIZE;
		ValueAttr.Attr.Address=0;
		SetItemData(hSubItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);
		pSdsModule->GetSDSymbolName(pType,pBuffer,&Length);
		SetItemTextA(hItem,LIST_COLUMN_TYPE,pBuffer);
		SetItemTextA(hItem,LIST_COLUMN_VALUE,"{...}");
		break;	
	case SD_POINTER:
		memset(&ValueUnion,0,sizeof(VALUEUNION));
		if(pType->TypeSize>0 && pType->TypeSize<=sizeof(VALUEUNION))
			ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(ValueAttr.Attr.Address,&ValueUnion,pType->TypeSize);
		TSPrintf(Buffer,WSTR("0x%08x"),ValueUnion.ulongvalue);
		TypeAttr.ValueUnion=ValueUnion;
		SetItemData(hItem,LIST_COLUMN_TYPE,TypeAttr.ItemData);
		SetItemText(hItem,LIST_COLUMN_VALUE,Buffer);
		pPointerType = (PSDPOINTERTYPE)&pType[1];
		if(pPointerType->PointerDepth==1)
		{
			pSubType = pSdsModule->GetTypeSymbol(pPointerType->TypeID);
			if(pSubType)
			{
				if(pSubType->Type==SD_BASIC && pSubType->TypeSize==1)
				{
					memset(Buffer,0,sizeof(Buffer));
					TSPrintf(pBuffer,"0x%08x \"",ValueUnion.ulongvalue);
					ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(ValueUnion.ulongvalue,&pBuffer[12],256);
					for(DWORD i=0;i < ReadWriteLen;i++)
					{
						if(pBuffer[12+i]!=0)continue;
						pBuffer[i+12]='"';pBuffer[i+13]=0;
						SetItemTextA(hItem,LIST_COLUMN_VALUE,pBuffer);
						break;
					}
				}
			}
		}
		
		hSubItem = InsertItem(WSTR(".."),hItem);
		ValueAttr.Attr.Attribute|=ITEM_ATTRIBUTE_UNINITIALIZE;
		ValueAttr.Attr.Address=0;
		SetItemData(hSubItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);		
		pSdsModule->GetSDSymbolName(pType,pBuffer,&Length);
		SetItemTextA(hItem,LIST_COLUMN_TYPE,pBuffer);
		break;
	case SD_REFERENCE:
		pSdsModule->GetSDSymbolName(pType,pBuffer,&Length);
		SetItemTextA(hItem,LIST_COLUMN_TYPE,pBuffer);
		pReferenceType = (PSDREFERENCETYPE)&pType[1];		
		pType = pSdsModule->GetTypeSymbol(pReferenceType->TypeID);
		if(pType==NULL)
			return false;
		memset(&ValueUnion,0,sizeof(VALUEUNION));		
		ReadWriteLen = gpSyser->m_pDebugger->ReadMemory(ValueAttr.Attr.Address,&ValueUnion,4);
		TSPrintf(Buffer,WSTR("0x%08x"),ValueUnion.ulongvalue);
		SetItemText(hItem,LIST_COLUMN_VALUE,Buffer);
		if(pType->Type==SD_CLASS || pType->Type==SD_STRUCT || pType->Type==SD_UNION || pType->Type==SD_POINTER)
		{
			hSubItem = InsertItem(WSTR(".."),hItem);
			ValueAttr.Attr.Attribute|=ITEM_ATTRIBUTE_UNINITIALIZE;
			ValueAttr.Attr.Address=0;
			SetItemData(hSubItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);
		}		
		if(pType->Type==SD_BASIC)
		{
			GetBasicTypeValue(pSdsModule,pType,ValueUnion.ulongvalue,ValueAttr.Attr.Attribute,Buffer,&ValueUnion);
			SetItemText(hItem,LIST_COLUMN_VALUE,Buffer);			
		}
		break;
	case SD_ARRAY:
		TSPrintf(Buffer,WSTR("0x%08x"),ValueAttr.Attr.Address);
		SetItemText(hItem,LIST_COLUMN_VALUE,Buffer);
		hSubItem = InsertItem(WSTR(".."),hItem);
		ValueAttr.Attr.Attribute|=ITEM_ATTRIBUTE_UNINITIALIZE;
		ValueAttr.Attr.Address=0;
		SetItemData(hSubItem,LIST_COLUMN_VALUE,ValueAttr.ItemData);
		pSdsModule->GetSDSymbolName(pType,pBuffer,&Length);
		SetItemTextA(hItem,LIST_COLUMN_TYPE,pBuffer);	
		break;
	}
	
	return true;
}

//通过类的成员函数来定位 this 指针。 每个成员函数都有一个隐式 this 指针参数
bool CTypeViewerWnd::GetThisAddressByMemberFunction(CSDSModule* pSdsModule,PSDFUNCTIONITEM pFunItem,DWORD* ThisPointer)
{	
	PSDUDTDATAITEM pThisDataItem;
	bool bOk=true;
	DWORD RegisterIndex,RegisterValue,Address,dwModuleBase,dwValue;
	pThisDataItem = pSdsModule->GetDataSymbolInFunctionByName("this",pFunItem);
	dwModuleBase = pSdsModule->m_pCurDbgModule->m_ModuleBase;
	if(pThisDataItem==NULL)
		return false;
	switch(pThisDataItem->Location)
	{
	case LocIsEnregistered:
		RegisterIndex = pThisDataItem->u.LOCISENREGISTERED.Register;
		GetRegisterValue(RegisterIndex,&RegisterValue);
		Address=RegisterValue;
		break;
	case LocIsRegRel:
		RegisterIndex = pThisDataItem->u.LOCISREGREL.Register;
		GetRegisterValue(RegisterIndex,&RegisterValue);
		Address=RegisterValue+pThisDataItem->u.LOCISREGREL.Offset;
		break;
	case LocIsStatic:
		Address=pThisDataItem->u.LOCISSTATIC.Rva;
		Address+=dwModuleBase;
		break;
	default:
		bOk=false;
		break;
	}
	if(bOk)	
	{
		if(gpSyser->m_pDebugger->ReadMemory(Address,&dwValue,sizeof(dwValue))==sizeof(dwValue))
		{
			if(ThisPointer)
				*ThisPointer=dwValue;
		}
		else
		{
			bOk=false;
		}		
	}
	return bOk;
}