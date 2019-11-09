#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "memory_management.h"

/********* REFERENCEING GLOBAL VARIABLES *********/
extern int        ff_global, np, ind;

/********* FUNCTION DEFINITION *********/
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

int least_recently_used_global()
{
   int        page;

   page = page_fifo_global();
   return page;
}

int most_recently_used_global()
{
   return ind;
}

int least_recently_used_local()
{
   int        page;

   page = page_fifo_local();
   return page;
}