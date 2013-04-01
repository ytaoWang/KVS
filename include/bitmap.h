#ifndef __BITMAP_H__
#define __BITMAP_H__

#include "kvs_types.h"
#include "bitops.h"

#include <string.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * bitmap operations for bitmap-allocation
 * bits start from 1,0 is just a flag for return status
 *
 */
    
static int __get_remain(off_t start,size_t len)
{
    len = len - (BITS_PER_U32 - start);
    return len % BITS_PER_U32;
}

/**
 * bitmap allocation notice u32 allocation position is reverse with our mind.
 * fox example:0,return 32 rather than 1,0 flags a status/fail
 */
static u32 __bitmap_alloc(u32 *bitmap,off_t hint,size_t len)
{
    u32 start,nbits;
    
    start = hint / BITS_PER_U32;

#ifdef DEBUG
    printf("start:%u,hint:%lu\n",start,hint);
#endif    
    //scan first u32 in near hint
    if(bitmap[start] != ~0UL) {
        int left,right,mid;

        mid = hint % BITS_PER_U32;
        left = mid + 1;
        right = mid -1;
        
        while(left < BITS_PER_U32 || right > 0) {
          
#ifdef DEBUG
            printf("start:%u,hint:%lu,left:%d(%0lx),right:%d\n",start,hint,left,1UL << left,right);
#endif    
            
            if((right > 0) && !(bitmap[start] & (1UL << right)))
                return start * BITS_PER_U32 + right;
            if((left < BITS_PER_U32) && !(bitmap[start] & (1UL << left))) {
                #ifdef DEBUG
                printf("left:%d,right:%d,res:%lx,bitmap[%d]:%0x\n",left,right,bitmap[start] & (1UL << left),start,bitmap[start]);
                #endif
                return start * BITS_PER_U32 + left;
            }
            
            left ++;
            right --;
        }
        
        return 1 + start * BITS_PER_U32 + find_last_zero_bit(bitmap[start]);
    }
    
#ifdef DEBUG
    printf("start:%u,nbits:%u,hint:%lu,len:%zu\n",start,nbits,hint,len);
#endif

    // then scan after hint u32
    for(nbits = (start + 1) * BITS_PER_U32,start++;nbits < hint + len; nbits += BITS_PER_U32,start++) {
#ifdef DEBUG
        printf("start:%u,nbits:%u,bitmap[%u]:%0x\n",start,nbits,start,bitmap[start]);
#endif
        if(bitmap[start] != ~0UL)
            return 1 + nbits + find_last_zero_bit(bitmap[start]);
    }
    
    //scan u32 reverse(index offset + bit offset within u32)
    for(nbits = (start - 1) * BITS_PER_U32,start--;nbits >= 0;nbits -= BITS_PER_U32,start--) {
        if(bitmap[start] != ~0UL)
            return 1 + nbits + find_first_zero_bit(bitmap[start]);
    }
    
#ifdef DEBUG
    printf("cann't find available bit\n");
#endif
    return 0;
}
    

static inline int bitmap_clean(u32 *bitmap,unsigned long bits)
{

    int k,lim = bits/BITS_PER_U32;
    
    for(k = 0;k < lim;k++)
        bitmap[k] &= 0UL;

    bitmap[k] &= BITMAP_LAST_WORD_ZERO(bits);
    

#ifdef DEBUG
    printf("bitmap[0]:%x\n",bitmap[0]);
#endif
    return 0;
}   


static inline int bitmap_empty(const u32 *bitmap,int bits) 
{
    int k,lim = bits / BITS_PER_U32;
    
    for(k = 0;k < lim;k++) 
        if(bitmap[k])
            return 0;
    
    if((bits % BITS_PER_U32) &&                 \
       (bitmap[k] & BITMAP_LAST_WORD_MASK(bits)))
        return 0;
  
    return 1;
}

    
static inline void bitmap_fill(u32 *bitmap,int bits)
{
    u32 nlongs = BITS_TO_U32(bits);
    
    if(nlongs > 0) {
        int len = (nlongs - 1) * sizeof(u32);
        memset(bitmap,0xff,len);
    }
    
    bitmap[nlongs] = BITMAP_LAST_WORD_MASK(bits);
}


static inline u32 bitmap_find_first_zero_bit(u32 *bitmap,unsigned long start,int len)
{
    return __bitmap_alloc(bitmap,start,len);
}

static inline void bitmap_set(u32 *bitmap,unsigned long off)
{
    int k;
    
    k = off / BITS_PER_U32;
    off = off % BITS_PER_U32 - 1;
    
    set_bit(off,&bitmap[k]);

#ifdef DEBUG
    printf("bitmap[%d]:%u,off:%ld\n",k,bitmap[k],off);
#endif

}

static inline void bitmap_clear(u32 *bitmap,unsigned long off)    
{
    int k;
    
    k = off / BITS_PER_U32;
    off = off % BITS_PER_U32 - 1;
    
    clear_bit(off,&bitmap[k]);
}
    

#ifdef __cplusplus
}
#endif

#endif
