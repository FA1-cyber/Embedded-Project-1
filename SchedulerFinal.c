#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX 1000
typedef void(*funcptr)();
void QueTask(funcptr ,int );
void ReRunMe(int);
void swap (int , int );
void sort ();
void sort2 ();
void QueTaskDelay(funcptr ,int );
void Dispatch();
void Init();
int doneflag = 0;
int c=0;
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
    delayQueue.currentTask[delayQueue.current_size].priority=newQueue.currentTask[0].priority;
    delayQueue.current_size++;
    sort2();


}
void ReRunMe(int ticks)
{
	if (ticks==0)
	{
		//add task to ready queue
        QueTask(newQueue.currentTask[0].funcName,newQueue.currentTask[0].priority);

 	}
	else
	{
		//add task into DelayQueue, priority based on number passed (ticks)
        QueTaskDelay(newQueue.currentTask[0].funcName,ticks);
	}
}
void Dispatch()
{
    int j=0;
    while(delayQueue.currentTask[0].delay==0)
    {
            QueTask(delayQueue.currentTask[0].funcName,delayQueue.currentTask[0].priority);
            for(int i=1;i<delayQueue.current_size;i++)
            {
                delayQueue.currentTask[i-1]=delayQueue.currentTask[i];
            }
            delayQueue.currentTask[delayQueue.current_size-1].funcName = NULL;
            delayQueue.currentTask[delayQueue.current_size-1].delay = MAX;
            delayQueue.currentTask[delayQueue.current_size-1].priority = -1;
            delayQueue.current_size--;
    }
    for (j;j<delayQueue.current_size;j++) delayQueue.currentTask[j].delay--;
    if (newQueue.current_size!=0){
    newQueue.currentTask[0].funcName();
    for(int i=1;i<newQueue.current_size;i++)
    {
        newQueue.currentTask[i-1]=newQueue.currentTask[i];
        
    }
    newQueue.currentTask[newQueue.current_size-1].funcName = NULL;
    newQueue.currentTask[newQueue.current_size-1].priority = 0;
    newQueue.current_size--;
    }
    if ((delayQueue.current_size==0)&&(newQueue.current_size==0)) doneflag=1;
}

void TaskA(void) //repeated for number of tasks needed
{
	//do something
    printf("Task 1");
    ReRunMe(2);   

void TaskB(void) //repeated for number of tasks needed
{
	//do something
    printf("Task 2");
    ReRunMe(1);
} 

void TaskC(void) //repeated for number of tasks needed
{
	//do something
    printf("Task 3");
    ReRunMe(4);  
} 


void swap (int x, int y)
{
    struct tasks temp =newQueue.currentTask[x];
    newQueue.currentTask[x] = newQueue.currentTask[y];
    newQueue.currentTask[y] = temp;
}

void swap2 (int x, int y)
{
    struct tasks temp =delayQueue.currentTask[x];
    delayQueue.currentTask[x] = delayQueue.currentTask[y];
    delayQueue.currentTask[y] = temp;

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
            }
        }
    }
}
void sort2()
{
   for (int i = 0; i<delayQueue.current_size;i++)
    {
        for(int j =i; j<delayQueue.current_size;j++)
        {
            if (delayQueue.currentTask[i].delay>delayQueue.currentTask[j].delay) 
            {
                swap2 (i,j);
            }
        }
    } 
}
void Init()
{
	newQueue.current_size=0;
    delayQueue.current_size=0;
    for (int i = 0; i<10;i++) delayQueue.currentTask[i].delay=MAX;
} 

int main ()
{
	Init();
    QueTask(&TaskA,5);
    QueTask(&TaskB,2);
    QueTask(&TaskC,3);
    for (int i = 0;i<300;i++)
    {
        Dispatch();
        printf("\n");
    }
    printf("Program terminated");
    
	return 0;
}






