#include "kvs_types.h"

#include <sys/types.h>

/*
 * SMP lock for synchronization
 * reference by /arch/x86/include/asm/alternative.h linux kernel
 * see also http://lxr.linux.no
 */

//CONFIG_SMP define in linux kernel,not in userspace
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

static inline void set_bit(size_t nr,volatile u32 *addr)
{
    if(IS_IMMEDIATE(nr)) {
        
    } else {
        
    }
}

static inline void clear_bit(size_t nr,volatile u32 *addr)
{
    
}

static inline void change_bit(size_t nr,u32 *addr)
{
    
}

static inline int test_and_set_bit(size_t nr,volatile u32 *addr)
{
    return 0;
}

static inline int test_and_clear_bit(size_t nr,volatile u32 *addr)
{
    return 0;
}

static inline int find_first_zero_bit(const u32 *addr,size_t size)
{
    return 0;
}

static inline int find_last_zero_bit(const u32 *addr, size_t size)
{
    return 0;
}

