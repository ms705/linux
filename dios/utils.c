/*
 *  dios/utils.c
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 *  Various core utility functions for DIOS within the Linux kernel.
 *  Functions should only go here if they MUST exist outside the module
 *  context, i.e. if they are needed prior to the module being invoked.
 */

#include <linux/kallsyms.h>

#include "utils.h"

#define DIOS_MODULE_NAME "dios"
#define DIOS_DAL_NAME "dios_dal_linux"

#define DIOS_BASE_SYSCALL_NUM 600
#define DIOS_SYSCALL_COUNT 15

bool dios_syscall_lookup_table_initialised = false;
EXPORT_SYMBOL(dios_syscall_lookup_table_initialised);

unsigned long dios_syscall_lookup_table[DIOS_SYSCALL_COUNT];
EXPORT_SYMBOL(dios_syscall_lookup_table);

/* returns address of syscall handler symbol or 0 if not found */
void* dios_get_syscall_handler_address(int syscall_num) {
  unsigned long call_addr;
  if (dios_syscall_lookup_table_initialised) {
    call_addr = dios_syscall_lookup_table[syscall_num - DIOS_BASE_SYSCALL_NUM];
  } else
    call_addr = 0;
  //call_addr = kallsyms_lookup_name(syscall);
  return (void*)call_addr;
}


/* returns indication if the DIOS kernel module is loaded */
bool dios_module_loaded(void) {
  /* check if DIOS module is loaded */
  struct module *mod;

  /* XXX(malte): should this use try_module_get? */
  if (mutex_lock_interruptible(&module_mutex) != 0)
    return -EINTR;
  mod = find_module(DIOS_MODULE_NAME);

  if (!mod) {
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
    printk("DIOS module NOT loaded.\n");
#endif
    goto out;
  } else {
#ifdef CONFIG_DIOS_DEBUG_VERBOSE
    //printk("DIOS module loaded! :)\n");
#endif
    goto out; 
  }

out:
  mutex_unlock(&module_mutex);
  return (mod != 0);
}
