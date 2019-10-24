# Scheduler

**Goal**

Implement a Scheduler with a few scheduling algorithms

**Languages Used**

1) C

**Data-Structures Used**

1) Queue (Array-based)
2) Maxheap (Array-based)
3) Minheap (Array-based)

**Run**

There is a make file included. It is self-explanatory

**Procedure**

A program to compute the waiting time and total time taken to execute all the processes using

* First-Come-First-Served
* Shortest-Job-First
* Round-Robin with a time quantum of 1 unit
* Highest-Response-Ratio-Next (Preemptive & Non-preemptive)
* Random (Preemptive & Non-preemptive)

scheduling algorithms. Assume that the scheduler looks at the process tables once every 1 time unit and makes decisions on which process to schedule.

**Data**

Data shows the arrival times and process lengths for execution.

| PID  | Arr Time | Length |
| ---- | -------- | ------ |
| 1000 |    0     |   4    |
| 1001 |    0     |   5    |
| 1002 |    0     |   8    |
| 1003 |    1     |   1    |
| 1004 |    2     |   1    |
| 1005 |    2     |   6    |
| 1006 |    3     |   6    |
| 1007 |    3     |   6    |
| 1008 |    4     |   2    |
| 1009 |    4     |   2    |
| 1010 |    5     |   6    |
| 1011 |    5     |   7    |
| 1012 |    6     |   8    |
| 1013 |    7     |   2    |
| 1014 |    7     |   9    |
| 1015 |    8     |   2    |
| 1016 |    8     |   10   |
| 1017 |    9     |   2    |
| 1018 |    9     |   3    |
| 1019 |    9     |   4    |

**Files**

process_details.txt contains the data of this table.
