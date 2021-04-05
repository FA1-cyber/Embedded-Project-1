#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX 1000
typedef void(*funcptr)();

struct tasks{
    funcptr funcName;
    int priority;
    int delay;

};

struct taskQueue{
    struct tasks * currentTask;
    int current_size;
    int max_size;
};

struct taskQueue newQueue[MAX];



void TaskA(void) //repeated for number of tasks needed
{
	//do something
    printf("Task 1");
}

void TaskB(void) //repeated for number of tasks needed
{
	//do something
    printf("Task 2");
} 

void TaskC(void) //repeated for number of tasks needed
{
	//do something
    printf("Task 3");
} 

void QueTask(funcptr function_name,int priority)
{
    newQueue[newQueue.currentsize].currentTask->funcName=function_name;
    newQueue[newQueue.currentsize].currentTask->priority=priority;
    newQueue.currentsize++;
}

int main ()
{
/* 	Init();
	while (1)
	{
		Dispatch();
	} */
    /* void (*taskApointer)(void) = &TaskA;
    (*taskApointer)(); */
    // TaskQueuePointer[0] = TaskA;
    // TaskQueuePointer[1] = TaskB;
    // TaskQueuePointer[2] = TaskC;
    // TaskA *Fa;
    // TaskB *Fb;
    // TaskC *Fc;
    newQueue.current_size=0;
    QueTask(&TaskA,1);
    QueTask(&TaskB,2);
    QueTask(&TaskC,3);
    for(int i=0;i<3;i++)
    {
        newQueue[i].currentTask->funcName();
        printf("\n");
    }

	return 0;
}
//subtract 1 from the ticks of every function in the delay queue each clock cycle
//each tick is 50ms




/*
void QueTaskDelay(/*type function_name,int ticks)
{
	//enque function in delay queue
}

void Init()
{
	//initialize function queue
	//initialize delay queue
} */

// void ReRunMe(int ticks)
// {
// 	if (ticks==0)
// 	{
// 		//add task to ready queue
// 	}
// 	else
// 	{
// 		//add task into DelayQueue, priority based on number passed (ticks)
// 	}
// }

// void Dispatch()
// {
// 	//start of scheduling
// }
