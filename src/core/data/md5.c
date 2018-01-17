#include "std.h"
#include "core/data/md5.h"

#if defined __x86_64__ || defined __i386__
typedef unsigned int md5_uint32_t;
#else
typedef unsigned char md5_uint32_t[4]; // NOT WORKING!
#endif

typedef struct md5 {
    md5_uint32_t LSB, MSB;
    md5_uint32_t A, B, C, D;
    unsigned char buffer[64];
    md5_uint32_t block[16];
} *md5_t;

// The basic MD5 functions.
#define F(x, y, z)	((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z)	((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z) (((x) ^  (y)) ^ (z))
#define H2(x, y, z)	((x) ^ ((y)  ^ (z)))
#define I(x, y, z)	((y) ^ ((x) | ~(z)))

// The MD5 transformation for all four rounds.
#define STEP(f, a, b, c, d, x, t, s) \
	(a) += f((b), (c), (d)) + (x) + (t); \
	(a) = (((a) << (s)) | (((a) & 0xffffffff) >> (32 - (s)))); \
	(a) += (b)

#if defined(__i386__) || defined(__x86_64__) || defined(__vax__)
#define SET(n) \
	(*(md5_uint32_t *)&ptr[(n) * 4])
#define GET(n) \
	SET(n)
#else
#define SET(n) \
	(checksum->block[(n)] = \
	( md5_uint32_t)ptr[(n) * 4] | \
	((md5_uint32_t)ptr[(n) * 4 + 1] << 8) | \
	((md5_uint32_t)ptr[(n) * 4 + 2] << 16) | \
	((md5_uint32_t)ptr[(n) * 4 + 3] << 24))
#define GET(n) \
	(checksum->block[(n)])
#endif

static const void* body(md5_t checksum, const void *data, size_t size) {
	const unsigned char *ptr;
	md5_uint32_t a, b, c, d;
	md5_uint32_t saved_a, saved_b, saved_c, saved_d;
	ptr = (const unsigned char *)data;
	a = checksum->A;
	b = checksum->B;
	c = checksum->C;
	d = checksum->D;
	do {
		saved_a = a;
		saved_b = b;
		saved_c = c;
		saved_d = d;

		/* Round 1 */
		STEP(F, a, b, c, d, SET(0),  0xd76aa478, 7);
		STEP(F, d, a, b, c, SET(1),  0xe8c7b756, 12);
		STEP(F, c, d, a, b, SET(2),  0x242070db, 17);
		STEP(F, b, c, d, a, SET(3),  0xc1bdceee, 22);
		STEP(F, a, b, c, d, SET(4),  0xf57c0faf, 7);
		STEP(F, d, a, b, c, SET(5),  0x4787c62a, 12);
		STEP(F, c, d, a, b, SET(6),  0xa8304613, 17);
		STEP(F, b, c, d, a, SET(7),  0xfd469501, 22);
		STEP(F, a, b, c, d, SET(8),  0x698098d8, 7);
		STEP(F, d, a, b, c, SET(9),  0x8b44f7af, 12);
		STEP(F, c, d, a, b, SET(10), 0xffff5bb1, 17);
		STEP(F, b, c, d, a, SET(11), 0x895cd7be, 22);
		STEP(F, a, b, c, d, SET(12), 0x6b901122, 7);
		STEP(F, d, a, b, c, SET(13), 0xfd987193, 12);
		STEP(F, c, d, a, b, SET(14), 0xa679438e, 17);
		STEP(F, b, c, d, a, SET(15), 0x49b40821, 22);

		/* Round 2 */
		STEP(G, a, b, c, d, GET(1),  0xf61e2562, 5);
		STEP(G, d, a, b, c, GET(6),  0xc040b340, 9);
		STEP(G, c, d, a, b, GET(11), 0x265e5a51, 14);
		STEP(G, b, c, d, a, GET(0),  0xe9b6c7aa, 20);
		STEP(G, a, b, c, d, GET(5),  0xd62f105d, 5);
		STEP(G, d, a, b, c, GET(10), 0x02441453, 9);
		STEP(G, c, d, a, b, GET(15), 0xd8a1e681, 14);
		STEP(G, b, c, d, a, GET(4),  0xe7d3fbc8, 20);
		STEP(G, a, b, c, d, GET(9),  0x21e1cde6, 5);
		STEP(G, d, a, b, c, GET(14), 0xc33707d6, 9);
		STEP(G, c, d, a, b, GET(3),  0xf4d50d87, 14);
		STEP(G, b, c, d, a, GET(8),  0x455a14ed, 20);
		STEP(G, a, b, c, d, GET(13), 0xa9e3e905, 5);
		STEP(G, d, a, b, c, GET(2),  0xfcefa3f8, 9);
		STEP(G, c, d, a, b, GET(7),  0x676f02d9, 14);
		STEP(G, b, c, d, a, GET(12), 0x8d2a4c8a, 20);

		/* Round 3 */
		STEP(H,  a, b, c, d, GET(5),  0xfffa3942, 4);
		STEP(H2, d, a, b, c, GET(8),  0x8771f681, 11);
		STEP(H,  c, d, a, b, GET(11), 0x6d9d6122, 16);
		STEP(H2, b, c, d, a, GET(14), 0xfde5380c, 23);
		STEP(H,  a, b, c, d, GET(1),  0xa4beea44, 4);
		STEP(H2, d, a, b, c, GET(4),  0x4bdecfa9, 11);
		STEP(H,  c, d, a, b, GET(7),  0xf6bb4b60, 16);
		STEP(H2, b, c, d, a, GET(10), 0xbebfbc70, 23);
		STEP(H,  a, b, c, d, GET(13), 0x289b7ec6, 4);
		STEP(H2, d, a, b, c, GET(0),  0xeaa127fa, 11);
		STEP(H,  c, d, a, b, GET(3),  0xd4ef3085, 16);
		STEP(H2, b, c, d, a, GET(6),  0x04881d05, 23);
		STEP(H,  a, b, c, d, GET(9),  0xd9d4d039, 4);
		STEP(H2, d, a, b, c, GET(12), 0xe6db99e5, 11);
		STEP(H,  c, d, a, b, GET(15), 0x1fa27cf8, 16);
		STEP(H2, b, c, d, a, GET(2),  0xc4ac5665, 23);

		/* Round 4 */
		STEP(I, a, b, c, d, GET(0),  0xf4292244, 6);
		STEP(I, d, a, b, c, GET(7),  0x432aff97, 10);
		STEP(I, c, d, a, b, GET(14), 0xab9423a7, 15);
		STEP(I, b, c, d, a, GET(5),  0xfc93a039, 21);
		STEP(I, a, b, c, d, GET(12), 0x655b59c3, 6);
		STEP(I, d, a, b, c, GET(3),  0x8f0ccc92, 10);
		STEP(I, c, d, a, b, GET(10), 0xffeff47d, 15);
		STEP(I, b, c, d, a, GET(1),  0x85845dd1, 21);
		STEP(I, a, b, c, d, GET(8),  0x6fa87e4f, 6);
		STEP(I, d, a, b, c, GET(15), 0xfe2ce6e0, 10);
		STEP(I, c, d, a, b, GET(6),  0xa3014314, 15);
		STEP(I, b, c, d, a, GET(13), 0x4e0811a1, 21);
		STEP(I, a, b, c, d, GET(4),  0xf7537e82, 6);
		STEP(I, d, a, b, c, GET(11), 0xbd3af235, 10);
		STEP(I, c, d, a, b, GET(2),  0x2ad7d2bb, 15);
		STEP(I, b, c, d, a, GET(9),  0xeb86d391, 21);

		a += saved_a;
		b += saved_b;
		c += saved_c;
		d += saved_d;
		ptr += 64;
	} while (size -= 64);

	checksum->A = a;
	checksum->B = b;
	checksum->C = c;
	checksum->D = d;
	return ptr;
}

