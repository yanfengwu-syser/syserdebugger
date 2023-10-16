#include "StdAfx.h"
#include "Compress.h"

NAME_SPACE_BEGIN
typedef	unsigned char	BIT8;
typedef	unsigned int	BIT32;

long do_compress(void*in,long in_len,void*out,long*out_len,BIT8**work_mem)
{
	BIT8 *ip,*op,*in_end,*ip_end,*ii,*m_pos,*end,*m;
	BIT32 m_off,m_len,dindex,t,tt;

	in_end = (BIT8*)in + in_len;
	ip_end = (BIT8*)in + in_len - 13;
	op = (BIT8*)out;
	ip = (BIT8*)in;
	ii = ip;
	ip += 4;
	for(;;)
	{
		dindex = ((0x21*(((((((BIT32)(ip[3])<<6)^ip[2])<<5)^ip[1])<<5)^ip[0]))>>5) & 0x3FFF;
		m_pos = work_mem [dindex];
		if( m_pos < in ||  (m_off = (BIT32)(ip-m_pos)) <= 0 || m_off > 0xBFFF)
			goto literal;
		if(m_off <= 0x0800 || m_pos[3] == ip[3])
			goto try_match;
		dindex = (dindex & 0x7FF ) ^ 0x201F;
		m_pos = work_mem[dindex];
		if(	m_pos <in|| (m_off = (BIT32)(ip-m_pos)) <= 0 || m_off > 0xBFFF)
			goto literal;
		if (m_off <= 0x0800 || m_pos[3] == ip[3])
			goto try_match;
		goto literal;
try_match:
		if(m_pos[0] == ip[0] && m_pos[1] == ip[1] && m_pos[2]==ip[2])
			goto match;
literal:
		work_mem[dindex] = ip;
		if(++ip >= ip_end)
			break;
		continue;
match:
		work_mem[dindex] = ip;
		if(ip - ii > 0)
		{
			t = (BIT32)(ip - ii);
			if (t <= 3)
				op[-2] |= (BIT8)t;
			else if(t <= 18)
				*op++ = (BIT8)(t - 3);
			else
			{
				tt = t - 18;
				*op++ = 0;
				while(tt > 255)
				{
					tt -= 255;
					*op++ = 0;
				}
				*op++ = (BIT8)tt;
			}
			do *op++ = *ii++; while (--t > 0);
		}
		ip += 3;
		if(	m_pos[3] != *ip++ || m_pos[4] != *ip++ || m_pos[5] != *ip++ ||
			m_pos[6] != *ip++ || m_pos[7] != *ip++ || m_pos[8] != *ip++ )
		{
			m_len = (BIT32)(--ip - ii);
			if(m_off <= 0x0800 )
			{
				--m_off;
				*op++ = (BIT8)(((m_len - 1) << 5) | ((m_off & 7) << 2));
				*op++ = (BIT8)(m_off >> 3);
			}
			else
				if (m_off <= 0x4000 )
				{
					m_off--;
					*op++ = (BIT8)(32 | (m_len - 2));
					goto m3_m4_offset;
				}
				else
				{
					m_off -= 0x4000;
					*op++ = (BIT8)(16 | ((m_off & 0x4000) >> 11) | (m_len - 2));
					goto m3_m4_offset;
				}
		}
		else
		{
			end = in_end;
			m = m_pos + 9;
			while (ip < end && *m == *ip)
			{
				m++;
				ip++;
			}
			m_len = (BIT32)(ip - ii);

			if(m_off <= 0x4000)
			{
				m_off--;
				if (m_len <= 33)
					*op++ = (BIT8)(32 | (m_len - 2));
				else
				{
					m_len -= 33;
					*op++=32;
					goto m3_m4_len;
				}
			}
			else
			{
				m_off -= 0x4000;
				if(m_len <= 9)
					*op++ = (BIT8)(16|((m_off & 0x4000) >> 11) | (m_len - 2));
				else
				{
					m_len -= 9;
					*op++ = (BIT8)(16 | ((m_off & 0x4000) >> 11));
m3_m4_len:
					while (m_len > 255)
					{
						m_len -= 255;
						*op++ = 0;
					}
					*op++ = (BIT8)m_len;
				}
			}
m3_m4_offset:
			*op++ = (BIT8)((m_off & 63) << 2);
			*op++ = (BIT8)(m_off >> 6);
		}
		ii = ip;
		if (ip >= ip_end)
			break;
	}
	*out_len = (long)(op - (BIT8*)out);
	return (long) (in_end - ii);
}

