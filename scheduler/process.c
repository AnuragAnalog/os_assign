#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "queue.h"             // User defined header files
#include "maxheap.h"           // queue, maxheap, minheap
#include "minheap.h"           // and process
#include "process.h"

/********* GLOBAL VARIABLES *********/
int        cur_time = 0, wait_t = 0;   // Current time and Total wait time

/********* MAIN STARTS HERE *********/
int main(int argc, char **argv)
{
   int        i, max_h = 0, min_h = 0, opt = 6;
   char       check, line[MAX], *fname = NULL;
   bool       idle = false;      // To check process status
   double     avg;
   FILE       *fp = NULL;
   Queue      q;                 // Ready Queue
   Maxheap    maxheap[MAX];      // Raedy Queue for HRRN
   Minheap    minheap[MAX];      // Ready Queue for SJN

   if (argc != 2)
   {
      fprintf(stderr, "Syntax: %s <filename>\n", argv[0]);
      exit(1);
   }

   fname = argv[1];
   fp = fopen(fname, "r");

   if (fp == NULL)
   {
      fprintf(stderr, "Sorry the requested file doesn't exist, or");
      fprintf(stderr, "it doesn't have a read permission.\n");
      exit(2);
   }

   check = fgetc(fp);
   if (check == EOF)
   {
      fprintf(stderr, "%s is an empty file.\n", fname);
      exit(3);
   }
   rewind(fp);

   for (i = 0; i < MAX; i++)
   {
      fgets(line, MAX, fp);
      sscanf(line, "%d %d %d", &proc[i].pid, &proc[i].arrival, &proc[i].time);
      proc[i].remaining = proc[i].time;
      proc[i].wait = 0;
      //printf("%d %d %d\n", proc[i].pid, proc[i].arrival, proc[i].time);
   }
   fclose(fp);

   reset_cpu();
   initialize(&q);

   opt = menu();
   switch (opt)
   {
      case 1:
            run_fcfs(&q, idle);
            break;
      case 2:
            run_sjf(minheap, min_h);
            break;
      case 3:
            run_round_robin(&q, idle);
            break;
      case 4:
            run_hrrn(maxheap, max_h, NONPREMPTIVE);
            break;
      case 5:
            run_hrrn(maxheap, max_h, PREMPTIVE);
            break;
      case 6:
            printf("See you soon :-)\n");
            exit(0);
   }

   printf("PID\t\tWait time\n");
   for (i = 0; i < MAX; i++)
   {
      wait_t = wait_t + proc[i].wait;
      printf("%d\t\t%d\n", proc[i].pid, proc[i].wait);
   }
   avg = (double) wait_t/ (double) MAX;
   printf("\nTotal wait time: %ds Avg wait time: %fs\n", wait_t, avg);
   printf("Total time of execution: %ds\n", cur_time);

   exit(0);
}
