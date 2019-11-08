#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "queue.h"
#include "memory_management.h"

/********* REFERENCEING GLOBAL VARIABLES *********/
extern int           ff_global, ind, np, pg_replace;

/********* FUNCTION DEFINITION *********/
void initialize_ready_q(int np)
{
   int        i, tmp_arr[MAXFRAMES];

   initialize(&proc_queue);
   for (i = 0; i < np; i++)
   {
      tmp_arr[i] = i+1;
   }

   shuffle_q(tmp_arr, np);

   for (i = 0; i < np; i++)
   {
      insert(&proc_queue, tmp_arr[i]);
   }

   return ;
}

void shuffle_q(int arr[], int size)
{
   int        i, j;

   srand(time(0));

   for (i = size-1; i > 0; i--)
   {
      j = rand() % i;
      swap(&arr[i], &arr[j]);
   }

   return ;
}

void swap(int *a, int *b)
{
   int        tmp;

   tmp = *b;
   *b = *a;
   *a = tmp;

   return ;
}

int no_of_digits(int num)
{
   int      count = 0;

   while (num != 0)
   {
      count = count + 1;
      num = (int) num / 10;
   }

   return count;
}

int rand_range(int lower, int upper)
{
   int        num;

   num = (int) (rand() % (upper - lower + 1)) + lower;
   return num;
}

int sim_process(int m, int s, FILE *fp)
{
   int        i, j, c, l, d, size1, size2, val, tot_ref = 0;
   int        normal[ULIMIT], uniform[ULIMIT];
   time_t     t;

   for (i = 0; i < m; i++)
   {
      c = (int) (m * drand48());
      l = rand_range(LLIMIT, ULIMIT);
   
      d = c * 4096 + 2048;
      size1 = (int) floorf(0.9*l);
   
      srand((unsigned) time(&t));

      j = 0;
      while (j < size1)
      {
         val = (int) (drand48() * (512 * (s+1)) + d);
         normal[j] = val;
         fprintf(fp, "%d ", normal[j]);
         j = j + 1;
      }
      fprintf(fp, "\n");

      c = ((int) (m * drand48())) + 1;
      size2 = (int) floorf(0.1*l);

      for (j = 0; j < size2; j++)
      {
         uniform[j] = (int) (drand48() * c);
         fprintf(fp, "%d ", uniform[j]);
      }
      fprintf(fp, "\n\n");
      tot_ref = tot_ref + size1 + size2;
   }

   return tot_ref;
}

void make_process(int pid, int m, int s)
{
   char       fname[FNAME] = "AR_\0";
   FILE       *fp = NULL;

   filename(fname, pid, INFILE);
   fp = fopen(fname, "w");
   page_pid[pid-1].pg_reference = sim_process(m, s, fp);
   fclose(fp);

   return ;
}

int mem_mapper(FILE *ifp, FILE *ofp, int pid)
{
   int    i = 0, j, a, pgnum, offset, addr, f_stat, rep_pg;
   char   buff[MAXCHAR];
   bool   check;

   a = rand_range(LLIMIT, ULIMIT);
   while (i < a)
   {
      f_stat = fscanf(ifp, "%s", buff);
      if (f_stat == EOF)
      {
         return 0;
      }

      check = true;
      addr = atoi(buff);
      pgnum = (int) addr/PAGESIZE;
      offset = addr%PAGESIZE;

      if (ind == MAXFRAMES)
      {
         check = in_memory(pid, ind, addr, ofp);
         if (check)
         {
            if (pg_replace == GLOBAL)
            {
               rep_pg = page_fifo_global();
               phy_mem[rep_pg].pid = pid;
               phy_mem[rep_pg].pgnum = pgnum;
            }
            else if (pg_replace == LOCAL)
            {
               rep_pg = page_fifo_local(pid);
               phy_mem[rep_pg].pgnum = pgnum;
            }
            page_pid[pid-1].pg_replacement = page_pid[pid-1].pg_replacement + 1;
            page_pid[pid-1].pg_fault = page_pid[pid-1].pg_fault + 1;
            fprintf(ofp, "%d,%d,1\n", addr, rep_pg * PAGESIZE + offset);
         }
      }
      else
      {
         check = in_memory(pid, ind, addr, ofp);
         if (check)
         {
            if (ff_local[pid-1].firstframe == -1)
            {
               ff_local[pid-1].firstframe = ind;
               ff_local[pid-1].first = true;
            }
            page_pid[pid-1].pg_fault = page_pid[pid-1].pg_fault + 1;
            fprintf(ofp, "%d,%d,1\n", addr, ind * PAGESIZE + offset);
            phy_mem[ind].pgnum = pgnum;
            phy_mem[ind].pid = pid;
            ind = ind + 1;
         }
      }
      i = i + 1;
   }

   return 1;
}