static void MD5_Init(md5_t checksum) {
	checksum->A = 0x67452301;
	checksum->B = 0xefcdab89;
	checksum->C = 0x98badcfe;
	checksum->D = 0x10325476;
	checksum->LSB = 0;
	checksum->MSB = 0;
}

static void MD5_Update(md5_t checksum, const void *data, size_t size) {
	md5_uint32_t saved_LSB;
	size_t used, available;
	saved_LSB = checksum->LSB;
	if ((checksum->LSB = (saved_LSB + size) & 0x1fffffff) < saved_LSB)
		checksum->MSB++;
	checksum->MSB += size >> 29;
	used = saved_LSB & 0x3f;
	if (used) {
		available = 64 - used;
		if (size < available) {
			memcpy(&checksum->buffer[used], data, size);
			return;
		}
		memcpy(&checksum->buffer[used], data, available);
		data = (const unsigned char *)data + available;
		size -= available;
		body(checksum, checksum->buffer, 64);
	}
	if (size >= 64) {
		data = body(checksum, data, size & ~(unsigned long)0x3f);
		size &= 0x3f;
	}
	memcpy(checksum->buffer, data, size);
}

#define OUT(dst, src) \
	(dst)[0] = (unsigned char)(src); \
	(dst)[1] = (unsigned char)((src) >> 8); \
	(dst)[2] = (unsigned char)((src) >> 16); \
	(dst)[3] = (unsigned char)((src) >> 24)

static void MD5_Final(md5_t checksum, md5sum_t result) {
	unsigned long used, available;
	used = checksum->LSB & 0x3f;
	checksum->buffer[used++] = 0x80;
	available = 64 - used;
	if (available < 8) {
		memset(&checksum->buffer[used], 0, available);
		body(checksum, checksum->buffer, 64);
		used = 0;
		available = 64;
	}
	memset(&checksum->buffer[used], 0, available - 8);
	checksum->LSB <<= 3;
	OUT(&checksum->buffer[56], checksum->LSB);
	OUT(&checksum->buffer[60], checksum->MSB);
	body(checksum, checksum->buffer, 64);
	OUT(&result[0], checksum->A);
	OUT(&result[4], checksum->B);
	OUT(&result[8], checksum->C);
	OUT(&result[12], checksum->D);
	memset(checksum, 0, sizeof(*checksum));
}

void md5_check(const void *data, size_t size, md5sum_t result) {
    md5_t checksum = malloc(sizeof(struct md5));
    alloc_check(checksum);
    MD5_Init(checksum);
    MD5_Update(checksum, data, size);
    MD5_Final(checksum, result);
    free(checksum);
}

#ifdef DEBUGED
int main(int argc, char const *argv[]) {
    if (argc == 2) {
        FILE* pFile = fopen (argv[1] , "rb");
        // get file size
        fseek (pFile , 0 , SEEK_END);
        size_t lSize = ftell (pFile);
        rewind (pFile);
        // read data!
        void* data = malloc(lSize);
        fread(data, 1, lSize, pFile);
        md5sum_t sum;
        md5_check(data, lSize, sum);
        for (size_t i = 0; i < 16; i++) {
            printf("%hhx", sum[i]);
        }
        printf("\n");
        free(data);
        fclose(pFile);
    } else {
        printf("Invalide arguments!\n");
    }
    return 0;
}
#endif
