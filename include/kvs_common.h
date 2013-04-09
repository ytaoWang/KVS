#ifndef __KVS_COMMON_H_
#define __KVS_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "kvs_types.h"

/**
 * kvs_key for indexing
 */

struct kvs_key {
    u64 minor;
    u64 major;
};

typedef int (*kvs_cmp_t)(const struct kvs_key *,const struct kvs_key *);

/*
 * record disk layout:
 * page header | header K/V  ... header K/V |
 *
 **/

/*
 * 4KB page header 
 */
struct kvs_header { 
    u64 offset;
    u64 count;
    u8 flags;
    u32 nritems;
}__attribute__((__packed__));

/*
 * key/value pair header
 */

struct kvs_pair_header {
    u8 klen;
    u32 vlen;
    u8 flags;
}__attribute__((__packed__));


#ifdef __cplusplus
}
#endif

#endif
