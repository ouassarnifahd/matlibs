#include "std.h"
#include "core/math/rmatrix.h"

#define INDEX(i, j, col) i * col + j

rmatrix_t rmatrix_init(size_t row, size_t col) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rmatrix_t mat = Mat_alloc(SIZE_RMATRIX);
    alloc_check(mat);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'mat': %zu Octets", SIZE_RMATRIX);
    #endif
    mat->row = row;
    mat->col = col;
    mat->matrix = Mat_alloc(SIZE_RMatrix(row, col));
    alloc_check(mat->matrix);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'mat->matrix': %zu Octets", (size_t)SIZE_RMatrix(row, col));
    #endif
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return mat;
}

rmatrix_t rmatrix_zero(size_t row, size_t col) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rmatrix_t zero = rmatrix_init(row, col);
    for (size_t i = 0; i < zero->row * zero->col; i++) {
        zero->matrix[i] = 0;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return zero;
}

rmatrix_t rmatrix_one(size_t row, size_t col) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rmatrix_t one = rmatrix_init(row, col);
    for (size_t i = 0; i < one->row * one->col; i++) {
        one->matrix[i] = 1;
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return one;
}

rmatrix_t rmatrix_eye(size_t size) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rmatrix_t eye = rmatrix_init(size, size);
    if (size == 1) {
        real_one(eye->matrix);
    } else {
        for (size_t i = 0; i < eye->row; i++) {
            for (size_t j = 0; j < eye->col; j++) {
                if (i == j) {
                    real_one(&eye->matrix[INDEX(i, j, eye->col)]);
                } else {
                    real_zero(&eye->matrix[INDEX(i, j, eye->col)]);
                }
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return eye;
}

rmatrix_t rmatrix_new(size_t row, size_t col, ...) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rmatrix_t mat = rmatrix_init(row, col);
    sreal_t arg;
    va_list args;
    va_start(args, col);
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            arg = va_arg(args, sreal_t);
            mat->matrix[INDEX(i, j, col)] = arg;
            #ifdef DEBUGED
            Mat_printf("Index(%zu, %zu) = %zu <- ",i, j, INDEX(i, j, col));
            real_print(&mat->matrix[INDEX(i, j, col)]);
            Mat_printf("\n");
            #endif
        }
    }
    va_end(args);
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return mat;
}

void rmatrix_delete(rmatrix_t mat) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (mat) {
        if (mat->matrix) {
            Mat_free(mat->matrix);
            #ifdef DEBUG_FREE
            debug("Memory freed (mat->matrix)");
            #endif
            mat->matrix = NULL;
        }
        Mat_free(mat);
        #ifdef DEBUG_FREE
        debug("Memory freed (mat)");
        #endif
        mat = NULL;
    } else {
        warning("NULL pointer exeption!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

bool rmatrix_is_null(const rmatrix_t mat) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (mat) {
        size_t i = 0;
        while(i < mat->row * mat->col && real_is_null(&mat->matrix[i])) i++;
        #ifdef DEBUG_CONTEXT
        debug("leaving function!\n");
        #endif
        if (i == mat->row * mat->col)
            return true;
        else
            return false;
    } else {
        error("NULL pointer is already null!");
    }
}

bool rmatrix_is_real(const rmatrix_t mat) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    if (mat) {
        return mat->row == 1 && mat->col == 1;
    } else {
        error("NULL pointer is not real!");
    }
}

bool rmatrix_is_row(const rmatrix_t mat) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    if (mat) {
        return mat->row == 1 && mat->col > 0;
    } else {
        error("NULL pointer is not a row Matrix!");
    }
}

bool rmatrix_is_column(const rmatrix_t mat) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    if (mat) {
        return mat->col == 1 && mat->row > 0;
    } else {
        error("NULL pointer is not a column Matrix!");
    }
}

bool rmatrix_is_square(const rmatrix_t mat) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    if (mat) {
        return mat->row == mat->col;
    } else {
        error("NULL pointer is not a square Matrix!");
    }
}

