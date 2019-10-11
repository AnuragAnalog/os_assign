#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "queue.h"
#include "memory_management.h"

/********* GLOBAL VARIABLES *********/
int           ind = 0, np = 0;

/********* MAIN STARTS HERE *********/
int main(int argc, char **argv)
{
   int        i, pid, cur_pid, status, m, s;
   char       infile[FNAME] = "AR_\0", outfile[FNAME] = "AR_\0", check;
   FILE       *ifp = NULL, *ofp = NULL;

   if (argc != 3)
   {
      fprintf(stderr, "Syntax: %s <NP> <filename>\n", argv[0]);
      exit(1);
   }

   np = atoi(argv[1]);
   ifp = fopen(argv[2], "r");
   if (ifp == NULL)
   {
      fprintf(stderr, "Sorry the requested file(%s) doesn't exist, or", argv[2]);
      fprintf(stderr, "it doesn't have a read permission.\n");
      exit(2);
   }

   check = fgetc(ifp);
   if (check == EOF)
   {
      fprintf(stderr, "%s is an empty file.\n", argv[2]);
      exit(3);
   }
   rewind(ifp);
   initialize_ready_q(np);

   for (pid = 1; pid < np+1; pid++)
   {
      fscanf(ifp, "%d %d", &m, &s);
      make_process(pid, m, s);
   }

   for (i = 0; i < np; i++)
   {
      file_desp[i] = NULL;
   }

   for (i = 0; i < MAXFRAMES; i++)
   {
      phy_mem[i].pgnum = -1;
   }

   while (!isempty(&proc_queue))
   {
      cur_pid = delete(&proc_queue);
      filename(infile, cur_pid, INFILE);
      if (file_desp[cur_pid-1] == NULL)
      {
         file_desp[cur_pid-1] = fopen(infile, "r");
      }
      filename(outfile, cur_pid, OUTFILE);
      ofp = fopen(outfile, "a+");
      status = mem_mapper(file_desp[cur_pid-1], ofp, cur_pid);
      fclose(ofp);

      if (status == MEMFULL)
      {
         printf("Memory not available\n");
         exit(4);
      }
      else if (status == TERMINATED)
      {
         printf("Process %d completed; removing from queue;\n", cur_pid);
         fclose(file_desp[cur_pid-1]);
      }
      else if (status == CONTINUE)
      {
         insert(&proc_queue, cur_pid);
      }
   }

   printf("\nFinal Frame-Table\n");
   display_frametable();
   exit(0);
}