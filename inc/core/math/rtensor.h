#ifndef RTENSOR_H
#define RTENSOR_H

#include "real.h"

typedef struct rtensor {
    size_t row;
    size_t col;
    size_t hgh;
    real_t tensor;
} *rtensor_t;

#define SIZE_RTENSOR sizeof(struct rtensor)

rtensor_t rtensor_init(size_t line, size_t row, size_t hgh);

rtensor_t rtensor_zero(size_t row, size_t col, size_t hgh);

rtensor_t rtensor_one(size_t row, size_t col, size_t hgh);

rtensor_t rtensor_new(size_t line, size_t row, size_t hgh, ...);

void rtensor_delete(rtensor_t mat);

bool rtensor_is_null(const rtensor_t mat);

bool rtensor_is_real(const rtensor_t mat);

bool rtensor_is_column(const rtensor_t mat);

bool rtensor_is_row(const rtensor_t mat);

bool rtensor_is_matrix(const rtensor_t mat);

rtensor_t rtensor_add(const rtensor_t mat1, const rtensor_t mat2);

rtensor_t rtensor_sub(const rtensor_t mat1, const rtensor_t mat2);

rtensor_t rtensor_mult(const rtensor_t mat1, const rtensor_t mat2);

rtensor_t rtensor_outer(const rtensor_t mat1, const rtensor_t mat2);

rtensor_t rtensor_scale(const rtensor_t mat, const rtensor_t scalar);

void rtensor_print(const rtensor_t mat);

#endif /* end of include guard: RTENSOR_H */
