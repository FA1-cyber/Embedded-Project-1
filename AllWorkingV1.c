#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX 1000
typedef void(*funcptr)();
void QueTask(funcptr ,int );
void ReRunMe(int ,funcptr ,int );
void swap (int , int );
void sort ();
void sort2 ();
void QueTaskDelay(funcptr ,int );
void Dispatch();
void Init();
int doneflag = 0;

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
struct taskQueue delayQueue;
void QueTask(funcptr function_name,int priority2)
{
    newQueue.currentTask[newQueue.current_size].funcName=function_name;
    newQueue.currentTask[newQueue.current_size].priority=priority2;
    newQueue.current_size++;
    sort();
}
void QueTaskDelay(funcptr function_name,int ticks)
{
	//enque function in delay queue
    delayQueue.currentTask[delayQueue.current_size].funcName = function_name;
    delayQueue.currentTask[delayQueue.current_size].delay = ticks;
    delayQueue.current_size++;
    sort2();


}
void ReRunMe(int ticks,funcptr function_name,int prio)
{
	if (ticks==0)
	{
		//add task to ready queue
        QueTask(function_name,prio);

 	}
	else
	{
		//add task into DelayQueue, priority based on number passed (ticks)
        QueTaskDelay(function_name,ticks);
	}
}
void Dispatch()
{
    if (newQueue.current_size==0)
    {
        if (delayQueue.current_size==0) doneflag=1;
        else
        {
            for(int j=0;j<delayQueue.current_size;j++)
                {
                    delayQueue.currentTask[j].delay--;
                    if(delayQueue.currentTask[j].delay == 0)
                    {
                        QueTask(delayQueue.currentTask[j].funcName,delayQueue.currentTask[j].priority);
                        delayQueue.currentTask[0].funcName = NULL;
                        for(int i=1;i<delayQueue.current_size;i++)
                        {
                            delayQueue.currentTask[i-1]=delayQueue.currentTask[i];
                        }
                        delayQueue.current_size--;
                    }
                }

        }
    }
    else{
        newQueue.currentTask[0].funcName();
        for(int i=1;i<newQueue.current_size;i++)
        {
            newQueue.currentTask[i-1]=newQueue.currentTask[i];
            
        }
        newQueue.currentTask[newQueue.current_size].funcName = NULL;
        newQueue.current_size--;
        for(int j=0;j<delayQueue.current_size;j++)
        {
            delayQueue.currentTask[j].delay--;
            if(delayQueue.currentTask[j].delay == 0)
            {
                QueTask(delayQueue.currentTask[j].funcName,delayQueue.currentTask[j].priority);
                delayQueue.currentTask[0].funcName = NULL;
                for(int i=1;i<delayQueue.current_size;i++)
                {
                    delayQueue.currentTask[i-1]=delayQueue.currentTask[i];
            
                }
                delayQueue.current_size--;
            }
        }
    }
    
}

void TaskA(void) //repeated for number of tasks needed
{
	//do something
    printf("Task 1");
    ReRunMe(10,TaskA,6);
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


void swap (int x, int y)
{
    //printf(newQueue.currentTask[x].priority);
    //printf(newQueue.currentTask[y].priority);
  //  printf("\n");
    struct tasks temp =newQueue.currentTask[x];
    newQueue.currentTask[x] = newQueue.currentTask[y];
    newQueue.currentTask[y] = temp;
    //printf(newQueue.currentTask[x].priority);
    //printf(newQueue.currentTask[y].priority);
   // printf("\n");
}
void sort ()
{
    for (int i = 0; i<newQueue.current_size;i++)
    {
        for(int j =0; j<newQueue.current_size-1;j++)
        {
            if (newQueue.currentTask[i].priority>newQueue.currentTask[j].priority) 
            {
                swap (i,j);
                //printf("SORTING");
               // printf("\n");
            }
        }
    }
}
void sort2()
{
   for (int i = 0; i<delayQueue.current_size;i++)
    {
        for(int j =0; j<delayQueue.current_size-1;j++)
        {
            if (delayQueue.currentTask[i].delay>delayQueue.currentTask[j].delay) 
            {
                swap (i,j);
                //printf("SORTING");
                //printf("\n");
            }
        }
    } 
}





void Init()
{
	newQueue.current_size=0;
} 

int main ()
{
	Init();
    QueTask(&TaskA,5);
    QueTask(&TaskB,2);
    QueTask(&TaskC,3);
    for (int i = 0;i<30;i++)
    //while(doneflag==0)
    {
        //newQueue.currentTask[i].funcName();
        Dispatch();
        printf("\n");
    }
	return 0;
}
//subtract 1 from the ticks of every function in the delay queue each clock cycle
//each tick is 50ms









