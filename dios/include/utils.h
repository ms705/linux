/*
 *  dios/dal_linux.h
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 *  DIOS Adaptation Layer (DAL) header for Linux.
 */

#ifndef DAL_LINUX_H
#define DAL_LINUX_H

#include "include/dios.h"

#include <linux/module.h>

void* dios_get_syscall_handler_address(const char* syscall);
bool dios_module_loaded(void);
//void dios_task_or_die(const char* syscall);

#endif  // DAL_LINUX_H
