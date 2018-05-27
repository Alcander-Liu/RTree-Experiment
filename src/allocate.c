
#include "options.h"
#include "assert.h"
#include <stdio.h>
#include "macros.h"
#include "index.h"

# ifndef	lint
	static	char	allocSccsid[] = "%W% %G%";
# endif	lint

# define ALLOCSIZE (1024 * 1024) /* one meg */

/*-----------------------------------------------------------------------------
| Space allocation routines.
| Very primitive, for speed.  Freed space is not reclaimed.
| Call myalloc() like malloc().
| Call myfree() like free().  Should not really be called; change free() call
| to null statement by using #define.
-----------------------------------------------------------------------------*/

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *
myalloc(n)
register int n;
{
	if (allocp + n <= allocbuf + ALLOCSIZE)
	{
		allocp += n;
		return (allocp - n);
	}
	else
		error("out of space in myalloc");
}

myfree(p)
{
}
