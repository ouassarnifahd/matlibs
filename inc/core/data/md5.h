#ifndef MD5_H
#define MD5_H

typedef unsigned char md5sum_t[16];

void md5_check(const void *data, size_t size, md5sum_t result);

#endif /* end of include guard: MD5_H */
