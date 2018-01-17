#include "std.h"
#include "core/math/cmatrix.h"

#define INDEX(i, j, col) i * col + j

cmatrix_t cmatrix_init(size_t row, size_t col) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cmatrix_t mat = Mat_alloc(SIZE_CMATRIX);
    alloc_check(mat);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'mat': %zu Octets", SIZE_CMATRIX);
    #endif
    mat->row = row;
    mat->col = col;
    mat->matrix = Mat_alloc(SIZE_CMatrix(row, col));
    alloc_check(mat->matrix);
    #ifdef DEBUG_MALLOC
    debug("Memory allocation 'mat->matrix': %zu Octets", (size_t)SIZE_CMatrix(row, col));
    #endif
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return mat;
}

cmatrix_t cmatrix_new(size_t row, size_t col, ...) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cmatrix_t mat = cmatrix_init(row, col);
    scomplexe_t arg;
    va_list args;
    va_start(args, col);
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            arg = va_arg(args, scomplexe_t);
            mat->matrix[INDEX(i, j, col)] = arg;
            #ifdef DEBUGED
            Mat_printf("Index(%zu, %zu) = %zu <- ",i, j, INDEX(i, j, col));
            complexe_print(&mat->matrix[INDEX(i, j, col)]);
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

void cmatrix_delete(cmatrix_t mat) {
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

bool cmatrix_is_null(const cmatrix_t mat) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (mat) {
        size_t i = 0;
        while(i < mat->row * mat->col && complexe_is_null(&mat->matrix[i])) i++;
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

bool cmatrix_is_complexe(const cmatrix_t mat) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    if (mat) {
        return mat->row == 1 && mat->col == 1;
    } else {
        error("NULL pointer is not real!");
    }
}

bool cmatrix_is_row(const cmatrix_t mat) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    if (mat) {
        return mat->row == 1 && mat->col > 0;
    } else {
        error("NULL pointer is not a row Matrix!");
    }
}

bool cmatrix_is_column(const cmatrix_t mat) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    if (mat) {
        return mat->col == 1 && mat->row > 0;
    } else {
        error("NULL pointer is not a column Matrix!");
    }
}

bool cmatrix_is_square(const cmatrix_t mat) {
    #ifdef DEBUG_INLINE
    debug("Inline function!\n");
    #endif
    if (mat) {
        return mat->row == mat->col;
    } else {
        error("NULL pointer is not a square Matrix!");
    }
}

// size_t cmatrix_rank(const cmatrix_t mat) {
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

// scomplexe_t cmatrix_descriminant(const cmatrix_t mat) {
//     #ifdef DEBUG_CONTEXT
//     debug("Entering function!");
//     #endif
//     scomplexe_t det = 0;
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

cmatrix_t cmatrix_zero(size_t row, size_t col) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cmatrix_t zero = cmatrix_init(row, col);
    for (size_t i = 0; i < zero->row * zero->col; i++) {
        complexe_zero(&zero->matrix[i]);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return zero;
}

cmatrix_t cmatrix_one(size_t row, size_t col) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cmatrix_t one = cmatrix_init(row, col);
    for (size_t i = 0; i < one->row * one->col; i++) {
        complexe_one(&one->matrix[i]);
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return one;
}

