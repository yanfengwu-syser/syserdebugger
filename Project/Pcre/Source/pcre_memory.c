#include "stdafx.h"
#include "pcre_internal.h"
 void pcre_set_function_pointer(void* alloc,void* free)
{
	pcre_malloc = alloc;
	pcre_stack_malloc = alloc;
	pcre_free = free;
	pcre_stack_free = free;
	pcre_callout = NULL;
	
}