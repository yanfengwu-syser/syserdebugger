#ifndef _VISTA_VIDEO_HOOK_H_
#define _VISTA_VIDEO_HOOK_H_

typedef struct _DXGK_SEGMENTBANKPREFERENCE {
	union {
		struct {
			UINT  Bank0: 7;
			UINT  Direction0: 1;
			UINT  Bank1: 7;
			UINT  Direction1: 1;
			UINT  Bank2: 7;
			UINT  Direction2: 1;
			UINT  Bank3: 7;
			UINT  Direction3: 1;
		};
		UINT  Value;
	};
} DXGK_SEGMENTBANKPREFERENCE;

typedef struct _DXGK_SEGMENTPREFERENCE {
	union {
		struct {
			UINT  SegmentId0: 5;
			UINT  Direction0: 1;
			UINT  SegmentId1: 5;
			UINT  Direction1: 1;
			UINT  SegmentId2: 5;
			UINT  Direction2: 1;
			UINT  SegmentId3: 5;
			UINT  Direction3: 1;
			UINT  SegmentId4: 5;
			UINT  Direction4: 1;
			UINT  Reserved: 2;
		};
		UINT Value;
	};
} DXGK_SEGMENTPREFERENCE;


typedef enum _D3DDDIFORMAT
{
	D3DDDIFMT_UNKNOWN           =  0,
	D3DDDIFMT_R8G8B8            = 20,
	D3DDDIFMT_A8R8G8B8          = 21,
	D3DDDIFMT_X8R8G8B8          = 22,
	D3DDDIFMT_R5G6B5            = 23,
	D3DDDIFMT_X1R5G5B5          = 24,
	D3DDDIFMT_A1R5G5B5          = 25,
	D3DDDIFMT_A4R4G4B4          = 26,
	D3DDDIFMT_R3G3B2            = 27,
	D3DDDIFMT_A8                = 28,
	D3DDDIFMT_A8R3G3B2          = 29,
	D3DDDIFMT_X4R4G4B4          = 30,
	D3DDDIFMT_A2B10G10R10       = 31,
	D3DDDIFMT_A8B8G8R8          = 32,
	D3DDDIFMT_X8B8G8R8          = 33,
	D3DDDIFMT_G16R16            = 34,
	D3DDDIFMT_A2R10G10B10       = 35,
	D3DDDIFMT_A16B16G16R16      = 36,
	D3DDDIFMT_A8P8              = 40,
	D3DDDIFMT_P8                = 41,
	D3DDDIFMT_L8                = 50,
	D3DDDIFMT_A8L8              = 51,
	D3DDDIFMT_A4L4              = 52,
	D3DDDIFMT_V8U8              = 60,
	D3DDDIFMT_L6V5U5            = 61,
	D3DDDIFMT_X8L8V8U8          = 62,
	D3DDDIFMT_Q8W8V8U8          = 63,
	D3DDDIFMT_V16U16            = 64,
	D3DDDIFMT_W11V11U10         = 65, 
	D3DDDIFMT_A2W10V10U10       = 67,
	D3DDDIFMT_UYVY              = MAKEFOURCC('U', 'Y', 'V', 'Y'),
	D3DDDIFMT_R8G8_B8G8         = MAKEFOURCC('R', 'G', 'B', 'G'),
	D3DDDIFMT_YUY2              = MAKEFOURCC('Y', 'U', 'Y', '2'),
	D3DDDIFMT_G8R8_G8B8         = MAKEFOURCC('G', 'R', 'G', 'B'),
	D3DDDIFMT_DXT1              = MAKEFOURCC('D', 'X', 'T', '1'),
	D3DDDIFMT_DXT2              = MAKEFOURCC('D', 'X', 'T', '2'),
	D3DDDIFMT_DXT3              = MAKEFOURCC('D', 'X', 'T', '3'),
	D3DDDIFMT_DXT4              = MAKEFOURCC('D', 'X', 'T', '4'),
	D3DDDIFMT_DXT5              = MAKEFOURCC('D', 'X', 'T', '5'),
	D3DDDIFMT_D16_LOCKABLE      = 70,
	D3DDDIFMT_D32               = 71,
	D3DDDIFMT_D15S1             = 73,
	D3DDDIFMT_D24S8             = 75,
	D3DDDIFMT_D24X8             = 77,
	D3DDDIFMT_D24X4S4           = 79,
	D3DDDIFMT_D16               = 80,
	D3DDDIFMT_D32F_LOCKABLE     = 82,
	D3DDDIFMT_D24FS8            = 83,
	D3DDDIFMT_D32_LOCKABLE      = 84,
	D3DDDIFMT_S8_LOCKABLE       = 85,
	D3DDDIFMT_S1D15             = 72,
	D3DDDIFMT_S8D24             = 74,
	D3DDDIFMT_X8D24             = 76,
	D3DDDIFMT_X4S4D24           = 78,
	D3DDDIFMT_L16               = 81,
	D3DDDIFMT_VERTEXDATA        =100,
	D3DDDIFMT_INDEX16           =101,
	D3DDDIFMT_INDEX32           =102,
	D3DDDIFMT_Q16W16V16U16      =110,
	D3DDDIFMT_MULTI2_ARGB8      = MAKEFOURCC('M','E','T','1'),
	D3DDDIFMT_R16F              = 111,
	D3DDDIFMT_G16R16F           = 112,
	D3DDDIFMT_A16B16G16R16F     = 113,
	D3DDDIFMT_R32F              = 114,
	D3DDDIFMT_G32R32F           = 115,
	D3DDDIFMT_A32B32G32R32F     = 116,
	D3DDDIFMT_CxV8U8            = 117,
	D3DDDIFMT_A1                = 118,
	D3DDDIFMT_DXVACOMPBUFFER_BASE = 150,
	D3DDDIFMT_PICTUREPARAMSDATA = D3DDDIFMT_DXVACOMPBUFFER_BASE+0,
	D3DDDIFMT_MACROBLOCKDATA    = D3DDDIFMT_DXVACOMPBUFFER_BASE+1,
	D3DDDIFMT_RESIDUALDIFFERENCEDATA = D3DDDIFMT_DXVACOMPBUFFER_BASE+2,
	D3DDDIFMT_DEBLOCKINGDATA    = D3DDDIFMT_DXVACOMPBUFFER_BASE+3,
	D3DDDIFMT_INVERSEQUANTIZATIONDATA = D3DDDIFMT_DXVACOMPBUFFER_BASE+4,
	D3DDDIFMT_SLICECONTROLDATA  = D3DDDIFMT_DXVACOMPBUFFER_BASE+5,
	D3DDDIFMT_BITSTREAMDATA     = D3DDDIFMT_DXVACOMPBUFFER_BASE+6,
	D3DDDIFMT_MOTIONVECTORBUFFER    = D3DDDIFMT_DXVACOMPBUFFER_BASE+7,
	D3DDDIFMT_FILMGRAINBUFFER    = D3DDDIFMT_DXVACOMPBUFFER_BASE+8,
	D3DDDIFMT_DXVA_RESERVED9    = D3DDDIFMT_DXVACOMPBUFFER_BASE+9,
	D3DDDIFMT_DXVA_RESERVED10   = D3DDDIFMT_DXVACOMPBUFFER_BASE+10,
	D3DDDIFMT_DXVA_RESERVED11   = D3DDDIFMT_DXVACOMPBUFFER_BASE+11,
	D3DDDIFMT_DXVA_RESERVED12   = D3DDDIFMT_DXVACOMPBUFFER_BASE+12,
	D3DDDIFMT_DXVA_RESERVED13   = D3DDDIFMT_DXVACOMPBUFFER_BASE+13,
	D3DDDIFMT_DXVA_RESERVED14   = D3DDDIFMT_DXVACOMPBUFFER_BASE+14,
	D3DDDIFMT_DXVA_RESERVED15   = D3DDDIFMT_DXVACOMPBUFFER_BASE+15,
	D3DDDIFMT_DXVA_RESERVED16   = D3DDDIFMT_DXVACOMPBUFFER_BASE+16,
	D3DDDIFMT_DXVA_RESERVED17   = D3DDDIFMT_DXVACOMPBUFFER_BASE+17,
	D3DDDIFMT_DXVA_RESERVED18   = D3DDDIFMT_DXVACOMPBUFFER_BASE+18,
	D3DDDIFMT_DXVA_RESERVED19   = D3DDDIFMT_DXVACOMPBUFFER_BASE+19,
	D3DDDIFMT_DXVA_RESERVED20   = D3DDDIFMT_DXVACOMPBUFFER_BASE+20,
	D3DDDIFMT_DXVA_RESERVED21   = D3DDDIFMT_DXVACOMPBUFFER_BASE+21,
	D3DDDIFMT_DXVA_RESERVED22   = D3DDDIFMT_DXVACOMPBUFFER_BASE+22,
	D3DDDIFMT_DXVA_RESERVED23   = D3DDDIFMT_DXVACOMPBUFFER_BASE+23,
	D3DDDIFMT_DXVA_RESERVED24   = D3DDDIFMT_DXVACOMPBUFFER_BASE+24,
	D3DDDIFMT_DXVA_RESERVED25   = D3DDDIFMT_DXVACOMPBUFFER_BASE+25,
	D3DDDIFMT_DXVA_RESERVED26   = D3DDDIFMT_DXVACOMPBUFFER_BASE+26,
	D3DDDIFMT_DXVA_RESERVED27   = D3DDDIFMT_DXVACOMPBUFFER_BASE+27,
	D3DDDIFMT_DXVA_RESERVED28   = D3DDDIFMT_DXVACOMPBUFFER_BASE+28,
	D3DDDIFMT_DXVA_RESERVED29   = D3DDDIFMT_DXVACOMPBUFFER_BASE+29,
	D3DDDIFMT_DXVA_RESERVED30   = D3DDDIFMT_DXVACOMPBUFFER_BASE+30,
	D3DDDIFMT_DXVA_RESERVED31   = D3DDDIFMT_DXVACOMPBUFFER_BASE+31,
	D3DDDIFMT_DXVACOMPBUFFER_MAX = D3DDDIFMT_DXVA_RESERVED31,
	D3DDDIFMT_BINARYBUFFER      = 199,
	D3DDDIFMT_FORCE_UINT        =0x7fffffff
} D3DDDIFORMAT;

