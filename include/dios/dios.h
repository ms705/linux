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

typedef uint64_t dios_flags_t;

typedef struct dios_iovec {
  void* __user buf;
  uint64_t len;
  // iovecs can be part of doubly-linked chains
  struct list_head list;
} dios_iovec_t;

#endif  // _DIOS_DIOS_H
