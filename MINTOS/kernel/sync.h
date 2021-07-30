#ifndef KERNEL_SYNC_H_
#define KERNEL_SYNC_H_

typedef struct KernelMutex_t
{
    uint32_t owner;
    uint8_t lock;
}KernelMutex_t;

void Kernel_sem_init(int32_t max);
int Kernel_sem_test(void);
void Kernel_sem_release(void);

void Kernel_mutex_init(void);
int Kernel_mutex_lock(uint32_t owner);
int Kernel_mutex_unlock(uint32_t owner);


#endif

