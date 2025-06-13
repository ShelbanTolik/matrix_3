#include "../include/matrix.h"
#include <stdio.h>

int main() {
    Matrix *A = matrix_load_from_file("matrices/A.txt");
    Matrix *B = matrix_load_from_file("matrices/B.txt");
    Matrix *C = matrix_load_from_file("matrices/C.txt");
    Matrix *D = matrix_load_from_file("matrices/D.txt");

    Matrix *BC = matrix_subtract(B, C);
    Matrix *DT = matrix_transpose(D);
    Matrix *MUL = matrix_multiply(BC, DT);
    Matrix *RES = matrix_add(A, MUL);

    printf("Result of A + (B - C) × D^T:\n");
    matrix_print(RES);

    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(D);
    matrix_free(BC);
    matrix_free(DT);
    matrix_free(MUL);
    matrix_free(RES);
    return 0;
}
