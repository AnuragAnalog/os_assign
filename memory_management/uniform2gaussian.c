#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

/********* FUNCTION DECLARATION *********/
double rand_normal(double mean, double sigma);
double rand_uniform(double mean, double sigma);

/********* FUNCTION DEFINITION *********/
double rand_normal(double mean, double sigma)
{
   static double V1, V2, S;
   static int phase = 0;
   double X, U1, U2;

   if (phase == 0) 
   {
      do
      {
         U1 = (double)rand() / RAND_MAX;
         U2 = (double)rand() / RAND_MAX;
	       
         V1 = 2 * U1 - 1;
         V2 = 2 * U2 - 1;
         S = V1 * V1 + V2 * V2;
      } while (S >= 1 || S == 0);
      X = V1 * sqrt(-2 * log(S) / S);
   }
   else
   {
      X = V2 * sqrt(-2 * log(S) / S);
   }
   phase = 1 - phase;
   X = X * sigma + mean;

   return X;
}

double rand_uniform(double ll, double hh)
{
   double X, U1;

   U1 = (double)rand() / RAND_MAX;
   X = (hh - ll) * U1 + ll;

   return(X);
}
