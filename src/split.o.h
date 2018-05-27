
/* %W% %G% */
/*-----------------------------------------------------------------------------
| Definitions used only by node split code.
-----------------------------------------------------------------------------*/

#define MAPMASK (~(~0 << NUMSIDES))

#ifdef GRAPHICS
/* optional definition of SHOWSPLIT here */
#	define SHOWSPLIT
#endif

#define HEADER 1  /* types of RectSide records */
#define SIDE 2

struct SetElement
{
	struct Branch branch;
	int group;
	struct RectSide *side[NUMSIDES];
	struct SetElement *stackLink;
};

struct RectSide
{
	int type; /* HEADER, SIDE */
	int value;
	struct SetElement *el;
	struct RectSide *out, *in;
};


/*-----------------------------------------------------------------------------
| Global variables for node split code.
-----------------------------------------------------------------------------*/

/* state of the set being split */
int BestPartition[NODECARD+1], NewPartition[NODECARD+1];
int BestArea;
int EvCount, FindCovCount;
int Map;
struct Rect BigCover;
int BigArea;
struct Rect Cover[2], BestCover[2];
int ExtremeValue[NUMSIDES];
struct SetElement Element[NODECARD+1];
struct RectSide SideList[NUMSIDES];
struct RectSide *CurExtreme[NUMSIDES];

/* buffer for side list nodes */
int NextFree;
struct RectSide ListNode[NUMSIDES * (NODECARD+1)];
