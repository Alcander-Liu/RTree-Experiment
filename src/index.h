
/* %W% %G% */
/*-----------------------------------------------------------------------------
| Global definitions.
-----------------------------------------------------------------------------*/

#define NUMSIDES 2*NUMDIMS

#ifdef GRAPHICS
#	define NDEBUG
#	define BLACK   0
#	define WHITE   1
#	define RED     2
#	define GREEN   3
#	define BLUE    4
#	define YELLOW  5
#	define CYAN    6
#	define MAGENTA 7
#endif

struct Rect
{
	int boundary[NUMSIDES];
};

struct Branch
{
	struct Rect rect;
	struct Node *child;
};

/* branching factor of a node */
#define NODECARD (int)((PGSIZE-(2*sizeof(int)))/sizeof(struct Branch))

struct Node
{
	int count;
	int level; /* 0 is leaf, others positive */
	struct Branch branch[NODECARD];
};

struct ListNode
{
	struct ListNode *next;
	struct Node *node;
};


/*-----------------------------------------------------------------------------
| Global variables.
-----------------------------------------------------------------------------*/

/* balance criterion for node splitting */
int MinFill;

/* index root node pointer */
struct Node *Root;

/* phase 1 for preliminary scan, 2 for inserting, 3 for deleting */
int Phase;

/* rectangle covering all data read */
struct Rect CoverAll;

/* times */
long ElapsedTime;
float UserTime, SystemTime;

/* variables for statistics */
int StatFlag; /* tells if we are counting or not */
int Deleting;

/* counters affected only when StatFlag set */
int InsertCount;
int DeleteCount;
int ReInsertCount;
int InSplitCount;
int DeSplitCount;
int ElimCount;
int EvalCount;
int InTouchCount;
int DeTouchCount;
int SeTouchCount;
int CallCount;
float SplitMeritSum;

/* counters used even when StatFlag not set */
int RectCount;
int NodeCount;
int LeafCount, NonLeafCount;
int EntryCount;
int SearchCount;
int HitCount;
