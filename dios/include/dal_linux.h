/*
 *  dios/dal_linux.h
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 *  DIOS Adaptation Layer (DAL) header for Linux.
 */

#ifndef _DIOS_DAL_LINUX_H
#define _DIOS_DAL_LINUX_H

#include "include/dios.h"
#include "include/dal.h"

#include <linux/module.h>

bool dios_module_loaded(void);


#endif  // _DIOS_DAL_LINUX_H
