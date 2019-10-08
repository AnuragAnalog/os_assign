#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "queue.h"
#include "maxheap.h"
#include "minheap.h"
#include "process.h"

/********* REFERENCING GLOBAL VARIABLES *********/
extern int     cur_time, wait_t;

/********* FUNCTION DEFINITION *********/
void reset_cpu()                      // Idle cpu
{
   cpu.pid = -1;
   cpu.arrival = -1;
   cpu.time = -1;
   cpu.start = -1;
   cpu.remaining = -1;
   cpu.wait = -1;
   cpu.end = -1;

   return ;
}

void load_process(int index, int param)
{
   cpu.pid = proc[index].pid;
   cpu.arrival = proc[index].arrival;
   cpu.time = proc[index].time;
   cpu.start = cur_time;
   proc[index].start = cur_time;
   cpu.remaining = proc[index].remaining;
   cpu.wait = proc[index].wait;

   if (param == 0 || param == 1)
   {
       cpu.end = cpu.start + cpu.time;
       proc[index].end = cpu.end;
   }
   else if (param == 2 || param == 3)
   {
      cpu.end = cpu.start + cpu.time;
      proc[index].end = -1;
   }

   return ;
}

void update_pcb1(Queue *q)                  // Only for FCFS, RR
{
   int      i;

   for (i = 0; i < MAX; i++)
   {
      if (is_member(q, proc[i].pid))
      {
         proc[i].wait = proc[i].wait + 1;
      }
   }

   return ;
}

void update_pcb2(Minheap heap[], int len)  // Only for SJN
{
   int        i;

   for (i = 0; i < MAX; i++)
   {
      if (min_is_member(heap, proc[i].pid, len))
      {
         proc[i].wait = proc[i].wait + 1;
      }
   }

   return ;
}

void update_pcb3(Maxheap heap[], int len)  // Only for HRRN
{
   int        i;
   
   for (i = 0; i < MAX; i++)
   {
      if (max_is_member(heap, proc[i].pid, len))
      {  
         proc[i].wait = proc[i].wait + 1;
      }
   }

   return ;
}

void put_proc_inq(Queue *q)                   // Only for FCFS, RR
{
   int        i;

   for (i = 0; i < MAX; i++)
   {
      if (proc[i].arrival == cur_time)
      {
         insert(q, proc[i].pid);
      }
   }

   return ;
}

int put_proc_in_maxheap(Maxheap maxheap[], int len) // Only for HRRN
{
   int        i;
   double     ratio, num, den;

   for (i = 0; i < MAX; i++)
   {
      if (proc[i].arrival == cur_time)
      {
         num = (double) proc[i].wait;
         den = (double) proc[i].time;
         ratio = num/den + (double) 1;
         len = max_insert(maxheap, len, proc[i].pid, ratio);
      }
   }

   return len;
}

int put_proc_in_minheap(Minheap minheap[], int len)  // Only for SJN
{
   int        i;

   for (i = 0; i < MAX; i++)
   {
      if (proc[i].arrival == cur_time)
      {
         len = min_insert(minheap, len, proc[i].pid, proc[i].time);
      }
   }

   return len;
}

void print_status(int param)                // Print cpu status
{
   printf("Current time is-> %d\n", cur_time);
   printf("Running process details\n");
   printf("PID: %d ", cpu.pid);
   printf("Arrival time: %d ", cpu.arrival);
   printf("Execution time: %d ", cpu.time);
   if (param == 0 || param == 1)
   {
      printf("Start time: %d ", cpu.start);
      printf("End time: %d\n", cpu.end);
   }
   else if (param == 2 || param == 3)
   {
      printf("Remaining time: %d ", cpu.remaining);
      printf("wait time: %d\n", cpu.wait);
      printf("Start time: %d ", cpu.start);
      printf("End time: %d\n", cpu.end);
   }
   printf("\n\n");

   return ;
}

int update_response_ratio(Maxheap heap[], int len)
{
   int        i, j, pid, tlen = 0, tmp[MAX];
   double     ratio, num, den;

   while (len != 0)
   {
      pid = max_delete(heap, len);
      tmp[tlen] = pid;
      tlen = tlen + 1;
      len = len - 1;
   }

   len = 0;
   for (i = 0; i < tlen; i++)
   {
      for (j = 0; j < MAX; j++)
      {
         if (tmp[i] == proc[j].pid)
         {
            num = (double) proc[j].wait;
            den = (double) proc[j].time;
            ratio = num/den;
            len = max_insert(heap, len, proc[j].pid, 1+ratio);
         }
      }
   }

   return len;
}

void run_fcfs(Queue *q, bool idle)
{
   while (INFINITY)
   {
      put_proc_inq(q);
      idle = fcfs(q);
      if (idle)
         break;
      print_status(FCFS);
      if (!isempty(q))
         update_pcb1(q);
      cur_time = cur_time + 1;
      cpu.remaining = cpu.remaining - 1;
   }

   return ;
}

void run_sjf(Minheap minheap[], int min_h)
{
   while (INFINITY)
   {
      min_h = put_proc_in_minheap(minheap, min_h);
      min_h = sjf(minheap, min_h);
      if (min_h == 0 && cpu.pid == -1)
         break;
      print_status(SJF);
      if (min_h != 0)
         update_pcb2(minheap, min_h);
      cur_time = cur_time + 1;
      cpu.remaining = cpu.remaining - 1;
   }

   return ;
}

void run_round_robin(Queue *q, bool idle)
{
   while (INFINITY)
   {
      put_proc_inq(q);
      idle = round_robin(q);
      if (idle)
         break;
      print_status(RR);
      if (!isempty(q))
         update_pcb1(q);
      cur_time = cur_time + 1;
      cpu.remaining = cpu.remaining - 1;
   }

   return ;
}

