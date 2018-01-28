#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>     // bool defs

#define Mat_PI  3.14159265358979323846264338327f
#define Mat_exp 2.7182818285

#define Mat_max(x,y) (x >= y ? x : y)
#define Mat_min(x,y) (x <= y ? x : y)
#define Mat_clamp(a,mn,mx) (a < mn ? mn : (a > mx ? mx : a))
#define Mat_signe(x) (x < 0)
#define Mat_abs(x) Mat_max(x,-x)

/*
     MAT TYPES ----- SIZE(x86_64) ------- SIZE(i386)
      Real                8o                  4o
      Complexe           16o                  8o
      RVector           n * 8o              n * 4o
      CVector          n * 16o              n * 8o
      RMatrix         n * m * 8o          n * m * 4o
      CMatrix        n * m * 16o          n * m * 8o
      RTensor       n * m * l * 8o      n * m * l * 4o
      CTensor      n * m * l * 16o      n * m * l * 8o
*/

#ifdef __x86_64__

#define PRINT_REAL "%7.4lf"

typedef double sreal_t;

#define EPSILON 1e-8

#elif __i386__

#define PRINT_REAL "%5.2f"

typedef float sreal_t;

#define EPSILON 1e-6

#endif

#define SIZE_REAL sizeof(sreal_t)
#define SIZE_COMPLEXE (2 * SIZE_REAL)

#define SIZE_RVector(Len) (Len * SIZE_REAL)
#define SIZE_CVector(Len) (Len * SIZE_COMPLEXE)

#define SIZE_RMatrix(Row, Col) (Row * Col * SIZE_REAL)
#define SIZE_CMatrix(Row, Col) (Row * Col * SIZE_COMPLEXE)

#define SIZE_RTensor(Row, Col, Hgh) (Row * Col * Hgh * SIZE_REAL)
#define SIZE_CTensor(Row, Col, Hgh) (Row * Col * Hgh * SIZE_COMPLEXE)

typedef enum {
    Real, Complexe,
    RVector, CVector,
    RMatrix, CMatrix,
    RTensor, CTensor,
    Other_Types
} dataType_t;

#endif /* end of include guard: TYPES_H */
