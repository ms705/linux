#ifndef _DIOS_DIOS_H
#define _DIOS_DIOS_H

#define CONFIG_DIOS_PCBEXT

#include <linux/types.h>
#include <linux/sched.h>
#include <asm-generic/current.h>
#include <linux/printk.h>

#include "include/dios_name.h"
#include "include/dios_reference.h"

asmlinkage long sys_dios_create(void);
asmlinkage long sys_dios_lookup(void);
asmlinkage long sys_dios_run(void);
asmlinkage long sys_dios_copy(void);
asmlinkage long sys_dios_delete(void);
asmlinkage long sys_dios_start_read(void);
asmlinkage long sys_dios_end_read(void);
asmlinkage long sys_dios_start_write(void);
asmlinkage long sys_dios_end_write(void);
asmlinkage long sys_dios_select(void);

asmlinkage long sys_dios_test(void);

#endif  // _DIOS_DIOS_H