cmatrix_t cmatrix_eye(size_t size) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cmatrix_t eye = cmatrix_init(size, size);
    if (size == 1) {
        complexe_one(eye->matrix);
    } else {
        for (size_t i = 0; i < eye->row; i++) {
            for (size_t j = 0; j < eye->col; j++) {
                if (i == j) {
                    complexe_one(&eye->matrix[INDEX(i, j, eye->col)]);
                } else {
                    complexe_zero(&eye->matrix[INDEX(i, j, eye->col)]);
                }
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return eye;
}

void cmatrix_transpose(cmatrix_t mat) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    if (mat) {
        size_t tmp = mat->row;
        mat->row = mat->col;
        mat->col = tmp;
        if (!(cmatrix_is_complexe(mat) || cmatrix_is_row(mat) || cmatrix_is_column(mat))) {
            for (size_t i = 0; i < mat->row; i++) {
                for (size_t j = 0; j < mat->col; j++) {
                    if (j > i) {
                        complexe_swap(&mat->matrix[INDEX(j, i, mat->col)],
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

// void cmatrix_inv(cmatrix_t mat) {
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

cmatrix_t cmatrix_add(const cmatrix_t mat1, const cmatrix_t mat2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cmatrix_t res = NULL;
    if (!mat1 || !mat2) {
        error("NULL pointer operation!");
    } else if (mat1->row != mat2->row || mat1->col != mat2->col) {
        error("Matrix dimentions must agree!");
    } else {
        res = cmatrix_init(mat1->row, mat1->col);
        if (cmatrix_is_complexe(mat1)) {
            complexe_add(&mat1->matrix[0], &mat2->matrix[0], &res->matrix[0]);
        } else {
            for (size_t i = 0; i < res->row * res->col; i++) {
                complexe_add(&mat1->matrix[i], &mat2->matrix[i], &res->matrix[i]);
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

cmatrix_t cmatrix_sub(const cmatrix_t mat1, const cmatrix_t mat2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cmatrix_t res = NULL;
    if (!mat1 || !mat2) {
        error("NULL pointer operation!");
    } else if (mat1->row != mat2->row || mat1->col != mat2->col) {
        error("Matrix dimentions must agree!");
    } else {
        res = cmatrix_init(mat1->row, mat1->col);
        if (cmatrix_is_complexe(mat1)) {
            complexe_sub(&mat1->matrix[0], &mat2->matrix[0], &res->matrix[0]);
        } else {
            for (size_t i = 0; i < res->row * res->col; i++) {
                complexe_sub(&mat1->matrix[i], &mat2->matrix[i], &res->matrix[i]);
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

cmatrix_t cmatrix_mult(const cmatrix_t mat1, const cmatrix_t mat2) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cmatrix_t res = NULL;
    if (!mat1 || !mat2) {
        error("NULL pointer operation!");
    } else if (mat1->col != mat2->row) {
        error("Matrix dimentions must agree!");
    } else {
        res = cmatrix_init(mat1->row, mat2->col);
        if (cmatrix_is_complexe(mat1)) {
            complexe_mult(&mat1->matrix[0], &mat2->matrix[0], &res->matrix[0]);
        } else {
            for (size_t i = 0; i < res->row; i++) {
                for (size_t j = 0; j < res->col; j++) {
                    scomplexe_t dot = complexe_new(0, 0);
                    for (size_t k = 0; k < mat1->col; k++) {
                        scomplexe_t tmp = complexe_new(0, 0);
                        complexe_mult(&mat1->matrix[INDEX(i, k, mat1->col)],
                                      &mat2->matrix[INDEX(k, j, mat2->col)], &tmp);
                        complexe_add(&tmp, &dot, &dot);
                    }
                    res->matrix[INDEX(i, j, res->col)] = dot;
                }
            }
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

cmatrix_t cmatrix_scale(const cmatrix_t mat, const cmatrix_t scalar) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cmatrix_t res = NULL;
    if (!mat || !scalar) {
        error("NULL pointer operation!");
    } else if (!cmatrix_is_complexe(scalar)) {
        error("'scalar' corrupted!");
    } else {
        res = cmatrix_init(mat->row, mat->col);
        for (size_t i = 0; i < res->row * res->col; i++) {
            complexe_mult(&mat->matrix[i], scalar->matrix, &res->matrix[i]);
        }
    }
    #ifdef DEBUG_CONTEXT
    debug("leaving function!\n");
    #endif
    return res;
}

cmatrix_t cmatrix_pow(const cmatrix_t mat, size_t power) {
    #ifdef DEBUG_CONTEXT
    debug("Entering function!");
    #endif
    cmatrix_t res = NULL;
    if (!mat) {
        error("NULL pointer operation!");
    } else if (!cmatrix_is_square(mat)) {
        error("Matrix dimentions must agree!");
    } else {
        res = cmatrix_eye(mat->row);
        if (cmatrix_is_complexe(mat)) {
            for (size_t i = 0; i < power; i++) {
                complexe_mult(&mat->matrix[0], &res->matrix[0], &res->matrix[0]);
            }
        } else {
            for (size_t i = 0; i < power; i++) {
                for (size_t i = 0; i < res->row; i++) {
                    for (size_t j = 0; j < res->col; j++) {
                        scomplexe_t dot = complexe_new(0, 0);
                        for (size_t k = 0; k < res->col; k++) {
                            scomplexe_t tmp = complexe_new(0, 0);
                            complexe_mult(&res->matrix[INDEX(i, k, res->col)],
                                          &mat->matrix[INDEX(k, j, mat->col)], &tmp);
                            complexe_add(&tmp, &dot, &dot);
                        }
                        res->matrix[INDEX(i, j, res->col)] = dot;
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

void cmatrix_print(const cmatrix_t mat) {
    #ifdef DEBUG_PRINT
    debug("Entering print function!");
    #endif
    if (mat) {
        if (cmatrix_is_complexe(mat)) {
            Mat_printf("\n\t");
            complexe_print(mat->matrix);
            Mat_printf("\n");
        } else {
            Mat_printf("\n");
            for (size_t i = 0; i < mat->row; i++) {
                Mat_printf("\t[ ");
                for (size_t j = 0; j < mat->col; j++) {
                    complexe_print(&mat->matrix[INDEX(i, j, mat->col)]);
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
int main(int argc, char const *argv[]) {
    init_log();
    #if defined (__x86_64__)
        debug("64-bit architecture!\n");
    #elif defined (__i386__)
        warning("32-bit architecture!\n");
    #else
        error("Incompatible architecture!");
    #endif

    cmatrix_t I2 = cmatrix_eye(4);
    Mat_printf("I2 ="); cmatrix_print(I2);

    cmatrix_t A1 = cmatrix_new(2, 3, complexe_new(1.0, 2.0),
                                     complexe_new(3.0, 4.0),
                                     complexe_new(5.0, 6.0),
                                     complexe_new(3.0, 4.0),
                                     complexe_new(1.0, 2.0),
                                     complexe_new(5.0, 6.0));
    Mat_printf("A1 ="); cmatrix_print(A1);

    cmatrix_t A2 = cmatrix_new(3, 2, complexe_new(0, 2.0),
                                     complexe_new(3.0, 0),
                                     complexe_new(5.0, 0),
                                     complexe_new(0, 4.0),
                                     complexe_new(0, 2.0),
                                     complexe_new(0, 6.0));
    Mat_printf("A2 ="); cmatrix_print(A2);

    cmatrix_t A12 = cmatrix_mult(A2, A1);
    Mat_printf("A12 ="); cmatrix_print(A12);

    cmatrix_transpose(A12);
    Mat_printf("A12' ="); cmatrix_print(A12);

    // cmatrix_t A22 = cmatrix_scale(I2, A12);
    // Mat_printf("A22 ="); cmatrix_print(A22);
    //
    // cmatrix_t A23 = cmatrix_pow(A22, 3);
    // Mat_printf("A23 ="); cmatrix_print(A23);

    cmatrix_delete(I2);
    cmatrix_delete(A1);
    cmatrix_delete(A2);
    cmatrix_delete(A12);
    // cmatrix_delete(A22);
    // cmatrix_delete(A23);
    debug("FY!");
    return 0;
}
#endif