typedef struct _D3DDDI_RATIONAL
{
	UINT  Numerator;
	UINT  Denominator;
} D3DDDI_RATIONAL;

#define D3DDDI_MAX_BROADCAST_CONTEXT        64

typedef UINT  D3DDDI_VIDEO_PRESENT_SOURCE_ID;

typedef struct _DXGK_SETVIDPNSOURCEADDRESS_FLAGS
{
	union
	{
		struct
		{

			UINT ModeChange      : 1;    // 0x00000001
			UINT FlipImmediate   : 1;    // 0x00000002
			UINT FlipOnNextVSync : 1;    // 0x00000004
			UINT Reserved        :29;    // 0xFFFFFFF8
		};
		UINT Value;
	};
} DXGK_SETVIDPNSOURCEADDRESS_FLAGS;

typedef struct _DXGKARG_SETVIDPNSOURCEADDRESS
{
	D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
	UINT  PrimarySegment;
	PHYSICAL_ADDRESS  PrimaryAddress;
	HANDLE  hAllocation;
	UINT	ContextCount;
	HANDLE	Context[1+D3DDDI_MAX_BROADCAST_CONTEXT];
	DXGK_SETVIDPNSOURCEADDRESS_FLAGS Flags;
}DXGKARG_SETVIDPNSOURCEADDRESS;

