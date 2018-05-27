# %W% %G%
# use flag -O for optimized code, slower compile
FLAGS=

SRC= main.c index.c newtid.c node.c rectangle.c \
	printstats.c clock.c y.spec allocate.c error.c\
	split.l.c \
	split.q.c \
	split.e.c

HEADERS= options.h macros.h index.h assert.h

ALL= $(SRC) $(HEADERS) split.l.h split.q.h split.e.h

OBJ= main.o index.o newtid.o node.o rectangle.o \
	printstats.o clock.o y.tab.o allocate.o error.o

OBJLIN= split.l.o
OBJQ= split.q.o
OBJEXP= split.e.o

$(OBJ): $(HEADERS)
$(OBJLIN): $(HEADERS) split.l.h
$(OBJQ): $(HEADERS) split.q.h
$(OBJEXP): $(HEADERS) split.e.h

# assembler chokes if graphics.c is compiled with -g option, do it without.
# graphics.o: graphics.c $(HEADERS)
#	cc -c graphics.c

# assembler chokes if y.tab.c is compiled with -g option, do it without.
# y.tab.o: y.tab.c $(HEADERS)
#	cc -c y.tab.c

.c.o: $(HEADERS)
	cc -c $(FLAGS) $*.c

linear: $(OBJ) $(OBJLIN)
	cc $(FLAGS) $(OBJ) $(OBJLIN) -lm -o linear

quad: $(OBJ) $(OBJQ)
	cc $(FLAGS) $(OBJ) $(OBJQ) -lm -o quad

exp: $(OBJ) $(OBJEXP)
	cc $(FLAGS) $(OBJ) $(OBJEXP) -lm -o exp

y.tab.c: y.spec $(HEADERS)
	yacc y.spec

edit:
	sccs edit $(SRC) $(HEADERS) split.l.h split.q.h split.o.h

unedit:
	sccs unedit $(ALL)
	rm -f tags

delta:
	sccs delta $(ALL)
	rm -f tags

get:
	sccs get $(ALL)

clean:
	rm -f *.o core y.tab.c tags

tags: $(SRC)
	ctags *.c

lint:
	rm -f lint.out
	lint *.c > lint.out
