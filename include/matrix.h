#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct {
    size_t rows;
    size_t cols;
    double **data;
} Matrix;

Matrix *matrix_create(size_t rows, size_t cols);
void matrix_free(Matrix *matrix);
Matrix *matrix_load_from_file(const char *filename);
void matrix_print(const Matrix *matrix);
Matrix *matrix_copy(const Matrix *src);
Matrix *matrix_add(const Matrix *a, const Matrix *b);
Matrix *matrix_subtract(const Matrix *a, const Matrix *b);
Matrix *matrix_multiply(const Matrix *a, const Matrix *b);
Matrix *matrix_transpose(const Matrix *matrix);
double matrix_determinant(Matrix *matrix);

#endif
