
# Makefile

CC = gcc
CCC = $(CC) -c
TARGET = process
CFLAGS = -Wall

all:	queue maxheap minheap funct process.c
	$(CC) $(CFLAGS) queue.o maxheap.o minheap.o process_funct.o process.c -o $(TARGET)
clean:
	rm *.o $(TARGET)

funct:		process_funct.c
	$(CCC) process_funct.c
queue:		queue.c
	$(CCC) queue.c
maxheap:	maxheap.c
	$(CCC) maxheap.c
minheap:	minheap.c
	$(CCC) minheap.c

