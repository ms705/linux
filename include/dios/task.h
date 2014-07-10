/*
 *  dios/include/task.h
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 */

#ifndef _DIOS_TASK_H
#define _DIOS_TASK_H

#include <dios/dios.h>

typedef struct dios_task_info {
  void* name_table;
  void* ref_table;
} dios_task_info_t;

#endif  // _DIOS_TASK_H
