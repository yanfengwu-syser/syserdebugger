/////////////////////////////////////////////////////////////////////////
// $Id: segment_ctrl_pro.cc,v 1.11 2001/11/13 05:11:41 bdenney Exp $
/////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "x86cpu.h"

Bit8u AR_BYTE_READ[0x20] = //read
{
	0,	0,	0,	0,		0,	0,	0,	0,
	0,	0,	0,	0,		0,	0,	0,	0,
	1,	1,	1,	1,		1,	1,	1,	1,
	0,	0,	1,	1,		0,	0,	1,	1,
};

Bit8u AR_BYTE_READWRITE[0x20] = //read write
{
	0,	0,	0,	0,		0,	0,	0,	0,
	0,	0,	0,	0,		0,	0,	0,	0,
	0,	0,	1,	1,		0,	0,	1,	1,
	0,	0,	0,	0,		0,	0,	0,	0,
};

	void
BX_CPU_C::load_seg_reg(bx_segment_reg_t *seg, Bit16u new_value)
{
#if BX_CPU_LEVEL >= 2
	if (protected_mode())
	{
		if (seg == &BX_CPU_THIS_PTR program_visible_sregs[BX_SREG_SS])
		{
			Bit16u index;
			Bit8u ti;
			Bit8u rpl;
			bx_descriptor_t descriptor;
			Bit32u dword1, dword2;

			if ((new_value & 0xfffc) == 0)
			{ /* null selector */
				BX_PANIC(("load_seg_reg: SS: new_value == 0"));
				exception(BX_GP_EXCEPTION, 0, 0);
				return;
			}

			index = new_value >> 3;
			ti = (new_value >> 2) & 0x01;
			rpl = (new_value & 0x03);
			/* examine AR byte of destination selector for legal values: */

			if (ti == 0)
			{ /* GDT */
				if ((index*8 + 7) > BX_CPU_THIS_PTR gdtr.limit)
				{
					BX_PANIC(("load_seg_reg: GDT: %s: index(%04x*8+7) > limit(%06x)",
					BX_CPU_THIS_PTR strseg(seg), (unsigned) index, (unsigned) BX_CPU_THIS_PTR gdtr.limit));
					exception(BX_GP_EXCEPTION, new_value & 0xfffc, 0);
					return;
				}

				BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR gdtr.base + index*8,     4, 0,
					BX_READ, &dword1);
				BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR gdtr.base + index*8 + 4, 4, 0,
					BX_READ, &dword2);
			}
			else
			{ /* LDT */
				if (BX_CPU_THIS_PTR ldtr.cache.valid==0)
				{ /* ??? */
					BX_ERROR(("load_seg_reg: LDT invalid"));
					exception(BX_GP_EXCEPTION, new_value & 0xfffc, 0);
					return;
				}
				if ((index*8 + 7) > BX_CPU_THIS_PTR ldtr.cache.u.ldt.limit)
				{
					BX_ERROR(("load_seg_reg ss: LDT: index > limit"));
					exception(BX_GP_EXCEPTION, new_value & 0xfffc, 0);
					return;
				}

				BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR ldtr.cache.u.ldt.base + index*8,     4, 0,
					BX_READ, &dword1);
				BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR ldtr.cache.u.ldt.base + index*8 + 4, 4, 0,
					BX_READ, &dword2);
			}

			/* selector's RPL must = CPL, else #GP(selector) */
			if (rpl != CPL)
			{
				BX_ERROR(("load_seg_reg(): rpl != CPL"));
				exception(BX_GP_EXCEPTION, new_value & 0xfffc, 0);
				return;
			}

			parse_descriptor(dword1, dword2, &descriptor);

			/* AR byte must indicate a writable data segment else #GP(selector) */
			if (AR_BYTE_READWRITE[descriptor.AR_byte&0x1f]==0)
			{
				BX_ERROR(("load_seg_reg(): not writable data segment"));
				exception(BX_GP_EXCEPTION, new_value & 0xfffc, 0);
				return ;
			}

			/* DPL in the AR byte must equal CPL else #GP(selector) */
			if (descriptor.dpl != CPL)
			{
				BX_ERROR(("load_seg_reg(): dpl != CPL"));
				exception(BX_GP_EXCEPTION, new_value & 0xfffc, 0);
			}

			/* segment must be marked PRESENT else #SS(selector) */
			if (descriptor.p == 0)
			{
				BX_ERROR(("load_seg_reg(): not present"));
				exception(BX_SS_EXCEPTION, new_value & 0xfffc, 0);
			}	

			/* load SS with selector, load SS cache with descriptor */
			BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.value        = new_value;
			BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.index        = index;
			BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.ti           = ti;
			BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.rpl          = rpl;
			BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache = descriptor;
			BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.valid           = 1;

			/* now set accessed bit in descriptor */
			dword2 |= 0x0100;
			if (ti == 0)
			{ /* GDT */
				BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR gdtr.base + index*8 + 4, 4, 0,
					BX_WRITE, &dword2);
			}
			else
			{ /* LDT */
				BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR ldtr.cache.u.ldt.base + index*8 + 4, 4, 0,
					BX_WRITE, &dword2);
			}
			return;
		}
		else
		{
			Bit16u index;
			Bit8u ti;
			Bit8u rpl;
			bx_descriptor_t descriptor;
			Bit32u dword1, dword2;

			if ((new_value & 0xfffc) == 0)
			{ /* null selector */
				seg->selector.index = 0;
				seg->selector.ti = 0;
				seg->selector.rpl = 0;
				seg->selector.value = 0;
				seg->cache.valid = 0; /* invalidate null selector */
				return;
			}

			index = new_value >> 3;
			ti = (new_value >> 2) & 0x01;
			rpl = (new_value & 0x03);

			/* selector index must be within descriptor limits, else #GP(selector) */

			if (ti == 0)
			{ /* GDT */
				if ((index*8 + 7) > BX_CPU_THIS_PTR gdtr.limit)
				{
					BX_ERROR(("load_seg_reg: GDT: %s: index(%04x) > limit(%06x)",
					BX_CPU_THIS_PTR strseg(seg), (unsigned) index, (unsigned) BX_CPU_THIS_PTR gdtr.limit));
					exception(BX_GP_EXCEPTION, new_value & 0xfffc, 0);
					return;
				}

				BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR gdtr.base + index*8,     4, 0,
					BX_READ, &dword1);
				BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR gdtr.base + index*8 + 4, 4, 0,
					BX_READ, &dword2);
			}
			else
			{ /* LDT */
				if (BX_CPU_THIS_PTR ldtr.cache.valid==0)
				{
					BX_ERROR(("load_seg_reg: LDT invalid"));
					exception(BX_GP_EXCEPTION, new_value & 0xfffc, 0);
					return;
				}

				if ((index*8 + 7) > BX_CPU_THIS_PTR ldtr.cache.u.ldt.limit)
				{
					BX_ERROR(("load_seg_reg ds,es: LDT: index > limit"));
					exception(BX_GP_EXCEPTION, new_value & 0xfffc, 0);
					return;
				}

				BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR ldtr.cache.u.ldt.base + index*8,     4, 0,
					BX_READ, &dword1);
				BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR ldtr.cache.u.ldt.base + index*8 + 4, 4, 0,
					BX_READ, &dword2);
			}

			parse_descriptor(dword1, dword2, &descriptor);

			/* AR byte must indicate data or readable code segment else #GP(selector) */
			if (AR_BYTE_READ[descriptor.AR_byte&0x1f]==0)
			{
				BX_ERROR(("load_seg_reg(): not data or readable code"));
				exception(BX_GP_EXCEPTION, new_value & 0xfffc, 0);
				return;
			}

			/* If data or non-conforming code, then both the RPL and the CPL
			 * must be less than or equal to DPL in AR byte else #GP(selector) */
			if ((descriptor.AR_byte&0x0c)!=0x0c)
			{
				if ((rpl > descriptor.dpl) || (CPL > descriptor.dpl))
				{
					BX_ERROR(("load_seg_reg: RPL & CPL must be <= DPL"));
					exception(BX_GP_EXCEPTION, new_value & 0xfffc, 0);
					return;
				}
			}

			/* segment must be marked PRESENT else #NP(selector) */
			if (descriptor.p == 0)
			{
				BX_ERROR(("load_seg_reg: segment not present"));
				exception(BX_NP_EXCEPTION, new_value & 0xfffc, 0);
				return;
			}

			/* load segment register with selector */
			/* load segment register-cache with descriptor */
			seg->selector.value        = new_value;
			seg->selector.index        = index;
			seg->selector.ti           = ti;
			seg->selector.rpl          = rpl;
			seg->cache = descriptor;
			seg->cache.valid             = 1;

			/* now set accessed bit in descriptor                   */
			/* wmr: don't bother if it's already set (thus allowing */ 
			/* GDT to be in read-only pages like real hdwe does)    */

			if (!(dword2 & 0x0100))
			{
				dword2 |= 0x0100;
				if (ti == 0)
				{ /* GDT */
					BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR gdtr.base + index*8 + 4, 4, 0,
						BX_WRITE, &dword2);
				}
				else
				{ /* LDT */
					BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR ldtr.cache.u.ldt.base + index*8 + 4, 4, 0,
						BX_WRITE, &dword2);
				}
			}
			return;
		}
    }
	else
	{
		// real mode and vm86 mode
		// seg->limit = ; ??? different behaviours depening on seg reg.
		// something about honoring previous values

		// ??? don't need to set all these fields
		if (seg == &BX_CPU_THIS_PTR program_visible_sregs[BX_SREG_CS])
		{
			seg->cache.AR_byte = 0x93;
			seg->cache.type = 3;
			seg->cache.u.segment.c_ed = 0;
		}

		seg->selector.value = new_value;
		seg->cache.u.segment.base = new_value << 4;
	}

