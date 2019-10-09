/********* DEFINED CONSTANTS *********/
#define   FCFS         0
#define   SJF          1
#define   RR           2
#define   HRRN         3
#define   NONPREMPTIVE 4
#define   PREMPTIVE    5
#define   MAX          20
#define   INFINITY     true

/********* STRUCTURE DEFINITION *********/
typedef struct PCB
{
   int        pid;
   int        arrival;
   int        time;
   int        start;
   int        wait;
   int        remaining;
   int        end;
} pcb;

/********* GLOBAL VARIABLES *********/
pcb        proc[MAX], cpu;              // Process Control Block

/********* FUNCTION DECLARATION *********/
int menu();
void reset_cpu();
void print_status(int param);
void put_proc_inq(Queue *q);
void update_pcb1(Queue *q);
void update_pcb2(Minheap heap[], int len);
void update_pcb3(Maxheap heap[], int len);
void run_fcfs(Queue *q, bool idle);
void run_sjf(Minheap minheap[], int min_h);
void run_round_robin(Queue *q, bool idle);
void run_hrrn(Maxheap maxheap[], int max_h, int param);
void run_randomized(Queue *q, bool idle, int param);
void load_process(int index, int param);
int update_response_ratio(Maxheap heap[], int len);
int put_proc_in_maxheap(Maxheap maxheap[], int len);
int put_proc_in_minheap(Minheap minheap[], int len);
bool fcfs(Queue *q);
int sjf(Minheap heap[], int len);
bool round_robin(Queue *q);
int hrrn(Maxheap heap[], int len);
int hrrn_premptive(Maxheap heap[], int len);
bool randomized(Queue *q);
bool randomized_premptive(Queue *q);