typedef NTSTATUS (APIENTRY*PFN_DXGKDDI_SETVIDPNSOURCEADDRESS)(CONST HANDLE  hAdapter,CONST DXGKARG_SETVIDPNSOURCEADDRESS*pSetVidPnSourceAddress);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _DXGKARG_SETVIDPNSOURCEVISIBILITY
{
	D3DDDI_VIDEO_PRESENT_SOURCE_ID  VidPnSourceId;
	BOOLEAN                         Visible;
} DXGKARG_SETVIDPNSOURCEVISIBILITY;

typedef NTSTATUS (APIENTRY*PFN_DXGKDDI_SETVIDPNSOURCEVISIBILITY)(CONST HANDLE hAdapter,CONST DXGKARG_SETVIDPNSOURCEVISIBILITY*pSetVidPnSourceVisibility);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _DXGK_ALLOCATIONINFOFLAGS {
	union {
		struct {
			UINT  CpuVisible: 1;
			UINT  PermanentSysMem: 1;
			UINT  Cached: 1;
			UINT  Protected: 1;
			UINT  ExistingSysMem: 1;
			UINT  ExistingKernelSysMem: 1;
			UINT  FromEndOfSegment: 1;
			UINT  Swizzled: 1;
			UINT  Overlay: 1;
			UINT  Capture: 1;
			UINT  UseAlternateVA: 1;
			UINT  SynchronousPaging: 1;
			UINT  LinkMirrored: 1;
			UINT  LinkInstanced: 1;
			UINT  Reserved: 14;
		};
		UINT  Value;
	};
} DXGK_ALLOCATIONINFOFLAGS;

