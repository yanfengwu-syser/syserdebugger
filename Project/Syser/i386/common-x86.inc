;	/*
;		公共功能封装
;		
;		十二羽翼
;		QQ:764439262
;	*/

;
;	需要跟InputDriver.h中的struct _KeyInterruptVariable同步
;

KEYINTERRUPTVARIABLE	STRUCT
	 IsActive        db	?
	 IsInsideActive  db	?
	                 db	?	
	                 db	?	
	 dwFuncKeyState  dd	?
	 dwOldKeyboardInterrupt dd	?
	 nCurrentKeyBufferIndex dd	?
	 timer           dd          ?           
	 dwOldTimerInterrupt dd		?
	 keyboard        dd          ?          
	 mouse           dd          ?          
	 wSystemDataSegment dw		?
	 wDSRegister     dw			?
	 chFuncKeyScanCode db			?
	 chSecondKeyScanCode db		?
	 IsSaveInterruptInformation db	?
	 Interrupt8259Shield_1 db		?
	 Interrupt8259Shield_2 db		?
	 chAltKeyState   db			?
	 chAltKeyScanCode db			?
	 chCurrentScanCode db			?
	 dwIOAPICLineAddress dd		?
	 dwIOAPICPhysAddress dd		?
	 dwLocalAPICPhysAddress dd	?
	 dwLocalAPICLineAddress dd	?
	 bIsUseAPIC      db			?
	                 db			?	
	                 db			?	
	                 db			?	
	 dwOldMouseInterrupt dd		?
	 bMouseResponseState db		?
	                 db			?	
	                 db			?	
	                 db			?	
	 dwMouseDataIndex dd		?
	 chCurrentMouseData db		?
	                 db			?	
	                 db			?	
	                 db			?	
	 dwLocalAPICTaskPriority dd	?
	 chPrveScanCode  db			?
	 chKeyBuffer     db 512 dup(?)
	                 db			?	
	                 db			?	
	                 db			?	
KEYINTERRUPTVARIABLE	ENDS

X86SAVEREGS	STRUCT
	SaveEdi	dd	?
	SaveEsi	dd	?
	SaveEbp	dd	?
	SaveEsp	dd	?
	SaveEbx	dd	?
	SaveEdx	dd	?
	SaveEcx	dd	?
	SaveEax	dd	?
X86SAVEREGS	ENDS

EAX_IDX		EQU 0
ECX_IDX		EQU 1
EDX_IDX		EQU 2
EBX_IDX		EQU 3
ESP_IDX		EQU 4
EBP_IDX		EQU 5
ESI_IDX		EQU 6
EDI_IDX		EQU 7
GENE_IDX_MAX 	EQU 8

ES_IDX		EQU 0
CS_IDX		EQU 1
SS_IDX		EQU 2
DS_IDX		EQU 3
FS_IDX		EQU 4
GS_IDX		EQU 5
SEG_IDX_MAX EQU 6


X86REGCONTEXT	STRUCT
	GeneReg	dd GENE_IDX_MAX dup(?)
	CR		dd 5 dup(?)
	DR		dd 8 dup(?)
	EIP		dd ?
	EFlags	dd ?
	SegReg	dw SEG_IDX_MAX dup(?)
	TR		dw ?
	LDT		dw ?
	Reserved1	dw ?
	GDTLimit	dw ?
	GDTBase	dd	?
	Reserved2	dw ?
	IDTLimit	dw ?
	IDTBase	dd	?
	ExceptionEIP	dd	?				;发生异常时的EIP，   只用在异常中才用
	ExceptionInterruptNumber	dd	?	;异常的中断号例如 0e 缺页中断, 0d 通用异常
	ExceptionInterruptErrorCode	dd	?	;异常的错误代码
	LocalAPIC	dd	?
	FPUStatusWord	dw	?
	FPUControlWord	dw	?
	FPUTagWord		dw	?
	Reserved3		dw	?
X86REGCONTEXT	ENDS

;
;	struct _RETURN_CONTEXT
;

RETURNCONTEXT	STRUCT
	rEIP		dd ?
	rCS			dd ?
	rEflags		dd ?
	r3ESP		dd ?
	r3SS		dd ?
	rV86ES		dd ?
	rV86DS		dd ?
	rV86FS		dd ?
	rV86GS		dd ?
RETURNCONTEXT	ENDS

;
;	APIC
;

IOAPIC_DEFAULT_PHYSICAL_BASE				EQU		0FEC00000h
MSR_INDEX_IA32_APIC_BASE					EQU		01Bh
MSR_APIC_GLOBAL_ENABLE_BIT_MASK				EQU		0800h
MSR_APIC_BASE_ADDRESS_BIT_MASK				EQU		0FFFFF000h
CPUID_1_EDX_FEATURE_APIC_ON_CHIP_BIT_MASK	EQU		0200h

LOCALAPICINFO	STRUCT
	APIC_ID         dd ?
	APICVersion     dd ?
	TaskPriority    dd ?
	ArbitrationPriority dd ?
	ProcessorPriority dd ?
	EOI             dd ?
	LogicalDestination dd ?
	DestinationFormat dd ?
	SpuriousInterruptVector dd ?
	                 db ? ; undefined
	                 db ? ; undefined
	                 db ? ; undefined
	                 db ? ; undefined
	InService       dd 8 dup(?)
	TriggerMode     dd 8 dup(?)
	InterruptRequest dd 8 dup(?)
	ErrorStatus     dd ?
	InterruptCommandLow dd ?
	InterruptCommandHigh dd ?
	LVTTimer        dd ?
	LVTThermalSensor dd ?
	LVTPerformanceMonitoringCounters dd ?
	LVTLINT0        dd ?
	LVTLINT1        dd ?
	LVTError        dd ?
	InitialCount    dd ?
	CurrentCount    dd ?
	DivideConfiguration dd ?
LOCALAPICINFO	ENDS