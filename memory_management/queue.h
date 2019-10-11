/********* DEFINED CONSTANTS *********/
#define   MAXQ        1536

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