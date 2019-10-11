# Process Simulator

**Goal**

Implement a program which simulates a process generation of many processes.

**Languages Used**

1) C

**Data-Structures Used**

* Queue

**Algorithms Used**

* Fisher-yates Shuffling Algorithm.

**Run**

There is a make file included. It is self-explanatory

**Procedure**

Many processes will be loaded into memory concurrently. However, we still assume that the total memory required for all the processes is less than the available physical memory. The process PIDs will start at 1 and sequentially go up to the number of processes (NP). NP is a global variable.

* **Physical Memory (Structure):** Create a global data structure phys_mem to represent physical memory. Its size must be equal to the number of frames. Each entry should keep track of the page number loaded into that frame along with the process PID, if a page is loaded; or a value indicating free frame. This data structure should be initialised to all free frames at the beginning.

     
* **Process Ready Queue (Data Structure):** Create a global data structure proc_queue to represent the ready queue. Its size is NP. Initialise it randomly with process PIDs.

Write the following programs:

* **Process Simulator:** int sim_process (int M, int S, FILE *outfile)
    M (number of pages), S, a real value between 0 and 5 indicating how well-behaved the program is (0 is Very well behaved, 5 is very poor).
    1. Generate a random number C less than M
    2. Generate a second random number L between 512 and 4096
    3. Generate 0.9 * L (round to the nearest integer) random numbers according to a Normal Distribution with mean C * 4096 + 2048 and standard deviation 500 * (S+1)
    4. Update C by generating it again as a random number less than M
    5. Generate 0.1 * L (round to the nearest integer) random numbers according to a uniform distribution between 0 and C.
    6. Repeat steps (2 - 5), M times.
    7. Write all the random numbers into the output file filename
    Return value is the number of address strings written into outfile.
     
* **Memory Mapper:** int mem_mapper (FILE *infile, FILE *outfile, int pid)
    1. Generate a random number A uniformly between 512 and 4096.
    2. Read the address reference from filename
    3. Calculate page number P and offset X
    4. If P is in memory with it's pid, write the triplet (logical, physical, 0) into outfile
    5. If P is not in memory, find a free frame E in memory.
    6. If E is found, then update the memory along with it's pid, calculate physical address; write the triplet (logical, physical, 1) to output file outfile
    7. Repeat the above steps until all A address references are read.
    8. The function returns a negative value if there is no free frame in physical memory to load a page; 0 ("terminated" status) if the entire file of address references is processed; and, a positive value if there are more addresses to be processed.
     
* **Memory Manager:** This is the main program for the present! It works as follows:
    1. For every PID from 1 ... NP, run process simulator with outfile = AR_pp.dat where pp stands for the PID of the process. If the PID is 1, it should be written into AR_01.dat file.
    2. Open the AR_*.dat files for reading.
    3. For every PID, open a file AR_pp_out.dat for writing the logical, physical addresses and page faults triplets.
    4. Initialise proc_queue and phys_mem.
    5. Get the first PID cur_pid from proc_queue.
    6. Call the mem_mapper() function with the correct input and output files and cur_pid.
    7. If return value is negative, exit with an error message Memory not available
        If return value is 0 (process terminated normally), print an informative message Process pid of the process completed; removing from queue;
        if the return value is positive, insert the process PID at the end of proc_queue.
    8. Repeat the last three steps (5 - 7) until proc_queue is empty.
    9. Print phys_mem data structure to see the current page to frame mapping of each process,

