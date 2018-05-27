
#include "options.h"
#include <stdio.h>
#include "assert.h"
#include "macros.h"
#include "index.h"
#include "split.l.h"

# ifndef	lint
	static	char	splitlSccsid[] = "%W% %G%";
# endif	lint

#ifdef GRAPHICS
#	define UNIX
#	include "/jb/ingres/toni/cad/lib/mfb.h"
#endif


/*-----------------------------------------------------------------------------
| Split a node.
| Divides the nodes branches and the extra one between two nodes.
| Old node is one of the new ones, and one really new one is created.
-----------------------------------------------------------------------------*/
SplitNode(n, b, nn)
register struct Node *n;
register struct Branch *b;
register struct Node **nn;
{
	struct Node *NewNode();
	register struct PartitionVars *p;
	register int i, area, level;

	assert(n);
	assert(b);

#	ifdef PRINT
		printf("Splitting:\n");
		PrintNode(n);
		PrintBranch(b);
#	endif

	if (StatFlag)
	{
		if (Deleting)
			DeSplitCount++;
		else
			InSplitCount++;
	}

	/* load all the branches into a buffer, initialize old node */
	level = n->level;
	GetBranches(n, b);

#	ifdef SHOWSPLIT
		/* Indicate that a split is about to take place */
		MFBSetColor(RED);
		for (i=0; i<NODECARD+1; i++)
		{
			PrintRect(&BranchBuf[i].rect);
		}
		MFBSetColor(YELLOW);
		PrintRect(&CoverSplit);
		GraphChar();
#	endif

	/* find partition */
	p = &Partitions[0];
	MethodZero(p);

	/* print it */
#	ifdef PRINT
		PrintPVars(p);
#	endif

	/* record how good the split was for statistics */
	area = p->area[0] + p->area[1];
	if (StatFlag && !Deleting && area)
		SplitMeritSum += (float)RectArea(&CoverSplit) / area;

	/* put branches from buffer into 2 nodes according to chosen partition */
	*nn = NewNode();
	(*nn)->level = n->level = level;
	LoadNodes(n, *nn, p);
	assert(n->count + (*nn)->count == NODECARD+1);

#	ifdef PRINT
		printf("group 0:\n");
		PrintNode(n);
		printf("group 1:\n");
		PrintNode(*nn);
		printf("\n");
#	endif

#	ifdef SHOWSPLIT
		EraseRect(&CoverSplit);
#	endif
}

/*-----------------------------------------------------------------------------
| Load branch buffer with branches from full node plus the extra branch.
-----------------------------------------------------------------------------*/
GetBranches(n, b)
register struct Node *n;
register struct Branch *b;
{
	register int i;
	struct Rect CombineRect();

	assert(n);
	assert(b);

	/* load the branch buffer */
	for (i=0; i<NODECARD; i++)
	{
		assert(n->branch[i].child);  /* node should have every entry full */
		BranchBuf[i] = n->branch[i];
	}
	BranchBuf[NODECARD] = *b;

	/* calculate rect containing all in the set */
	CoverSplit = BranchBuf[0].rect;
	for (i=1; i<NODECARD+1; i++)
	{
		CoverSplit = CombineRect(&CoverSplit, &BranchBuf[i].rect);
	}

	InitNode(n);
}

/*-----------------------------------------------------------------------------
| Method 0 for finding a partition:
| First find two seeds, one for each group, well separated.
| Then put other rects in whichever group will be smallest after addition.
-----------------------------------------------------------------------------*/
MethodZero(p)
register struct PartitionVars *p;
{

#	ifdef SHOWSPLIT
		EraseData();
#	endif

	InitPVars(p);
	PickSeeds(p);
	Pigeonhole(p);

#	ifdef SHOWSPLIT
		/* erase the final cover boxes */
		EraseRect(&p->cover[0]);
		EraseRect(&p->cover[1]);
#	endif
}

