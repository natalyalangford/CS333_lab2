CC = gcc
DEFINES =
CFLAGS = $(DEFINES) -Wall -Wextra -Wshadow -Wunreachable-code -Wredundant-decls \
         -Wmissing-declarations -Wold-style-definition \
         -Wmissing-prototypes -Wdeclaration-after-statement \
         -Wno-return-local-addr -Wuninitialized -Werror -Wunsafe-loop-optimizations

PROGS = caesar decimation

all: $(PROGS) caesar.o decimation.o

caesar: caesar.o
	$(CC) $(CFLAGS) -o $@ $^

decimation: decimation.o
	$(CC) $(CFLAGS) -o $@ $^

caesar.o: caesar.c
	$(CC) $(CFLAGS) -c $<

decimation.o: decimation.c
	$(CC) $(CFLAGS) -c $<

TAR_FILE = ${LOGNAME}_lab1.tar.gz
tar:
	rm -f $(TAR_FILE)
	tar cvaf $(TAR_FILE) *.[ch] [Mm]akefile
	tar tvaf $(TAR_FILE)

clean:
	rm -f *.o $(PROGS) *~ \#*





