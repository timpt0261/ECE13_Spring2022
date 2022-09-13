/* ************************************************************************** */
/** MatrixMath.c
 * 
 * Reuben Chavez
 * April 11, 2022
 * ECE 13E (Spring 2022)
 * 
 */
/* ************************************************************************** */

//User Libraries
#include "MatrixMath.h"
#include <stdio.h>
#include <math.h>

void MatrixPrint(float mat[3][3]) {
    printf("----------------------\n");
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            printf("|%.4f", mat[i][j]);

            if (j == 2) {
                printf("|\n");
            }
        }
    }
    printf("----------------------\n");
    return;
}

int MatrixEquals(float mat1[3][3], float mat2[3][3]) {

    for (int row = 0; row < DIM; row++) {
        for (int col = 0; col < DIM; col++) {
            // if difference between two nums in matrix is greater 0.0001
            if (fabsf(mat1[row][col] - mat2[row][col]) > FP_DELTA) {
                return 0; // matrix not equal
            }
        }
    }

    return 1; // matrixes are equal
}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]) {

    for (int row = 0; row < DIM; row++) {
        for (int col = 0; col < DIM; col++) {
            result[row][col] = mat1[row][col] + mat2[row][col];

        }
    }

    return;
}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]) {

    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            result[r][c] = 0;
            for (int iter = 0; iter < DIM; iter++) {
                result[r][c] += mat1[r][iter] * mat2[iter][c];
            }

        }
    }
    return;

}

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]) {

    for (int row = 0; row < DIM; row++) {
        for (int col = 0; col < DIM; col++) {
            result[row][col] = 0;
            if (mat[row][col] > 0) {
                result[row][col] = mat[row][col] + x;
            }


        }
    }
    return;
}

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]) {
    for (int row = 0; row < DIM; row++) {
        for (int col = 0; col < DIM; col++) {
            if (mat[row][col] > 0) {
                result[row][col] = mat[row][col] * x;
            }
        }
    }

    return;
}

float MatrixTrace(float mat[3][3]) {
    float result = 0;

    for (int i = 0; i < DIM; i++) {
        result += mat[i][i];
    }

    return result;
}

void MatrixTranspose(float mat[3][3], float result[3][3]) {

    // Iterate through matrix and place result in transpose location
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            result[i][j] = mat[j][i];

        }
    }
    return;
}

void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]) {
    // results row and columns, avoid out of range error/ override error
    int start_row = 0, start_col = 0;

    // checks that the i-th and j-th are in range
    if (0 <= i && i < DIM && 0 <= j && j < DIM) {
        //iterate through rows in mat
        for (int row = 0; row < DIM; row++) {
            //iterate through columns in mat
            if (row != i) {
                for (int col = 0; col < DIM; col++) {
                    // check it's not specified row to column
                    if (col != j) {
                        // store in available space in result
                        result[start_row][start_col] = mat[row][col];
                        start_col++;
                    }
                }
                // Avoid 
                start_col = 0; // set col to zero
                start_row++; // increment to next available row in result

            }

        }

    } else {
        printf("The i-th or j-th row you have entered are out of range.\n");
    }

    return;
}

/*
 * Function: Determines determinant for a 2x2 matrix
 * @para: mat[2][2] take a float matrix of 2x2 only
 * @return: A float of the determinant equation for 2x2
 * 
 * Based on Document in Lab2
 */
static float MatrixDeterminant2x2(float mat[2][2]) {
    // det[M] = a * d - b * C
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

float MatrixDeterminant(float mat[3][3]) {
    // initialize three 2x2 matrices
    float a[2][2] = {
        {},
        {}
    };
    float b[2][2] = {
        {},
        {}
    };
    float c[2][2] = {
        {},
        {}
    };

    //Find The SubMatrix for the first row
    MatrixSubmatrix(0, 0, mat, a);
    MatrixSubmatrix(0, 1, mat, b);
    MatrixSubmatrix(0, 2, mat, c);

    // Store the 2x2 matrix Determinant in  in a float var
    float mda = MatrixDeterminant2x2(a);
    float mdb = MatrixDeterminant2x2(b);
    float mdc = MatrixDeterminant2x2(c);

    // a * det(submatrix(a)) - b*det(submatrix(b)) + c * det(submatrix(c))
    return mat[0][0] * mda - mat[0][1] * mdb + mat[0][2] * mdc;
}

void MatrixInverse(float mat[3][3], float result[3][3]) {

    // Store Matrix Determinant
    float mat_det = MatrixDeterminant(mat);

    //check that Determinant is Not Zero -> No Inverse if so
    if (mat_det != 0) {
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {

                float co_factor = 0; // stores cofactor

                //matrix for co_factor
                float co_matrix[2][2] = {
                    {},
                    {}
                };

                // determines sign if odd or even
                if (((i + j) % 2) == 0) {
                    //find co-factor at mat[i][j]
                    MatrixSubmatrix(i, j, mat, co_matrix);
                    co_factor = MatrixDeterminant2x2(co_matrix);

                    //place at transpose location                  
                    result[j][i] = (1.0 / mat_det) * co_factor;
                } else {
                    //find co-factor at mat[i][j]
                    MatrixSubmatrix(i, j, mat, co_matrix);
                    co_factor = MatrixDeterminant2x2(co_matrix);

                    //place at transpose location                  
                    result[j][i] = (-1.0 / mat_det) * co_factor;
                }
            }
        }
    }

    return;
}