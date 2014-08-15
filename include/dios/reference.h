#ifndef _DIOS_REFERENCE_H
#define _DIOS_REFERENCE_H

#include <dios/name.h>

#define D_REF_PERM_READ  0x1
#define D_REF_PERM_WRITE 0x2
#define D_REF_PERM_EXEC  0x4

/* Reference types */
typedef enum {
  D_REF_SHMEM,
  D_REF_BLOB,
  D_REF_HDFS,
  D_REF_SPECIAL,
  D_REF_TASK,
} dios_ref_type_t;

/* Reference proximity indication */
typedef enum {
  D_REF_LOCAL_TO_CPU,
  D_REF_LOCAL_MEMORY,
  D_REF_LOCAL_DISK,
  D_REF_REMOTE_MEMORY_1HOP,
  D_REF_REMOTE_MEMORY_MULTIHOP,
  D_REF_REMOTE_MEMORY_DISTANT,
  D_REF_REMOTE_DISK_1HOP,
  D_REF_REMOTE_DISK_MULTIHOP,
  D_REF_REMOTE_DISK_DISTANT,
} dios_ref_proximity_t;

/* High-level consistency flags for references */
typedef enum {
  D_REF_CONSISTENCY_NONE,
  D_REF_CONSISTENCY_EVENTUAL,
  D_REF_CONSISTENCY_MUTEX,
} dios_ref_consistency_t;

/* States for distributed MESI protocol */
typedef enum {
  D_KREF_MODIFIED,
  D_KREF_EXCLUSIVE,
  D_KREF_SHARED,
  D_KREF_INVALID,
} dios_kref_state_t;

/* Public reference struct: this is mapped READ-ONLY into user-space. */
typedef struct {
  /* Reference ID (~= FD num) */
  uint64_t id;
  /* Object type */
  dios_ref_type_t type;
  /* Object proximity relative to this task */
  dios_ref_proximity_t proximity;
  /* Consistency levels offered for this reference */
  dios_ref_consistency_t read_consistency;
  dios_ref_consistency_t write_consistency;
  /* Is the reference read for I/O? */
  bool io_ready;
  /* Maximum size of the write buffers offered by this reference. 
     Zero if the reference is not ready or reading is not possible. */
  uint64_t read_buffer_size;
  /* Maximum size of the read buffers offered by this reference
     Zero if the reference is not ready or reading is not possible. */
  uint64_t write_buffer_size;
} dios_ref_t;

/* private kernel reference struct, allocated in kernel memory */
typedef struct {
  uint64_t id; 
  /* N.B.: ref is allocated in VIRTUAL memory, as it
   * gets passed back to user-space.
   * ref holds the kernel-space pointer to the reference struct */
  dios_ref_t* ref;
  /* uref holds the user-space pointer to the reference struct */
  dios_ref_t* __user uref;
  /* The name, by contrast, is in kernel memory and only *copied*
   * to user-space. */
  dios_name_t* name;
  /* Object type, matches ref->type */
  dios_ref_type_t type;
  /* Location: this is not necessarily a string -- may hold arbitrary
     type-specific data. */
  char* location;
  /* Flags */
  uint64_t flags;
  /* Reference permissions */
  uint64_t permissions;
  /* Current state of reference in MESI protocol */
  dios_kref_state_t state;
  /* Reference to task owning this reference, usually self_ref */
  dios_ref_t* owner_task;
  /* Reference count for deletion */
  uint64_t ref_count;
  /* For putting krefs into linked lists */
  struct list_head list;
  /* For linking chains of iovecs currently granted to user-space
     for reading and writing */
  struct list_head read_iov_list;
  struct list_head write_iov_list;
} dios_kref_t;

#endif /* _DIOS_REFERENCE_H */
