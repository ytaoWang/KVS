#ifndef __BITOPS_H_
#define __BITOPS_H_

#include "kvs_types.h"
#ifdef DEBUG
#include <stdio.h>
#endif
#include <sys/types.h>

/*
 * SMP lock for synchronization
 * reference by /arch/x86/include/asm/alternative.h linux kernel
 * /arch/x86/include/asm/bitops.h
 * see also http://lxr.linux.no
 * All scan also come from bit 0
 */

#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 1)
#define BITOP_ADDR(x) "=m" (*(volatile long *) (x))
#else
#define BITOP_ADDR(x) "+m" (*(volatile long *)(x))
#endif

#define ADDR  BITOP_ADDR(addr)
#define CONST_MASK_ADDR(nr,addr)  BITOP_ADDR((void *)(addr) + ((nr) >>3))
#define CONST_MASK(nr)  (1 << ((nr) & 7))

//CONFIG_SMP define in linux kernel,not in userspace,make sure it's atomic operation
#ifdef CONFIG_SMP
#define LOCK_PREFIX                             \
    ".section .smp_locks,\"a\"\n"               \
    ".align 4\n"                                \
    ".long 661f\n" /* offset */                 \
    ".previous\n"                               \
    "661:\n\tlock;"
#else
#define LOCK_PREFIX ""
#endif

/**
 * X86 assembly language form:
 * ("instruction list":output:input:clobber/modify)
 */

/**
 * set_bit - Atomically set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This function is atomic and may not be reordered. @nr may be almost arbitrarily large; this function is
 * not restricted to acting on a single-world quantity.
 * set_bit count from low bit,
 * for example:set_bit(2,1) ==> 5,set_bit(0,1) ==> 1
 */
static inline void set_bit(size_t nr,u32 *addr)
{
    if (IS_IMMEDIATE(nr)) {
        asm volatile(LOCK_PREFIX "orb %1,%0"
                     :CONST_MASK_ADDR(nr,addr)
                     :"iq" ((u8)CONST_MASK(nr))
                     :"memory");
    } else {
        asm volatile(LOCK_PREFIX "bts %1,%0"
                     :BITOP_ADDR(addr):"Ir"(nr):"memory");
    }
}
/**
 * clear_bit - Clears a bit in memory,characteristic as set bit
 * @nr: Bit to clear
 * @addr: Address to start counting from
 * 
 */
static inline void clear_bit(size_t nr,volatile u32 *addr)
{
    if (IS_IMMEDIATE(nr)) {
        asm volatile(LOCK_PREFIX "andb %1,%0"
                     : CONST_MASK_ADDR(nr,addr)
                     : "iq" ((u8)~CONST_MASK(nr)));
    } else {
        asm volatile(LOCK_PREFIX "btr %1,%0"
                     : BITOP_ADDR(addr)
                     : "Ir" (nr));
    }
}
/**
 * change_bit - Toggle a bit in memory
 * @nr: Bit to change
 * @addr: Address to start counting from
 *
 * change_bit() is atomic and may not be reordered.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static inline void change_bit(size_t nr,u32 *addr)
{
    if (IS_IMMEDIATE(nr)) {
        asm volatile(LOCK_PREFIX "xorb %1,%0"
                     : CONST_MASK_ADDR(nr,addr)
                     : "iq" ((u8)CONST_MASK(nr)));
    } else {
        asm volatile(LOCK_PREFIX "btc %1,%0"
                     : BITOP_ADDR(addr)
                     : "Ir" (nr));
    }
}

/**
 * test_and_set_bit - Set a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static inline int test_and_set_bit(size_t nr,volatile u32 *addr)
{
    int oldbit;

    asm volatile(LOCK_PREFIX "bts %2,%1\n\t"
                 "sbb %0,%0" : "=r" (oldbit),ADDR:"Ir" (nr): "memory");
    
    return oldbit;
}

/**
 * test_and_clear_bit - Clear a bit and return its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This opration is atomic and cnannot be reordered.
 * It also implies a memory barrier.
 */
static inline int test_and_clear_bit(size_t nr,volatile u32 *addr)
{
    int oldbit;

    asm volatile(LOCK_PREFIX "btr %2,%1\n\t"
                 "sbb %0,%0"
                 : "=r" (oldbit),ADDR: "Ir"(nr) : "memory");
    return oldbit;
}

static inline int test_and_change_bit(size_t nr,volatile u32 *addr)
{
    int oldbit;

    asm volatile(LOCK_PREFIX "btc %2,%1\n\t"
                 "sbb %0,%0"
                 :"=r" (oldbit),ADDR:"Ir"(nr):"memory");
    return oldbit;
}

/**
 * return undefined if not zero has found,check ~0UL before call the 
 * following function
 */
static inline int find_first_zero_bit(u32 addr)
{
    asm volatile(LOCK_PREFIX "rep; bsf %1,%0"
                 :"=r"(addr):"r"(~addr));
    
    return addr;
}

static inline int find_last_zero_bit(u32 addr)
{
    asm volatile(LOCK_PREFIX "rep; bsr %1,%0"
                 :"=r"(addr):"r"(~addr));
    return addr;
}

#endif
