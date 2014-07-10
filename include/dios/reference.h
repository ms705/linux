#ifndef _DIOS_REFERENCE_H
#define _DIOS_REFERENCE_H

#define D_REF_PERM_READ  0x1
#define D_REF_PERM_WRITE 0x2
#define D_REF_PERM_EXEC  0x4

/* Reference types */
typedef enum {
  D_REF_SHMEM,
  D_REF_BLOB,
  D_REF_HDFS,
  D_REF_SPECIAL,
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

/* public reference struct */
typedef struct {
  uint64_t id;
  dios_ref_type_t type;
  dios_ref_proximity_t proximity;
  //uint16_t consistency;
  //uint16_t congestion;
  //uint16_t ordering;
  //uint8_t stream_ready;
  //uint8_t notified;
} dios_ref_t;

/* private kernel reference struct, allocated in kernel memory */
typedef struct {
  uint64_t id; 
  // N.B.: ref is allocated in VIRTUAL memory, as it
  // gets passed back to user-space
  dios_ref_t* ref;
  // The name, by contrast, is in kernel memory and only *copied*
  // to user-space.
  dios_name_t* name;
  dios_ref_type_t type;
  char* location;
  uint64_t flags;
  uint64_t permissions;
  //uint64_t len;
  //uint64_t in_selector;
  dios_ref_t* owner_task;
  uint64_t ref_count;
} dios_kref_t;

#endif /* _DIOS_REFERENCE_H */
