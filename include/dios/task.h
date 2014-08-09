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
#include <dios/name.h>
#include <dios/reference.h>

typedef struct dios_task_info {
  void* name_table;
  void* ref_table;
  dios_name_t* self_name;
  dios_kref_t* self_kref;
  uint64_t spawn_counter;
} dios_task_info_t;

typedef struct dios_task_spec {
  /* Inputs */
  dios_name_t** input_names;
  uint64_t input_count;
  /* Outputs */
  dios_name_t** output_names;
  uint64_t output_count;
} dios_task_spec_t;

extern int dios_init_task(struct task_struct* task_struct,
                          const char* filename);
extern int dios_exit_task(struct task_struct* task_struct);

#endif  // _DIOS_TASK_H
