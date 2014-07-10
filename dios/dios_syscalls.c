/*
 *  dios/dios_syscalls.c
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 * DIOS first-contact system call handlers for Linux. These only check if the
 * DIOS module is loaded and forward the calls if so (and return quietly if
 * not).
 */

#include <linux/syscalls.h>
#include <linux/signal.h>

#include <dios/dios.h>
#include <dios/name.h>
#include <dios/reference.h>
#include <dios/utils.h>
#include <dios/task.h>

/* syscall handler for DIOS_CREATE */
SYSCALL_DEFINE3(dios_create, dios_flags_t, flags, dios_name_t**, name,
                dios_ref_t**, ref) {
  long (*call_addr)(dios_flags_t, dios_name_t**, dios_ref_t**);
  /* Is the DIOS module loaded? If not, die. */
  if (!dios_module_loaded()) {
    return -ENOSYS;
  }
  /* Retrieve handler address from symbol table */
  call_addr = (long (*)(dios_flags_t, dios_name_t**, dios_ref_t**))
      dios_get_syscall_handler_address("dios_create");
  if (call_addr == NULL) {
    printk(KERN_ALERT "DIOS module loaded, but system call handler for %s "
           "missing!", "dios_create");
    return -ENOSYS;
  }
  /* Invoke handler */
  return (*call_addr)(flags, name, ref);
}

/* syscall handler for DIOS_LOOKUP */
SYSCALL_DEFINE4(dios_lookup, dios_flags_t, flags, dios_name_t*, name,
                dios_ref_t**, refs, uint64_t*, refs_count) {
  long (*call_addr)(dios_flags_t, dios_name_t*, dios_ref_t**, uint64_t*);
  /* Is the DIOS module loaded? If not, die. */
  if (!dios_module_loaded()) {
    return -ENOSYS;
  }
  /* Retrieve handler address from symbol table */
  call_addr = (long (*)(dios_flags_t, dios_name_t*, dios_ref_t**, uint64_t*))
      dios_get_syscall_handler_address("dios_lookup");
  if (call_addr == NULL) {
    printk(KERN_ALERT "DIOS module loaded, but system call handler for %s "
           "missing!", "dios_create");
    return -ENOSYS;
  }
  /* Invoke handler */
  return (*call_addr)(flags, name, refs, refs_count);
}

/* syscall handler for DIOS_RUN */
SYSCALL_DEFINE3(dios_run, dios_flags_t, flags, dios_ref_t*, ref,
                dios_ref_t**, exec_ref) {
  long (*call_addr)(dios_flags_t, dios_ref_t*, dios_ref_t**);
  /* Is the DIOS module loaded? If not, die. */
  if (!dios_module_loaded()) {
    return -ENOSYS;
  }
  /* Retrieve handler address from symbol table */
  call_addr = (long (*)(dios_flags_t, dios_ref_t*, dios_ref_t**))
      dios_get_syscall_handler_address("dios_run");
  if (call_addr == NULL) {
    printk(KERN_ALERT "DIOS module loaded, but system call handler for %s "
           "missing!", "dios_run");
    return -ENOSYS;
  }
  /* Invoke handler */
  return (*call_addr)(flags, ref, exec_ref);
}

/* syscall handler for DIOS_COPY */
SYSCALL_DEFINE4(dios_copy, dios_flags_t, flags, dios_ref_t**, refs,
                uint64_t, ref_count, dios_ref_t*, target) {
  printk("dios_copy stub called!\n");
  return 0;
}

/* syscall handler for DIOS_DELETE */
SYSCALL_DEFINE2(dios_delete, dios_flags_t, flags, dios_ref_t*, ref) {
  long (*call_addr)(dios_flags_t, dios_ref_t*);
  /* Is the DIOS module loaded? If not, die. */
  if (!dios_module_loaded()) {
    return -ENOSYS;
  }
  /* Retrieve handler address from symbol table */
  call_addr = (long (*)(dios_flags_t, dios_ref_t*))
      dios_get_syscall_handler_address("dios_delete");
  if (call_addr == NULL) {
    printk(KERN_ALERT "DIOS module loaded, but system call handler for %s "
           "missing!", "dios_delete");
    return -ENOSYS;
  }
  /* Invoke handler */
  return (*call_addr)(flags, ref);
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
SYSCALL_DEFINE3(dios_start_write, dios_flags_t, flags,
                dios_ref_t*, ref, uint64_t, len) {
  long (*call_addr)(dios_flags_t, dios_ref_t*, uint64_t);
  /* Is the DIOS module loaded? If not, die. */
  if (!dios_module_loaded()) {
    return -ENOSYS;
  }
  /* Retrieve handler address from symbol table */
  call_addr = (long (*)(dios_flags_t, dios_ref_t*, uint64_t))
      dios_get_syscall_handler_address("dios_start_write");
  if (call_addr == NULL) {
    printk(KERN_ALERT "DIOS module loaded, but system call handler for %s "
           "missing!", "dios_start_write");
    return -ENOSYS;
  }
  /* Invoke handler */
  return (*call_addr)(flags, ref, len);
}

/* syscall handler for DIOS_END_WRITE */
SYSCALL_DEFINE2(dios_end_write, dios_flags_t, flags, dios_ref_t*, ref) {
  long (*call_addr)(dios_flags_t, dios_ref_t*);
  /* Is the DIOS module loaded? If not, die. */
  if (!dios_module_loaded()) {
    return -ENOSYS;
  }
  /* Retrieve handler address from symbol table */
  call_addr = (long (*)(dios_flags_t, dios_ref_t*))
      dios_get_syscall_handler_address("dios_end_write");
  if (call_addr == NULL) {
    printk(KERN_ALERT "DIOS module loaded, but system call handler for %s "
           "missing!", "dios_end_write");
    return -ENOSYS;
  }
  /* Invoke handler */
  return (*call_addr)(flags, ref);
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
  long (*call_addr)(void);
  /* Is the DIOS module loaded? If not, die. */
  if (!dios_module_loaded()) {
    return -ENOSYS;
  }
  /* Retrieve handler address from symbol table */
  call_addr = (long (*)(void))dios_get_syscall_handler_address("dios_test");
  if (call_addr == NULL) {
    printk(KERN_ALERT "DIOS module loaded, but system call handler for %s "
           "missing!", "dios_test");
    return -ENOSYS;
  }
  /* Invoke handler */
  return (*call_addr)();
}


