#ifndef CMATRIX_H
#define CMATRIX_H

#include "complexe.h"

typedef struct cmatrix {
    size_t row;
    size_t col;
    complexe_t matrix;
} *cmatrix_t;

#define SIZE_CMATRIX sizeof(struct cmatrix)

cmatrix_t cmatrix_init(size_t line, size_t row);

cmatrix_t cmatrix_zero(size_t row, size_t col);

cmatrix_t cmatrix_one(size_t row, size_t col);

cmatrix_t cmatrix_i(size_t row, size_t col);

cmatrix_t cmatrix_eye(size_t size);

cmatrix_t cmatrix_new(size_t line, size_t row, ...);

void cmatrix_delete(cmatrix_t mat);

bool cmatrix_is_null(const cmatrix_t mat);

bool cmatrix_is_complexe(const cmatrix_t mat);

bool cmatrix_is_column(const cmatrix_t mat);

bool cmatrix_is_row(const cmatrix_t mat);

bool cmatrix_is_square(const cmatrix_t mat);

size_t cmatrix_rank(const cmatrix_t mat);

sreal_t cmatrix_descriminant(const cmatrix_t mat);

void cmatrix_inv(cmatrix_t mat);

void cmatrix_transpose(cmatrix_t mat);

cmatrix_t cmatrix_add(const cmatrix_t mat1, const cmatrix_t mat2);

cmatrix_t cmatrix_sub(const cmatrix_t mat1, const cmatrix_t mat2);

cmatrix_t cmatrix_mult(const cmatrix_t mat, const cmatrix_t mat2);

cmatrix_t cmatrix_scale(const cmatrix_t mat, const cmatrix_t scalar);

cmatrix_t cmatrix_pow(const cmatrix_t mat, size_t power);

void cmatrix_print(const cmatrix_t mat);

#endif /* end of include guard: CMATRIX_H */
