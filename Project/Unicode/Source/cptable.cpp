/*
 * Codepage tables
 *
 * Copyright 2000 Alexandre Julliard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include "StdAfx.h"
//#include <stdlib.h>

#include "unicode.h"

/* Everything below this line is generated automatically by cpmap.pl */
/* ### cpmap begin ### */


static const union cptable * const cptables[60] =
{
    (const union cptable *)&cptable_037,
    (const union cptable *)&cptable_042,
    (const union cptable *)&cptable_424,
    (const union cptable *)&cptable_437,
    (const union cptable *)&cptable_500,
    (const union cptable *)&cptable_737,
    (const union cptable *)&cptable_775,
    (const union cptable *)&cptable_850,
    (const union cptable *)&cptable_852,
    (const union cptable *)&cptable_855,
    (const union cptable *)&cptable_856,
    (const union cptable *)&cptable_857,
    (const union cptable *)&cptable_860,
    (const union cptable *)&cptable_861,
    (const union cptable *)&cptable_862,
    (const union cptable *)&cptable_863,
    (const union cptable *)&cptable_864,
    (const union cptable *)&cptable_865,
    (const union cptable *)&cptable_866,
    (const union cptable *)&cptable_869,
    (const union cptable *)&cptable_874,
    (const union cptable *)&cptable_875,
    (const union cptable *)&cptable_878,
    (const union cptable *)&cptable_932,
    (const union cptable *)&cptable_936,
    (const union cptable *)&cptable_949,
    (const union cptable *)&cptable_950,
    (const union cptable *)&cptable_1006,
    (const union cptable *)&cptable_1026,
    (const union cptable *)&cptable_1250,
    (const union cptable *)&cptable_1251,
    (const union cptable *)&cptable_1252,
    (const union cptable *)&cptable_1253,
    (const union cptable *)&cptable_1254,
    (const union cptable *)&cptable_1255,
    (const union cptable *)&cptable_1256,
    (const union cptable *)&cptable_1257,
    (const union cptable *)&cptable_1258,
    (const union cptable *)&cptable_10000,
    (const union cptable *)&cptable_10006,
    (const union cptable *)&cptable_10007,
    (const union cptable *)&cptable_10029,
    (const union cptable *)&cptable_10079,
    (const union cptable *)&cptable_10081,
    (const union cptable *)&cptable_20866,
    (const union cptable *)&cptable_20932,
    (const union cptable *)&cptable_28591,
    (const union cptable *)&cptable_28592,
    (const union cptable *)&cptable_28593,
    (const union cptable *)&cptable_28594,
    (const union cptable *)&cptable_28595,
    (const union cptable *)&cptable_28596,
    (const union cptable *)&cptable_28597,
    (const union cptable *)&cptable_28598,
    (const union cptable *)&cptable_28599,
    (const union cptable *)&cptable_28600,
    (const union cptable *)&cptable_28603,
    (const union cptable *)&cptable_28604,
    (const union cptable *)&cptable_28605,
    (const union cptable *)&cptable_28606,
};
/* ### cpmap end ### */
/* Everything above this line is generated automatically by cpmap.pl */

#define NB_CODEPAGES  (sizeof(cptables)/sizeof(cptables[0]))


static int __cdecl cmp_codepage( unsigned int codepage, const void *entry )
{
    return (unsigned int)codepage - (*(union cptable **)entry)->info.codepage;
}


/* get the table of a given code page */
const union cptable *cp_get_table( unsigned int codepage )
{
	int i = 0;
    //const union cptable **res;
	
	for(;i<NB_CODEPAGES;i++)
	{
		if(cptables[i]->info.codepage == codepage)
			return cptables[i];
	}
	return NULL;
	/*
    if (!(res = (const union cptable **)bsearch( (void *)codepage, cptables, NB_CODEPAGES,
                         sizeof(cptables[0]), cmp_codepage ))) return NULL;
						 
    return *res;*/
}


/* enum valid codepages */
const union cptable *cp_enum_table( unsigned int index )
{
    if (index >= NB_CODEPAGES) return NULL;
    return cptables[index];
}