// size_t rmatrix_rank(const rmatrix_t mat) {
//     #ifdef DEBUG_CONTEXT
//     debug("Entering function!");
//     #endif
//     size_t rank = Mat_min(mat->row, mat->col);
//     if (mat) {
//
//     } else {
//         error("NULL pointer methode!");
//     }
//     #ifdef DEBUG_CONTEXT
//     debug("leaving function!\n");
//     #endif
//     return rank;
// }

// sreal_t rmatrix_descriminant(const rmatrix_t mat) {
//     #ifdef DEBUG_CONTEXT
//     debug("Entering function!");
//     #endif
//     sreal_t det = 0;
//     if (mat) {
//
//     } else {
//         error("NULL pointer methode!");
//     }
//     #ifdef DEBUG_CONTEXT
//     debug("leaving function!\n");
//     #endif
//     return det;
// }

void rmatrix_transpose(rmatrix_t mat) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (mat) {
        size_t tmp = mat->row;
        mat->row = mat->col;
        mat->col = tmp;
        if (!(rmatrix_is_real(mat) || rmatrix_is_row(mat) || rmatrix_is_column(mat))) {
            for (size_t i = 0; i < mat->row; i++) {
                for (size_t j = 0; j < mat->col; j++) {
                    if (j > i) {
                        real_swap(&mat->matrix[INDEX(j, i, mat->col)],
                                  &mat->matrix[INDEX(i, j, mat->col)]);
                    }
                }
            }
        }
    } else {
        error("NULL pointer methode!");
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

// void rmatrix_inv(rmatrix_t mat) {
//     #ifdef DEBUG_CONTEXT
//     debug("Entering function!");
//     #endif
//     if (mat) {
//         for (size_t i = 0; i < mat->row * mat->col; i++)
//             real_inv(&mat->matrix[i]);
//     } else {
//         error("NULL pointer can't be inversed!");
//     }
//     #ifdef DEBUG_CONTEXT
//     debug("leaving function!\n");
//     #endif
// }

rmatrix_t rmatrix_add(const rmatrix_t mat1, const rmatrix_t mat2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rmatrix_t res = NULL;
    if (!mat1 || !mat2) {
        error("NULL pointer operation!");
    } else if (mat1->row != mat2->row || mat1->col != mat2->col) {
        error("Matrix dimentions must agree!");
    } else {
        res = rmatrix_init(mat1->row, mat1->col);
        if (rmatrix_is_real(mat1)) {
            *res->matrix = *mat1->matrix + *mat2->matrix;
        } else {
            for (size_t i = 0; i < res->row * res->col; i++) {
                res->matrix[i] = mat1->matrix[i] + mat2->matrix[i];
                // real_add(&mat1->matrix[i], &mat2->matrix[i], &res->matrix[i]);
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

rmatrix_t rmatrix_sub(const rmatrix_t mat1, const rmatrix_t mat2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rmatrix_t res = NULL;
    if (!mat1 || !mat2) {
        error("NULL pointer operation!");
    } else if (mat1->row != mat2->row || mat1->col != mat2->col) {
        error("Matrix dimentions must agree!");
    } else {
        res = rmatrix_init(mat1->row, mat1->col);
        if (rmatrix_is_real(mat1)) {
            *res->matrix = *mat1->matrix - *mat2->matrix;
        } else {
            for (size_t i = 0; i < res->row * res->col; i++) {
                res->matrix[i] = mat1->matrix[i] - mat2->matrix[i];
                // real_sub(&mat1->matrix[i], &mat2->matrix[i], &res->matrix[i]);
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

rmatrix_t rmatrix_mult(const rmatrix_t mat1, const rmatrix_t mat2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rmatrix_t res = NULL;
    if (!mat1 || !mat2) {
        error("NULL pointer operation!");
    } else if (mat1->col != mat2->row) {
        error("Matrix dimentions must agree!");
    } else {
        res = rmatrix_init(mat1->row, mat2->col);
        if (rmatrix_is_real(mat1)) {
            *res->matrix = *mat1->matrix * *mat2->matrix;
        } else {
            for (size_t i = 0; i < res->row; i++) {
                for (size_t j = 0; j < res->col; j++) {
                    sreal_t tmp = 0;
                    for (size_t k = 0; k < mat1->col; k++) {
                        tmp += mat1->matrix[INDEX(i, k, mat1->col)]
                             * mat2->matrix[INDEX(k, j, mat2->col)];
                        // real_mult(&mat1->matrix[i + k], &mat2->matrix[i + k], &tmp);
                        // real_add(&tmp, &dot, &dot);
                    }
                    res->matrix[INDEX(i, j, res->col)] = tmp;
                    // res->matrix[i] = dot;
                }
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

rmatrix_t rmatrix_scale(const rmatrix_t mat, const rmatrix_t scalar) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rmatrix_t res = NULL;
    if (!mat || !scalar) {
        error("NULL pointer operation!");
    } else if (!rmatrix_is_real(scalar)) {
        error("'scalar' corrupted!");
    } else {
        res = rmatrix_init(mat->row, mat->col);
        for (size_t i = 0; i < res->row * res->col; i++) {
            res->matrix[i] = mat->matrix[i] * *scalar->matrix;
            // real_mult(&vect1->vector[i], &vect2->vector[i], &res->vector[i]);
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

rmatrix_t rmatrix_pow(const rmatrix_t mat, size_t power) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    rmatrix_t res = NULL;
    if (!mat) {
        error("NULL pointer operation!");
    } else if (!rmatrix_is_square(mat)) {
        error("Matrix dimentions must agree!");
    } else {
        res = rmatrix_eye(mat->row);
        if (rmatrix_is_real(mat)) {
            for (size_t i = 0; i < power; i++) {
                res->matrix[0] *= mat->matrix[0];
            }
        } else {
            for (size_t i = 0; i < power; i++) {
                for (size_t i = 0; i < res->row; i++) {
                    for (size_t j = 0; j < res->col; j++) {
                        sreal_t tmp = 0;
                        for (size_t k = 0; k < res->col; k++) {
                            tmp += res->matrix[INDEX(i, k, res->col)]
                                 * mat->matrix[INDEX(k, j, mat->col)];
                        }
                        res->matrix[INDEX(i, j, res->col)] = tmp;
                    }
                }
            }
        }
    }
    return res;
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
}

void rmatrix_print(const rmatrix_t mat) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (mat) {
        if (rmatrix_is_real(mat)) {
            Mat_printf("\n\t");
            real_print(mat->matrix);
            Mat_printf("\n");
        } else {
            Mat_printf("\n");
            for (size_t i = 0; i < mat->row; i++) {
                Mat_printf("\t[ ");
                for (size_t j = 0; j < mat->col; j++) {
                    real_print(&mat->matrix[INDEX(i, j, mat->col)]);
                    if (j != mat->col - 1) {
                        Mat_printf("  ");
                    }
                }
                Mat_printf(" ]\n");
            }
            Mat_printf("\n");
        }
    } else {
        error("NULL pointer print!");
    }
    #ifdef DEBUG_PRINT
    debug("leaving print function!\n");
    #endif
}

#ifdef DEBUGED
#define N 15

int main(int argc, char const *argv[]) {
    init_log();
    #if defined (__x86_64__)
        debug("64-bit architecture!\n");
    #elif defined (__i386__)
        warning("32-bit architecture!\n");
    #else
        error("Incompatible architecture!");
    #endif

    rmatrix_t m_one  = rmatrix_one(N, N);

    // memory_Debug();

    // rmatrix_t m_one2 = rmatrix_mult(m_one, m_one);

    // memory_Debug();

    Mat_printf("one = "); rmatrix_print(m_one);

    rmatrix_delete(m_one);
    // rmatrix_delete(m_one2);

    debug("FY!");
    return 0;
}
#endif