#else /* 8086 */

	seg->selector.value = new_value;
	seg->cache.u.segment.base = new_value << 4;

#endif
#if BX_SupportICache
  BX_CPU_THIS_PTR iCache.fetchModeMask =
      BX_CPU_THIS_PTR iCache.createFetchModeMask(BX_CPU_THIS);
#endif
}

#if BX_CPU_LEVEL >= 2
	void
BX_CPU_C::parse_selector(Bit16u raw_selector, bx_selector_t *selector)
{
	selector->value  = raw_selector;
	selector->index  = raw_selector >> 3;
	selector->ti     = (raw_selector >> 2) & 0x01;
	selector->rpl    = raw_selector & 0x03;
}
#endif

	void
BX_CPU_C::parse_descriptor(Bit32u dword1, Bit32u dword2, bx_descriptor_t *temp)
{
	Bit8u AR_byte;

	temp->AR_byte  = dword2 >> 8;
	AR_byte        = dword2 >> 8;
	temp->p        = (AR_byte >> 7) & 0x01;
	temp->dpl      = (AR_byte >> 5) & 0x03;
	temp->segment  = (AR_byte >> 4) & 0x01;
	temp->type     = (AR_byte & 0x0f);
	temp->valid    = 0; /* start out invalid */

	if (temp->segment)
	{ /* data/code segment descriptors */
		temp->u.segment.executable = (AR_byte >> 3) & 0x01;
		temp->u.segment.c_ed       = (AR_byte >> 2) & 0x01;
		temp->u.segment.r_w        = (AR_byte >> 1) & 0x01;
		temp->u.segment.a          = (AR_byte >> 0) & 0x01;
		temp->u.segment.limit      = (dword1 & 0xffff);
	    temp->u.segment.base       = (dword1 >> 16) |
										((dword2 & 0xFF) << 16);

#if BX_CPU_LEVEL >= 3
		temp->u.segment.limit        |= (dword2 & 0x000F0000);
		temp->u.segment.g            =  (dword2 & 0x00800000) > 0;
		temp->u.segment.d_b          =  (dword2 & 0x00400000) > 0;
		temp->u.segment.avl          =  (dword2 & 0x00100000) > 0;
		temp->u.segment.base         |= (dword2 & 0xFF000000);

		if (temp->u.segment.g)
		{
			if ( (temp->u.segment.executable==0) && (temp->u.segment.c_ed) )
				temp->u.segment.limit_scaled = (temp->u.segment.limit << 12);
			else
				temp->u.segment.limit_scaled = (temp->u.segment.limit << 12) | 0x0fff;
		}
		else
#endif
			temp->u.segment.limit_scaled = temp->u.segment.limit;
	    temp->valid    = 1;
	}
	else
	{	// system & gate segment descriptors
		switch ( temp->type )
		{
		case  0: // reserved
		case  8: // reserved
		case 10: // reserved
		case 13: // reserved
			temp->valid    = 0;
			break;
		case 1: // 286 TSS (available)
		case 3: // 286 TSS (busy)
			temp->u.tss286.base  = (dword1 >> 16) |
				((dword2 & 0xff) << 16);
			temp->u.tss286.limit = (dword1 & 0xffff);
			temp->valid    = 1;
	        break;

		case 2: // LDT descriptor
			temp->u.ldt.base = (dword1 >> 16) |
                           ((dword2 & 0xFF) << 16);
#if BX_CPU_LEVEL >= 3
			temp->u.ldt.base |= (dword2 & 0xff000000);
#endif
			temp->u.ldt.limit = (dword1 & 0xffff);
			temp->valid    = 1;
			break;
		case 4: // 286 call gate
		case 6: // 286 interrupt gate
		case 7: // 286 trap gate
			/* word count only used for call gate */
			temp->u.gate286.word_count = dword2 & 0x1f;
			temp->u.gate286.dest_selector = dword1 >> 16;;
			temp->u.gate286.dest_offset   = dword1 & 0xffff;
			temp->valid = 1;
			break;
		case 5: // 286/386 task gate
			temp->u.taskgate.tss_selector = dword1 >> 16;;
			temp->valid = 1;
			break;

#if BX_CPU_LEVEL >= 3
		case 9:  // 386 TSS (available)
		case 11: // 386 TSS (busy)
	        temp->u.tss386.base  = (dword1 >> 16) |
                               ((dword2 & 0xff) << 16) |
                               (dword2 & 0xff000000);
	        temp->u.tss386.limit = (dword1 & 0x0000ffff) |
		                           (dword2 & 0x000f0000);
			temp->u.tss386.g     = (dword2 & 0x00800000) > 0;
			temp->u.tss386.avl   = (dword2 & 0x00100000) > 0;
			if (temp->u.tss386.g)
				temp->u.tss386.limit_scaled = (temp->u.tss386.limit << 12) | 0x0fff;
			else
				temp->u.tss386.limit_scaled = temp->u.tss386.limit;
			temp->valid = 1;
			break;

		case 12: // 386 call gate
		case 14: // 386 interrupt gate
		case 15: // 386 trap gate
        // word count only used for call gate
			temp->u.gate386.dword_count   = dword2 & 0x1f;
			temp->u.gate386.dest_selector = dword1 >> 16;;
			temp->u.gate386.dest_offset   = (dword2 & 0xffff0000) |
				                            (dword1 & 0x0000ffff);
			temp->valid = 1;
			break;
#endif
		default: BX_PANIC(("parse_descriptor(): case %d unfinished",
                 (unsigned) temp->type));
			temp->valid    = 0;
		}
	}
}

  void
