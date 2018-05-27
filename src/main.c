#include "options.h"
#include <stdio.h>
#include "assert.h"
#include <ctype.h>
#include "sccs.h"
#include "macros.h"
#include "index.h"

# ifndef	lint
	static	char	mainSccsid[] = "%W% %G%";
# endif	lint

/* the current caesar file to read */
FILE *Infile;

main(argc, argv)
int argc;
char *argv[];
{
	int i, nextArg = 1, firstFile;
	FILE *fopen();
	struct Node *NewIndex();
	int NewTid(), InsertRect();
	struct Rect r;
	extern char TermType[];

	/* Set up balance criterion for node splitting */
	assert(argc >= 2);
	if (!strcmp(argv[1], "half"))
		MinFill = NODECARD / 2;
	else if (!strcmp(argv[1], "third"))
		MinFill = NODECARD / 3;

	GeneralStats();

	/* Initialize all-covering rectangle to be whole space */
	for (i=0; i<NUMDIMS; i++)
	{
		CoverAll.boundary[i] = MININT;
		CoverAll.boundary[NUMDIMS+i] = MAXINT;
	}

	/* make one pass through files to find min and max x and y, # of rects */
	Phase = 1;

	printf("%s\n", argv[2]);
	fflush(stdout);
	if ((Infile = fopen(argv[2], "r")) == NULL)
	{
		error("main: can't open file");
	}
	else
	{
		yyparse();
		fclose(Infile);
	}

	Root = NewIndex();

	/* Insert rectangles into index structure */
	Phase = 2;
	ResetTid();
	ResetClock();
#ifdef PRINT
			printf ("Inserting from file %s\n", argv[nextArg]);
			fflush(stdout);
#endif
	if ((Infile = fopen(argv[2], "r")) == NULL)
	{
		error("main: can't open file");
	}
	else
	{
		yyparse();
		fclose(Infile);
	}

	//PrintIndex(Root);

	InsertStats();

	Phase = 3;
	if ((Infile = fopen(argv[3], "r")) == NULL)
	{
		error("main: can't open file");
	}
	else
	{
		ResetClock();
		StartClock();

		yyparse();
		fclose(Infile);

		StopClock();
		SearchStats();
	}
}
