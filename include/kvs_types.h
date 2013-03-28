#ifndef __KVS_TYPES_H_
#define __KVS_TYPES_H_

/*
 * all data type definition
 * 
 */

#include <stdint.h>

typedef uint32_t u32;
typedef int32_t s32;
typedef uint64_t u64;
typedef int64_t s64;
typedef uint8_t u8;
typedef int8_t s8;

typedef unsigned long ptr_t;

#define BITS_PER_U32 (sizeof(u32)*8)
#define U32_MAX ((u32)-1)
#define BITS_PER_BYTE (sizeof(char)*8)

#define BITMAP_LAST_WORD_MASK(nbits)                \
    (                                               \
     ((nbits % BITS_PER_U32))?                      \
     (1UL << (nbits % BITS_PER_U32) -1 : ~0UL)      \
                                                    )

#define BITMAP_LAST_WORD_ZERO(nbits)            \
    (                                           \
     ((nbits % BITS_PER_U32))?                  \
     (~0UL >> (nbits % BITS_PER_U32)):0UL       \
                                                )

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define BITS_TO_U32(nr) DIV_ROUND_UP(nr,BITS_PER_BYTE * sizeof(u32))

#define IS_IMMEDIATE(nr)		(__builtin_constant_p(nr))

#endif
