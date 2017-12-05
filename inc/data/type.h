#ifndef TYPE_H
#define TYPE_H

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

#define SIZE_REAL sizeof(double)
#define SIZE_COMPLEXE 2 * SIZE_REAL

#define SIZE_RVector(Len) Len * SIZE_REAL
#define SIZE_CVector(Len) Len * SIZE_COMPLEXE

#define SIZE_RMatrix(Row, Col) Row * Col * SIZE_REAL
#define SIZE_CMatrix(Row, Col) Row * Col * SIZE_COMPLEXE

#define SIZE_RTensor(Row, Col, Hgh) Row * Col * Hgh * SIZE_REAL
#define SIZE_CTensor(Row, Col, Hgh) Row * Col * Hgh * SIZE_COMPLEXE

#define PRINT_REAL "%7.2lf"

typedef double* real_t;

#elif __i386__

#define SIZE_REAL sizeof(float)
#define SIZE_COMPLEXE 2 * SIZE_REAL

#define SIZE_RVector(Len) Len * SIZE_REAL
#define SIZE_CVector(Len) Len * SIZE_COMPLEXE

#define SIZE_RMatrix(Row, Col) Row * Col * SIZE_REAL
#define SIZE_CMatrix(Row, Col) Row * Col * SIZE_COMPLEXE

#define SIZE_RTensor(Row, Col, Hgh) Row * Col * Hgh * SIZE_REAL
#define SIZE_CTensor(Row, Col, Hgh) Row * Col * Hgh * SIZE_COMPLEXE

#define PRINT_REAL "%5.2f"

typedef float* real_t;

#endif

typedef enum {
  Real, Complexe,
  RVector, CVector,
  RMatrix, CMatrix,
  RTensor, CTensor,
  Mat_Types
} dataType_t;

bool type_isReal(const void* data, const size_t size);

bool type_isComplexe(const void* data, const size_t size);

bool type_isRealVector(const void* data, const size_t size);

bool type_isComplexeVector(const void* data, const size_t size);

bool type_isRealMatrix(const void* data, const size_t size);

bool type_isComplexeMatrix(const void* data, const size_t size);

bool type_isRealTensor(const void* data, const size_t size);

bool type_isComplexeTensor(const void* data, const size_t size);

dataType_t type_data(const void* data, const size_t size);

#endif /* end of include guard: TYPE_H */
