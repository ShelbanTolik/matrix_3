#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

Matrix *matrix_create(size_t rows, size_t cols) {
    Matrix *m = malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = malloc(rows * sizeof(double *));
    for (size_t i = 0; i < rows; i++)
        m->data[i] = calloc(cols, sizeof(double));
    return m;
}

void matrix_free(Matrix *matrix) {
    if (matrix) {
        for (size_t i = 0; i < matrix->rows; i++)
            free(matrix->data[i]);
        free(matrix->data);
        free(matrix);
    }
}

Matrix *matrix_load_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    size_t rows, cols;
    fscanf(file, "%zu %zu", &rows, &cols);
    Matrix *m = matrix_create(rows, cols);
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            fscanf(file, "%lf", &m->data[i][j]);
    fclose(file);
    return m;
}

void matrix_print(const Matrix *m) {
    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++)
            printf("%8.2f ", m->data[i][j]);
        printf("\n");
    }
}

Matrix *matrix_copy(const Matrix *src) {
    Matrix *copy = matrix_create(src->rows, src->cols);
    for (size_t i = 0; i < src->rows; i++)
        for (size_t j = 0; j < src->cols; j++)
            copy->data[i][j] = src->data[i][j];
    return copy;
}

Matrix *matrix_add(const Matrix *a, const Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    Matrix *res = matrix_create(a->rows, a->cols);
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            res->data[i][j] = a->data[i][j] + b->data[i][j];
    return res;
}

Matrix *matrix_subtract(const Matrix *a, const Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    Matrix *res = matrix_create(a->rows, a->cols);
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < a->cols; j++)
            res->data[i][j] = a->data[i][j] - b->data[i][j];
    return res;
}

Matrix *matrix_multiply(const Matrix *a, const Matrix *b) {
    if (a->cols != b->rows) return NULL;
    Matrix *res = matrix_create(a->rows, b->cols);
    for (size_t i = 0; i < a->rows; i++)
        for (size_t j = 0; j < b->cols; j++)
            for (size_t k = 0; k < a->cols; k++)
                res->data[i][j] += a->data[i][k] * b->data[k][j];
    return res;
}

Matrix *matrix_transpose(const Matrix *m) {
    Matrix *t = matrix_create(m->cols, m->rows);
    for (size_t i = 0; i < m->rows; i++)
        for (size_t j = 0; j < m->cols; j++)
            t->data[j][i] = m->data[i][j];
    return t;
}

double matrix_determinant(Matrix *m) {
    if (m->rows != m->cols) return NAN;
    if (m->rows == 1) return m->data[0][0];
    if (m->rows == 2)
        return m->data[0][0]*m->data[1][1] - m->data[0][1]*m->data[1][0];

    double det = 0.0;
    for (size_t k = 0; k < m->cols; k++) {
        Matrix *sub = matrix_create(m->rows - 1, m->cols - 1);
        for (size_t i = 1; i < m->rows; i++) {
            size_t col = 0;
            for (size_t j = 0; j < m->cols; j++) {
                if (j == k) continue;
                sub->data[i - 1][col++] = m->data[i][j];
            }
        }
        double sign = (k % 2 == 0) ? 1 : -1;
        det += sign * m->data[0][k] * matrix_determinant(sub);
        matrix_free(sub);
    }
    return det;
}
