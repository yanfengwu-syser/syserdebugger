/////////////////////////////////////////////////////////////////////////
// $Id: fetchdecode.cc,v 1.7 2001/10/03 13:10:37 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

///////////////////////////
// prefix bytes
// opcode bytes
// modrm/sib
// address displacement
// immediate constant
///////////////////////////

// sign extended to osize:
//   6a push ib
//   6b imul gvevib
//   70..7f jo..jnle
//   83 G1 0..7 ADD..CMP EvIb

// is 6b imul_gvevib sign extended?  don't think
//   I'm sign extending it properly in old decode/execute

//check all the groups.  Make sure to add duplicates rather
// than error.

// mark instructions as changing control transfer, then
// don't always load from fetch_ptr, etc.

// cant use immediate as another because of Group3 where
// some have immediate and some don't, and those won't
// be picked up by logic until indirection.

// get attr and execute ptr at same time

// maybe move 16bit only i's like  MOV_EwSw, MOV_SwEw
// to 32 bit modules.

// use 0F as a prefix too?

void BxResolveError(bxInstruction_c *);

#if BX_DYNAMIC_TRANSLATION
// For 16-bit address mode, this matrix describes the registers
// used to formulate the offset, indexed by the RM field.
// This info is needed by the dynamic translation code for dataflow.
static unsigned BxMemRegsUsed16[8] =
{
	(1<<3) | (1<<6), // BX + SI
	(1<<3) | (1<<7), // BX + DI
	(1<<5) | (1<<6), // BP + SI
	(1<<5) | (1<<7), // BP + DI
	(1<<6),          // SI
	(1<<7),          // DI
	(1<<5),          // BP
	(1<<3)           // BX
};

#endif

static BxExecutePtr_t BxResolve16Mod0[8] =
{
	&BX_CPU_C::Resolve16Mod0Rm0,
	&BX_CPU_C::Resolve16Mod0Rm1,
	&BX_CPU_C::Resolve16Mod0Rm2,
	&BX_CPU_C::Resolve16Mod0Rm3,
	&BX_CPU_C::Resolve16Mod0Rm4,
	&BX_CPU_C::Resolve16Mod0Rm5,
	&BX_CPU_C::Resolve16Mod0Rm6, // d16, no registers used
	&BX_CPU_C::Resolve16Mod0Rm7
};

static BxExecutePtr_t BxResolve16Mod1or2[8] =
{
	&BX_CPU_C::Resolve16Mod1or2Rm0,
	&BX_CPU_C::Resolve16Mod1or2Rm1,
	&BX_CPU_C::Resolve16Mod1or2Rm2,
	&BX_CPU_C::Resolve16Mod1or2Rm3,
	&BX_CPU_C::Resolve16Mod1or2Rm4,
	&BX_CPU_C::Resolve16Mod1or2Rm5,
	&BX_CPU_C::Resolve16Mod1or2Rm6,
	&BX_CPU_C::Resolve16Mod1or2Rm7
};

static BxExecutePtr_t BxResolve32Mod0[8] =
{
	&BX_CPU_C::Resolve32Mod0Rm0,
	&BX_CPU_C::Resolve32Mod0Rm1,
	&BX_CPU_C::Resolve32Mod0Rm2,
	&BX_CPU_C::Resolve32Mod0Rm3,
	&BX_CPU_C::Resolve32Mod0Rm4, // escape to 2-byte
	&BX_CPU_C::Resolve32Mod0Rm5, // d32, no registers used
	&BX_CPU_C::Resolve32Mod0Rm6,
	&BX_CPU_C::Resolve32Mod0Rm7
};

static BxExecutePtr_t BxResolve32Mod1or2[8] =
{
	&BX_CPU_C::Resolve32Mod1or2Rm0,
	&BX_CPU_C::Resolve32Mod1or2Rm1,
	&BX_CPU_C::Resolve32Mod1or2Rm2,
	&BX_CPU_C::Resolve32Mod1or2Rm3,
	&BX_CPU_C::Resolve32Mod1or2Rm4, // escape to 2-byte
	&BX_CPU_C::Resolve32Mod1or2Rm5,
	&BX_CPU_C::Resolve32Mod1or2Rm6,
	&BX_CPU_C::Resolve32Mod1or2Rm7
};

static BxExecutePtr_t BxResolve32Mod1or2EffectAddressBaseIndexScaled[0x100] =
{
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x00,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x01,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x02,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x03,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x04,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x05,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x06,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x07,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x08,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x09,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0a,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0b,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0c,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0d,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0e,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x0f,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x10,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x11,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x12,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x13,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x14,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x15,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x16,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x17,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x18,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x19,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1a,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1b,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1c,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1d,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1e,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x1f,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x20,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x21,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x22,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x23,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x24,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x25,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x26,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x27,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x28,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x29,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2a,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2b,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2c,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2d,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2e,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x2f,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x30,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x31,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x32,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x33,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x34,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x35,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x36,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x37,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x38,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x39,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3a,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3b,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3c,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3d,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3e,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x3f,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x40,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x41,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x42,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x43,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x44,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x45,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x46,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x47,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x48,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x49,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4a,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4b,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4c,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4d,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4e,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x4f,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x50,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x51,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x52,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x53,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x54,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x55,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x56,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x57,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x58,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x59,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5a,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5b,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5c,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5d,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5e,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x5f,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x60,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x61,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x62,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x63,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x64,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x65,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x66,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x67,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x68,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x69,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6a,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6b,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6c,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6d,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6e,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x6f,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x70,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x71,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x72,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x73,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x74,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x75,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x76,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x77,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x78,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x79,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7a,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7b,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7c,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7d,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7e,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x7f,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x80,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x81,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x82,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x83,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x84,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x85,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x86,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x87,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x88,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x89,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8a,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8b,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8c,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8d,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8e,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x8f,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x90,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x91,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x92,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x93,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x94,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x95,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x96,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x97,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x98,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x99,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9a,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9b,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9c,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9d,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9e,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0x9f,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa0,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa1,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa2,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa3,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa4,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa5,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa6,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa7,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa8,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xa9,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xaa,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xab,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xac,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xad,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xae,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xaf,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb0,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb1,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb2,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb3,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb4,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb5,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb6,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb7,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb8,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xb9,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xba,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xbb,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xbc,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xbd,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xbe,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xbf,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc0,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc1,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc2,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc3,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc4,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc5,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc6,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc7,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc8,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xc9,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xca,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xcb,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xcc,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xcd,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xce,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xcf,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd0,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd1,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd2,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd3,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd4,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd5,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd6,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd7,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd8,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xd9,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xda,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xdb,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xdc,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xdd,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xde,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xdf,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe0,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe1,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe2,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe3,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe4,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe5,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe6,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe7,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe8,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xe9,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xea,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xeb,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xec,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xed,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xee,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xef,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf0,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf1,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf2,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf3,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf4,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf5,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf6,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf7,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf8,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xf9,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xfa,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xfb,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xfc,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xfd,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xfe,
	&BX_CPU_C::Resolve32Mod1or2EffectAddress_sib0xff

};

