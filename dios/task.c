/*
 *  dios/task.c
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 */

#include <linux/kallsyms.h>
#include <linux/sched.h>

#include <dios/task.h>
#include <dios/utils.h>

int dios_init_task(struct task_struct* task_struct, const char* filename) {
  long (*call_addr)(struct task_struct*, const char*);
  /* Is the DIOS module loaded? If not, die. */
  if (!dios_module_loaded() || !task_struct->is_dios_task) {
    return -ENOSYS;
  }
  /* Retrieve handler address from symbol table */
  call_addr = (long (*)(dios_kref_t*, const char*))
      dios_get_syscall_handler_address(327);
  if (call_addr == NULL) {
    printk(KERN_ALERT "DIOS module loaded, but for %s missing!",
           "dios_task_init");
    return -ENOSYS;
  }
  /* Invoke handler */
  return (*call_addr)(task_struct, filename);
}

int dios_exit_task(struct task_struct* task_struct) {
  long (*call_addr)(void);
  /* Is the DIOS module loaded? If not, die. */
  if (!dios_module_loaded() || !task_struct->is_dios_task) {
    return -ENOSYS;
  }
  /* Retrieve handler address from symbol table */
  call_addr = (long (*)(dios_kref_t*))
      dios_get_syscall_handler_address(328);
  if (call_addr == NULL) {
    printk(KERN_ALERT "DIOS module loaded, but for %s missing!",
           "dios_task_exit");
    return -ENOSYS;
  }
  /* Invoke handler */
  return (*call_addr)();
}