bool in_memory(int pid, int index, int addr, FILE *ofp)
{
   int        i, pgnum, offset;

   pgnum = (int) addr/PAGESIZE;
   offset = addr%PAGESIZE;

   for (i = 0; i < ind; i++)
   {
      if (phy_mem[i].pgnum == pgnum && phy_mem[i].pid == pid)
      {
         fprintf(ofp, "%d,%d,0\n", addr, i * PAGESIZE + offset);
         return false;
      }
   }

   return true;
}

int page_fifo_global()
{
   ff_global = (ff_global + 1) % MAXFRAMES;

   return ff_global;
}

int page_fifo_local(int pid)
{
   int        i, frame_no = -1;

   if (ff_local[pid-1].first)
   {
      frame_no = ff_local[pid-1].firstframe;
      ff_local[pid-1].first = false;
   }

   if (ff_local[pid-1].first == false && frame_no == -1)
   {
      for (i = 0; i < np; i++)
      {
         if (pid-1 == i)
         {
            frame_no = ff_local[i].cur_frame;
         }
      }
   }

   for (i = frame_no+1; i < MAXFRAMES; i++)
   {
      if (phy_mem[i].pid == pid)
      {
         ff_local[pid-1].cur_frame = i;
         break;
      }
   }
   if (i == MAXFRAMES)
   {
      ff_local[pid-1].cur_frame = ff_local[pid-1].firstframe;
      ff_local[pid-1].first = true;
   }

   return frame_no;
}

void calc_display_slowdown_rate()
{
   int        i, num = 0, den = 0;

   printf("+-------------------------------------------------------+\n");
   printf("|PID\t|Expected time\t|Observed time\t|%c Slow down\t|\n", 37);
   printf("+-------------------------------------------------------+\n");
   for (i = 0; i < np; i++)
   {
      slowdown[i].expected = page_pid[i].pg_reference*1;
      slowdown[i].observed = (page_pid[i].pg_reference - page_pid[i].pg_fault)*1 + (page_pid[i].pg_fault - page_pid[i].pg_replacement)*PG_FLT_TIME + page_pid[i].pg_replacement*PG_REPLACE_TIME;
      slowdown[i].percent_slow = 100 * (double) (slowdown[i].observed - slowdown[i].expected)/ (double) slowdown[i].expected;
      printf("|%d\t|%d\tms\t|%d\tms\t|%f %c\t|\n", i+1, slowdown[i].expected, slowdown[i].observed, slowdown[i].percent_slow, 37);
      num = num + slowdown[i].observed - slowdown[i].expected;
      den = den + slowdown[i].expected;
   }
   printf("+-------------------------------------------------------+\n");
   printf("Total Slow down %.2f %c\n", 100 * (double) num/(double) den, 37);
   printf("Average Slow down %.2f %c\n", 100 * (double) num/((double) den*(double) np), 37);
   return ;
}

void display_frametable()
{
   int        i = 0;

   printf("+-----------------------+\n");
   printf("|Pid\t|Page no.\t|\n");
   printf("+-----------------------+\n");
   while (i < ind)
   {
      printf("|%d\t|%d\t\t|\n", phy_mem[i].pid, phy_mem[i].pgnum);
      i = i + 1;
   }
   printf("+-----------------------+\n");

   return ;
}

void display_page_flt_table()
{
   int        i;

   printf("+---------------------------------------------------------------+\n");
   printf("|Pid\t|Page-fault\t|Page-replacement\t|Page-references|\n");
   printf("+---------------------------------------------------------------+\n");
   for (i = 0; i < np; i++)
   {
      printf("|%d\t|%d\t\t|%d\t\t\t|%d\t\t|\n", i+1, page_pid[i].pg_fault, page_pid[i].pg_replacement, page_pid[i].pg_reference);
   }
   printf("+---------------------------------------------------------------+\n");

   return ;
}

void filename(char *fname, int pid, int param)
{
   int        dig;

   dig = no_of_digits(pid);

   if (param == INFILE)
   {
      if (dig == 1)
      {
         snprintf(fname, FNAME, "AR_000%d.dat", pid);
      }
      else if (dig == 2)
      {
         snprintf(fname, FNAME, "AR_00%d.dat", pid);
      }
      else if (dig == 3)
      {
         snprintf(fname, FNAME, "AR_0%d.dat", pid);
      }
      else
      {
         snprintf(fname, FNAME, "AR_%d.dat", pid);
      }
   }
   else if (param == OUTFILE)
   {
      if (dig == 1)
      {
         snprintf(fname, FNAME, "AR_000%d_out.dat", pid);
      }
      else if (dig == 2)
      {
         snprintf(fname, FNAME, "AR_00%d_out.dat", pid);
      }
      else if (dig == 3)
      {
         snprintf(fname, FNAME, "AR_0%d_out.dat", pid);
      }
      else
      {
         snprintf(fname, FNAME, "AR_%d_out.dat", pid);
      }  
   }

   return ;
}
