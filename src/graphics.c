
#include "options.h"

/* skip over the rest of the file unless GRAPHICS is defined */
# ifdef GRAPHICS

#define UNIX
#include "/jb/ingres/toni/cad/lib/mfb.h"
#include <stdio.h>
#include "assert.h"
#include "macros.h"
#include "index.h"

#define SCREENSIZE 400

#ifndef lint
	static	char	graphicsSccsid[] = "@(#)graphics.c	1.15 7/12/83";
#endif lint

int ScreenSize, WorldSize;
char TermType[20];
struct MFB *Mfb;

MFB *
StartGraphics()
{
	MFB *p;
	int errorcode;

	p = MFBOpen(TermType, NULL, &errorcode);
	if (p == NULL)
	{
		MFBClose();
      printf("\nMFBOpen returned null, errorcode=%d\n", errorcode);
		fflush(stdout);
		assert(FALSE);
	} 
	ScreenSize = min(p->maxX, p->maxY);
	WorldSize = max(CoverAll.boundary[NUMDIMS]-CoverAll.boundary[0],
		CoverAll.boundary[NUMDIMS+1]-CoverAll.boundary[1]);
	MFBDefineColor(BLACK,   0,     0,     0    ); /* 0 */
	MFBDefineColor(WHITE,   800,   800,   1000 ); /* 1 */
	MFBDefineColor(RED,     800,   0,     0    ); /* 2 */
	MFBDefineColor(GREEN,   0,     800,   0    ); /* 3 */
	MFBDefineColor(BLUE,    0,     200,   1000 ); /* 4 */
	MFBDefineColor(YELLOW,  800,   800,   0    ); /* 5 */
	MFBDefineColor(CYAN,    0,     800,   1000 ); /* 6 */
	MFBDefineColor(MAGENTA, 800,   0,     1000 ); /* 7 */

	/* other colors (see Chromatics manual):
		pink          1000 500 500
		light orange  1000 760 500
		brown         576  380 256
	*/

	ClearScreen();
	MFBUpdate();
	return p;
}

EndGraphics()
{
	MFBClose();
}

DrawBox(r)
struct Rect *r;
{
	int x1, y1, x2, y2;
	float ratio;

	/* graphics uses first two dimensions, ignores the rest */

	/* using mfb, doesn't seem to work */
	/*
	x1 = MFBScaleX(r->boundary[0] - CoverAll.boundary[0]);
	y1 = MFBScaleY(r->boundary[1] - CoverAll.boundary[NUMDIMS]);
	x2 = MFBScaleX(r->boundary[NUMDIMS] - CoverAll.boundary[0]);
	y2 = MFBScaleY(r->boundary[NUMDIMS+1] - CoverAll.boundary[NUMDIMS]);
	*/

	/* same thing done by hand */
	ratio = (float)ScreenSize / (float)WorldSize;
	x1 = (r->boundary[0] - CoverAll.boundary[0]) * ratio;
	x2 = (r->boundary[NUMDIMS] - CoverAll.boundary[0]) * ratio;
	y1 = (r->boundary[1] - CoverAll.boundary[1]) * ratio;
	y2 = (r->boundary[NUMDIMS+1] - CoverAll.boundary[1]) * ratio;

	MFBMoveTo(x1, y1);
	MFBDrawLineTo(x2, y1);
	MFBDrawLineTo(x2, y2);
	MFBDrawLineTo(x1, y2);
	MFBDrawLineTo(x1, y1);
	MFBUpdate();
}

GraphChar()
{
	char c;
	int count = 0;

	do
	{
		c = MFBGetchar();
		if (c == ' ' || c == '\n' || c == '\r')
			return;
		else if (c == 'q')
		{
			EndGraphics();
			exit(0);
		}
	} while (count++ < 10);

	EndGraphics();
	exit(0);
}

ClearScreen()
{
	MFBSetColor(BLACK);
	MFBFlood();
	MFBUpdate();
}

# endif GRAPHICS