typedef struct _DXGK_ALLOCATIONUSAGEINFO1 {
	union {
		struct {
			UINT  PrivateFormat: 1;
			UINT  Swizzled: 1;
			UINT  MipMap: 1;
			UINT  Cube: 1;
			UINT  Volume: 1;
			UINT  Vertex: 1;
			UINT  Index: 1;
			UINT  Reserved: 25;
		};
		UINT  Value;
	} Flags;
	union {
		D3DDDIFORMAT  Format;
		UINT  PrivateFormat;
	};
	UINT  SwizzledFormat;
	UINT  ByteOffset;
	UINT  Width;
	UINT  Height;
	UINT  Pitch;
	UINT  Depth;
	UINT  SlicePitch;
} DXGK_ALLOCATIONUSAGEINFO1;

typedef struct _DXGK_ALLOCATIONUSAGEHINT {
	UINT  Version;
	DXGK_ALLOCATIONUSAGEINFO1  v1;
} DXGK_ALLOCATIONUSAGEHINT;

typedef struct _DXGK_ALLOCATIONINFO {
	VOID*  pPrivateDriverData;
	UINT  PrivateDriverDataSize;
	UINT  Alignment;
	SIZE_T  Size;
	SIZE_T  PitchAlignedSize;
	DXGK_SEGMENTBANKPREFERENCE  HintedBank;
	DXGK_SEGMENTPREFERENCE  PreferredSegment;
	UINT  SupportedReadSegmentSet;
	UINT  SupportedWriteSegmentSet;
	UINT  EvictionSegmentSet; 
	UINT  MaximumRenamingListLength;
	HANDLE  hAllocation;
	DXGK_ALLOCATIONINFOFLAGS  Flags;
	DXGK_ALLOCATIONUSAGEHINT*  pAllocationUsageHint;
	UINT  AllocationPriority;
} DXGK_ALLOCATIONINFO;



typedef struct _DXGK_CREATEALLOCATIONFLAGS {
	union {
		struct {
			UINT  Resource: 1;
			UINT  Reserved: 31;
		};
		UINT  Value;
	};
} DXGK_CREATEALLOCATIONFLAGS;

typedef struct _DXGKARG_CREATEALLOCATION {
	CONST VOID*  pPrivateDriverData;
	UINT  PrivateDriverDataSize;
	UINT  NumAllocations;
	DXGK_ALLOCATIONINFO*  pAllocationInfo;
	HANDLE  hResource;
	DXGK_CREATEALLOCATIONFLAGS  Flags;
} DXGKARG_CREATEALLOCATION;


typedef NTSTATUS (APIENTRY*PFN_DXGKDDI_CREATEALLOCATION)(CONST HANDLE  hAdapter,DXGKARG_CREATEALLOCATION*pCreateAllocation);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _DXGK_DESTROYALLOCATIONFLAGS
{
	union
	{
		struct
		{
			UINT    DestroyResource : 1;    // 0x00000001
			UINT    Reserved        :31;    // 0xFFFFFFFE
		};
		UINT        Value;
	};
} DXGK_DESTROYALLOCATIONFLAGS;

