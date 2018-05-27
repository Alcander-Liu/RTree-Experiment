
#include "options.h"
#include <stdio.h>
#include "assert.h"
#include "macros.h"
#include "index.h"

# ifndef	lint
	static	char	nodeSccsid[] = "%W% %G%";
# endif	lint

#ifdef GRAPHICS
#	define UNIX
#	include "/jb/ingres/toni/cad/lib/mfb.h"
#endif

/* Make a new node and initialize to have all branch cells empty.
*/
struct Node *
NewNode()
{
	register struct Node *n;
	char *malloc();

	NodeCount++;
	n = (struct Node *) malloc (sizeof(struct Node));
	InitNode(n);
	return n;
}

FreeNode(p)
register struct Node *p;
{
	NodeCount--;
	if (p->level == 0)
		LeafCount--;
	else
		NonLeafCount--;
	free(p);
}

/* Initialize a Node structure.
*/
InitNode(n)
register struct Node *n;
{
	register int i;
	n->count = 0;
	n->level = -1;
	for (i = 0; i < NODECARD; i++)
		InitBranch(&(n->branch[i]));
}

/* Initialize one branch cell in a node.
*/
InitBranch(b)
register struct Branch *b;
{
	InitRect(&(b->rect));
	b->child = NULL;
}

/* Print out the data in a node.
*/
PrintNode(n)
struct Node *n;
{
	int i;
	assert(n);

#	ifdef PRINT
		printf("node");
		if (n->level == 0)
			printf(" LEAF");
		else if (n->level > 0)
			printf(" NONLEAF");
		else
			printf(" TYPE=?");
		printf("  level=%d  count=%d  address=%o\n", n->level, n->count, n);
	
		for (i=0; i<NODECARD; i++)
		{
			printf("branch %d\n", i);
			PrintBranch(&n->branch[i]);
		}
#	endif PRINT

#	ifdef GRAPHICS
		for (i=0; i<NODECARD; i++)
		{
			if (n->branch[i].child != NULL)
				PrintBranch(&n->branch[i]);
		}
#	endif GRAPHICS
}

PrintBranch(b)
struct Branch *b;
{
#		ifdef PRINTINDEX
			printf("  child %o  tid %d\n", b->child, (int)b->child);
#		endif

		PrintRect(&(b->rect));
}

/* Find the smallest rectangle that includes all rectangles in
** branches of a node.
*/
struct Rect
NodeCover(n)
register struct Node *n;
{
	register int i, flag;
	struct Rect r, CombineRect();
	assert(n);

	InitRect(&r);
	flag = 1;
	for (i = 0; i < NODECARD; i++)
		if (n->branch[i].child)
		{
			if (flag)
			{
				r = n->branch[i].rect;
				flag = 0;
			}
			else
				r = CombineRect(&r, &(n->branch[i].rect));
		}
	return r;
}

/* Pick a branch.  Pick the one that will need the smallest increase
** in area to accomodate the new rectangle.  This will result in the
** least total area for the covering rectangles in the current node.
** In case of a tie, pick the one which was smaller before, to get
** the best resolution when searching.
*/
int
PickBranch(r, n)
register struct Rect *r;
register struct Node *n;
{
	register struct Rect *rr;
	register int i, flag, increase, bestIncr, area, bestArea;
	int best;
	struct Rect CombineRect();
	assert(r && n);

	flag = 1;
	for (i=0; i<NODECARD; i++)
	{
		if (n->branch[i].child)
		{
			rr = &n->branch[i].rect;
			area = RectArea(rr);
			struct Rect tmpRect;
			tmpRect = CombineRect(r, rr);
			increase = RectArea(&tmpRect) - area;
			if (increase <  bestIncr || flag)
			{
				best = i;
				bestArea = area;
				bestIncr = increase;
				flag = 0;
			}
			else if (increase == bestIncr && area < bestArea)
			{
				best = i;
				bestArea = area;
				bestIncr = increase;
			}
#			ifdef PRINT
				printf("i=%d  area before=%d  area after=%d  increase=%d\n",
				i, area, area+increase, increase);
#			endif
		}
	}
#	ifdef PRINT
		printf("\tpicked %d\n", best);
#	endif
	return best;
}

/* Add a branch to a node.  Split the node if necessary.
** Returns 0 if node not split.  Old node updated.
** Returns 1 if node split, sets *new to address of new node.
** Old node updated, becomes one of two.
*/
int
AddBranch(b, n, new)
register struct Branch *b;
register struct Node *n;
register struct Node **new;
{
	register int i;

	assert(b);
	assert(n);

	if (n->count < NODECARD)  /* split won't be necessary */
	{
		for (i = 0; i < NODECARD; i++)  /* find empty branch */
		{
			if (n->branch[i].child == NULL)
			{
				n->branch[i] = *b;
				n->count++;
				break;
			}
		}
		assert(i<NODECARD);
		return 0;
	}
	else
	{
		if (StatFlag)
		{
			if (Deleting)
				DeTouchCount++;
			else
				InTouchCount++;
		}
		assert(new);
		SplitNode(n, b, new);
		if (n->level == 0)
			LeafCount++;
		else
			NonLeafCount++;
		return 1;
	}
}

/* Disconnect a dependent node.
*/
DisconBranch(n, i)
register struct Node *n;
register int i;
{
	assert(n && i>=0 && i<NODECARD);
	assert(n->branch[i].child);

	InitBranch(&(n->branch[i]));
	n->count--;
}
