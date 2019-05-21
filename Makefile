COPTS=-Wall -g -c -O0 -std=c99
OBJS=linked_list.o \

EXES=test \

all: $(EXES)

clean:
	rm -f $(OBJS)
	rm -f $(EXES)

valgrind: all
	valgrind ./test

test: test.c $(OBJS)
	gcc $@.c $(OBJS) -g -o $@ -std=c99 -lm

%: %.c $(OBJS)
	gcc $@.c $(OBJS) -g -o $@

.c.o:
	gcc $(COPTS) $? -o $@
