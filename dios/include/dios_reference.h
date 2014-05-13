#ifndef DIOS_REFERENCE_H_
#define DIOS_REFERENCE_H_

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


#endif /* DIOS_REFERENCE_H_ */
