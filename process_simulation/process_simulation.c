#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/********* DEFINED CONSTANTS *********/
#define   MAX        20
#define   LLIMIT     512
#define   ULIMIT     4096

/********* FUNCTION DECLARATION *********/
int rand_range(int lower, int upper);
void generate_addr(int m, int s, FILE *fp);

/********* MAIN STARTS HERE *********/
int main(int argc, char **argv)
{
   int        m, s;
   char       *fname = NULL;
   FILE       *fp = NULL;

   if (argc != 4)
   {
      fprintf(stderr, "Syntax: %s M S <filename>\n", argv[0]);
      exit(1);
   }

   m = atoi(argv[1]);
   s = atoi(argv[2]);
   fname = argv[3];

   fp = fopen(fname, "w");
   if (s < 0 || s > 5)
   {
      fprintf(stderr, "S should be in the range of [0-5]\n");
      exit(2);
   }

   generate_addr(m, s, fp);

   exit(0);
}

/********* FUNCTION DEFINITION *********/
int rand_range(int lower, int upper)
{
   int        num;

   num = (int) (rand() % (upper - lower + 1)) + lower;
   return num;
}

void generate_addr(int m, int s, FILE *fp)
{
   int        i, j, c, l, d, size1, size2, val;
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
   }

   fclose(fp);

   return ;
}
