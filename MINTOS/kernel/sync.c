#define SEMMAX 10
#include<stdio.h>
#include "sync.h"
static int32_t sem_max;
static int32_t sem;

KernelMutex_t sMutex;

void Kernel_sem_init(int32_t max)
{
    if(max > SEMMAX)
        sem_max = SEMMAX;
    else sem_max = max;

    sem = sem_max;
}

int Kernel_sem_test(void)
{
    if(sem <= 0)
        return 0;
    sem--;
    return 1;
}

void Kernel_sem_release(void){
    sem++;
    if(sem >= sem_max)
    {
        sem = sem_max;
    }
}

void Kernel_mutex_init(){
    sMutex.owner = 0;
    sMutex.lock = 0; //false
}

int Kernel_mutex_lock(uint32_t owner){
    if(sMutex.lock)
        return 0;
    sMutex.owner = owner;
    sMutex.lock = 1;
    
    return 1;
}


int Kernel_mutex_unlock(uint32_t owner){
    if(sMutex.owner == owner){
        sMutex.lock = 0;
        return 1;
    }
    return 0;
}
        