static BxExecutePtr_t BxResolve32Mod0EffectAddressBaseIndexScaled[0x100] =
{
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x00,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x01,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x02,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x03,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x04,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x05,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x06,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x07,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x08,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x09,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0a,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0b,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0c,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0d,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0e,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x0f,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x10,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x11,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x12,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x13,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x14,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x15,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x16,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x17,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x18,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x19,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1a,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1b,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1c,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1d,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1e,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x1f,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x20,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x21,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x22,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x23,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x24,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x25,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x26,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x27,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x28,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x29,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2a,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2b,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2c,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2d,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2e,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x2f,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x30,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x31,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x32,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x33,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x34,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x35,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x36,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x37,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x38,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x39,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3a,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3b,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3c,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3d,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3e,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x3f,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x40,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x41,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x42,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x43,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x44,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x45,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x46,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x47,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x48,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x49,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4a,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4b,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4c,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4d,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4e,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x4f,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x50,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x51,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x52,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x53,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x54,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x55,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x56,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x57,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x58,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x59,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5a,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5b,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5c,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5d,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5e,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x5f,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x60,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x61,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x62,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x63,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x64,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x65,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x66,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x67,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x68,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x69,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6a,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6b,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6c,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6d,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6e,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x6f,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x70,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x71,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x72,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x73,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x74,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x75,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x76,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x77,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x78,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x79,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7a,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7b,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7c,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7d,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7e,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x7f,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x80,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x81,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x82,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x83,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x84,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x85,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x86,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x87,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x88,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x89,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8a,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8b,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8c,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8d,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8e,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x8f,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x90,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x91,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x92,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x93,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x94,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x95,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x96,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x97,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x98,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x99,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9a,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9b,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9c,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9d,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9e,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0x9f,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa0,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa1,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa2,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa3,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa4,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa5,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa6,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa7,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa8,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xa9,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xaa,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xab,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xac,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xad,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xae,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xaf,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb0,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb1,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb2,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb3,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb4,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb5,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb6,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb7,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb8,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xb9,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xba,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xbb,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xbc,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xbd,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xbe,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xbf,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc0,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc1,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc2,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc3,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc4,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc5,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc6,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc7,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc8,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xc9,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xca,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xcb,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xcc,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xcd,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xce,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xcf,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd0,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd1,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd2,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd3,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd4,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd5,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd6,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd7,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd8,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xd9,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xda,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xdb,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xdc,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xdd,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xde,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xdf,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe0,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe1,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe2,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe3,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe4,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe5,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe6,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe7,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe8,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xe9,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xea,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xeb,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xec,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xed,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xee,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xef,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf0,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf1,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf2,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf3,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf4,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf5,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf6,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf7,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf8,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xf9,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xfa,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xfb,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xfc,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xfd,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xfe,
	&BX_CPU_C::Resolve32Mod0EffectAddress_sib0xff

};

