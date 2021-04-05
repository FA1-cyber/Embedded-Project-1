#include <stdio.h> ////Queueing is working
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
    struct tasks currentTask[10];
    int current_size;
    int max_size;
};


struct taskQueue newQueue;


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
    newQueue.currentTask[newQueue.current_size].funcName=function_name;
    newQueue.currentTask[newQueue.current_size].priority=1;
    newQueue.current_size++;
}

void Init()
{
	newQueue.current_size=0;
} 

int main ()
{
	Init();
    QueTask(&TaskA,1);
    QueTask(&TaskB,2);
    QueTask(&TaskC,3);
    for (int i = 0;i<3;i++)
    {
        newQueue.currentTask[i].funcName();
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
