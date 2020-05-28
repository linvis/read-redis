#include "stdio.h"
#include "sds.h"
#include "server.h"

int main(void)
{
    // sdsnewlen
#if 0
    sds s1 = sdsnewlen("hello", 5);

    uint8_t flag = *((unsigned char *)s1 - 1);

    printf("string:%s, flag:0x%02x, len:%d, type:%d\n", s1, flag, (flag & 0xF8) >> 3, flag & 0x07);
#endif

#ifdef SDSCATLEN
    sds s1 = sdsnewlen("hello", 5);
    sds s2 = sdscatlen(s1, " world", 6);
    printf("string:%s", s2);
#endif

// zskiplist
#if 1
    zskiplist *z1 = zslCreate();
    sds s1 = sdsnewlen("hello1", 6);
    sds s2 = sdsnewlen("hello2", 6);
    sds s3 = sdsnewlen("hello3", 6);
    sds s4 = sdsnewlen("hello4", 6);
    zslInsert(z1, 3.0, s1);
    zslInsert(z1, 2.0, s2);
    zslInsert(z1, 1.0, s3);
    zslInsert(z1, 4.0, s4);
#endif

    return 0;
}