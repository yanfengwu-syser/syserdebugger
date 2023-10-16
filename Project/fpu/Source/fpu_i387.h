/*---------------------------------------------------------------------------+
 |  status_w.h                                                               |
 |  $Id: status_w.h,v 1.3 2001/10/06 03:53:46 bdenney Exp $
 |                                                                           |
 | Copyright (C) 1992,1993                                                   |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@vaxc.cc.monash.edu.au    |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#ifndef _FPU_I387_H_
#define _FPU_I387_H_

struct BX_FCPU_I387
{
	class BX_CPU_C *fpu_cpu_ptr_;
	class bxInstruction_c *fpu_iptr_;
	union FpuMmxRegisters *current_i387_;
};

#if 0

#define current_i387_definefunyuan_void void
#define current_i387_definefunyuan_
#define current_i387_yuan_
#define current_i387_yuan_clono
#define current_i387_yuan_void
#define current_i387_yuan_doc
#define current_i387_yuan_le
#define current_i387_yuan_cc

#else

#define current_i387_definefunyuan_void struct BX_FCPU_I387 *bx_fcpu_i387
#define current_i387_definefunyuan_ struct BX_FCPU_I387 *bx_fcpu_i387,
#define current_i387_yuan_ bx_fcpu_i387,
#define current_i387_yuan_clono bx_fcpu_i387
#define current_i387_yuan_void bx_fcpu_i387
#define current_i387_yuan_doc bx_fcpu_i387
#define current_i387_yuan_le bx_fcpu_i387
#define current_i387_yuan_cc bx_fcpu_i387

#endif

//WIN32,NDEBUG,_MBCS,_LIB,PARANOID,DEBUGGING,NO_ASSEMBLER,USE_WITH_CPU_SIM
//WIN32,_DEBUG,_MBCS,_LIB,NDEBUG,_WINDOWS,PARANOID,DEBUGGING,NO_ASSEMBLER,USE_WITH_CPU_SIM

#define PARANOID
#define DEBUGGING
#define NO_ASSEMBLER
#define USE_WITH_CPU_SIM

#include <stdlib.h>
#include <stdio.h>



















#endif /* _FPU_I387_H_ */
