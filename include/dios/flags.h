#ifndef _DIOS_FLAGS_H
#define _DIOS_FLAGS_H

/* Generic */
#define D_NONE 0x0


/* begin_read() flags */

/* end_read() flags */

/* begin_write() flags */

/* end_write() flags */

/* run() flags */

/* lookup() flags */

/* pause() flags */

/* create() flags */
#define D_CREATE_TYPE_SHMEM    0x1
#define D_CREATE_TYPE_BLOB     0x2
#define D_CREATE_TYPE_HDFS     0x4

#define D_CREATE_LOCAL_ONLY    0x10
#define D_CREATE_BROADCAST     0x20

#define D_CREATE_NAME_DETERMINISTIC   0x100
#define D_CREATE_NAME_RANDOM          0x200

/* delete() flags */

/* select() flags */

#endif /* _DIOS_FLAGS_H */
