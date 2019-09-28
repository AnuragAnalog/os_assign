/********* DEFINED CONSTSNATS *********/
#define MAXHEAP      100

/********* STRUCTURE DEFINITION *********/
typedef struct maxheap
{
   int        key;
   double      value;
} Maxheap;

/********* FUNCTION DECLARATION *********/
int max_menu();
int max_left_child(int k);
int max_right_child(int k);
int max_parent(int k);
int max_insert(Maxheap heap[], int len, int key, int value);
int max_delete(Maxheap heap[], int len);
void max_heapify_up(Maxheap heap[], int len);
void max_heapify_down(Maxheap heap[], int len, int len1);
void max_display(Maxheap heap[], int len);
void max_swap(int *a, int *b);
void max_swapf(double *a, double *b);
bool max_is_member(Maxheap heap[], int value, int len);