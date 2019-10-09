/********* DEFINED CONSTANTS *********/
#define   MAXQ        100

/********* DATA-STRUCTURE DEFINITION *********/
typedef struct queue2
{
   int        front, rear;
   int        items[MAXQ];
} Queue;

/********* FUNCTION DECLARATION *********/
void initialize(Queue *q);
int isempty(Queue *q);
int isfull(Queue *q);
void insert(Queue *q, int val);
int delete(Queue *q);
void display(Queue *q);
bool is_member(Queue *q, int value);
void shuffle_the_q(Queue *q);
void swap(int *a, int *b);