/*
 *  dios/dios_syscalls.c
 *
 *  Copyright (C) 2014 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
 *
 * DIOS first-contact system call handlers for Linux. These only check if the
 * DIOS module is loaded and forward the calls if so (and return quietly if
 * not).
 */

/* Prevent the block for pure DIOS tasks used for legacy syscalls. */
#define PURE_DIOS_SYSCALL_OVERRIDE
#include <linux/syscalls.h>
#include <linux/signal.h>

#include <uapi/dios/flags.h>
#include <uapi/dios/iovec.h>
#include <uapi/dios/name.h>
#include <uapi/dios/ref.h>
#include <uapi/dios/task.h>

#include "utils.h"

#define __DSC_TYPES(t, a) t

#define DIOS_SYSCALL_PROXY0(name) \
  SYSCALL_DEFINE0(name) { __DIOS_SYSCALL_PROXY(1, name, void, ) }

#define DIOS_SYSCALL_PROXY1(name, ...) DIOS_SYSCALL_PROXYx(1, name, __VA_ARGS__)
#define DIOS_SYSCALL_PROXY2(name, ...) DIOS_SYSCALL_PROXYx(2, name, __VA_ARGS__)
#define DIOS_SYSCALL_PROXY3(name, ...) DIOS_SYSCALL_PROXYx(3, name, __VA_ARGS__)
#define DIOS_SYSCALL_PROXY4(name, ...) DIOS_SYSCALL_PROXYx(4, name, __VA_ARGS__)
#define DIOS_SYSCALL_PROXY5(name, ...) DIOS_SYSCALL_PROXYx(5, name, __VA_ARGS__)
#define DIOS_SYSCALL_PROXY6(name, ...) DIOS_SYSCALL_PROXYx(6, name, __VA_ARGS__)

#define DIOS_SYSCALL_PROXYx(x, name, ...)      \
  SYSCALL_DEFINE##x(name, __VA_ARGS__) {       \
    __DIOS_SYSCALL_PROXY(x, name, __VA_ARGS__) \
  }

#define __DIOS_SYSCALL_PROXY(x, name, ...)                                   \
  long (*call_addr)(__MAP(x,__DSC_TYPES,__VA_ARGS__));                       \
  if (!dios_module_loaded())                                                 \
    return -ENOSYS;                                                          \
  call_addr = dios_get_syscall_handler_address(__NR_##name);                 \
  if (call_addr == NULL) {                                                   \
    printk(KERN_ALERT "DIOS module loaded, but system call handler for %s "  \
           "missing!", #name);                                               \
    return -ENOSYS;                                                          \
  }                                                                          \
  return (*call_addr)(__MAP(x,__SC_ARGS,__VA_ARGS__));

DIOS_SYSCALL_PROXY6(dios_create, dios_flags_t , flags,
                                 dios_object_type_t, type,
                                 void*, arg,
                                 dios_name_t**, name,
                                 dios_ref_t** , ref,
                                 uint64_t, host_id);

DIOS_SYSCALL_PROXY4(dios_lookup, dios_flags_t, flags,
                                 dios_name_t*, name,
                                 dios_ref_t**, refs,
                                 uint64_t*   , refs_count);

DIOS_SYSCALL_PROXY4(dios_run, dios_flags_t     , flags,
                              dios_ref_t*      , ref,
                              dios_task_spec_t*, task_spec,
                              dios_ref_t**     , exec_ref);

DIOS_SYSCALL_PROXY4(dios_copy, dios_flags_t, flags,
                               dios_ref_t**, refs,
                               uint64_t    , ref_count,
                               dios_ref_t* , target);

DIOS_SYSCALL_PROXY2(dios_delete, dios_flags_t, flags,
                                dios_ref_t*  , ref);

DIOS_SYSCALL_PROXY4(dios_acquire_read, dios_flags_t  , flags,
                                       dios_ref_t*   , ref,
                                       uint64_t      , len,
                                       dios_iovec_t**, iov);

DIOS_SYSCALL_PROXY3(dios_commit_read, dios_flags_t , flags,
                                      dios_ref_t*  , ref,
                                      dios_iovec_t*, iov);

DIOS_SYSCALL_PROXY3(dios_release_read, dios_flags_t , flags,
                                       dios_ref_t*  , ref,
                                       dios_iovec_t*, iov);

DIOS_SYSCALL_PROXY4(dios_acquire_write, dios_flags_t  , flags,
                                        dios_ref_t*   , ref,
                                        uint64_t, len ,
                                        dios_iovec_t**, iov);

DIOS_SYSCALL_PROXY4(dios_commit_write, dios_flags_t , flags,
                                       dios_ref_t*  , ref,
                                       uint64_t     , len,
                                       dios_iovec_t*, iov);

DIOS_SYSCALL_PROXY3(dios_release_write, dios_flags_t , flags,
                                        dios_ref_t*  , ref,
                                        dios_iovec_t*, iov);

DIOS_SYSCALL_PROXY4(dios_select, dios_flags_t, flags,
                                 dios_ref_t**, refs,
                                 uint64_t    , num_refs,
                                 dios_ref_t**, selected);

DIOS_SYSCALL_PROXY0(dios_info);
