#include "bitops.h"
#include "bitmap.h"

#include <assert.h>

#define SIZE(a) (sizeof a/sizeof a[0])

/*
 * gcc test_bitops.c -I ../include -o bitops
 */
void test_set_bit(void);
void test_clear_bit(void);
void test_change_bit(void);
void test_test_and_set_bit(void);
void test_test_and_clear_bit(void);
void test_test_and_change_bit(void);
void test_find_first_zero_bit(void);

int main(int argc,char *argv[])
{
    //test_set_bit();
    //test_clear_bit();
    //test_change_bit();
    //test_test_and_set_bit();
    //test_test_and_clear_bit();
    //test_test_and_change_bit();
    test_find_first_zero_bit();
    return 0;
}

void test_set_bit(void)
{
    int i;
    u32 num[]= {1,2,1};
    set_bit(2,num);
    for(i = 0;i <SIZE(num);++i)
        printf("num[%d]:%u\n",i,num[i]);
}

void test_clear_bit(void)
{
    int i;
    u32 num[] = {1,3,5};
    clear_bit(33,num);
    for(i = 0;i < SIZE(num); ++i)
        printf("num[%d]:%u\n",i,num[i]);
    
}

void test_change_bit(void)
{
    int i;
    u32 num[] = {1,3,5};
    change_bit(33,num);
    for(i = 0;i < SIZE(num); ++i)
        printf("num[%d]:%u\n",i,num[i]);
}

void test_test_and_set_bit(void)
{
    int i;
    u32 num[] = {1,3,5};
    test_and_set_bit(33,num);
    for(i = 0;i < SIZE(num); ++i)
        printf("num[%d]:%u\n",i,num[i]);
}

void test_test_and_clear_bit(void)
{
    int i;
    u32 num[] = {1,3,5};
    test_and_clear_bit(33,num);
    for(i = 0;i < SIZE(num); ++i)
        printf("num[%d]:%u\n",i,num[i]);
}

void test_test_and_change_bit(void)
{
    int i;
    u32 num[] = {1,3,5};
    test_and_clear_bit(33,num);
    for(i = 0;i < SIZE(num); ++i)
        printf("num[%d]:%u\n",i,num[i]);
}

void test_find_first_zero_bit(void)
{
    int i;
    u32 num[] = {0x0fffffff,3,4};
    i = find_first_zero_bit(num[0]);
    printf("zero bit:%d\n",i);
    for(i = 0;i < SIZE(num);++i)
        printf("num[%d]:%0x\n",i,num[i]);
    num[0] = -1;
    i = find_last_zero_bit(num[0]);
    printf("zero bit:%d\n",i);
    for(i = 0;i < SIZE(num);++i)
        printf("num[%d]:%0x\n",i,num[i]);
}