const BxOpcodeInfo_t BxOpcodeInfoG_MOVSB[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::MOVSB_XbYb_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::MOVSB_XbYb_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::MOVSB_XbYb_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::MOVSB_XbYb_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::MOVSB_XbYb_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::MOVSB_XbYb_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::MOVSB_XbYb_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::MOVSB_XbYb_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_MOVSW[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::MOVSW_XvYv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::MOVSW_XvYv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::MOVSW_XvYv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::MOVSW_XvYv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::MOVSW_XvYv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::MOVSW_XvYv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::MOVSW_XvYv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::MOVSW_XvYv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_MOVSD[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::MOVSD_XvYv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::MOVSD_XvYv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::MOVSD_XvYv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::MOVSD_XvYv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::MOVSD_XvYv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::MOVSD_XvYv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::MOVSD_XvYv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::MOVSD_XvYv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_CMPSB[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::CMPSB_XbYb_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::CMPSB_XbYb_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::CMPSB_XbYb_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::CMPSB_XbYb_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::CMPSB_XbYb_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::CMPSB_XbYb_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::CMPSB_XbYb_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::CMPSB_XbYb_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_CMPSW[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::CMPSW_XvYv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::CMPSW_XvYv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::CMPSW_XvYv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::CMPSW_XvYv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::CMPSW_XvYv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::CMPSW_XvYv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::CMPSW_XvYv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::CMPSW_XvYv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_CMPSD[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::CMPSD_XvYv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::CMPSD_XvYv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::CMPSD_XvYv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::CMPSD_XvYv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::CMPSD_XvYv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::CMPSD_XvYv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::CMPSD_XvYv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::CMPSD_XvYv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_SCASB[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::SCASB_ALYb_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::SCASB_ALYb_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::SCASB_ALYb_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::SCASB_ALYb_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::SCASB_ALYb_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::SCASB_ALYb_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::SCASB_ALYb_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::SCASB_ALYb_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_SCASW[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::SCASW_eAXYv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::SCASW_eAXYv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::SCASW_eAXYv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::SCASW_eAXYv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::SCASW_eAXYv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::SCASW_eAXYv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::SCASW_eAXYv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::SCASW_eAXYv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_SCASD[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::SCASD_eAXYv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::SCASD_eAXYv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::SCASD_eAXYv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::SCASD_eAXYv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::SCASD_eAXYv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::SCASD_eAXYv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::SCASD_eAXYv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::SCASD_eAXYv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_STOSB[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::STOSB_ALYb_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::STOSB_ALYb_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::STOSB_ALYb_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::STOSB_ALYb_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::STOSB_ALYb_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::STOSB_ALYb_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::STOSB_ALYb_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::STOSB_ALYb_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_STOSW[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::STOSW_eAXYv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::STOSW_eAXYv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::STOSW_eAXYv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::STOSW_eAXYv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::STOSW_eAXYv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::STOSW_eAXYv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::STOSW_eAXYv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::STOSW_eAXYv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_STOSD[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::STOSD_eAXYv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::STOSD_eAXYv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::STOSD_eAXYv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::STOSD_eAXYv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::STOSD_eAXYv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::STOSD_eAXYv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::STOSD_eAXYv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::STOSD_eAXYv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_LODSB[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::LODSB_ALXb_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::LODSB_ALXb_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::LODSB_ALXb_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::LODSB_ALXb_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::LODSB_ALXb_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::LODSB_ALXb_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::LODSB_ALXb_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::LODSB_ALXb_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_LODSW[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::LODSW_eAXXv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::LODSW_eAXXv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::LODSW_eAXXv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::LODSW_eAXXv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::LODSW_eAXXv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::LODSW_eAXXv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::LODSW_eAXXv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::LODSW_eAXXv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_LODSD[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::LODSD_eAXXv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::LODSD_eAXXv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::LODSD_eAXXv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::LODSD_eAXXv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::LODSD_eAXXv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::LODSD_eAXXv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::LODSD_eAXXv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::LODSD_eAXXv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_OUTSB[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::OUTSB_DXXb_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::OUTSB_DXXb_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::OUTSB_DXXb_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::OUTSB_DXXb_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::OUTSB_DXXb_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::OUTSB_DXXb_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::OUTSB_DXXb_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::OUTSB_DXXb_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_OUTSW[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::OUTSW_DXXv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::OUTSW_DXXv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::OUTSW_DXXv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::OUTSW_DXXv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::OUTSW_DXXv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::OUTSW_DXXv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::OUTSW_DXXv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::OUTSW_DXXv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_OUTSD[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::OUTSD_DXXv_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::OUTSD_DXXv_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::OUTSD_DXXv_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::OUTSD_DXXv_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::OUTSD_DXXv_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::OUTSD_DXXv_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::OUTSD_DXXv_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::OUTSD_DXXv_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_INSB[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::INSB_YbDX_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::INSB_YbDX_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::INSB_YbDX_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::INSB_YbDX_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::INSB_YbDX_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::INSB_YbDX_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::INSB_YbDX_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::INSB_YbDX_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_INSW[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::INSW_YvDX_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::INSW_YvDX_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::INSW_YvDX_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::INSW_YvDX_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::INSW_YvDX_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::INSW_YvDX_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::INSW_YvDX_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::INSW_YvDX_E32_repf3, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG_INSD[8] =
{
	// attributes defined in main area
	/* 0 */  { 0,	&BX_CPU_C::INSD_YvDX_E16_rep__, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::INSD_YvDX_E16_rep__, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::INSD_YvDX_E16_repf2, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::INSD_YvDX_E16_repf3, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::INSD_YvDX_E32_rep__, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::INSD_YvDX_E32_rep__, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::INSD_YvDX_E32_repf2, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::INSD_YvDX_E32_repf3, NULL, NULL }
}; 


//+===================================================
const BxOpcodeInfo_t BxOpcodeInfoG1EGbIb[] =
{
	/* 0 */  { BxImmediate_Ib,  &BX_CPU_C::ADD_EGbIb, NULL, NULL },
	/* 1 */  { BxImmediate_Ib,  &BX_CPU_C:: OR_EGbIb, NULL, NULL },
	/* 2 */  { BxImmediate_Ib,  &BX_CPU_C::ADC_EGbIb, NULL, NULL },
	/* 3 */  { BxImmediate_Ib,  &BX_CPU_C::SBB_EGbIb, NULL, NULL },
	/* 4 */  { BxImmediate_Ib,  &BX_CPU_C::AND_EGbIb, NULL, NULL },
	/* 5 */  { BxImmediate_Ib,  &BX_CPU_C::SUB_EGbIb, NULL, NULL },
	/* 6 */  { BxImmediate_Ib,  &BX_CPU_C::XOR_EGbIb, NULL, NULL },
	/* 7 */  { BxImmediate_Ib,  &BX_CPU_C::CMP_EGbIb, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG1EEbIb[] =
{
	/* 0 */  { BxImmediate_Ib,  &BX_CPU_C::ADD_EEbIb, NULL, NULL },
	/* 1 */  { BxImmediate_Ib,  &BX_CPU_C:: OR_EEbIb, NULL, NULL },
	/* 2 */  { BxImmediate_Ib,  &BX_CPU_C::ADC_EEbIb, NULL, NULL },
	/* 3 */  { BxImmediate_Ib,  &BX_CPU_C::SBB_EEbIb, NULL, NULL },
	/* 4 */  { BxImmediate_Ib,  &BX_CPU_C::AND_EEbIb, NULL, NULL },
	/* 5 */  { BxImmediate_Ib,  &BX_CPU_C::SUB_EEbIb, NULL, NULL },
	/* 6 */  { BxImmediate_Ib,  &BX_CPU_C::XOR_EEbIb, NULL, NULL },
	/* 7 */  { BxImmediate_Ib,  &BX_CPU_C::CMP_EEbIb, NULL, NULL },
}; 

const BxOpcodeInfo_t BxOpcodeInfoG1EGwIsb[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ADD_EGwIw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C:: OR_EGwIw, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::ADC_EGwIw, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::SBB_EGwIw, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::AND_EGwIw, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SUB_EGwIw, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::XOR_EGwIw, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::CMP_EGwIw, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG1EEwIsb[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ADD_EEwIw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C:: OR_EEwIw, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::ADC_EEwIw, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::SBB_EEwIw, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::AND_EEwIw, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SUB_EEwIw, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::XOR_EEwIw, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::CMP_EEwIw, NULL, NULL }
}; 


const BxOpcodeInfo_t BxOpcodeInfoG1EGwIw[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ADD_EGwIw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C:: OR_EGwIw, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::ADC_EGwIw, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::SBB_EGwIw, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::AND_EGwIw, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SUB_EGwIw, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::XOR_EGwIw, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::CMP_EGwIw, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG1EEwIw[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ADD_EEwIw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C:: OR_EEwIw, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::ADC_EEwIw, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::SBB_EEwIw, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::AND_EEwIw, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SUB_EEwIw, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::XOR_EEwIw, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::CMP_EEwIw, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG1EGdIsb[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ADD_EGdId, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C:: OR_EGdId, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::ADC_EGdId, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::SBB_EGdId, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::AND_EGdId, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SUB_EGdId, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::XOR_EGdId, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::CMP_EGdId, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG1EEdIsb[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ADD_EEdId, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C:: OR_EEdId, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::ADC_EEdId, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::SBB_EEdId, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::AND_EEdId, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SUB_EEdId, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::XOR_EEdId, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::CMP_EEdId, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG1EGdId[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ADD_EGdId, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C:: OR_EGdId, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::ADC_EGdId, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::SBB_EGdId, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::AND_EGdId, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SUB_EGdId, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::XOR_EGdId, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::CMP_EGdId, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG1EEdId[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ADD_EEdId, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C:: OR_EEdId, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::ADC_EEdId, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::SBB_EEdId, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::AND_EEdId, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SUB_EEdId, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::XOR_EEdId, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::CMP_EEdId, NULL, NULL }
}; 

//-----------------------------------------------------------
//-----------------------------------------------------------
const BxOpcodeInfo_t BxOpcodeInfoG0x8fEGw[] =
{
	/* 0 */  { 0,  &BX_CPU_C::POP_EGw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::BxError, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG0x8fEEw[] =
{
	/* 0 */  { 0,  &BX_CPU_C::POP_EEw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::BxError, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG0x8fEGd[] =
{
	/* 0 */  { 0,  &BX_CPU_C::POP_EGd, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::BxError, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG0x8fEEd[] =
{
	/* 0 */  { 0,  &BX_CPU_C::POP_EEd, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::BxError, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG0xc6EGbIb[] =
{
	/* 0 */  { 0,  &BX_CPU_C::MOV_EGbIb, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::BxError, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG0xc6EEbIb[] =
{
	/* 0 */  { 0,  &BX_CPU_C::MOV_EEbIb, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::BxError, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG0xc7EGwIw[] =
{
	/* 0 */  { 0,  &BX_CPU_C::MOV_EGwIw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::BxError, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG0xc7EEwIw[] =
{
	/* 0 */  { 0,  &BX_CPU_C::MOV_EEwIw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::BxError, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG0xc7EGdId[] =
{
	/* 0 */  { 0,  &BX_CPU_C::MOV_EGdId, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::BxError, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG0xc7EEdId[] =
{
	/* 0 */  { 0,  &BX_CPU_C::MOV_EEdId, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::BxError, NULL, NULL }
}; 
//-----------------------------------------------------------
//移计数为 字节立即数的低5比特位
const BxOpcodeInfo_t BxOpcodeInfoG2EGbIb[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EGb, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EGb, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EGb, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EGb, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EGb, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EGb, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EGb, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EGb, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EEbIb[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EEb, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EEb, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EEb, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EEb, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EEb, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EEb, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EEb, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EEb, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG2EGwIb[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EGw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EGw, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EGw, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EGw, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EGw, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EGw, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EGw, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EGw, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EEwIb[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EEw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EEw, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EEw, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EEw, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EEw, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EEw, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EEw, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EEw, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EGdIb[] =
{
	/* 0 */  { 0,	&BX_CPU_C::ROL_EGd, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::ROR_EGd, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::RCL_EGd, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::RCR_EGd, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::SHL_EGd, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::SHR_EGd, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::SHL_EGd, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::SAR_EGd, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EEdIb[] =
{
	/* 0 */  { 0,	&BX_CPU_C::ROL_EEd, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::ROR_EEd, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::RCL_EEd, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::RCR_EEd, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::SHL_EEd, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::SHR_EEd, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::SHL_EEd, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::SAR_EEd, NULL, NULL }
};

//-----------------------------------------------------------
//移计数默认为 1
const BxOpcodeInfo_t BxOpcodeInfoG2EGb_1[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EGb, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EGb, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EGb, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EGb, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EGb, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EGb, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EGb, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EGb, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EEb_1[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EEb, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EEb, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EEb, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EEb, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EEb, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EEb, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EEb, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EEb, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG2EGw_1[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EGw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EGw, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EGw, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EGw, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EGw, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EGw, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EGw, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EGw, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EEw_1[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EEw, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EEw, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EEw, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EEw, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EEw, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EEw, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EEw, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EEw, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EGd_1[] =
{
	/* 0 */  { 0,	&BX_CPU_C::ROL_EGd, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::ROR_EGd, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::RCL_EGd, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::RCR_EGd, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::SHL_EGd, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::SHR_EGd, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::SHL_EGd, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::SAR_EGd, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EEd_1[] =
{
	/* 0 */  { 0,	&BX_CPU_C::ROL_EEd, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::ROR_EEd, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::RCL_EEd, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::RCR_EEd, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::SHL_EEd, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::SHR_EEd, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::SHL_EEd, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::SAR_EEd, NULL, NULL }
};

//-----------------------------------------------------------
//移计数为 cl 寄存器的低5比特位
const BxOpcodeInfo_t BxOpcodeInfoG2EGbCL[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EGbCL, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EGbCL, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EGbCL, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EGbCL, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EGbCL, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EGbCL, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EGbCL, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EGbCL, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EEbCL[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EEbCL, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EEbCL, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EEbCL, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EEbCL, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EEbCL, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EEbCL, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EEbCL, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EEbCL, NULL, NULL }
}; 

const BxOpcodeInfo_t BxOpcodeInfoG2EGwCL[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EGwCL, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EGwCL, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EGwCL, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EGwCL, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EGwCL, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EGwCL, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EGwCL, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EGwCL, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EEwCL[] =
{
	/* 0 */  { 0,  &BX_CPU_C::ROL_EEwCL, NULL, NULL },
	/* 1 */  { 0,  &BX_CPU_C::ROR_EEwCL, NULL, NULL },
	/* 2 */  { 0,  &BX_CPU_C::RCL_EEwCL, NULL, NULL },
	/* 3 */  { 0,  &BX_CPU_C::RCR_EEwCL, NULL, NULL },
	/* 4 */  { 0,  &BX_CPU_C::SHL_EEwCL, NULL, NULL },
	/* 5 */  { 0,  &BX_CPU_C::SHR_EEwCL, NULL, NULL },
	/* 6 */  { 0,  &BX_CPU_C::SHL_EEwCL, NULL, NULL },
	/* 7 */  { 0,  &BX_CPU_C::SAR_EEwCL, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EGdCL[] =
{
	/* 0 */  { 0,	&BX_CPU_C::ROL_EGdCL, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::ROR_EGdCL, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::RCL_EGdCL, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::RCR_EGdCL, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::SHL_EGdCL, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::SHR_EGdCL, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::SHL_EGdCL, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::SAR_EGdCL, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG2EEdCL[] =
{
	/* 0 */  { 0,	&BX_CPU_C::ROL_EEdCL, NULL, NULL },
	/* 1 */  { 0,	&BX_CPU_C::ROR_EEdCL, NULL, NULL },
	/* 2 */  { 0,	&BX_CPU_C::RCL_EEdCL, NULL, NULL },
	/* 3 */  { 0,	&BX_CPU_C::RCR_EEdCL, NULL, NULL },
	/* 4 */  { 0,	&BX_CPU_C::SHL_EEdCL, NULL, NULL },
	/* 5 */  { 0,	&BX_CPU_C::SHR_EEdCL, NULL, NULL },
	/* 6 */  { 0,	&BX_CPU_C::SHL_EEdCL, NULL, NULL },
	/* 7 */  { 0,	&BX_CPU_C::SAR_EEdCL, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG3EGb[] =
{
	/* 0 */  { BxImmediate_Ib, &BX_CPU_C::TEST_EGbIb, NULL, NULL },
	/* 1 */  { BxImmediate_Ib, &BX_CPU_C::TEST_EGbIb, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::NOT_EGb,	 NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::NEG_EGb,    NULL, NULL },
	/* 4 */  { 0, &BX_CPU_C::MUL_ALEGb,  NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::IMUL_ALEGb, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::DIV_ALEGb,  NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::IDIV_ALEGb, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG3EEb[] =
{
	/* 0 */  { BxImmediate_Ib, &BX_CPU_C::TEST_EEbIb, NULL, NULL },
	/* 1 */  { BxImmediate_Ib, &BX_CPU_C::TEST_EEbIb, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::NOT_EEb,    NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::NEG_EEb,    NULL, NULL },
	/* 4 */  { 0, &BX_CPU_C::MUL_ALEEb,  NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::IMUL_ALEEb, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::DIV_ALEEb,  NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::IDIV_ALEEb, NULL, NULL }
};  

const BxOpcodeInfo_t BxOpcodeInfoG3EGw[] =
{
	/* 0 */  { BxImmediate_Iw, &BX_CPU_C::TEST_EGwIw, NULL, NULL },
	/* 1 */  { BxImmediate_Iw, &BX_CPU_C::TEST_EGwIw, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::NOT_EGw,    NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::NEG_EGw,    NULL, NULL },
	/* 4 */  { 0, &BX_CPU_C::MUL_AXEGw,  NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::IMUL_AXEGw, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::DIV_AXEGw,  NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::IDIV_AXEGw, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG3EEw[] =
{
	/* 0 */  { BxImmediate_Iw, &BX_CPU_C::TEST_EEwIw, NULL, NULL },
	/* 1 */  { BxImmediate_Iw, &BX_CPU_C::TEST_EEwIw, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::NOT_EEw,    NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::NEG_EEw,    NULL, NULL },
	/* 4 */  { 0, &BX_CPU_C::MUL_AXEEw,  NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::IMUL_AXEEw, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::DIV_AXEEw,  NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::IDIV_AXEEw, NULL, NULL }
};  

const BxOpcodeInfo_t BxOpcodeInfoG3EGd[] =
{
	/* 0 */  { BxImmediate_Iv, &BX_CPU_C::TEST_EGdId, NULL, NULL },
	/* 1 */  { BxImmediate_Iv, &BX_CPU_C::TEST_EGdId, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::NOT_EGd,     NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::NEG_EGd,     NULL, NULL },
	/* 4 */  { 0, &BX_CPU_C::MUL_EAXEGd,  NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::IMUL_EAXEGd, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::DIV_EAXEGd,  NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::IDIV_EAXEGd, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG3EEd[] =
{
	/* 0 */  { BxImmediate_Iv, &BX_CPU_C::TEST_EEdId, NULL, NULL },
	/* 1 */  { BxImmediate_Iv, &BX_CPU_C::TEST_EEdId, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::NOT_EEd,     NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::NEG_EEd,     NULL, NULL },
	/* 4 */  { 0, &BX_CPU_C::MUL_EAXEEd,  NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::IMUL_EAXEEd, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::DIV_EAXEEd,  NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::IDIV_EAXEEd, NULL, NULL }
};  

const BxOpcodeInfo_t BxOpcodeInfoG4EGb[] =
{
	/* 0 */  { 0, &BX_CPU_C::INC_EGb, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::DEC_EGb, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::BxError, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG4EEb[] =
{
	/* 0 */  { 0, &BX_CPU_C::INC_EEb, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::DEC_EEb, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::BxError, NULL, NULL }
};  

const BxOpcodeInfo_t BxOpcodeInfoG5EGw[] =
{
	/* 0 */  { 0, &BX_CPU_C::INC_EGw, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::DEC_EGw, NULL, NULL },
	/* 2 */  { BxBranch_absolute, &BX_CPU_C::CALL_EGw,NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { BxBranch_absolute, &BX_CPU_C::JMP_EGw, NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::PUSH_EGw,NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::BxError, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG5EEw[] =
{
	/* 0 */  { 0, &BX_CPU_C::INC_EEw, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::DEC_EEw, NULL, NULL },
	/* 2 */  { BxBranch_absolute, &BX_CPU_C::CALL_EEw,NULL, NULL },
	/* 3 */  { BxBranch_absolute, &BX_CPU_C::CALL16_Ep,NULL, NULL },
	/* 4 */  { BxBranch_absolute, &BX_CPU_C::JMP_EEw, NULL, NULL },
	/* 5 */  { BxBranch_absolute, &BX_CPU_C::JMP16_Ep,NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::PUSH_EEw,NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::BxError, NULL, NULL }
};  

const BxOpcodeInfo_t BxOpcodeInfoG5EGd[] =
{
	/* 0 */  { 0, &BX_CPU_C::INC_EGd, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::DEC_EGd, NULL, NULL },
	/* 2 */  { BxBranch_absolute, &BX_CPU_C::CALL_EGd, NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { BxBranch_absolute, &BX_CPU_C::JMP_EGd, NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::PUSH_EGd, NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::BxError, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG5EEd[] =
{
	/* 0 */  { 0, &BX_CPU_C::INC_EEd, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::DEC_EEd, NULL, NULL },
	/* 2 */  { BxBranch_absolute, &BX_CPU_C::CALL_EEd, NULL, NULL },
	/* 3 */  { BxBranch_absolute, &BX_CPU_C::CALL32_Ep, NULL, NULL },
	/* 4 */  { BxBranch_absolute, &BX_CPU_C::JMP_EEd, NULL, NULL },
	/* 5 */  { BxBranch_absolute, &BX_CPU_C::JMP32_Ep, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::PUSH_EEd, NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::BxError, NULL, NULL }
};   

const BxOpcodeInfo_t BxOpcodeInfoG6[] =
{
	/* 0 */  { 0, &BX_CPU_C::SLDT_Ew, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::STR_Ew, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::LLDT_Ew, NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::LTR_Ew, NULL, NULL },
	/* 4 */  { 0, &BX_CPU_C::VERR_Ew, NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::VERW_Ew, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::BxError, NULL, NULL }
};   

const BxOpcodeInfo_t BxOpcodeInfoG7[] =
{
	/* 0 */  { 0, &BX_CPU_C::SGDT_Ms, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::SIDT_Ms, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::LGDT_Ms, NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::LIDT_Ms, NULL, NULL },
	/* 4 */  { 0, &BX_CPU_C::SMSW_Ew, NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::LMSW_Ew, NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::INVLPG, NULL, NULL }
};    

const BxOpcodeInfo_t BxOpcodeInfoG8EGwIb[] =
{
	/* 0 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { BxImmediate_Ib,	&BX_CPU_C::BT_EGwIb, NULL, NULL },
	/* 5 */  { BxImmediate_Ib,	&BX_CPU_C::BTS_EGwIb, NULL, NULL },
	/* 6 */  { BxImmediate_Ib,	&BX_CPU_C::BTR_EGwIb, NULL, NULL },
	/* 7 */  { BxImmediate_Ib,	&BX_CPU_C::BTC_EGwIb, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG8EEwIb[] =
{
	/* 0 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { BxImmediate_Ib,	&BX_CPU_C::BT_EEwIb, NULL, NULL },
	/* 5 */  { BxImmediate_Ib,	&BX_CPU_C::BTS_EEwIb, NULL, NULL },
	/* 6 */  { BxImmediate_Ib,	&BX_CPU_C::BTR_EEwIb, NULL, NULL },
	/* 7 */  { BxImmediate_Ib,	&BX_CPU_C::BTC_EEwIb, NULL, NULL }
};    

const BxOpcodeInfo_t BxOpcodeInfoG8EGdIb[] =
{
	/* 0 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { BxImmediate_Ib,	&BX_CPU_C::BT_EGdIb, NULL, NULL },
	/* 5 */  { BxImmediate_Ib,	&BX_CPU_C::BTS_EGdIb, NULL, NULL },
	/* 6 */  { BxImmediate_Ib,	&BX_CPU_C::BTR_EGdIb, NULL, NULL },
	/* 7 */  { BxImmediate_Ib,	&BX_CPU_C::BTC_EGdIb, NULL, NULL }
};

const BxOpcodeInfo_t BxOpcodeInfoG8EEdIb[] =
{
	/* 0 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { BxImmediate_Ib,	&BX_CPU_C::BT_EEdIb, NULL, NULL },
	/* 5 */  { BxImmediate_Ib,	&BX_CPU_C::BTS_EEdIb, NULL, NULL },
	/* 6 */  { BxImmediate_Ib,	&BX_CPU_C::BTR_EEdIb, NULL, NULL },
	/* 7 */  { BxImmediate_Ib,	&BX_CPU_C::BTC_EEdIb, NULL, NULL }
};    

const BxOpcodeInfo_t BxOpcodeInfoG9[] =
{
	/* 0 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 1 */  { 0, &BX_CPU_C::CMPXCHG8B, NULL, NULL },
	/* 2 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 3 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 4 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 5 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 6 */  { 0, &BX_CPU_C::BxError, NULL, NULL },
	/* 7 */  { 0, &BX_CPU_C::BxError, NULL, NULL }
};

//const BxOpcodeInfo_t BxOpcodeInfo[512*2*2] =
//{
//};

	unsigned
BX_CPU_C::fetchDecode(Bit8u *iptr, bxInstruction_c *instruction,
                      unsigned remain)
{
	// remain must be at least 1
	bx_bool is_32;
	unsigned b1, b2, i_bytes=1;
	unsigned attr;
	unsigned immed_mode,offset;
	unsigned fetch_rep;
	unsigned fetch_os32;
	unsigned fetch_as32;
	unsigned fetch_seg;
	unsigned fetch_mod;
	unsigned fetch_rm;

	is_32 = BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.u.segment.d_b;

	fetch_rep = 0xf0;
	fetch_os32 = is_32;
	fetch_as32 = is_32;
	fetch_seg = BX_SEG_REG_NULL;
	instruction->ResolveModrm = NULL;

fetch_b1:

	b1 = *iptr++;

another_byte:

//	BX_CPU_THIS_PTR iptr = iptr-1;

	offset = fetch_os32 << 9; // * 512
	attr = BxOpcodeInfo[b1+offset].Attr;

	if (attr & BxAnother)
	{
		if (attr & BxPrefix)
		{
			switch (b1)
			{
			case 0x66: // OperSize
				fetch_os32 = !is_32;
				break;

			case 0x67: // AddrSize
				fetch_as32 = !is_32;
				break;

			case 0xf2: // REPNE/REPNZ
				fetch_rep = 0xf2;
				break;
			case 0xf3: // REP/REPE/REPZ
				fetch_rep = 0xf3;
				break;

			case 0x2e: // CS:
				fetch_seg = BX_SEG_REG_CS;
				break;

			case 0x26: // ES:
				fetch_seg = BX_SEG_REG_ES;
				break;

			case 0x36: // SS:
				fetch_seg = BX_SEG_REG_SS;
				break;

			case 0x3e: // DS:
				fetch_seg = BX_SEG_REG_DS;
				break;

			case 0x64: // FS:
				fetch_seg = BX_SEG_REG_FS;
				break;

			case 0x65: // GS:
				fetch_seg = BX_SEG_REG_GS;
				break;

			case 0xf0: // LOCK:
				break;

			default:
				BX_PANIC(("fetch_decode: prefix default = 0x%02x", b1));
			}

			if (i_bytes < remain)
			{
				i_bytes++;
				goto fetch_b1;
			}

			return(0);
		}

		// opcode requires another byte
		if (i_bytes < remain)
		{
			i_bytes++;
			b2 = *iptr++;
			if (b1 == 0x0f)
			{
				// 2-byte prefix
				b1 = 0x100 | b2;
				goto another_byte;
			}
		}
		else
			return(0);
	    // Parse mod-nnn-rm and related bytes
		OPCODEb2(instruction) = b2;
		fetch_mod = b2 & 0xc0; // leave unshifted
		fetch_rm =
		MODRMrm(instruction)    = b2 & 0x07;
		MODRMnnn(instruction)   = (b2 >> 3) & 0x07;

		if (fetch_mod == 0xc0)
		{	// mod == 11b
			goto modrm_done;
		}

		offset += 512*2;

		if (fetch_as32)
		{
			//BX_CPU_THIS_PTR modrm_len = ::Translate_modrm32_length[(b2&0xc7)|((*iptr&0x7)<<3)];

			// 32-bit addressing modes; note that mod==11b handled above
			if (fetch_rm != 4)
			{ // no s-i-b byte
#if BX_DYNAMIC_TRANSLATION
				instruction->DTMemRegsUsed = 1<<fetch_rm; // except for mod=00b rm=100b
#endif
				if (fetch_mod == 0x00)
				{ // mod == 00b
					instruction->ResolveModrm = BxResolve32Mod0[fetch_rm];
#if BX_DYNAMIC_TRANSLATION
					instruction->DTResolveModrm = (BxVoidFPtr_t) BxDTResolve32Mod0[fetch_rm];
#endif
					if (BX_NULL_SEG_REG(fetch_seg))
						fetch_seg = BX_SEG_REG_DS;
					if (fetch_rm == 5)
					{
						if ((i_bytes+3) < remain)
						{
							Bit32u imm32u;
							imm32u = *iptr++;
							imm32u |= (*iptr++) << 8;
							imm32u |= (*iptr++) << 16;
							imm32u |= (*iptr++) << 24;
							instruction->displ32u = imm32u;
							//RMAddr(instruction) = imm32u;
							i_bytes += 4;
#if BX_DYNAMIC_TRANSLATION
							instruction->DTMemRegsUsed = 0;
#endif
							goto modrm_done;
						}
						else
						{
							return(0);
						}
					}

					// mod==00b, rm!=4, rm!=5
					goto modrm_done;
				}

				if (fetch_mod == 0x40)
				{ // mod == 01b
					instruction->ResolveModrm = BxResolve32Mod1or2[fetch_rm];
#if BX_DYNAMIC_TRANSLATION
					instruction->DTResolveModrm = (BxVoidFPtr_t) BxDTResolve32Mod1or2[fetch_rm];
#endif
					if (BX_NULL_SEG_REG(fetch_seg))
						fetch_seg = BX_CPU_THIS_PTR sreg_mod01_rm32[fetch_rm];
get_8bit_displ:
					if (i_bytes < remain)
					{
						// 8 sign extended to 32
						instruction->displ32u = (Bit8s) *iptr++;
						i_bytes++;
						goto modrm_done;
					}
			        else
					{
						return(0);
					}
				}

				// (mod == 0x80) mod == 10b
				instruction->ResolveModrm = BxResolve32Mod1or2[fetch_rm];
#if BX_DYNAMIC_TRANSLATION
				instruction->DTResolveModrm = (BxVoidFPtr_t) BxDTResolve32Mod1or2[fetch_rm];
#endif
				if (BX_NULL_SEG_REG(fetch_seg))
					fetch_seg = BX_CPU_THIS_PTR sreg_mod10_rm32[fetch_rm];
get_32bit_displ:
				if ((i_bytes+3) < remain)
				{
					Bit32u imm32u;
					imm32u = *iptr++;
					imm32u |= (*iptr++) << 8;
					imm32u |= (*iptr++) << 16;
					imm32u |= (*iptr++) << 24;
					instruction->displ32u = imm32u;
			        i_bytes += 4;
					goto modrm_done;
				}
				else
				{
					return(0);
				}
			}	
			else
			{ // mod!=11b, rm==4, s-i-b byte follows
				unsigned sib, base;
				if (i_bytes < remain)
				{
					sib = *iptr++;
					i_bytes++;
				}
				else
				{
					return(0);
				}
				
				base = sib & 0x07;

#if BX_DYNAMIC_TRANSLATION
				if (instruction->index == 0x04) // 100b
					instruction->DTMemRegsUsed = 0;
				else
					instruction->DTMemRegsUsed = 1<<instruction->index;
#endif
				if (fetch_mod == 0x00)
				{ // mod==00b, rm==4
					instruction->ResolveModrm =
						BxResolve32Mod0EffectAddressBaseIndexScaled[sib];//effect_address

#if BX_DYNAMIC_TRANSLATION
					instruction->DTResolveModrm = (BxVoidFPtr_t) BxDTResolve32Mod0Base[base];
#endif
					if (BX_NULL_SEG_REG(fetch_seg))
						fetch_seg = BX_CPU_THIS_PTR sreg_mod0_base32[base];
					if (base == 0x05)
					{
						goto get_32bit_displ;
					}
					// mod==00b, rm==4, base!=5
#if BX_DYNAMIC_TRANSLATION
					instruction->DTMemRegsUsed |= 1<<base;
#endif
					goto modrm_done;
				}
#if BX_DYNAMIC_TRANSLATION
				// for remaining 32bit cases
		        instruction->DTMemRegsUsed |= 1<<base;
#endif
				if (fetch_mod == 0x40)
				{ // mod==01b, rm==4
					instruction->ResolveModrm =
						BxResolve32Mod1or2EffectAddressBaseIndexScaled[sib];//effect_address
#if BX_DYNAMIC_TRANSLATION
					instruction->DTResolveModrm = (BxVoidFPtr_t) BxDTResolve32Mod1or2Base[base];
#endif
					if (BX_NULL_SEG_REG(fetch_seg))
						fetch_seg = BX_CPU_THIS_PTR sreg_mod1or2_base32[base];
					goto get_8bit_displ;
				}

				// (fetch_mod == 0x80),  mod==10b, rm==4
				instruction->ResolveModrm =
                    BxResolve32Mod1or2EffectAddressBaseIndexScaled[sib];//effect_address
#if BX_DYNAMIC_TRANSLATION
				instruction->DTResolveModrm = (BxVoidFPtr_t) BxDTResolve32Mod1or2Base[base];
#endif
				if (BX_NULL_SEG_REG(fetch_seg))
					fetch_seg = BX_CPU_THIS_PTR sreg_mod1or2_base32[base];

				goto get_32bit_displ;
			}
		}
		else
		{
			//BX_CPU_THIS_PTR modrm_len = ::Translate_modrm16_length[b2];
		
			// 16-bit addressing modes, mod==11b handled above
			if (fetch_mod == 0x40)
			{ // mod == 01b
				instruction->ResolveModrm = BxResolve16Mod1or2[fetch_rm];
#if BX_DYNAMIC_TRANSLATION
				instruction->DTResolveModrm = (BxVoidFPtr_t) BxDTResolve16Mod1or2[fetch_rm];
#endif
				if (BX_NULL_SEG_REG(fetch_seg))
					fetch_seg = BX_CPU_THIS_PTR sreg_mod01_rm16[fetch_rm];
#if BX_DYNAMIC_TRANSLATION
				instruction->DTMemRegsUsed = BxMemRegsUsed16[fetch_rm];
#endif
				if (i_bytes < remain)
				{
					// 8 sign extended to 16
					instruction->displ16u = (Bit8s) *iptr++;
					i_bytes++;
					goto modrm_done;
				}
				else
				{
					return(0);
				}
			}

			if (fetch_mod == 0x80)
			{ // mod == 10b
				instruction->ResolveModrm = BxResolve16Mod1or2[fetch_rm];
#if BX_DYNAMIC_TRANSLATION
		        instruction->DTResolveModrm = (BxVoidFPtr_t) BxDTResolve16Mod1or2[fetch_rm];
#endif
				if (BX_NULL_SEG_REG(fetch_seg))
					fetch_seg = BX_CPU_THIS_PTR sreg_mod10_rm16[fetch_rm];
#if BX_DYNAMIC_TRANSLATION
				instruction->DTMemRegsUsed = BxMemRegsUsed16[fetch_rm];
#endif
				if ((i_bytes+1) < remain)
				{
					Bit16u displ16u;
					displ16u = *iptr++;
					displ16u |= (*iptr++) << 8;
					instruction->displ16u = displ16u;
					i_bytes += 2;
					goto modrm_done;
				}
				else 
				{
					return(0);
				}
			}

			// mod must be 00b at this point
			instruction->ResolveModrm = BxResolve16Mod0[fetch_rm];
#if BX_DYNAMIC_TRANSLATION
			instruction->DTResolveModrm = (BxVoidFPtr_t) BxDTResolve16Mod0[fetch_rm];
#endif
			if (BX_NULL_SEG_REG(fetch_seg))
				fetch_seg = BX_CPU_THIS_PTR sreg_mod00_rm16[fetch_rm];

			if (fetch_rm == 0x06)
			{
				if ((i_bytes+1) < remain)
				{
					Bit16u displ16u;
					displ16u = *iptr++;
					displ16u |= (*iptr++) << 8;
					instruction->displ16u = displ16u;
					//RMAddr(instruction) = displ16u;
					i_bytes += 2;
					goto modrm_done;
				}
				else
				{
					return(0);
				}
			}
			// mod=00b rm!=6
#if BX_DYNAMIC_TRANSLATION
			instruction->DTMemRegsUsed = BxMemRegsUsed16[fetch_rm];
#endif
		}

modrm_done:

//		BX_CPU_THIS_PTR modrm_len = iptr - BX_CPU_THIS_PTR iptr-1;

		if (attr & BxGroupN)
		{
			BxOpcodeInfo_t *OpcodeInfoPtr;

			OpcodeInfoPtr = (BxOpcodeInfo_t *)BxOpcodeInfo[b1+offset].OpcodeInfoPtr;

			instruction->execute =
				OpcodeInfoPtr[MODRMnnn(instruction)].ExecutePtr;
//			BX_CPU_THIS_PTR translateptr =
//				OpcodeInfoPtr[MODRMnnn(instruction)].TranslatePtr;
			
			// get additional attributes from group table
			attr |= OpcodeInfoPtr[MODRMnnn(instruction)].Attr;
#if BX_DYNAMIC_TRANSLATION
			instruction->DTAttr = 0; // for now
#endif
		}
		else
		{
			instruction->execute =
				BxOpcodeInfo[b1+offset].ExecutePtr;
//			BX_CPU_THIS_PTR translateptr =
//				BxOpcodeInfo[b1+offset].TranslatePtr;

#if BX_DYNAMIC_TRANSLATION
			instruction->DTAttr = BxDTOpcodeInfo[b1+offset].DTAttr;
			instruction->DTFPtr = BxDTOpcodeInfo[b1+offset].DTASFPtr;
#endif
		}
	}
	else
	{
		// Opcode does not require a MODRM byte.
		// Note that a 2-byte opcode (0F XX) will jump to before
		// the if() above after fetching the 2nd byte, so this path is
		// taken in all cases if a modrm byte is NOT required.
		instruction->execute = BxOpcodeInfo[b1+offset].ExecutePtr;
//		BX_CPU_THIS_PTR translateptr = BxOpcodeInfo[b1+offset].TranslatePtr;

#if BX_DYNAMIC_TRANSLATION
	    instruction->DTAttr = BxDTOpcodeInfo[b1+offset].DTAttr;
	    instruction->DTFPtr = BxDTOpcodeInfo[b1+offset].DTASFPtr;
#endif
    }

	immed_mode = attr & BxImmediate;
	if (immed_mode)
	{
		Bit8s temp8s;
		Bit32u imm32u;
		Bit16u imm16u;

		switch (immed_mode)
		{
		case BxImmediate_1:
			IMMEDIATEIb(instruction) = 1;
			break;

		case BxImmediate_CL:
			IMMEDIATEIb(instruction) = X86_CL;
			break;

		case BxImmediate_Ib:
			if(i_bytes>=remain)
				return 0;
			IMMEDIATEIb(instruction) = *iptr;
			i_bytes++;
			break;

		case BxImmediate_Ib_SE: // Sign extend to OS size
			if(i_bytes>=remain)
				return 0;
			temp8s = *iptr;
			if (fetch_os32)
				IMMEDIATEId(instruction) = (Bit32s) temp8s;
			else
				IMMEDIATEIw(instruction) = (Bit16s) temp8s;
			i_bytes++;
			break;
		case BxImmediate_Iv: // same as BxImmediate_BrOff32
		case BxImmediate_IvIw: // CALL_Ap JMP_Ap
			if (fetch_os32)
			{
				if ((i_bytes+4) > remain)
					return 0;
				imm32u = *iptr++;
				imm32u |= (*iptr++) << 8;
				imm32u |= (*iptr++) << 16;
				imm32u |= (*iptr) << 24;
				IMMEDIATEId(instruction) = imm32u;
				i_bytes += 4;
			}
			else
			{
				if(i_bytes+2>remain)
					return 0;
				imm16u = *iptr++;
				imm16u |= (*iptr) << 8;
				IMMEDIATEIw(instruction) = imm16u;
				i_bytes += 2;
			}

			if (immed_mode != BxImmediate_IvIw)
				break;

			iptr++;
			// Get Iw for BxImmediate_IvIw
			if(i_bytes+2>remain)
				return 0;
			imm16u = *iptr++;
			imm16u |= (*iptr) << 8;
			IMMEDIATEIw2(instruction) = imm16u;
			i_bytes += 2;
			break;

		case BxImmediate_O:
			if (fetch_as32)
			{
				if ((i_bytes+4) > remain)
					return 0;
				// fetch 32bit address into Id
				imm32u = *iptr++;
				imm32u |= (*iptr++) << 8;
				imm32u |= (*iptr++) << 16;
				imm32u |= (*iptr) << 24;
				IMMEDIATEId(instruction) = imm32u;
				i_bytes += 4;
			}
			else
			{
				if(i_bytes+2>remain)
					return 0;
				// fetch 16bit address into Id
				imm32u = *iptr++;
				imm32u |= (*iptr) << 8;
				IMMEDIATEId(instruction) = imm32u;
				i_bytes += 2;
			}

			if (BX_NULL_SEG_REG(fetch_seg))
				fetch_seg = BX_SEG_REG_DS;
			break;

		case BxImmediate_Iw:
		case BxImmediate_IwIb:
			if(i_bytes+2>remain)
				return 0;
			imm16u = *iptr++;
			imm16u |= (*iptr) << 8;
			IMMEDIATEIw(instruction) = imm16u;
			i_bytes += 2;
			if (immed_mode == BxImmediate_Iw)
				break;
			if(i_bytes>=remain)
				return 0;
			iptr++;
			IMMEDIATEIb2(instruction) = *iptr;
			i_bytes++;
			break;

		case BxImmediate_BrOff8:
			if(i_bytes>=remain)
				return 0;
			temp8s = *iptr;
			IMMEDIATEId(instruction) = temp8s;
			i_bytes++;
			break;

      case BxImmediate_BrOff16:
			if(i_bytes+2>remain)
				return 0;
			imm16u = *iptr++;
			imm16u |= (*iptr) << 8;
			IMMEDIATEId(instruction) = (Bit16s) imm16u;
			i_bytes += 2;
			break;

      case BxImmediate_BrOff32:
			if ((i_bytes+4) > remain)
				return 0;
			imm32u = *iptr++;
			imm32u |= (*iptr++) << 8;
			imm32u |= (*iptr++) << 16;
			imm32u |= (*iptr) << 24;
			IMMEDIATEId(instruction) = imm32u;
			i_bytes += 4;
			break;
		default:
			BX_INFO(("b1 was %x", b1));
			BX_PANIC(("fetchdecode: immed_mode = %u", immed_mode));
		}
		if (i_bytes>remain)
			return(0);
	}

	if ((attr & BxRepeatable))
	{
		//	b1==0x6c||b1==0x6d||		//ins
		//	b1==0x6e||b1==0x6f||		//outs
		//	b1==0xa4||b1==0xa5||		//movs
		//	b1==0xa6||b1==0xa7||		//cmps
		//	b1==0xaa||b1==0xab||		//stos		
		//	b1==0xac||b1==0xad||		//lods
		//	b1==0xae||b1==0xaf||		//scas

		BxOpcodeInfo_t *OpcodeInfoPtr;
		int string_num;

		if (BX_NULL_SEG_REG(fetch_seg))
			fetch_seg = BX_SEG_REG_DS;

		string_num = fetch_rep-0xf0 + (fetch_as32<<2);

		OpcodeInfoPtr = (BxOpcodeInfo_t *)BxOpcodeInfo[b1+offset].OpcodeInfoPtr;

		instruction->execute = OpcodeInfoPtr[string_num].ExecutePtr;
//		BX_CPU_THIS_PTR translateptr = OpcodeInfoPtr[string_num].TranslatePtr;
		// get additional attributes from group table
		attr |= OpcodeInfoPtr[string_num].Attr;
	}

	OPCODEb1(instruction) = b1;
	MODRMSeg(instruction) = fetch_seg;
	instruction->size_mode.os_32 = fetch_os32;
	instruction->size_mode.as_32 = fetch_as32;
	instruction->i_bytes = (Bit8u)i_bytes;
//	BX_CPU_THIS_PTR attr = attr;

	return(i_bytes);
}

	void
BX_CPU_C::BxError(BX_CPU_C *icpu,bxInstruction_c *i)
{
	// extern void dump_core();
	BX_INFO(("BxError: instruction with op1=0x%x", i->b1));
	BX_INFO(("nnn was %u", i->nnn));

	BX_INFO(("WARNING: Encountered an unknown instruction (signalling illegal instruction):"));
	// dump_core();
	BX_PANIC(("BxError:inst with op1=0x%x nnn was %u", i->b1,i->nnn));
	BX_CPU_CLASS_PTR UndefinedOpcode(icpu,i);
}

	void
BX_CPU_C::BxResolveError(BX_CPU_C *icpu,bxInstruction_c *i)
{
	BX_PANIC(("BxResolveError: instruction with op1=0x%x", i->b1));
}