typedef struct _DXGKARG_DESTROYALLOCATION
{
	UINT            NumAllocations;
	CONST HANDLE*   pAllocationList;
	HANDLE          hResource;
	DXGK_DESTROYALLOCATIONFLAGS Flags;
} DXGKARG_DESTROYALLOCATION;


typedef NTSTATUS (APIENTRY*PFN_DXGKDDI_DESTROYALLOCATION)(CONST HANDLE hAdapter,CONST DXGKARG_DESTROYALLOCATION*pDestroyAllocation);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum D3DDDI_FLIPINTERVAL_TYPE
{
	D3DDDI_FLIPINTERVAL_IMMEDIATE = 0,
	D3DDDI_FLIPINTERVAL_ONE       = 1,
	D3DDDI_FLIPINTERVAL_TWO       = 2,
	D3DDDI_FLIPINTERVAL_THREE     = 3,
	D3DDDI_FLIPINTERVAL_FOUR      = 4,
} D3DDDI_FLIPINTERVAL_TYPE;

#define DXGK_PRESENT_SOURCE_INDEX       1
#define DXGK_PRESENT_DESTINATION_INDEX  2
#define DXGK_PRESENT_MAX_INDEX          DXGK_PRESENT_DESTINATION_INDEX

typedef struct _DXGK_PRESENTFLAGS
{
	union
	{
		struct
		{
			UINT    Blt             : 1;    // 0x00000001
			UINT    ColorFill       : 1;    // 0x00000002
			UINT    Flip            : 1;    // 0x00000004
			UINT    FlipWithNoWait  : 1;    // 0x00000008
			UINT    SrcColorKey     : 1;    // 0x00000010
			UINT    DstColorKey     : 1;    // 0x00000020
			UINT    LinearToSrgb    : 1;    // 0x00000040
			UINT    Rotate          : 1;    // 0x00000080
			UINT    Reserved        :24;    // 0xFFFFFF00
		};
		UINT Value;
	};
} DXGK_PRESENTFLAGS;

typedef struct _D3DDDI_PATCHLOCATIONLIST
{
	UINT                AllocationIndex;
	union
	{
		struct
		{
			UINT            SlotId          : 24;   // 0x00FFFFFF
			UINT            Reserved        : 8;    // 0xFF000000
		};
		UINT                Value;
	};
	UINT                DriverId;
	UINT                AllocationOffset;
	UINT                PatchOffset;
	UINT                SplitOffset;
} D3DDDI_PATCHLOCATIONLIST;

typedef struct _DXGK_ALLOCATIONLIST
{
	HANDLE              hDeviceSpecificAllocation;
	struct
	{
		UINT            WriteOperation  : 1;    // 0x00000001
		UINT            SegmentId       : 5;    // 0x0000002E
		UINT            Reserved        : 26;   // 0xFFFFFFC0
	};
	PHYSICAL_ADDRESS    PhysicalAddress;
} DXGK_ALLOCATIONLIST;


typedef struct _DXGKARG_PRESENT
{
	VOID*                       pDmaBuffer;
	UINT                        DmaSize;
	VOID*                       pDmaBufferPrivateData;
	UINT                        DmaBufferPrivateDataSize;
	DXGK_ALLOCATIONLIST*        pAllocationList;
	D3DDDI_PATCHLOCATIONLIST*   pPatchLocationListOut;
	UINT                        PatchLocationListOutSize;
	UINT                        MultipassOffset;
	UINT                        Color;
	RECT                        DstRect;
	RECT                        SrcRect;
	UINT                        SubRectCnt;
	CONST RECT*                 pDstSubRects;
	D3DDDI_FLIPINTERVAL_TYPE    FlipInterval;
	DXGK_PRESENTFLAGS           Flags;
	UINT                        DmaBufferSegmentId;
	PHYSICAL_ADDRESS            DmaBufferPhysicalAddress;    
} DXGKARG_PRESENT;

