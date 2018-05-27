
#include "options.h"
#include <stdio.h>
#include "assert.h"
#include "macros.h"
#include "index.h"

# ifndef	lint
	static	char	rectangleSccsid[] = "%W% %G%";
# endif	lint

#define Undefined(x) ((x)->boundary[0] > (x)->boundary[NUMDIMS])

extern struct Rect CoverAll;

/*-----------------------------------------------------------------------------
| Initialize a rectangle to have all 0 coordinates.
-----------------------------------------------------------------------------*/
InitRect(r)
register struct Rect *r;
{
	register int i;
	for (i=0; i<NUMSIDES; i++)
		r->boundary[i] = 0;
}

/*-----------------------------------------------------------------------------
| Return a rect whose first low side is higher than its opposite side -
| interpreted as an undefined rect.
-----------------------------------------------------------------------------*/
struct Rect
NullRect()
{
	struct Rect r;
	register int i;

	r.boundary[0] = 1;
	r.boundary[NUMDIMS] = -1;
	for (i=1; i<NUMDIMS; i++)
		r.boundary[i] = r.boundary[i+NUMDIMS] = 0;
	return r;
}

/*-----------------------------------------------------------------------------
| Fills in random coordinates in a rectangle.
| The low side is guaranteed to be less than the high side.
-----------------------------------------------------------------------------*/
RandomRect(r)
register struct Rect *r;
{
	register int i, width;
	for (i = 0; i < NUMDIMS; i++)
	{
		/* width from 1 to 1000 / 4, more small ones */
		width = rand() % (1000 / 4) + 1;

		/* sprinkle a given size evenly but so they stay in [0,100] */
		r->boundary[i] = rand() % (1000-width); /* low side */
		r->boundary[i + NUMDIMS] = r->boundary[i] + width;  /* high side */
	}
}

/*-----------------------------------------------------------------------------
| Fill in the boundaries for a random search rectangle.
| Pass in a pointer to a rect that contains all the data,
| and a pointer to the rect to be filled in.
| Generated rect is centered randomly anywhere in the data area,
| and has size from 0 to the size of the data area in each dimension,
| i.e. search rect can stick out beyond data area.
-----------------------------------------------------------------------------*/
SearchRect(search, data)
register struct Rect *search, *data;
{
	register int i, j, size, center;

	assert(search);
	assert(data);

	for (i=0; i<NUMDIMS; i++)
	{
		j = i + NUMDIMS; /* index for high side boundary */
		if (data->boundary[i] > MININT && data->boundary[j] < MAXINT)
		{
			size = (rand() % (data->boundary[j] - data->boundary[i] + 1)) / 2;
			center = data->boundary[i]
				+ rand() % (data->boundary[j] - data->boundary[i] + 1);
			search->boundary[i] = center - size/2;
			search->boundary[j] = center + size/2;
		}
		else /* some open boundary, search entire dimension */
		{
			search->boundary[i] = MININT;
			search->boundary[j] = MAXINT;
		}
	}
}

/*-----------------------------------------------------------------------------
| Print out the data for a rectangle.
-----------------------------------------------------------------------------*/
PrintRect(r)
register struct Rect *r;
{
	register int i, j;
	struct Rect new;
	assert(r);

#	ifdef PRINT
		printf("rect:");
		for (i = 0; i < NUMDIMS; i++)
			printf("\t%d\t%d\n", r->boundary[i], r->boundary[i + NUMDIMS]);
#	endif
}

/*-----------------------------------------------------------------------------
| Another version that always prints, no graphics.
-----------------------------------------------------------------------------*/
PrintRect2(r)
register struct Rect *r;
{
	register int i;
	assert(r);
	printf("rect:");
	for (i = 0; i < NUMDIMS; i++)
		printf("\t%d\t%d\n", r->boundary[i], r->boundary[i + NUMDIMS]);
}

/*-----------------------------------------------------------------------------
| Erase a rectangle by drawing it black.  Graphics only.
-----------------------------------------------------------------------------*/
EraseRect(r)
struct Rect *r;
{
}

/*-----------------------------------------------------------------------------
| Calculate the n-dimensional area of a rectangle
-----------------------------------------------------------------------------*/
int
RectArea(r)
register struct Rect *r;
{
	register int i, area;
	assert(r);

	if (Undefined(r))
		return 0;

	area = 1;
	for (i=0; i<NUMDIMS; i++)
	{
		area *= r->boundary[i+NUMDIMS] - r->boundary[i];
	}
	return area;
}

/*-----------------------------------------------------------------------------
| Combine two rectangles, make one that includes both.
-----------------------------------------------------------------------------*/
struct Rect
CombineRect(r, rr)
register struct Rect *r, *rr;
{
	register int i, j;
	struct Rect new;
	assert(r && rr);

	if (Undefined(r))
		return *rr;

	if (Undefined(rr))
		return *r;

	for (i = 0; i < NUMDIMS; i++)
	{
		new.boundary[i] = min(r->boundary[i], rr->boundary[i]);
		j = i + NUMDIMS;
		new.boundary[j] = max(r->boundary[j], rr->boundary[j]);
	}
	return new;
}

/*-----------------------------------------------------------------------------
| Decide whether two rectangles overlap.
-----------------------------------------------------------------------------*/
int
Overlap(r, s)
register struct Rect *r, *s;
{
	register int i, j;
	assert(r && s);

	for (i=0; i<NUMDIMS; i++)
	{
		j = i + NUMDIMS;  /* index for high sides */
		if (r->boundary[i] > s->boundary[j] || s->boundary[i] > r->boundary[j])
			return FALSE;
	}
	return TRUE;
}

/*-----------------------------------------------------------------------------
| Decide whether rectangle r is contained in rectangle s.
-----------------------------------------------------------------------------*/
int
Contained(r, s)
register struct Rect *r, *s;
{
	register int i, j, result;
	assert((int)r && (int)s);

 	/* undefined rect is contained in any other */
	if (Undefined(r))
		return TRUE;

	/* no rect (except an undefined one) is contained in an undef rect */
	if (Undefined(s))
		return FALSE;

	result = TRUE;
	for (i = 0; i < NUMDIMS; i++)
	{
		j = i + NUMDIMS;  /* index for high sides */
		result = result
			&& r->boundary[i] >= s->boundary[i]
			&& r->boundary[j] <= s->boundary[j];
	}
	return result;
}
