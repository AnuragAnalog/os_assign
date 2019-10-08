#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "maxheap.h"

/********* MAINS STARTS HERE *********/
/*int main(void)        // un-comment this for testing heap program
{
   int        len = 0, opt, val1, val2;
   Maxheap    heap[MAXHEAP];

   while (opt != 4)
   {
      opt = max_menu();
      //system("clear");
      switch (opt)
      {
         case 1:
               printf("*** Insert a node ***\n");
               printf("Enter the key to be max_inserted: ");
               scanf("%d", &val1);
               printf("Enter the value to be max_inserted: ");
               scanf("%d", &val2);
               len = max_insert(heap, len, val1, val2);
               break;
         case 2:
               printf("*** Delete a node ***\n");
               val1 = max_delete(heap, len);
               len = len - 1;
               break;
         case 3:
               max_display(heap, len);
               break;
         case 4:
               printf("Hope you had a good time with my data-structure.\n");
               exit(0);
         default:
               break;
      }
   }

   exit(0);
}*/

/********* FUNCTION DEFINITION *********/
int max_insert(Maxheap heap[], int len, int key, double value)
{
   heap[len].key = key;
   heap[len].value = value;
   if (len == 0)
   {
      return len+1;
   }

   max_heapify_up(heap, len);
   return len+1;
}

int max_delete(Maxheap heap[], int len)
{
   int        hold, init = 0;

   if (len <= 0)
   {
      printf("Sorry, heap is empty");
      return -1;
   }

   hold = heap[0].key;
   heap[0].key = heap[len-1].key;
   heap[0].value = heap[len-1].value;

   max_heapify_down(heap, init, len-1);
   return hold;
}

void max_heapify_up(Maxheap heap[], int len)
{
   int         p;

   p = max_parent(len);

   if (p < 0)
   {
      return ;
   }

   if (heap[p].value < heap[len].value)
   {
      max_swapf(&heap[p].value, &heap[len].value);
      max_swap(&heap[p].key, &heap[len].key);
      max_heapify_up(heap, p);
   }

   return ;
}

void max_heapify_down(Maxheap heap[], int s, int len)
{
   int        r, l, cmp;

   r = max_right_child(s);
   l = max_left_child(s);

   if (l <= len && heap[l].value > heap[s].value)
   {
      cmp = l;
   }
   else
   {
      cmp = s;
   }

   if (r <= len && heap[r].value > heap[cmp].value)
   {
      cmp = r;
   }

   if (cmp != s)
   {
      max_swap(&heap[cmp].key, &heap[s].key);
      max_swapf(&heap[cmp].value, &heap[s].value);
      max_heapify_down(heap, cmp, len);
   }

   return ;
}

void max_display(Maxheap heap[], int len)
{
   int        i;

   if (len == 0)
   {
      printf("Sorry tree is empty.\n");
      return ;
   }

   for (i = 0; i < len; i++)
   {
      printf("(%d, %f), ", heap[i].key, heap[i].value);
   }
   printf("\n");

   return ;
}

bool max_is_member(Maxheap heap[], int value, int len)
{
   int         i;

   for (i = 0; i < len; i++)
   {
      if (heap[i].key == value)
      {
         return true;
      }
   }

   return false;
}

int max_left_child(int k)
{
   return 2*k+1;
}

int max_right_child(int k)
{
   return 2*k+2;
}

int max_parent(int k)
{
   return (int) (k-1)/2;
}

void max_swap(int *a, int *b)
{
   int      tmp;

   tmp = *a;
   *a = *b;
   *b = tmp;

   return ;
}

void max_swapf(double *a, double *b)
{
   double    tmp;

   tmp = *a;
   *a = *b;
   *b = tmp;

   return ;
}

int max_menu()
{
   int       option;

   printf("\n--------------------------\n");
   printf("         Binary Heap        \n");
   printf("----------------------------\n");
   printf("Your operations are: \n");
   printf("1) Insert a node.\n");
   printf("2) Delete a node.\n");
   printf("3) Display the tree.\n");
   printf("4) Exit\n");

   printf("Enter your choice: ");
   scanf("%d", &option);

   return option;
}
