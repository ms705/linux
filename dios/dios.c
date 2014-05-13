#define CONFIG_DIOS_PCBEXT

#include <asm-generic/current.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/printk.h>

#include "dios.h"

#define DIOS_MODULE_NAME "dios"

bool module_loaded(void) {
  /* check if dios module is loaded */
  struct module *mod;

  if (mutex_lock_interruptible(&module_mutex) != 0)
    return -EINTR;
  mod = find_module(DIOS_MODULE_NAME);

  if (!mod) {
    printk("DIOS module NOT loaded.\n");
    goto out;
  } else {
    printk("DIOS module loaded! :)\n");
    goto out; 
  }

out:
  mutex_unlock(&module_mutex);
  return (mod != 0);
}

/* syscall handler for DIOS_CREATE */
asmlinkage long sys_dios_create(void) {
  printk("dios_create stub called!\n");
  return 0;
}

/* syscall handler for DIOS_LOOKUP */
asmlinkage long sys_dios_lookup(void) {
  printk("dios_lookup stub called!\n");
  return 0;
}

/* syscall handler for DIOS_RUN */
asmlinkage long sys_dios_run(void) {
  printk("dios_run stub called!\n");
  return 0;
}

/* syscall handler for DIOS_COPY */
asmlinkage long sys_dios_copy(void) {
  printk("dios_copy stub called!\n");
  return 0;
}

/* syscall handler for DIOS_DELETE */
asmlinkage long sys_dios_delete(void) {
  printk("dios_delete stub called!\n");
  return 0;
}

/* syscall handler for DIOS_START_READ */
asmlinkage long sys_dios_start_read(void) {
  printk("dios_start_read stub called!\n");
  return 0;
}

/* syscall handler for DIOS_END_READ */
asmlinkage long sys_dios_end_read(void) {
  printk("dios_end_read stub called!\n");
  return 0;
}

/* syscall handler for DIOS_START_WRITE */
asmlinkage long sys_dios_start_write(void) {
  printk("dios_start_write stub called!\n");
  return 0;
}

/* syscall handler for DIOS_END_WRITE */
asmlinkage long sys_dios_end_write(void) {
  printk("dios_end_write stub called!\n");
  return 0;
}

/* syscall handler for DIOS_SELECT */
asmlinkage long sys_dios_select(void) {
  printk("dios_select stub called!\n");
  return 0;
}

/* syscall handler for DIOS_TEST */
asmlinkage long sys_dios_test(void) {
  module_loaded();
  printk("Hello world from sys_dios_test()! I was called from PID %d, "
         "which %s a DIOS task\n", current->pid,
          (current->is_dios_task ? "IS" : "IS NOT"));
  return 0;
}


