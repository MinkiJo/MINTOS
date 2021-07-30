#include <stdio.h>
#include "kernel.h"
#define SET_BIT(p,n) ((p) |= (1<<(n)))
void Kernel_yield(void)
{
    Kernel_task_scheduler();
}

void Kernel_start(void){
    Kernel_task_start();
}

void Kernel_send_events(uint32_t event_list)
{
    KernelEventFlag_t sending_event = KernelEventFlag_Empty;

    for (uint32_t i = 0 ; i < 32 ; i++)
    {
        if ((event_list >> i) & 1)
        {
            SET_BIT(sending_event, i);
            Kernel_event_flag_set(sending_event);
        }
    }
}

KernelEventFlag_t Kernel_wait_events(uint32_t waiting_list)
{
    KernelEventFlag_t waiting_event = KernelEventFlag_Empty;

    for (uint32_t i = 0 ; i < 32 ; i++)
    {
        if ((waiting_list >> i) & 1)
        {
            SET_BIT(waiting_event, i);

            if (Kernel_event_flag_check(waiting_event))
            {
                return waiting_event;
            }
        }
    }

    return KernelEventFlag_Empty;
}

void Kernel_lock_sem(void){
    while(Kernel_sem_test() == 0)
        Kernel_yield();
}

void Kernel_unlock_sem(void){
    Kernel_sem_release();
}


void Kernel_lock_mutex(void){
    while(1){
        uint32_t current_task_id = Kernel_get_current_task_id();
        if(Kernel_mutex_lock(current_task_id) == 0){
            Kernel_yield();
        }else{
            break;
        }
    }
}

void Kernel_unlock_mutex(void){
    uint32_t current_task_id = Kernel_get_current_task_id();
    if(Kernel_mutex_unlock(current_task_id) == 0){
        Kernel_yield();
    }
}
