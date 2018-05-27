%token
	ARRAY
	BOX
	END
	GTGT
	LABEL
	LABELS
	LTLT
	NUMBER
	POSITIONER
	RECT
	SIGN
	TECH
	TRANSFORM
	USE
	WORD

%{
# include "options.h"
# include <stdio.h>
# include "assert.h"
# include <ctype.h>
# include "macros.h"
# include "index.h"

# ifndef	lint
	static	char	yspecSccsid[] = "%W% %G%";
# endif	lint

# ifdef GRAPHICS
#	define UNIX
#	include "/jb/ingres/toni/cad/lib/mfb.h"
# endif

/* character types */
# define LETTER		1001
# define DIGIT		1002
# define WHITESPACE		1003

struct layertab
{
	char *name;
	char *letter;
};

struct
{
	char *string;
	int token;
} Keywords[] =
{
	"array",	ARRAY,
	"box",		BOX,
	"end",		END,
	">>",		GTGT,
	"<<",		LTLT,
	"labels",	LABELS,
	"label",	LABEL,
	"positioner",	POSITIONER,
	"rect",		RECT,
	"tech",		TECH,
	"transform",	TRANSFORM,
	"use",		USE,
	NULL,		0
};

struct layertab Layers[] =
{
	"polysilicon",		"p",
	"diffusion",		"d",
	"metal",		"m",
	"implant",		"i",
	"buried_contact",	"b",
	"cut",			"c",
	"overglass",		"o",
	"errors",		"e",
	"all",			"-",
	NULL,			0
};

FILE *Infile;
char Layer[30], Technology[20];
int tokenval;
char Tokenstring[80], label[20], subname[20];
int x1, y1, x2, y2, side, t[3][2];
int axlo, axhi, axsep, aylo, ayhi, aysep;
int vFeature[256];
int iFeatureIndex = 0;
%}

%start celldef

%% /* rules section */

arrayx		:
		| ARRAY
		  NUMBER { axlo = tokenval; }
		  NUMBER { axhi = tokenval; }
		  NUMBER { axsep = tokenval; }
		  NUMBER { aylo = tokenval; }
		  NUMBER { ayhi = tokenval; }
		  NUMBER { aysep = tokenval; }
		;
block		: LTLT ltltblock
		| USE useblock
		| POSITIONER positionerblock
		;
body		: block
		| body block
		;
celldef		:
		| body endline 
		| techline body endline 
		;
endline		: LTLT END GTGT
		;
geomblock	: WORD { getlayer(Tokenstring); }
		  GTGT geomlist
		;
geomlist	:
		| geomline
		| geomlist geomline
		;
geomline	: RECT { iFeatureIndex = 0;} FEATURE
		{ ProcessBox( vFeature, iFeatureIndex ); } 
		;
FEATURE		: NUMBER { vFeature[iFeatureIndex++] = tokenval; }
		| FEATURE NUMBER
		{
			vFeature[iFeatureIndex++] = tokenval;
		}
		;
labelblock	: LABELS GTGT labellist
		;
labelline	: LABEL WORD {strcpy(label, Tokenstring);}
		  NUMBER {x1 = tokenval;}
		  NUMBER {y1 = tokenval;}
		  NUMBER {x2 = tokenval;}
		  NUMBER {y2 = tokenval;}
		  NUMBER
		  {
			side = tokenval;
		  }
		;
labellist	:
		| labelline
		| labellist labelline
		;
ltltblock	: geomblock
		| labelblock
		;
positionerblock	: NUMBER
		  NUMBER
		  NUMBER
		  NUMBER
		;
techline	: TECH WORD { strcpy(Technology, Tokenstring); }
		;
useblock	: WORD
		  {
			strcpy(subname, Tokenstring);
			axlo = axhi = axsep = aylo = ayhi = aysep = 0;
		  }
		  arrayx
		  TRANSFORM
		  NUMBER {t[0][0] = tokenval;}
		  NUMBER {t[1][0] = tokenval;}
		  NUMBER {t[2][0] = tokenval;}
		  NUMBER {t[0][1] = tokenval;}
		  NUMBER {t[1][1] = tokenval;}
		  NUMBER {t[2][1] = tokenval;}
		  BOX
		  NUMBER {x1 = tokenval;}
		  NUMBER {y1 = tokenval;}
		  NUMBER {x2 = tokenval;}
		  NUMBER
		  {
			int xx1, xx2, yy1, yy2;
			y2 = tokenval;
			xx1 = x1*t[0][0]+y1*t[1][0]+t[2][0];
			yy1 = x1*t[0][1]+y1*t[1][1]+t[2][1];
			xx2 = x2*t[0][0]+y2*t[1][0]+t[2][0];
			yy2 = x2*t[0][1]+y2*t[1][1]+t[2][1];
			ProcessBox(xx1, yy1, xx2, yy2);
		  }
		;

%% /* programs section */

/* derived from scan.c	1.4 6/22/82 */

