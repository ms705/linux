// TODO: put in linux/dios src dir
/*
 *  dios/include/utils.h
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 */

#ifndef _DIOS_UTILS_H
#define _DIOS_UTILS_H

#include <linux/module.h>

void* dios_get_syscall_handler_address(int syscall_num);
bool dios_module_loaded(void);

#endif  // _DIOS_UTILS_H
