#ifndef __KVS_ERROR_H_
#define __KVS_ERROR_H_


#define KVS_NO_ERROR 0
#define KVS_INDEX_OPEN_ERROR 1
#define KVS_META_OPEN_ERROR 2
#define KVS_INDEX_READ_ERROR 3
#define KVS_META_READ_ERROR 4
#define KVS_INDEX_WRITE_ERROR 5
#define KVS_META_WRITE_ERROR 6
#define KVS_BAD_MAGIC_NUMBER 7
#define KVS_META_CANT_BE_WRITER 8
#define KVS_INDEX_CANT_BE_WRITER 9
#define KVS_META_CANT_BE_READER 10
#define KVS_INDEX_CANT_BE_READER 11

#define KVS_MIN_ERRNO             0
#define KVS_MAX_ERRNO             11

#define N_(s)  (s)
#define _(s)  ((const char *)s)


#endif
