#ifndef __BITMAP_H__
#define __BITMAP_H__

#include "kvs_types.h"
#include "bitops.h"

#include <string.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

/*
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
static u32 __bitmap_alloc(u32 *bitmap,off_t start,size_t len)
{
    int k,lim,s1,s2,pos;
    u32 b,e;
    
    k = start / BITS_PER_U32;
    s1 = start % BITS_PER_U32;
    lim = (len >= BITS_PER_U32 ? BITS_PER_U32:len);
    
#ifdef DEBUG
    printf("begin index:%d,offset:%d,start:%ld,len:%u\n",k,s1,start,len);
#endif
    /*    
    b = bitmap[k] | (~0UL << (BITS_PER_U32 - s1));
    
    if((pos = find_first_zero_bit(b,lim)) != lim)
    {
#ifdef DEBUG
        printf("find in first u32,pos:%d\n",pos);
#endif
        return BITS_PER_U32 - (pos + 1) + k * BITS_PER_U32;
    }
    
    lim = (start + len)/BITS_PER_U32;
    
#ifdef DEBUG
    printf("k:%d,lim:%d\n",k,lim);
#endif
    for(k=k+1;k<lim;k++)
    {
        if((pos = find_first_zero_bit(bitmap[k],BITS_PER_U32)) != BITS_PER_U32)
        {
#ifdef DEBUG
            printf("find in internal u32,pos:%d\n",pos);
#endif
            return k * BITS_PER_U32 + BITS_PER_U32 - pos - 1;
        }
    }

    s2 = __get_remain(start,len);
    //get the last u32's starting bit
#ifdef DEBUG
    printf("find in the last u32:%d\n",s2);
#endif
    
    b = bitmap[k] | (~0UL << (BITS_PER_U32 - s2));
    if((pos = find_first_zero_bit(b,s2+1)) != (s2+1))
    {
        #ifdef DEBUG
        printf("find in last u32,pos:%d\n",pos);
        #endif
        return (k+1) * BITS_PER_U32 - pos - 1;
    }
*/    
    return 0;
}
    

static inline int bitmap_clean(u32 *bitmap,unsigned long bits)
{

    int k,lim = bits/BITS_PER_U32;
    
    for(k = 0;k < lim;k++)
        bitmap[k] &= 0UL;

    #ifdef DEBUG
    #endif 

    bitmap[k] &= BITMAP_LAST_WORD_ZERO(bits);
    

    #ifdef DEBUG
    printf("bitmap[0]:%x\n",bitmap[0]);
    #endif
}   


static inline int bitmap_empty(const u32 *bitmap,int bits) 
{
  int k,lim = bits / BITS_PER_U32;
  
  for(k = 0;k < lim;k++) 
    if(bitmap[k])
      	return 0;
  
  if((bits % BITS_PER_U32) && \
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
    off = off % BITS_PER_U32;
    
    set_bit((BITS_PER_U32 - off -1 ),&bitmap[k]);
    #ifdef DEBUG
    printf("bitmap[%d]:%u,off:%ld\n",k,bitmap[k],off);
    #endif
}

static inline void bitmap_clear(u32 *bitmap,unsigned long off)    
{
    int k;
    
    k = off / BITS_PER_U32;
    off = off % BITS_PER_U32;
    
    clear_bit((BITS_PER_U32 - k - 1),&bitmap[off]);
}
    

#ifdef __cplusplus
}
#endif

#endif
