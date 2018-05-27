
# ifndef	lint
	static	char	newtidSccsid[] = "%W% %G%";
# endif	lint

/* Allocate unique numbers for use as pretend tids.
** Zero is not used.
*/

int Tid;

int
NewTid()
{
	return ++Tid;
}

ResetTid()
{
	Tid = 0;
}