typedef NTSTATUS (APIENTRY*PFN_DXGKDDI_PRESENT)(CONST HANDLE hContext,DXGKARG_PRESENT* pPresent);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Vista Video Miniport Driver Initialization Data
typedef struct _DRIVER_INITIALIZATION_DATA
{
	ULONG		Version;
	void*		DxgkDdiAddDevice;
	void*		DxgkDdiStartDevice;
	void*		DxgkDdiStopDevice;
	void*		DxgkDdiRemoveDevice;
	void*		DxgkDdiDispatchIoRequest;
	void*		DxgkDdiInterruptRoutine;
	void*		DxgkDdiDpcRoutine;
	void*		DxgkDdiQueryChildRelations;
	void*		DxgkDdiQueryChildStatus;
	void*		DxgkDdiQueryDeviceDescriptor;
	void*		DxgkDdiSetPowerState;
	void*		DxgkDdiNotifyAcpiEvent;
	void*		DxgkDdiResetDevice;
	void*		DxgkDdiUnload;
	void*		DxgkDdiQueryInterface;
	void*		DxgkDdiControlEtwLogging;
	void*		DxgkDdiQueryAdapterInfo;
	void*		DxgkDdiCreateDevice;
	void*		DxgkDdiCreateAllocation;
	void*		DxgkDdiDestroyAllocation;
	void*		DxgkDdiDescribeAllocation;
	void*		DxgkDdiGetStandardAllocationDriverData;
	void*		DxgkDdiAcquireSwizzlingRange;
	void*		DxgkDdiReleaseSwizzlingRange;
	void*		DxgkDdiPatch;
	void*		DxgkDdiSubmitCommand;
	void*		DxgkDdiPreemptCommand;
	void*		DxgkDdiBuildPagingBuffer;
	void*		DxgkDdiSetPalette;
	void*		DxgkDdiSetPointerPosition;
	void*		DxgkDdiSetPointerShape;
	void*		DxgkDdiResetFromTimeout;
	void*		DxgkDdiRestartFromTimeout;
	void*		DxgkDdiEscape;
	void*		DxgkDdiCollectDbgInfo;
	void*		DxgkDdiQueryCurrentFence;
	void*		DxgkDdiIsSupportedVidPn;
	void*       DxgkDdiRecommendFunctionalVidPn;
	void*		DxgkDdiEnumVidPnCofuncModality;
	void*		DxgkDdiSetVidPnSourceAddress;
	void*		DxgkDdiSetVidPnSourceVisibility;
	void*		DxgkDdiCommitVidPn;
	void*		DxgkDdiUpdateActiveVidPnPresentPath;
	void*		DxgkDdiRecommendMonitorModes;
	void*		DxgkDdiRecommendVidPnTopology;
	void*		DxgkDdiGetScanLine;
	void*		DxgkDdiStopCapture;
	void*		DxgkDdiControlInterrupt;
	void*		DxgkDdiCreateOverlay;
	//
	// Device functions
	//
	void*		DxgkDdiDestroyDevice;
	void*		DxgkDdiOpenAllocation;
	void*		DxgkDdiCloseAllocation;
	void*		DxgkDdiRender;
	void*		DxgkDdiPresent;
	//
	// Overlay functions
	//
	void*		DxgkDdiUpdateOverlay;
	void*		DxgkDdiFlipOverlay;
	void*		DxgkDdiDestroyOverlay;
	//
	// Context supports.
	//
	void*		DxgkDdiCreateContext;
	void*		DxgkDdiDestroyContext;
	//
	// Linked Display Adapter support.
	//
	void*		DxgkDdiLinkDevice;
	void*		DxgkDdiSetDisplayPrivateDriverFormat;
}DRIVER_INITIALIZATION_DATA, *PDRIVER_INITIALIZATION_DATA;


NTSTATUS NewDxgkInitialize(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath,IN PDRIVER_INITIALIZATION_DATA DriverInitializationData);
typedef NTSTATUS (*PFN_DxgkInitialize)(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath,IN PDRIVER_INITIALIZATION_DATA DriverInitializationData);
extern PFN_DxgkInitialize	OldDxgkInitialize;

#endif