BX_CPU_C::load_ldtr(bx_selector_t *selector, bx_descriptor_t *descriptor)
{
	/* check for null selector, if so invalidate LDTR */
	if ( (selector->value & 0xfffc)==0 )
	{
		BX_CPU_THIS_PTR ldtr.selector = *selector;
		BX_CPU_THIS_PTR ldtr.cache.valid = 0;
		return;
    }

	if (!descriptor)
		BX_PANIC(("load_ldtr(): descriptor == NULL!"));

	BX_CPU_THIS_PTR ldtr.cache = *descriptor; /* whole structure copy */
	BX_CPU_THIS_PTR ldtr.selector = *selector;

	if (BX_CPU_THIS_PTR ldtr.cache.u.ldt.limit < 7)
	{
		BX_PANIC(("load_ldtr(): ldtr.limit < 7"));
    }

	BX_CPU_THIS_PTR ldtr.cache.valid = 1;
}

	void
BX_CPU_C::load_cs(bx_selector_t *selector, bx_descriptor_t *descriptor,
           Bit8u cpl)
{
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector     = *selector;
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache        = *descriptor;

	/* caller may request different CPL then in selector */
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.rpl = cpl;
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].cache.valid = 1; /* ??? */
	// (BW) Added cpl to the selector value.

	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value =
	    (0xfffc & BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.value) | cpl;

	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_CS].selector.cpl__3 = (cpl==3);