yylex()
{
	int c, c_type, token_type, lim;
	char *w;

	w = Tokenstring;
	while ((c_type = type(c = getc(Infile))) == WHITESPACE)
		;
	*w++ = c;

	switch (c_type)
	{
	case '+':
	case '-':
		token_type = SIGN;
		break;
	case DIGIT:
		token_type = NUMBER;
		break;
	case EOF:
		*w = '\0';
		return EOF;
	default:
		token_type = WORD;
		break;
	}

	lim = 80;
	while (--lim > 0)
	{
		c_type = type(c = *w++ = getc(Infile));
		if (c_type == WHITESPACE || c == EOF)
		{
			*--w = '\0';
			if (token_type == WORD)
				return (checkword(Tokenstring));
			else if (token_type == NUMBER)
			{
				/* evaluate number string */
				sscanf(Tokenstring, "%ld", &tokenval);
				return (NUMBER);
			}
			else
				return (token_type);
		}
		else if (token_type == NUMBER && c_type != DIGIT)
			token_type = WORD;
		else if (token_type == SIGN)
		{
			if (c_type == DIGIT)
				token_type = NUMBER;
			else
				token_type = WORD;
		}
	}
	error("scan: token too long");
	return (EOF);
}

type(c)		/* return type of ascii character */
int c;
{
	if (isspace(c))
		return(WHITESPACE);
	else if (isalpha(c))
		return(LETTER);
	else if (isdigit(c))
		return(DIGIT);
	else
		return(c);
}

int
checkword(w)
char *w;
{
	int i;
	char *s;

	for (i = 0; (s = Keywords[i].string) != NULL; i++)
	{
		if (!strcmp(w, s))
			return (Keywords[i].token);
	}
	return(WORD);
}


yyerror(string)
char *string;
{
#	ifdef GRAPHICS
		EndGraphics();
#	endif
	Tokenstring[79] = '\0';
	fflush(stdout);
	fprintf(stderr, "Error: %s token=\"%s\"\n", string, Tokenstring);
	fflush(stderr);
}


getlayer(n)
char *n;
{
	int i;
	char *s;

	for (i = 0; (s = Layers[i].name) != NULL; i++)
	{
		if (!strcmp(n, s))
		{
			strcpy(Layer, Layers[i].letter);
			return;
		}
	}
#	ifdef GRAPHICS
		EndGraphics();
#	endif
	error("getlayer: layer name not found");
}

ProcessBox( vFeature, iFeatureNum)
int *vFeature;
int iFeatureNum;
{
	/*
	int iFeatureIndex = 0;
	for ( iFeatureIndex = 0; iFeatureIndex<iFeatureNum; iFeatureIndex++ )
		printf("%d ", vFeature[iFeatureIndex] );
	printf("\n");*/

	static int flag=0, count=0, result;
	int tid;
	struct Rect r;

	if (Phase == 1)
	{
		count++;

		if ( NUMDIMS!=iFeatureNum)
		{
			printf( "Feature dimension of the input data is not equal with NUMDIMS\n" );
			printf( "Feature dimension is %d;\tNUMDIMS is %d\n", iFeatureNum, NUMDIMS );
			exit(0);
		}


		if (!flag)
		{
			flag = 1;

			for ( iFeatureIndex=0; iFeatureIndex<NUMDIMS; iFeatureIndex++ )
			{
				CoverAll.boundary[iFeatureIndex] = vFeature[iFeatureIndex];
				CoverAll.boundary[iFeatureIndex+NUMDIMS] = vFeature[iFeatureIndex]+1;
			}
		}
		else
		{
			for ( iFeatureIndex=0; iFeatureIndex<NUMDIMS; iFeatureIndex++ )
			{
				CoverAll.boundary[iFeatureIndex] = min( vFeature[iFeatureIndex], CoverAll.boundary[iFeatureIndex] );
				CoverAll.boundary[iFeatureIndex+NUMDIMS] = max( vFeature[iFeatureIndex]+1, CoverAll.boundary[iFeatureIndex+NUMDIMS] );
			}
		}
	}
	else if (Phase == 2)
	{
		if ( NUMDIMS!=iFeatureNum)
		{
			printf( "Feature dimension of the input data is not equal with NUMDIMS\n" );
			printf( "Feature dimension is %d;\tNUMDIMS is %d\n", iFeatureNum, NUMDIMS );
			exit(0);
		}

		for ( iFeatureIndex=0; iFeatureIndex<NUMDIMS; iFeatureIndex++ )
		{
			r.boundary[iFeatureIndex] = vFeature[iFeatureIndex];
			r.boundary[iFeatureIndex+NUMDIMS] = vFeature[iFeatureIndex]+1;
		}

		StatFlag = TRUE;
		StartClock();
		InsertRect(&r, tid, &Root, 0);
		StopClock();
		StatFlag = FALSE;
	}
	else if (Phase == 3)
	{
		if ( NUMDIMS!=iFeatureNum)
		{
			printf( "Feature dimension of the input data is not equal with NUMDIMS\n" );
			printf( "Feature dimension is %d;\tNUMDIMS is %d\n", iFeatureNum, NUMDIMS );
			exit(0);
		}

		for ( iFeatureIndex=0; iFeatureIndex<NUMDIMS; iFeatureIndex++ )
		{
			r.boundary[iFeatureIndex] = vFeature[iFeatureIndex];
			r.boundary[iFeatureIndex+NUMDIMS] = vFeature[iFeatureIndex]+1;
		}


		/* Do searches using the index */
		//printf("Search rect:\n");
		//PrintRect2(&r);
		HitCount += Search(Root, &r);
		SearchCount++;
	}
}
