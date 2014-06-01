/*
 *  dios/dios.h
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 *  Shared header for DIOS.
 */

#ifndef _DIOS_DIOS_H
#define _DIOS_DIOS_H

#include <linux/types.h>
#include <linux/sched.h>
#include <asm-generic/current.h>
#include <linux/printk.h>

#include "include/dios_name.h"
#include "include/dios_reference.h"

typedef uint64_t dios_flags_t;

asmlinkage long sys_dios_create(dios_flags_t flags, dios_name_t** name, dios_ref_t** ref);
asmlinkage long sys_dios_lookup(dios_flags_t flags, dios_name_t* name, dios_ref_t** refs, uint64_t* refs_cnt);
asmlinkage long sys_dios_run(void);
asmlinkage long sys_dios_copy(void);
asmlinkage long sys_dios_delete(dios_flags_t flags, dios_ref_t* ref);
asmlinkage long sys_dios_start_read(void);
asmlinkage long sys_dios_end_read(void);
asmlinkage long sys_dios_start_write(void);
asmlinkage long sys_dios_end_write(void);
asmlinkage long sys_dios_select(void);

asmlinkage long sys_dios_test(void);

#endif  // _DIOS_DIOS_H
