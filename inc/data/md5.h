#ifndef MD5_H
#define MD5_H

#include "common.h"

#if defined __x86_64__ || defined __i386__
typedef unsigned int md5_uint32_t;
#else
typedef unsigned char md5_uint32_t[4]; // NOT WORKING!
#endif

typedef unsigned char md5sum_t[16];

typedef struct md5 {
    md5_uint32_t LSB, MSB;
    md5_uint32_t A, B, C, D;
    unsigned char buffer[64];
    md5_uint32_t block[16];
} *md5_t;

void md5_check(const void *data, size_t size, md5sum_t result);

#endif /* end of include guard: MD5_H */
