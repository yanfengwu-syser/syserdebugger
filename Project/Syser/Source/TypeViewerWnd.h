#ifndef _TYPEVIEWERWND_H_
#define _TYPEVIEWERWND_H_
#include "../../Addition/SyserDebugger/SDSymbol.h"
enum
{
	LIST_COLUMN_NAME=0, 
	LIST_COLUMN_VALUE,
	LIST_COLUMN_TYPE,    
	LIST_COLUMN_ADDRESS, 
};
enum
{
	ITEM_ATTRIBUTE_UNINITIALIZE =	0x80000000,
	ITEM_ATTRIBUTE_TYPE			=	0x40000000,
	ITEM_ATTRIBUTE_DATA			=	0x20000000,
	ITEM_ATTRIBUTE_LOCK			=	0x10000000,
	ITEM_ATTRIBUTE_FLOAT		=	0x08000000,
	ITEM_ATTRIBUTE_HEX			=	0x04000000,
	ITEM_ATTRIBUTE_DEC			=	0x02000000,
	ITEM_ATTRIBUTE_WATCH_NAME	=	0x01000000,
	ITEM_ATTRIBUTE_VFTABLE		=	0x00800000,
	ITEM_ATTRIBUTE_TYPEDATA_MASK = ~(ITEM_ATTRIBUTE_DATA|ITEM_ATTRIBUTE_TYPE),
};
typedef union _VALUEUNION
{
	unsigned char ucharvalue;
	unsigned short ushortvalue;
	unsigned int uintvalue;
	unsigned long ulongvalue;
	ULONGLONG uint64value;
	char charvalue;
	short shortvalue;
	int intvalue;
	long longvalue;
	LONGLONG int64value;
	bool boolvalue;
}VALUEUNION,*PVALUEUNION;
typedef union _TYPEVIEW_NAME_ATTRIB
{
	NUM_PTR ItemData;
	struct 
	{
		DWORD TypeIndex;
		CSDSModule* pSDSModule;
	}Attr;		
}TYPE_NAME_ATTR;
typedef union _TYPEVIEW_VALUE_ATTRIB
{
	NUM_PTR ItemData;
	struct {
		DWORD Address;
		DWORD Attribute;
	}Attr;
}TYPE_VALUE_ATTR;
typedef union _TYPEVIEW_TYPE_ATTRIB
{
	NUM_PTR ItemData;
	VALUEUNION ValueUnion;	
	struct _FUNSTR{
		DWORD Address;		
		DWORD FunctionID;
	}FunctionType;
	struct _VTABLE{
		DWORD Address;
		DWORD FunctionCount;
	}VFTable;
}TYPE_TYPE_ATTR;
typedef union _TYPEVIEW_ADDRESS_ATTRIB
{
	NUM_PTR ItemData;

	struct {
		DWORD Address;
		DWORD Attribute;
	}Attr;
}TYPE_ADDRESS_ATTR;
typedef struct _WATCH_DATA
{
	TYPE_NAME_ATTR Name;
	TYPE_VALUE_ATTR Value;
	TYPE_TYPE_ATTR Type;
	TYPE_ADDRESS_ATTR Address;
}WATCH_DATA,*PWATCH_DATA;
class CTypeViewerWnd:public CWispList
{
	enum CHILD_CMD_ID;
public:
	CTypeViewerWnd();
	~CTypeViewerWnd();
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnKeyEvent);
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnDestroy);
	DECLARE_WISP_MSG_EVENT_MAP
	DECLARE_WISP_MSG_CMD_MAP
	DECLARE_WISP_MSG_EVENT(OnHexDisplayEvent)
	DECLARE_WISP_MSG_EVENT(OnDeleteWatchEvent)
	DECLARE_WISP_MSG_EVENT(OnEventShowData)
	DECLARE_WISP_MSG_CMD(OnViewerCmd)
	bool BeginEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	bool ChangeValueBoolAndBitField1(DWORD Address,CSDSModule* pSDSModule,DWORD DataIndex,WCHAR* ValueBuf);
	void ItemChangedNotify(HANDLE hItem,int Col,CWispString&String);
	void ItemExpandedNotify(HANDLE hItem);
	bool EndEditItemNotify(HANDLE hItem,int Col,CWispString&String);
	void WatchType(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem=NULL,char* DataMemberName=NULL);
	
	void AddUdtTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem=NULL,char* DataMemberName=NULL,bool bIsData=false);
	void AddBaseClassTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem=NULL,char* DataMemberName=NULL,bool bIsData=false);
	
	void AddEnumerationTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem=NULL,char* DataMemberName=NULL,bool bIsData=false);
	void AddPointerTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName=NULL,bool bIsData=false);
	void AddArrayTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName=NULL,bool bIsData=false);
	void AddBasicTypeWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName=NULL,bool bIsData=false);
	void AddClassVFPTRWatch(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address,DWORD Attribute,HANDLE hItem,char* DataMemberName);

	void RemoveTypeAttachByAddress(DWORD Address);
	void ModifyTypeAttachAddress(CSDSModule* pSDSModule,DWORD TypeIndex,DWORD Address);
	bool ChangeValue(HANDLE hItem);
	bool GetBasicTypeValue(CSDSModule* pSDSModule,PSDTYPE_INFILE pType,DWORD Address,DWORD Attribute,WCHAR* ValueBuf,PVALUEUNION pValueUnion);

	void ExpandType(HANDLE hItem,bool bIsData=false);
	void ExpandPointerType(HANDLE hItem,bool bIsData);	
	void ExpandArrayType(HANDLE hItem,bool bIsData=false);
	void ExpandUDTType(HANDLE hItem,PWATCH_DATA pWatchData);
	void ExpendVirtualFunctionTable(HANDLE hItem,PWATCH_DATA pWatchData);
	//bool GetBasicTypeValue(CSDSModule* pSDSModule,PSDTYPE_INFILE pType,DWORD Address,PVALUEUNION pValueUnion);
	WCHAR* GetDataValue(IN DWORD Address,IN CSDSModule* pSDSModule,IN DWORD DataIndex,IN DWORD Attribute,OUT WCHAR* ValueBuf,IN DWORD BufLen,PVALUEUNION pDefValue=NULL);
	WCHAR* GetTypeValue(IN DWORD Address,IN CSDSModule* pSDSModule,IN DWORD TypeIndex,IN DWORD Attribute,OUT WCHAR* ValueBuf,IN DWORD BufLen,PVALUEUNION pDefValue=NULL);
	bool ModifyDataValue(DWORD Address,CSDSModule* pSDSModule,DWORD TypeIndex,VALUEUNION ValueUnion);
	bool ChangeUDTBaseClassAddressByUDT(HANDLE hItem,DWORD BaseAddress);
	bool GetRegisterValue(DWORD RegisterIndex,DWORD* RegisterValue);
	PSDTYPE_INFILE GetTypeByDataIndex(CSDSModule* pSDSModule,DWORD DataIndex);
	void ExpandReferenceType(HANDLE hItem);
	void ResetContext();
	void UpdateContext();
	bool UpdateItemContext(HANDLE hItem,WCHAR* ValueBuf,DWORD ValueBufLen,DWORD Address=0);
	bool UpdateItemContextUDT(HANDLE hItem,WCHAR* ValueBuf,DWORD ValueBufLen,DWORD BaseAddress=0);
	bool UpdateItemContextUDTPointer(HANDLE hItem,WCHAR* ValueBuf,DWORD ValueBufLen,DWORD BaseAddress=0);
	bool UpdateItemContextUDTReference(HANDLE hItem,WCHAR* ValueBuf,DWORD ValueBufLen,DWORD BaseAddress=0);
	void AddWatchByName(char* Name,HANDLE hItem=NULL);
	void AddWatchByName(WCHAR* Name,HANDLE hItem=NULL);

	bool GetItemDataAll(HANDLE hItem,PWATCH_DATA pWatchData);
	bool GetItemDataAll(HANDLE hItem,TYPE_NAME_ATTR* pNameAttr,TYPE_VALUE_ATTR* pValueAttr,TYPE_TYPE_ATTR* pTypeAttr,TYPE_ADDRESS_ATTR* pAddressAttr);
	bool GetThisAddressByMemberFunction(CSDSModule* pSdsModule,PSDFUNCTIONITEM pFunItem,DWORD* ThisPointer);
	
	bool GetFunctionAddressByName(const char* VariableName,DWORD* VariableAddress,PSDFUNCTIONITEM* DataItem,CSDSModule** SDSModule);
	bool GetVariableAddressByName(const char* VariableName,DWORD* VariableAddress,PSDUDTDATAITEM* DataItem,CSDSModule** SDSModule);
	bool UpdateItemValue(HANDLE hItem);
	bool UpdateItemValueForUDTType(HANDLE hItem,PSDTYPE_INFILE pType,CSDSModule* pSdsModule);
	void InsertLastItem();
	void UnloadSDSModule(CSDSModule*pSDSModule);

	void InsertExpandItem(HANDLE hItem);
	bool ChangeUDTBaseClassAddress(HANDLE hItem,DWORD TypeIndex,DWORD Address);
	bool ChangeUDTBaseClassAddressPointer(HANDLE hItem,DWORD BaseAddress);
	bool UpdateItemContextArray(HANDLE hItem,WCHAR* ValueBuf,DWORD ValueBufLen,DWORD BaseAddress);
	CSDSModule*m_pSDSModule;
	CWispMenu m_PopupMenu;
	HANDLE	m_hRemoveItem;
	HANDLE m_hLastItem;
};	
#endif //_TYPEVIEWERWND_H_