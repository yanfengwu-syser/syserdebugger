;	/*
;		兼容VMWARE等虚拟机相关的
;		
;		十二羽翼
;		QQ:764439262
;	*/

VMVWARE_CALL	STRUCT
	Return_Status	dd	?
	Exist_flag		dd	?
	Func_num		dd	?
	Port			dd	?
	Trans_Src		dd	?
	Trans_Dest		dd	?
VMVWARE_CALL	ENDS