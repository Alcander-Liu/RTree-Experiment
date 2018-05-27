# ifndef NDEBUG
# define _assert(ex) {if (!(ex)){fflush(stdout);fprintf(stderr,"Assertion failed: file %s, line %d\n", __FILE__, __LINE__);abort();}}
# define assert(ex) {if (!(ex)){fflush(stdout);fprintf(stderr,"Assertion failed: file %s, line %d\n", __FILE__, __LINE__);abort();}}
# else
# define _assert(ex) ;
# define assert(ex) ;
# endif
