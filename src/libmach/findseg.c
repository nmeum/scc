#include <stdio.h>
#include <string.h>

#include <scc/mach.h>

#include "libmach.h"

int
findseg(Map *map, unsigned long long addr)
{
	int i;
	Mapsec *seg;

	for (i = 0; i < map->nseg; ++i) {
		seg = &map->seg[i];
		if (seg->used && seg->sec.base == addr)
			return i;
	}

	return -1;
}
