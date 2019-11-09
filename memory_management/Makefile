
# Makefile

CC = gcc
CCC = $(CC) -c
CFLAGS = -Wall
MFLAG = -lm
DEBUG = -g
TARGET = memory_management

all:	queue functions page_replace
	$(CC) $(CFLAGS) page_replacement.o req_functs.o queue.o memory_management.c -o $(TARGET) $(MFLAG) $(DEBUG)

clean:
	rm *.o *.dat *.txt $(TARGET)

queue:		queue.c
	$(CCC) queue.c

functions:	req_functs.c
	$(CCC) req_functs.c

page_replace:	page_replacement.c
	$(CCC) page_replacement.c
