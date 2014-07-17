#ifndef _DIOS_NAME_H
#define _DIOS_NAME_H

#define DIOS_NAME_BITS 256
#define DIOS_NAME_BYTES (DIOS_NAME_BITS/8)
#define DIOS_NAME_QWORDS (DIOS_NAME_BYTES/8)

#define D_NAME_GEN_DETERMINISTIC 0x1
#define D_NAME_GEN_RANDOM 0x2
#define D_NAME_GEN_DETERMINISTIC_STRING 0x4

typedef struct dios_name {
  union {
    uint64_t value[DIOS_NAME_QWORDS];
    uint8_t raw[DIOS_NAME_BYTES];
  };
} dios_name_t;

#endif /* _DIOS_NAME_H */
