CC=gcc
CFLAGES=-std=c99 -Wall -Wextra -Wshadow -fsanitize=address,undefined -O3
OBJS=genkat_aead.o photon.o encrypt.o
REFOBJS=genkat_aead.o photon.o encrypt.o
TIMEOBJS=timing_aead.o photon.o encrypt.o

all: table3 timingtable3

table3: $(REFOBJS)
	$(CC) -o table3 $(REFOBJS) $(CFLAGES)

timingtable3: $(TIMEOBJS)
	$(CC) -o timingtable3 $(TIMEOBJS) $(CFLAGES) -lm

genkat_aead.o: ../../../genkat_aead.c
	$(CC) -c ../../../genkat_aead.c $(CFLAGES) -I./

timing_aead.o: ../../../timing_aead.c
	$(CC) -c ../../../timing_aead.c $(CFLAGES) -I./ -lm

encrypt.o: encrypt.c
	$(CC) -o encrypt.o -c encrypt.c $(CFLAGES) -I../../../

photon.o: photon.c
	$(CC) -c photon.c $(CFLAGES)

.PHONY : clean

clean :
	rm $(OBJS)