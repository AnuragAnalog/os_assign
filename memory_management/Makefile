
# Makefile

CC = gcc
CCC = $(CC) -c
CFLAGS = -Wall
MFLAG = -lm
DEBUG = -g
TARGET = memory_management

all:	queue functions
	$(CC) $(CFLAGS) req_functs.o queue.o memory_management.c -o $(TARGET) $(MFLAG) $(DEBUG)

clean:
	rm *.o *.dat *.txt $(TARGET)

queue:		queue.c
	$(CCC) queue.c

functions:	req_functs.c
	$(CCC) req_functs.c
