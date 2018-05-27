#include "options.h"
#include <stdio.h>
#include "assert.h"
#include "macros.h"
#include "index.h"

# ifndef	lint
	static	char	indexSccsid[] = "%W% %G%";
# endif	lint


/* Make a new index, empty.  Consists of a single node.
*/
struct Node *
NewIndex()
{
	struct Node *x, *NewNode();
	x = NewNode();
	x->level = 0; /* leaf */
	LeafCount++;
	return x;
}

/* Print out all the nodes in an index.
** For graphics output, displays lower boxes first so they don't obscure
** enclosing boxes.  For printed output, prints from root downward.
*/
PrintIndex(n)
struct Node *n;
{
	int i;
	struct Node *nn;
	assert(n);
	assert(n->level >= 0);


	if (n->level > 0)
	{
		for (i = 0; i < NODECARD; i++)
		{
			if ((nn = n->branch[i].child) != NULL)
				PrintIndex(nn);
		}
	}

}

/* Print out all the data rectangles in an index.
*/
PrintData(n)
struct Node *n;
{
	int i;
	struct Node *nn;
	assert(n);
	assert(n->level >= 0);

	if (n->level == 0)
		PrintNode(n);
	else
	{
		for (i = 0; i < NODECARD; i++)
		{
			if ((nn = n->branch[i].child) != NULL)
				PrintData(nn);
		}
	}
}

/* Search in an index tree or subtree for all data retangles that
** overlap the argument rectangle.
** Returns the number of qualifying data rects.
*/
int
Search(n, r)
register struct Node *n;
register struct Rect *r;
{
	register int hitCount = 0;
	register int i;

	assert(n);
	assert(n->level >= 0);
	assert(r);

	SeTouchCount++;

	if (n->level > 0) /* this is an internal node in the tree */
	{
		for (i=0; i<NODECARD; i++)
			if (n->branch[i].child && Overlap(r, &n->branch[i].rect))
				hitCount += Search(n->branch[i].child, r);
	}
	else /* this is a leaf node */
	{
		for (i=0; i<NODECARD; i++)
		{
			if (n->branch[i].child && Overlap(r, &n->branch[i].rect))
			{
				hitCount++;
			}
		}
	}
	return hitCount;
}

/* Insert a data rectangle into an index structure.
** InsertRect provides for splitting the root;
** returns 1 if root was split, 0 if it was not.
** The level argument specifies the number of steps up from the leaf
** level to insert; e.g. a data rectangle goes in at level = 0.
** InsertRect2 does the recursion.
*/

int
InsertRect(r, tid, root, level)
register struct Rect *r;
register int tid;
register struct Node **root;
register int level;
{
	register int i;
	register struct Node *newroot;
	struct Node *newnode, *NewNode();
	struct Branch b;
	struct Rect NodeCover();
	int result;
	int AddBranch();

	assert(r && root);
	assert(level >= 0 && level <= (*root)->level);
	for (i=0; i<NUMDIMS; i++)
		assert(r->boundary[i] <= r->boundary[NUMDIMS+i]);

#	ifdef PRINT
		printf("InsertRect  level=%d\n", level);
#	endif

	if (StatFlag)
	{
		if (Deleting)
			ReInsertCount++;
		else
			InsertCount++;
	}
	if (!Deleting)
		RectCount++;

	if (InsertRect2(r, tid, *root, &newnode, level))  /* root was split */
	{
		if (StatFlag)
		{
			if (Deleting)
				DeTouchCount++;
			else
				InTouchCount++;
		}

		newroot = NewNode();  /* grow a new root, make tree taller */
		NonLeafCount++;
		newroot->level = (*root)->level + 1;
		b.rect = NodeCover(*root);
		b.child = *root;
		AddBranch(&b, newroot, NULL);
		b.rect = NodeCover(newnode);
		b.child = newnode;
		AddBranch(&b, newroot, NULL);
		*root = newroot;
		EntryCount += 2;
		result = 1;
	}
	else
		result = 0;

	return result;
}

/* Inserts a new data rectangle into the index structure.
** Recursively descends tree, propagates splits back up.
** Returns 0 if node was not split.  Old node updated.
** If node was split, returns 1 and sets the pointer pointed to by
** new to point to the new node.  Old node updated to become one of two.
** The level argument specifies the number of steps up from the leaf
** level to insert; e.g. a data rectangle goes in at level = 0.
*/
int
InsertRect2(r, tid, n, new, level)
register struct Rect *r;
register int tid;
register struct Node *n, **new;
register int level;
{
	register int i;
	int NewTid();
	struct Rect NodeCover(), CombineRect();
	struct Branch b;
	struct Node *n2;

	assert(r && n && new);
	assert(level >= 0 && level <= n->level);

	if (StatFlag)
	{
		if (Deleting)
			DeTouchCount++;
		else
			InTouchCount++;
	}

	/* Still above level for insertion, go down tree recursively */
	if (n->level > level)
	{
		i = PickBranch(r, n);
		if (!InsertRect2(r, tid, n->branch[i].child, &n2, level))
		{
			/* child was not split */
			n->branch[i].rect = CombineRect(r, &(n->branch[i].rect));
			return 0;
		}
		else		/* child was split */
		{
			n->branch[i].rect = NodeCover(n->branch[i].child);
			b.child = n2;
			b.rect = NodeCover(n2);
			EntryCount++;
			return AddBranch(&b, n, new);
		}
	}

	/* Have reached level for insertion. Add rect, split if necessary */
	else if (n->level == level)
	{
		b.rect = *r;
		b.child = (struct Node *) tid;
		/* child field of leaves contains tid of data record */
		EntryCount++;
		return AddBranch(&b, n, new);
	}

	else
	{
		/* Not supposed to happen */
		assert (FALSE);
		return 0;
	}
}

