#include "stdio.h"
#include "sds.h"

int main(void)
{
// sdsnewlen
#ifdef SDSNEWLEN
    sds s1 = sdsnewlen("hello", 5);

    uint8_t flag = *((unsigned char *)s1 - 1);

    printf("string:%s, flag:0x%02x, len:%d, type:%d\n", s1, flag, (flag & 0xF8) >> 3, flag & 0x07);
#endif

#ifdef SDSCATLEN
    sds s1 = sdsnewlen("hello", 5);
    sds s2 = sdscatlen(s1, " world", 6);
    printf("string:%s", s2);
#endif

    return 0;
}