/*-----------------------------------------------------------------------------
| Pick two rects from set to be the first elements of the two groups.
| Pick the two that are separated most along any dimension, or overlap least.
| Distance for separation or overlap is measured modulo the width of the
| space covered by the entire set along that dimension.
-----------------------------------------------------------------------------*/
PickSeeds(p)
register struct PartitionVars *p;
{
	register int i, dim, high;
	register struct Rect *r, *rlow, *rhigh;
	register float w, separation, bestSep;
	int width[NUMDIMS], leastUpper[NUMDIMS], greatestLower[NUMDIMS];
	int seed0, seed1;
	assert(p);
	
	for (dim=0; dim<NUMDIMS; dim++)
	{
		high = dim + NUMDIMS;

		/* find the rectangles farthest out in each direction along this dimens */
		greatestLower[dim] = leastUpper[dim] = 0;
		for (i=1; i<NODECARD+1; i++)
		{
			r = &BranchBuf[i].rect;
			if (r->boundary[dim]>BranchBuf[greatestLower[dim]].rect.boundary[dim])
				greatestLower[dim] = i;
			if (r->boundary[high]<BranchBuf[leastUpper[dim]].rect.boundary[high])
				leastUpper[dim] = i;
		}

		/* find the width of the whole collection along this dimension */
		width[dim] = CoverSplit.boundary[high] - CoverSplit.boundary[dim];
#		ifdef PRINT
			printf("width along %d is %d\n", dim, width[dim]);
#		endif
	}

	/* pick the best separation dimension and the two seed rects */
	for (dim=0; dim<NUMDIMS; dim++)
	{
		high = dim + NUMDIMS;

		/* divisor for normalizing by width */
		assert(width[dim] >= 0);
		if (width[dim] == 0)
			w = 1;
		else
			w = width[dim];

		rlow = &BranchBuf[leastUpper[dim]].rect;
		rhigh = &BranchBuf[greatestLower[dim]].rect;
		if (dim == 0)
		{
			seed0 = leastUpper[0];
			seed1 = greatestLower[0];
			separation = bestSep
				= (rhigh->boundary[0] - rlow->boundary[NUMDIMS]) / w;
		}
		else
		{
			separation = (rhigh->boundary[dim] - rlow->boundary[dim+NUMDIMS]) / w;
			if (separation > bestSep)
			{
				seed0 = leastUpper[dim];
				seed1 = greatestLower[dim];
				bestSep = separation;
			}
		}
#		ifdef PRINT
			printf("dimension %d leastUpper = %d with %d,  greatestLower = %d with %d\n",
				dim,
				leastUpper[dim],
				BranchBuf[leastUpper[dim]].rect.boundary[high],
				greatestLower[dim],
				BranchBuf[greatestLower[dim]].rect.boundary[dim]);
			printf("normalized separation %f, un-normalized %f\n",
				separation, w * separation);
#		endif
	}

#	ifdef PRINT
		printf("normalized separation = %f\n", bestSep);
		printf("seed0 = %d  seed1 = %d\n", seed0, seed1);
		PrintRect(&BranchBuf[seed0].rect);
		PrintRect(&BranchBuf[seed1].rect);
#	endif

	if (seed0 != seed1)
	{
		Classify(seed0, 0, p);
		Classify(seed1, 1, p);
	}
}

/*-----------------------------------------------------------------------------
| Put each rect that is not already in a group into a group.
| Process one rect at a time, using the following hierarchy of criteria.
| In case of a tie, go to the next test.
| 1) If one group already has the max number of elements that will allow
| the minimum fill for the other group, put r in the other.
| 2) Put r in the group whose cover will expand less.  This automatically
| takes care of the case where one group cover contains r.
| 3) Put r in the group whose cover will be smaller.  This takes care of the
| case where r is contained in both covers.
| 4) Put r in the group with fewer elements.
| 5) Put in group 1 (arbitrary).
|
| Also update the covers for both groups.
-----------------------------------------------------------------------------*/
Pigeonhole(p)
register struct PartitionVars *p;
{
	struct Rect CombineRect();
	struct Rect newCover[2];
	register int i, group;
	int newArea[2], increase[2];

	for (i=0; i<NODECARD+1; i++)
	{
		if (!p->taken[i])
		{
			/* if one group too full, put rect in the other regardless */
			if (p->count[0] >= NODECARD+1-MinFill)
			{
				Classify(i, 1, p);
				continue;
			}
			else if (p->count[1] >= NODECARD+1-MinFill)
			{
				Classify(i, 0, p);
				continue;
			}

			/* find the areas of the two groups' old and new covers */
			for (group=0; group<2; group++)
			{
				if (p->count[group]>0)
				{
					newCover[group]=CombineRect(&BranchBuf[i].rect,&p->cover[group]);
				}
				else
				{
					newCover[group] = BranchBuf[i].rect;
				}
				newArea[group] = RectArea(&newCover[group]);
				increase[group] = newArea[group] - p->area[group];
			}

			/* put rect in group whose cover will need to expand less */
			if (increase[0] < increase[1])
				Classify(i, 0, p);
			else if (increase[1] < increase[0])
				Classify(i, 1, p);

			/* put rect in group that will have a smaller area cover */
			else if (p->area[0] < p->area[1])
				Classify(i, 0, p);
			else if (p->area[1] < p->area[0])
				Classify(i, 1, p);

			/* put rect in group with fewer elements */
			else if (p->count[0] < p->count[1])
				Classify(i, 0, p);
			else
				Classify(i, 1, p);
		}
	}
	assert(p->count[0] + p->count[1] == NODECARD + 1);
}

