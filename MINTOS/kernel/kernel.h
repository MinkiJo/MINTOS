#ifndef KERNEL_KERNEL_H_
#define KERNEL_KERNEL_H_

#include "task.h"
#include "event.h"
#include "sync.h"

void Kernel_yield(void);
void Kernel_start(void);
void Kernel_send_events(uint32_t event_list);
KernelEventFlag_t Kernel_wait_events(uint32_t waiting_list);
void Kernel_lock_sem(void);
void Kernel_unlock_sem(void);

#endif
