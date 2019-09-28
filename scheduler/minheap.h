/********* DEFINED CONSTSNATS *********/
#define MINHEAP      100

/********* STRUCTURE DEFINITION *********/
typedef struct minheap
{
   int        key;
   int        value;
} Minheap;

/********* FUNCTION DECLARATION *********/
int min_menu();
int min_left_child(int k);
int min_right_child(int k);
int min_parent(int k);
int min_insert(Minheap heap[], int len, int key, int value);
int min_delete(Minheap heap[], int len);
void min_heapify_up(Minheap heap[], int len);
void min_heapify_down(Minheap heap[], int len, int len1);
void min_display(Minheap heap[], int len);
void min_swap(int *a, int *b);
void min_swapf(double *a, double *b);
bool min_is_member(Minheap heap[], int value, int len);