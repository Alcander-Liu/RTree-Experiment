
/*-----------------------------------------------------------------------------
| Definitions and global variables used in linear split code.
-----------------------------------------------------------------------------*/

#ifndef	lint
	static	char	SplitSccsid[] = "%W% %G%";
#endif	lint

#define METHODS 1

#ifdef GRAPHICS
/* optional definition of SHOWSPLIT here */
#	define SHOWSPLIT
#endif

struct Branch BranchBuf[NODECARD+1];
struct Rect CoverSplit;

/* variables for finding a partition */
struct PartitionVars
{
	int partition[NODECARD+1];
	int taken[NODECARD+1];
	int count[2];
	struct Rect cover[2];
	int area[2];
} Partitions[METHODS];