void run_hrrn(Maxheap maxheap[], int max_h, int param)
{
   while (INFINITY)
   {
      max_h = put_proc_in_maxheap(maxheap, max_h);
      if (param == 4)
      {
         max_h = hrrn(maxheap, max_h);
      }
      else if (param == 5)
      {
         max_h = hrrn_premptive(maxheap, max_h);
      }
      
      if (max_h == 0 && cpu.pid == -1)
         break;
      print_status(HRRN);
      if (max_h != 0)
         update_pcb3(maxheap, max_h);
      cur_time = cur_time + 1;
      cpu.remaining = cpu.remaining - 1;
   }

   return ;
}

bool fcfs(Queue *q)
{
   int        i, pid, check = false;

   if (cpu.pid == -1)
   {
      if (isempty(q))
      {
         printf("There are no more processes in the Queue\n");
         return true;
      }
      else
      {
         pid = delete(q);
         for (i = 0; i < MAX; i++)
         {
             if (pid == proc[i].pid)
             {
                load_process(i, FCFS);
                break;
             }
         }
      }
   }
   else
   {
      if (cpu.end == cur_time)
      {
         reset_cpu();
         check = fcfs(q);
      }
   }

   return check;
}

int sjf(Minheap heap[], int len)
{
   int        i, pid;

   if (cpu.pid == -1)
   {
      if (len == 0)
      {
         printf("There are no more processes in the Queue\n");
         return 0;
      }
      else
      {
         pid = min_delete(heap, len);
         len = len - 1;
         for (i = 0; i < MAX; i++)
         {
             if (pid == proc[i].pid)
             {  
                load_process(i, SJF);
                break;
             }
         }
      }
   }
   else
   {
      if (cpu.end == cur_time)
      {
         reset_cpu();
         len = sjf(heap, len);
      }
   }

   return len;
}

bool round_robin(Queue *q)
{
   int        i, pid1, pid2, rem;
   bool       check = false;

   if (cpu.pid == -1)
   {
      if (isempty(q))
      {
         printf("There are no more processes in the Queue\n");
         return true;
      }
      else
      {
         pid1 = delete(q);
         for (i = 0; i < MAX; i++)
         {
             if (pid1 == proc[i].pid)
             {
                load_process(i, RR);
                break;
             }
         }
      }
   }
   else
   {
      if (cpu.remaining == 0)
      {
         reset_cpu();
         check = round_robin(q);
      }
      else
      {
         if (!isempty(q))
         {
            pid1 = delete(q);
            pid2 = cpu.pid;
            rem = cpu.remaining;
            for (i = 0; i < MAX; i++)
            {
                if (pid1 == proc[i].pid)
                {
                   load_process(i, RR);
                   break;
                }
            }
            for (i = 0; i < MAX; i++)
            {
               if (pid2 == proc[i].pid)
               {
                  insert(q, pid2);
                  proc[i].remaining = rem;
                  break;
               }
            }
         }
      }
   }

   return check;
}

int hrrn(Maxheap heap[], int len)
{
   int        i, pid1, pid2, rem;

   if (cpu.pid == -1)
   {
      if (len == 0)
      {
         printf("There are no more processes in the Queue\n");
         return 0;
      }
      else
      {
         len = update_response_ratio(heap, len);
         pid1 = max_delete(heap, len);
         len = len - 1;
         for (i = 0; i < MAX; i++)
         {
             if (pid1 == proc[i].pid)
             {
                load_process(i, HRRN);
                break;
             }
         }
      }
   }
   else
   {
      if (cpu.end == cur_time)
      {
         reset_cpu();
         len = hrrn(heap, len);
      }
   }

   return len;
}

int hrrn_premptive(Maxheap heap[], int len)
{
   int        i, pid1, pid2, rem, num, den;
   double     ratio;

   if (cpu.pid == -1)
   {
      if (len == 0)
      {
         printf("There are no more processes in the Queue\n");
         return 0;
      }
      else
      {
         len = update_response_ratio(heap, len);
         pid1 = max_delete(heap, len);
         len = len - 1;
         for (i = 0; i < MAX; i++)
         {
             if (pid1 == proc[i].pid)
             {
                load_process(i, HRRN);
                break;
             }
         }
      }
   }
   else
   {
      if (cpu.remaining == 0)
      {
         reset_cpu();
         len = hrrn_premptive(heap, len);
      }
      else
      {
         pid2 = cpu.pid;
         for (i = 0; i < MAX; i++)
         {
            if (pid2 == proc[i].pid)
            {
               proc[i].remaining = proc[i].remaining - 1;
               num = (double) proc[i].wait;
               den = (double) proc[i].time;
               ratio = num/den + (double) 1;
               len = max_insert(heap, len, proc[i].pid, ratio);
            }
         }

         len = update_response_ratio(heap, len);
         pid1 = max_delete(heap, len);
         len = len - 1;
         for (i = 0; i < MAX; i++)
         {
            if (pid1 == proc[i].pid)
            {
               load_process(i, HRRN);
               break;
            }
         }
      }
   }

   return len;
}

int menu()
{
   int       option;

   printf("\n--------------------------------------\n");
   printf("                Scheduler               \n");
   printf("--------------------------------------  \n");
   printf("Algorithms which I implement: \n");
   printf("1) First Come First Serve(FCFS)\n");
   printf("2) Shortest Job First(SJF)\n");
   printf("3) Round Robin(RR)\n");
   printf("4) Highest Response Ratio Next(HRRN) NON-PREMPTIVE\n");
   printf("5) Highest Response Ratio Next(HRRN) PREMPTIVE\n");
   printf("6) Exit\n");

   printf("Enter your choice: ");
   scanf("%d", &option);

   return option;
}
