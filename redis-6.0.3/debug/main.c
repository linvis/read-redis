#include "stdio.h"
#include "sds.h"
#include "server.h"

uint64_t hashCallback(const void *key)
{
    return dictGenHashFunction((unsigned char *)key, sdslen((char *)key));
}

int compareCallback(void *privdata, const void *key1, const void *key2)
{
    int l1, l2;
    DICT_NOTUSED(privdata);

    l1 = sdslen((sds)key1);
    l2 = sdslen((sds)key2);
    if (l1 != l2)
        return 0;
    return memcmp(key1, key2, l1) == 0;
}

void freeCallback(void *privdata, void *val)
{
    DICT_NOTUSED(privdata);

    sdsfree(val);
}
dictType debugDictType = {
    hashCallback,
    NULL,
    NULL,
    compareCallback,
    freeCallback,
    NULL};

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
#if 0
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

#if 0
    unsigned char *z1 = ziplistNew();
    unsigned char *fptr, *vptr;
    sds s1 = sdsnewlen("hello1", 6);
    sds s2 = sdsnewlen("world", 5);
    sds s3 = sdsnewlen("hi, there", 9);

    // push tail
    z1 = ziplistPush(z1, (unsigned char *)s1, sdslen(s1), ZIPLIST_TAIL);
    z1 = ziplistPush(z1, (unsigned char *)s2, sdslen(s2), ZIPLIST_TAIL);

    fptr = ziplistIndex(z1, ZIPLIST_HEAD);
    fptr = ziplistFind(fptr, (unsigned char *)s1, sdslen(s1), 1);
    vptr = ziplistNext(z1, fptr);
    z1 = ziplistInsert(z1, vptr, (unsigned char *)s3, sdslen(s3));
#endif

    // dict
    dict *dict = dictCreate(&debugDictType, NULL);
    for (int j = 0; j < 2; j++) {
        int retval = dictAdd(dict,sdsfromlonglong(j),(void*)j);
    }

    // while (dictIsRehashing(dict)) {
    //     dictRehashMilliseconds(dict, 100);
    // }
    for (int j = 0; j < 2; j++) {
        sds key = sdsfromlonglong(j);
        dictEntry *de = dictFind(dict,key);
        printf("key:%s, val:%d\n", de->key, (int)(de->v.val));

        sdsfree(key);
    }

    return 0;
}