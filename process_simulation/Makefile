
# Makefile

CC = gcc
CFLAGS = -Wall
MFLAG = -lm
TARGET1 = process_simulation
TARGET2 = memory_manager
TARGET3 = stats

all:	process memory stats

clean:
	rm *.dat $(TARGET1) $(TARGET2) $(TARGET3)

process:	process_simulation.c
	$(CC) $(CFLAGS) process_simulation.c -o $(TARGET1) $(MFLAG)

memory:		memory_manager.c
	$(CC) $(CFLAGS) memory_manager.c -o $(TARGET2)

stats:		stats.c
	$(CC) $(CFLAGS) stats.c -o $(TARGET3)

