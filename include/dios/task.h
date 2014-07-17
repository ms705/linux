/*
 *  dios/include/task.h
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 */

#ifndef _DIOS_TASK_H
#define _DIOS_TASK_H

#include <linux/sched.h>

#include <dios/dios.h>
#include <dios/reference.h>

typedef struct dios_task_info {
  void* name_table;
  void* ref_table;
  dios_name_t* self_name;
  dios_kref_t* self_kref;
  uint64_t spawn_counter;
} dios_task_info_t;

extern int dios_init_task(struct task_struct* task_struct);

#endif  // _DIOS_TASK_H