/* Delete a data rectangle from an index structure.
** Pass in a pointer to a Rect, the tid of the record, ptr to ptr to root node.
** Returns 1 if record not found, 0 if success.
** DeleteRect provides for eliminating the root.
*/
int
DeleteRect(r, tid, nn)
register struct Rect *r;
register int tid;
register struct Node **nn;
{
	register int i;
	register struct Node *t;
	struct ListNode *reInsertList = NULL;
	register struct ListNode *e;

	assert(r && nn);
	assert(*nn);
	assert(tid >= 0);

	Deleting = TRUE;


#	ifdef PRINT
		printf("DeleteRect\n");
#	endif

	if (!DeleteRect2(r, tid, *nn, &reInsertList))
	{
		/* found and deleted a data item */
		if (StatFlag)
			DeleteCount++;
		RectCount--;

		/* reinsert any branches from eliminated nodes */
		while (reInsertList)
		{
			t = reInsertList->node;
			for (i = 0; i < NODECARD; i++)
			{
				if (t->branch[i].child)
				{
					InsertRect(
						&(t->branch[i].rect),
						(int) t->branch[i].child,
						nn,
						t->level);
					EntryCount--;
				}
			}
			e = reInsertList;
			reInsertList = reInsertList->next;
			FreeNode(e->node);
			FreeListNode(e);
		}
		
		/* check for redundant root (not leaf, 1 child) and eliminate */
		if ((*nn)->count == 1 && (*nn)->level > 0)
		{
			if (StatFlag)
				ElimCount++;
			EntryCount--;
			for (i = 0; i < NODECARD; i++)
			{
				if ((t = (*nn)->branch[i].child))
					break;
			}
			FreeNode(*nn);
			*nn = t;
		}
		Deleting = FALSE;
		return 0;
	}
	else
	{
		Deleting = FALSE;
		return 1;
	}
}

/* Delete a rectangle from non-root part of an index structure.
** Called by DeleteRect.  Descends tree recursively,
** merges branches on the way back up.
*/
int
DeleteRect2(r, tid, n, ee)
register struct Rect *r;
register int tid;
register struct Node *n;
register struct ListNode **ee;
{
	register int i;
	int Overlap();
	struct Rect NodeCover();

	assert(r && n && ee);
	assert(tid >= 0);
	assert(n->level >= 0);

	if (StatFlag)
		DeTouchCount++;

	if (n->level > 0) /* not a leaf node */
	{
		for (i = 0; i < NODECARD; i++)
		{
			if (n->branch[i].child && Overlap(r, &(n->branch[i].rect)))
			{
				if (!DeleteRect2(r, tid, n->branch[i].child, ee))
				{
					if (n->branch[i].child->count >= MinFill)
						n->branch[i].rect = NodeCover(n->branch[i].child);
					else
					{
						/* not enough entries in child, eliminate child node */
						ReInsert(n->branch[i].child, ee);
						DisconBranch(n, i);
						EntryCount--;
						if (StatFlag)
							ElimCount++;
					}
					return 0;
				}
			}
		}
		return 1;
	}
	else  /* a leaf node */
	{
		for (i = 0; i < NODECARD; i++)
		{
			if (n->branch[i].child
			&& n->branch[i].child == (struct Node *) tid)
			{
				DisconBranch(n, i);
				EntryCount--;
				return 0;
			}
		}
		return 1;
	}
}

/* Add a node to the reinsertion list.  All its branches will later
** be reinserted into the index structure.
*/
ReInsert(n, ee)
register struct Node *n;
register struct ListNode **ee;
{
	register struct ListNode *l;
	struct ListNode *NewListNode();

	l = NewListNode();
	l->node = n;
	l->next = *ee;
	*ee = l;
}

/* Allocate space for a node in the list used in DeletRect to
** store Nodes that are too empty.
*/
struct ListNode *
NewListNode()
{
	char *malloc();
	return (struct ListNode *) malloc(sizeof(struct ListNode));
}

FreeListNode(p)
register struct ListNode *p;
{
	free(p);
}
