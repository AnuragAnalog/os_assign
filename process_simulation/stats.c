#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********* DEFINED CONSTANTS *********/
#define   MAX        512

/********* FUNCTION DECLARATION *********/
void display_stats(FILE *fp);
void initialize(int array[], int size);

/********* MAIN STARTS HERE *********/
int main(int argc, char **argv)
{
   char       *fname = NULL, check;
   FILE       *fp = NULL;

   if (argc != 2)
   {
      fprintf(stderr, "Syntax: %s <Filename>\n", argv[0]);
      exit(1);
   }

   fname = argv[1];
   fp = fopen(fname, "r");
   if (fp == NULL)
   {
      fprintf(stderr, "Sorry the requested file(%s) doesn't exist, or", fname);
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

   display_stats(fp);

   exit(0);
}

/********* FUNCTION DEFINITION *********/
void initialize(int array[], int size)
{
   int       i;

   for (i = 0; i < size; i++)
   {
      array[i] = -1;
   }

   return ;
}

void display_stats(FILE *fp)
{
   int        i = 0, log, pg_fault, addr_ref = 0, total_pg_flt = 0;
   int        ref_table[MAX];
   char       line[MAX];

   initialize(ref_table, MAX);

   while (fscanf(fp, "%s", line) != EOF)
   {
      log = atoi(strtok(line, ","));
      atoi(strtok(NULL, ","));
      pg_fault = atoi(strtok(NULL, ","));

      addr_ref = addr_ref + 1;
      if (ref_table[log] == -1)
      {
         ref_table[log] = 1;
      }
      else
      {
          ref_table[log] = ref_table[log] + 1;
      }

      if (pg_fault == 1)
      {
         total_pg_flt = total_pg_flt + 1;
      }
   }

   printf("+-----------------------+\n");
   printf("|Pg num\t| No. of ref.\t|\n");
   printf("+-----------------------+\n");
   while (ref_table[i] != -1)
   {
      printf("|%d\t| %d\t\t|\n", i, ref_table[i]);
      i = i + 1;
   }
   printf("+-----------------------+\n");
   printf("Page Fault Ratio:- %f\n", (double) total_pg_flt/ (double) addr_ref);
   return ;
}