#if BX_SupportICache
  BX_CPU_THIS_PTR iCache.fetchModeMask =
      BX_CPU_THIS_PTR iCache.createFetchModeMask(BX_CPU_THIS);
#endif
}

	void
BX_CPU_C::load_ss(bx_selector_t *selector, bx_descriptor_t *descriptor, Bit8u cpl)
{
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].selector = *selector;
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache = *descriptor;
	BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.rpl = cpl;

	if ( (BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].selector.value & 0xfffc) == 0 )
		BX_PANIC(("load_ss(): null selector passed"));

	if ( !BX_CPU_THIS_PTR program_visible_sregs[BX_SEG_REG_SS].cache.valid )
	{
		BX_PANIC(("load_ss(): invalid selector/descriptor passed."));
	}
}



#if BX_CPU_LEVEL >= 2
	void
BX_CPU_C::fetch_raw_descriptor(bx_selector_t *selector,
                        Bit32u *dword1, Bit32u *dword2, Bit8u exception_no)
{
	if (selector->ti == 0)
	{ /* GDT */
		if ((selector->index*8 + 7) > BX_CPU_THIS_PTR gdtr.limit)
		{
BX_INFO(("-----------------------------------"));
BX_INFO(("selector->index*8 + 7 = %u", (unsigned) selector->index*8 + 7));
BX_INFO(("gdtr.limit = %u", (unsigned) BX_CPU_THIS_PTR gdtr.limit));
BX_INFO(("fetch_raw_descriptor: GDT: index > limit"));
debug(BX_CPU_THIS_PTR prev_eip);
BX_INFO(("-----------------------------------"));
			exception(exception_no, selector->value & 0xfffc, 0);
			return;
		}

		BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR gdtr.base + selector->index*8,     4, 0,
			BX_READ, dword1);
		BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR gdtr.base + selector->index*8 + 4, 4, 0,
			BX_READ, dword2);
    }
	else
	{ /* LDT */
		if (BX_CPU_THIS_PTR ldtr.cache.valid==0)
		{
			BX_PANIC(("fetch_raw_descriptor: LDTR.valid=0"));
			exception(exception_no, selector->value & 0xfffc, 0);
			return;
		}
		if ((selector->index*8 + 7) > BX_CPU_THIS_PTR ldtr.cache.u.ldt.limit)
		{
			BX_PANIC(("fetch_raw_descriptor: LDT: index > limit"));
			exception(exception_no, selector->value & 0xfffc, 0);
			return;
		}
		BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR ldtr.cache.u.ldt.base + selector->index*8,     4, 0,
			BX_READ, dword1);
		BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR ldtr.cache.u.ldt.base + selector->index*8 + 4, 4, 0,
			BX_READ, dword2);
    }
}
#endif

	Boolean
BX_CPU_C::fetch_raw_descriptor2(bx_selector_t *selector,
                        Bit32u *dword1, Bit32u *dword2)
{
	if (selector->ti == 0)
	{ /* GDT */
		if ((selector->index*8 + 7) > BX_CPU_THIS_PTR gdtr.limit)
			return(0);
		BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR gdtr.base + selector->index*8,     4, 0,
			BX_READ, dword1);
		BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR gdtr.base + selector->index*8 + 4, 4, 0,
			BX_READ, dword2);
		return(1);
	}
	else
	{ /* LDT */
		if (BX_CPU_THIS_PTR ldtr.cache.valid==0)
			return(0);
		if ((selector->index*8 + 7) > BX_CPU_THIS_PTR ldtr.cache.u.ldt.limit)
			return(0);
		BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR ldtr.cache.u.ldt.base + selector->index*8,     4, 0,
			BX_READ, dword1);
		BX_CPU_THIS_PTR access_linear(BX_CPU_THIS_PTR ldtr.cache.u.ldt.base + selector->index*8 + 4, 4, 0,
			BX_READ, dword2);
		return(1);
    }
}
