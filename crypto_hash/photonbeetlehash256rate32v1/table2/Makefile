CC=gcc
CFLAGES=-std=c99 -Wall -Wextra -Wshadow -fsanitize=address,undefined -fuse-ld=gold -O3
OBJS=genkat_hash.o hash.o photon.o timing_hash.o
REFOBJS=genkat_hash.o photon.o hash.o
TIMEOBJS=timing_hash.o photon.o hash.o

all: table2 timingtable2

table2: $(REFOBJS)
	$(CC) -o table2 $(REFOBJS) $(CFLAGES)

timingtable2: $(TIMEOBJS)
	$(CC) -o timingtable2 $(TIMEOBJS) $(CFLAGES) -lm

genkat_hash.o: ../../../genkat_hash.c
	$(CC) -c ../../../genkat_hash.c $(CFLAGES) -I./

timing_hash.o: ../../../timing_hash.c
	$(CC) -c ../../../timing_hash.c $(CFLAGES) -I./ -lm

hash.o: hash.c
	$(CC) -o hash.o -c hash.c $(CFLAGES) -I../../../

photon.o: photon.c
	$(CC) -c photon.c $(CFLAGES)

.PHONY : clean

clean :
	rm $(OBJS)