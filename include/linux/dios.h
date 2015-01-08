#ifndef _LINUX_DIOS_H
#define _LINUX_DIOS_H

#include <linux/sched.h>

/* Declare for use in PCB */
struct dios_task_info;

int dios_init_task(struct task_struct* task_struct, const char* filename);
int dios_exit_task(struct task_struct* task_struct);

int dios_load_elf(const char* filename,
                  unsigned char osabi,
                  unsigned char abiversion);

#endif /* _LINUX_DIOS__H */
