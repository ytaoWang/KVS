#ifndef __KVS_BDB_H_
#define __KVS_BDB_H_

/*
 * index disk layout:
 * bnode | bnode
 */

struct stp_bnode_key {
    struct kvs_key key;
}__attribute__((__packed__));

#define KVS_KEY(t)  (2*(t) - 1)
#define KVS_MIN_KEY(t)  ((t) - 1)
#define KVS_MIN_CHILD(t) (t)
#define KVS_CHILD(t) (2 * (t))


#define KVS_BTREE_DEGREE 59
#define KVS_BTREE_CHILD_MAX (KVS_CHILD(KVS_BTREE_DEGREE))
#define KVS_BTREE_CHILD_MIN (KVS_MIN_CHILD(KVS_BTREE_DEGREE))
#define KVS_BTREE_KEY_MIN (KVS_MIN_KEY(KVS_BTREE_DEGREE))
#define KVS_BTREE_KEY_MAX (KVS_KEY(KVS_BTREE_DEGREE))


struct kvs_bnode_item {  //4096 bytes
    struct kvs_header location;
    struct kvs_bnode_key key[KVS_KEY_MAX];
    u8 nrkeys;
    struct kvs_bnode_off ptrs[KVS_CHILD_MAX];
    u8 nrptrs;
    u32 level;
    u8 flags;
    struct kvs_header parent;
    u8 padding[38];
}__attribute__((__packed__));

    

#endif