/*-----------------------------------------------------------------------------
| Put a branch in one of the groups.
-----------------------------------------------------------------------------*/
Classify(i, group, p)
register int i, group;
register struct PartitionVars *p;
{
	struct Rect CombineRect();

	assert(p);
	assert(!p->taken[i]);

#	ifdef SHOWSPLIT
		/* erase old group cover if nec. */
		if (p->count[group] > 0)
			EraseRect(&p->cover[group]);
#	endif

	p->partition[i] = group;
	p->taken[i] = TRUE;

	if (p->count[group] == 0)
		p->cover[group] = BranchBuf[i].rect;
	else
		p->cover[group] = CombineRect(&BranchBuf[i].rect, &p->cover[group]);
	p->area[group] = RectArea(&p->cover[group]);
	p->count[group]++;

#	ifdef SHOWSPLIT
	{
		int j;
		MFBSetColor(group + 3); /* group 0 green, group 1 blue */
		for (j=0; j<NODECARD+1; j++)
		{
			if (p->taken[j] && p->partition[j]==group)
			PrintRect(&BranchBuf[j].rect);
		}
		MFBSetColor(WHITE); /* cover is white */
		PrintRect(&p->cover[group]);
		GraphChar();
	}
#	endif
}

/*-----------------------------------------------------------------------------
| Copy branches from the buffer into two nodes according to the partition.
-----------------------------------------------------------------------------*/
LoadNodes(n, q, p)
register struct Node *n, *q;
register struct PartitionVars *p;
{
	register int i;
	assert(n);
	assert(q);
	assert(p);

	for (i=0; i<NODECARD+1; i++)
	{
		if (p->partition[i] == 0)
			AddBranch(&BranchBuf[i], n, NULL);
		else if (p->partition[i] == 1)
			AddBranch(&BranchBuf[i], q, NULL);
		else
			assert(FALSE);
	}
}

/*-----------------------------------------------------------------------------
| Initialize a PartitionVars structure.
-----------------------------------------------------------------------------*/
InitPVars(p)
register struct PartitionVars *p;
{
	register int i;
	assert(p);

	p->count[0] = p->count[1] = 0;
	for (i=0; i<NODECARD+1; i++)
	{
		p->taken[i] = FALSE;
		p->partition[i] = -1;
	}
}

/*-----------------------------------------------------------------------------
| Print out data for a partition from PartitionVars struct.
-----------------------------------------------------------------------------*/
PrintPVars(p)
struct PartitionVars *p;
{
	int i;
	assert(p);

	printf("\npartition:\n");
	for (i=0; i<NODECARD+1; i++)
	{
		printf("%3d\t", i);
	}
	printf("\n");
	for (i=0; i<NODECARD+1; i++)
	{
		if (p->taken[i])
			printf("  t\t");
		else
			printf("\t");
	}
	printf("\n");
	for (i=0; i<NODECARD+1; i++)
	{
		printf("%3d\t", p->partition[i]);
	}
	printf("\n");

	printf("count[0] = %d  area = %d\n", p->count[0], p->area[0]);
	printf("count[1] = %d  area = %d\n", p->count[1], p->area[1]);
	printf("total area = %d  effectiveness = %3.2f\n",
		p->area[0] + p->area[1],
		(float)RectArea(&CoverSplit) / (p->area[0] + p->area[1]));

	printf("cover[0]:\n");
	PrintRect(&p->cover[0]);

	printf("cover[1]:\n");
	PrintRect(&p->cover[1]);
}

/*-----------------------------------------------------------------------------
| Erase all rects in the set to be split by drawing them black.  Graphics only.
-----------------------------------------------------------------------------*/
EraseData()
{
	int i;

	for (i=0; i<NODECARD+1; i++)
		EraseRect(&BranchBuf[i].rect);
}
