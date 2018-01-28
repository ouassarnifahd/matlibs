#ifndef RMATRIX_H
#define RMATRIX_H

#include "real.h"

typedef struct rmatrix {
    size_t row;
    size_t col;
    real_t matrix;
} *rmatrix_t;

#define SIZE_RMATRIX sizeof(struct rmatrix)

rmatrix_t rmatrix_init(size_t line, size_t row);

rmatrix_t rmatrix_zero(size_t row, size_t col);

rmatrix_t rmatrix_one(size_t row, size_t col);

rmatrix_t rmatrix_eye(size_t size);

rmatrix_t rmatrix_new(size_t line, size_t row, ...);

void rmatrix_delete(rmatrix_t mat);

bool rmatrix_is_null(const rmatrix_t mat);

bool rmatrix_is_real(const rmatrix_t mat);

bool rmatrix_is_column(const rmatrix_t mat);

bool rmatrix_is_row(const rmatrix_t mat);

bool rmatrix_is_square(const rmatrix_t mat);

size_t rmatrix_rank(const rmatrix_t mat);

sreal_t rmatrix_descriminant(const rmatrix_t mat);

void rmatrix_inv(rmatrix_t mat);

void rmatrix_transpose(rmatrix_t mat);

rmatrix_t rmatrix_add(const rmatrix_t mat1, const rmatrix_t mat2);

rmatrix_t rmatrix_sub(const rmatrix_t mat1, const rmatrix_t mat2);

rmatrix_t rmatrix_mult(const rmatrix_t mat, const rmatrix_t mat2);

rmatrix_t rmatrix_scale(const rmatrix_t mat, const rmatrix_t scalar);

rmatrix_t rmatrix_pow(const rmatrix_t mat, size_t power);

void rmatrix_print(const rmatrix_t mat);

#endif /* end of include guard: RMATRIX_H */
