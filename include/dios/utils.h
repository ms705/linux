/*
 *  dios/include/utils.h
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 */

#ifndef DIOS_UTILS_H
#define DIOS_UTILS_H

#include <dios/dios.h>

#include <linux/module.h>

void* dios_get_syscall_handler_address(int syscall_num);
bool dios_module_loaded(void);

#endif  // DIOS_UTILS_H