long Compress(void *in, long in_len,void *out)
{
	long out_len;
    BIT8 *op,*ii;
	BIT32 t,tt;
	BIT8*work_mem[0x4000];
    op = &((BIT8*)out)[4];
    if (in_len <= 13)
	{
		t = in_len;
	}
    else 
	{
		t = do_compress ((BIT8*)in,in_len,op,&out_len,work_mem);
		op += out_len;
    }
    if (t > 0)
	{
		ii = (BIT8*)in + in_len - t;
		if (op == &((BIT8*)out)[4] && t <= 238)
			*op++ = (BIT8) ( 17 + t );
		else
			if (t <= 3)
				op[-2] |= (BIT8)t ;
			else
				if (t <= 18)
					*op++ = (BIT8)(t-3);
				else
				{
					tt = t - 18;
					*op++ = 0;
					while (tt > 255) 
					{
						tt -= 255;
						*op++ = 0;
					}
					*op++ = (BIT8)tt;
				}
				do *op++ = *ii++; while (--t > 0);
    }
    *op++ = 17;
    *op++ = 0;
    *op++ = 0;
	*(long*)out = in_len;
    return (long)(op - (BIT8*)out);
}

long Decompress(void *in, long in_len,void *out)
{
    BIT32 t;
    BIT8 *op,*ip,*m_pos,*ip_end;
    
	ip_end = &((BIT8*)in)[4] + in_len;
    op = (BIT8*)out;
    ip = &((BIT8*)in)[4];
    if(*ip > 17)
	{
		t = *ip++ - 17;
		if (t < 4)
			goto match_next;
		do *op++ = *ip++; while (--t > 0);
		goto first_literal_run;
    }
    for(;;)
	{
		t = *ip++;
		if (t >= 16) goto match;
		if (t == 0)
		{
			while (*ip == 0)
			{
				t += 255;
				ip++;
			}
			t += 15 + *ip++;
		}
		op[0]=ip[0];
		op[1]=ip[1];
		op[2]=ip[2];
		op[3]=ip[3];
		op += 4; ip += 4;
		if(--t > 0)
		{
			if (t >= 4)
			{
				do
				{
					op[0]=ip[0];
					op[1]=ip[1];
					op[2]=ip[2];
					op[3]=ip[3];
					op += 4; ip += 4; t -= 4;
				} while (t >= 4);
				if (t > 0) do *op++ = *ip++; while (--t > 0);
			}
			else
				do *op++ = *ip++; while (--t > 0);
		}
first_literal_run:
		t = *ip++;
		if (t >= 16)
			goto match;
		m_pos = op - 0x0801;
		m_pos -= t >> 2;
		m_pos -= *ip++ << 2;
		*op++ = *m_pos++; 
		*op++ = *m_pos++; 
		*op++ = *m_pos;
		goto match_done;
		for(;;)
		{
match:
		if (t >= 64)
		{
			m_pos = op - 1;
			m_pos -= (t >> 2) & 7;
			m_pos -= *ip++ << 3;
			t = (t >> 5) - 1;
			goto copy_match;
		}
		else 
			if (t >= 32)
			{
				t &= 31;
				if (t == 0)	
				{
					while (*ip == 0) 
					{
						t += 255;
						ip++;
					}
					t += 31 + *ip++;
				}
				m_pos = op - 1;
				m_pos -= (ip[0]+(ip[1]<<8)) >> 2;
				ip += 2;
			}
			else
				if (t >= 16) 
				{
					m_pos = op;
					m_pos -= (t & 8) << 11;
					t &= 7;
					if (t == 0)
					{
						while (*ip == 0)
						{
							t += 255;
							ip++;
						}
						t += 7 + *ip++;
					}
					m_pos -= (ip[0]+(ip[1]<<8)) >> 2;
					ip += 2;
					if (m_pos == op)
						goto eof_found;
					m_pos -= 0x4000;
				}
				else 
				{
					m_pos = op - 1;
					m_pos -= t >> 2;
					m_pos -= *ip++ << 2;
					*op++ = *m_pos++; *op++ = *m_pos;
					goto match_done;
				}
				if (t >= 6 && (op - m_pos) >= 4) 
				{
					op[0]=m_pos[0];
					op[1]=m_pos[1];
					op[2]=m_pos[2];
					op[3]=m_pos[3];
					op += 4; m_pos += 4; t -= 2;
					do
					{
						op[0]=m_pos[0];
						op[1]=m_pos[1];
						op[2]=m_pos[2];
						op[3]=m_pos[3];
						op += 4; m_pos += 4; t -= 4;
					}while (t >= 4);
					if (t > 0)
						do *op++ = *m_pos++; while (--t > 0);
				}
				else
				{
copy_match:
				*op++ = *m_pos++; *op++ = *m_pos++;
				do *op++ = *m_pos++; while (--t > 0);
				}
match_done:
				t = ip[-2] & 3;
				if (t == 0)	break;
match_next:
				do *op++ = *ip++; while (--t > 0);
				t = *ip++;
		}
   }
eof_found:
   return (long)(op - (BIT8*)out);
}

long GetDecompressLength(void *in)
{
	return *(long*)in;
}

NAME_SPACE_END

