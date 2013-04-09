#ifndef __KVS_BDB_H_
#define __KVS_BDB_H_

#include "kvs_common.h"
#include "kvs_types.h"
#include "list.h"

/*
 * index disk layout:
 * super | bnode | bnode
 */

struct kvs_bnode_key {
    struct kvs_key key;
}__attribute__((__packed__));

struct kvs_bnode_off {
    u8 flags;
    u64 offset;
}__attribute__((__packed__));

    

#define KVS_KEY(t)  (2*(t) - 1)
#define KVS_MIN_KEY(t)  ((t) - 1)
#define KVS_MIN_CHILD(t) (t)
#define KVS_CHILD(t) (2 * (t))


#define KVS_BTREE_DEGREE 80
#define KVS_BTREE_CHILD_MAX (KVS_CHILD(KVS_BTREE_DEGREE))
#define KVS_BTREE_CHILD_MIN (KVS_MIN_CHILD(KVS_BTREE_DEGREE))
#define KVS_BTREE_KEY_MIN (KVS_MIN_KEY(KVS_BTREE_DEGREE))
#define KVS_BTREE_KEY_MAX (KVS_KEY(KVS_BTREE_DEGREE))


struct kvs_bnode_item {  //4096 bytes
    struct kvs_header location;
    struct kvs_bnode_key key[KVS_BTREE_KEY_MAX];
    u8 nrkeys;
    struct kvs_bnode_off ptrs[KVS_BTREE_CHILD_MAX];
    u8 nrptrs;
    u32 level;
    u8 flags;
    struct kvs_header parent;
    u8 padding[63];
}__attribute__((__packed__));

//btree node's num:32*1024*32
#define KVS_BTREE_BITMAP_ENTRY (32*1024)
#define KVS_BTREE_MAX_BNODE (KVS_BTREE_BITMAP_ENTRY * sizeof(u32) * sizeof(u8))

//132KB:4KB + bitmap(128KB)
struct kvs_btree_super {
    u32 magic;
    u32 flags;
    u64 size;
    u32 nritems;
    u64 nrkeys;
    u64 hints; //hint next available pos in bitmap
    u32 bitmap[KVS_BTREE_BITMAP_ENTRY];
    struct kvs_header root;
    u8 padding[4039];
}__attribute__((__packed__));
 
#define KVS_BTREE_SIZE (KVS_BTREE_MAX_BNODE * sizeof(struct kvs_bnode_item) + sizeof(struct kvs_btree_super))   

/*
 * memory info of btree definition
 * add transaction in here,need to prepare for that
 * need layer:
 * super --> node cache --> blk cache --> disk
 * super --> trasaction --> log
 */
struct kvs_bnode;

struct kvs_btree_info {
    const char *filename;
    u8 mode;
    struct kvs_btree_super *super;
    struct kvs_bnode *root;
    struct list node_list;
    struct list node_lru;
    struct list dirty_list;
};

#endif
