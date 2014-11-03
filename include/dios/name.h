#ifndef _DIOS_NAME_H
#define _DIOS_NAME_H

#define DIOS_NAME_BITS 256
#define DIOS_NAME_BYTES (DIOS_NAME_BITS/8)
#define DIOS_NAME_QWORDS (DIOS_NAME_BYTES/8)

#define D_NAME_GEN_DETERMINISTIC 0x1
#define D_NAME_GEN_RANDOM 0x2
#define D_NAME_GEN_DETERMINISTIC_STRING 0x4

/* Object types */
typedef enum {
  D_OBJ_PRIVMEM,
  D_OBJ_SHMEM,
  D_OBJ_BLOB,
  D_OBJ_HDFS,
  D_OBJ_SPECIAL,
  D_OBJ_TASK,
} dios_object_type_t;

/* Object lifecycle types */
typedef enum {
  D_OBJ_IMMORTAL,
  D_OBJ_SINGLE_DELETE,
  D_OBJ_REF_COUNTED,
} dios_object_lifecycle_t;

/*
 * Universal representation of a DIOS name.
 * May be copied to user-space, etc.
 */
typedef struct dios_name {
  union {
    uint64_t value[DIOS_NAME_QWORDS];
    uint8_t raw[DIOS_NAME_BYTES];
  };
} dios_name_t;

/*
 * Kernel-level representation of a DIOS object.
 */
typedef struct dios_object {
  /* Name for this object */
  dios_name_t* name;
  /* Object type */
  dios_object_type_t type;
  /* Pointer to object's location; type-dependent. */
  void* location;
  /* Destruction mode */
  dios_object_lifecycle_t lifecycle;
  /* Reference count */
  int64_t ref_count;
} dios_object_t;

#endif /* _DIOS_NAME_H */
