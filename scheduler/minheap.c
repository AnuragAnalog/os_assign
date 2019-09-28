#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minheap.h"

/********* MAINS STARTS HERE *********/
/*int main(void)        // un-comment this for testing heap program
{
   int        len = 0, opt, val1, val2;
   Minheap    heap[MINHEAP];

   while (opt != 4)
   {
      opt = min_menu();
      //system("clear");
      switch (opt)
      {
         case 1:
               printf("*** Insert a node ***\n");
               printf("Enter the key to be min_inserted: ");
               scanf("%d", &val1);
               printf("Enter the value to be min_inserted: ");
               scanf("%d", &val2);
               len = min_insert(heap, len, val1, val2);
               break;
         case 2:
               printf("*** Delete a node ***\n");
               val1 = min_delete(heap, len);
               len = len - 1;
               break;
         case 3:
               min_display(heap, len);
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
int min_insert(Minheap heap[], int len, int key, int value)
{
   heap[len].key = key;
   heap[len].value = value;
   if (len == 0)
   {
      return len+1;
   }

   min_heapify_up(heap, len);
   return len+1;
}

int min_delete(Minheap heap[], int len)
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

   min_heapify_down(heap, init, len-1);
   return hold;
}

void min_heapify_up(Minheap heap[], int len)
{
   int         p;

   p = min_parent(len);

   if (p < 0)
   {
      return ;
   }

   if (heap[p].value > heap[len].value)
   {
      min_swap(&heap[p].value, &heap[len].value);
      min_swap(&heap[p].key, &heap[len].key);
      min_heapify_up(heap, p);
   }

   return ;
}

void min_heapify_down(Minheap heap[], int s, int len)
{
   int        r, l, cmp;

   r = min_right_child(s);
   l = min_left_child(s);

   if (l <= len && heap[l].value < heap[s].value)
   {
      cmp = l;
   }
   else
   {
      cmp = s;
   }

   if (r <= len && heap[r].value < heap[cmp].value)
   {
      cmp = r;
   }

   if (cmp != s)
   {
      min_swap(&heap[cmp].key, &heap[s].key);
      min_swap(&heap[cmp].value, &heap[s].value);
      min_heapify_down(heap, cmp, len);
   }

   return ;
}

void min_display(Minheap heap[], int len)
{
   int        i;

   if (len == 0)
   {
      printf("Sorry tree is empty.\n");
      return ;
   }

   for (i = 0; i < len; i++)
   {
      printf("(%d, %d), ", heap[i].key, heap[i].value);
   }
   printf("\n");

   return ;
}

bool min_is_member(Minheap heap[], int value, int len)
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

int min_left_child(int k)
{
   return 2*k+1;
}

int min_right_child(int k)
{
   return 2*k+2;
}

int min_parent(int k)
{
   return (int) (k-1)/2;
}

void min_swap(int *a, int *b)
{
   int      tmp;

   tmp = *a;
   *a = *b;
   *b = tmp;

   return ;
}

void min_swapf(double *a, double *b)
{
   double    tmp;

   tmp = *a;
   *a = *b;
   *b = tmp;

   return ;
}

int min_menu()
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
