#ifndef DIOS_NAME_H_
#define DIOS_NAME_H_

#define DIOS_NAME_BITS 256
#define DIOS_NAME_BYTES (DIOS_NAME_BITS/8)
#define DIOS_NAME_QWORDS (DIOS_NAME_BYTES/8)

typedef struct {
    union {
        uint64_t value[DIOS_NAME_QWORDS];
        uint8_t raw[DIOS_NAME_BYTES];
    };
} dios_name_t;


typedef struct{
//    in_addr_t ip;
} dios_value_t;

void name_to_str(dios_name_t* name, char* name_out);

#endif /* DIOS_NAME_H_ */
