#ifndef DIOS_REFERENCE_H
#define DIOS_REFERENCE_H

/* public reference struct */
typedef struct {
  uint64_t id;
  uint16_t type;
  uint16_t consistency;
  uint16_t congestion;
  uint16_t ordering;
  uint16_t proximity;
  uint8_t stream_ready;
  uint8_t notified;
} dios_ref_t;

/* private kernel reference struct, allocated in kernel memory */
typedef struct {
  uint64_t id; 
  // N.B.: ref is allocated in VIRTUAL memory, as it
  // gets passed back to user-space
  dios_ref_t* ref;
  dios_name_t* name;
  uint64_t type;
  uint64_t flags;
  //uint64_t len;
  //uint64_t in_selector;
  dios_ref_t* owner_task;
  uint64_t ref_count;
} dios_kref_t;


dios_kref_t* dios_kref_alloc(dios_name_t* name);
void dios_kref_print(dios_kref_t* kref);

#endif /* DIOS_REFERENCE_H */
