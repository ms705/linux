#ifndef _DIOS_FLAGS_H
#define _DIOS_FLAGS_H

/* Generic */
#define D_NONE 0x0


/* begin_read() flags */

/* end_read() flags */

/* begin_write() flags */

/* end_write() flags */

/* run() flags */

/* copy() flags */
#define D_COPY_MAKE_LOCAL      0x1

/* lookup() flags */
#define D_LOOKUP_LOCAL_ONLY    0x1

/* pause() flags */

/* create() flags */
#define D_CREATE_TYPE_PRIVMEM  0x1
#define D_CREATE_TYPE_SHMEM    0x2
#define D_CREATE_TYPE_BLOB     0x4
#define D_CREATE_TYPE_HDFS     0x8

#define D_CREATE_LOCAL_ONLY    0x10
#define D_CREATE_BROADCAST     0x20

#define D_CREATE_NAME_DETERMINISTIC   0x100
#define D_CREATE_NAME_RANDOM          0x200

/* delete() flags */
#define D_DELETE_EXIT_SUCCESS  0x0
#define D_DELETE_EXIT_FAILURE  0x1

/* select() flags */

#endif /* _DIOS_FLAGS_H */
