/*
 *  dios/dios_syscalls.c
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 * DIOS first-contact system call handlers for Linux. These only check if the
 * DIOS module is loaded and forward the calls if so (and return quietly if
 * not).
 */

#define CONFIG_DIOS_PCBEXT

#include <linux/syscalls.h>
#include <linux/signal.h>

#include "include/dios.h"
#include "include/utils.h"

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
SYSCALL_DEFINE0(dios_start_write) {
  void* call_addr;
  if (!dios_module_loaded()) {
    return -ENOSYS;
  }
  call_addr = dios_get_syscall_handler_address("dios_start_write");
  return (*(long (*)(void))call_addr)();
}

/* syscall handler for DIOS_END_WRITE */
SYSCALL_DEFINE0(dios_end_write) {
  void* call_addr;
  if (!dios_module_loaded()) {
    return -ENOSYS;
  }
  call_addr = dios_get_syscall_handler_address("dios_end_write");
  return (*(long (*)(void))call_addr)();
}

/* syscall handler for DIOS_SELECT */
SYSCALL_DEFINE0(dios_select) {
  void* call_addr;
  if (!dios_module_loaded()) {
    return -ENOSYS;
  }
  call_addr = dios_get_syscall_handler_address("dios_select");
  return (*(long (*)(void))call_addr)();
}

/* syscall handler for DIOS_TEST */
SYSCALL_DEFINE0(dios_test) {
  void* call_addr;
  if (!dios_module_loaded()) {
    return -ENOSYS;
  }
  call_addr = dios_get_syscall_handler_address("dios_test");
  return (*(long (*)(void))call_addr)();
}


