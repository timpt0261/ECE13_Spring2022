// mml_test.c
//Reuben Chavez
// April 14, 2022
//ECE 13E Spring 2022

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"
#include <math.h>

// Self-Made Functions
void ZeroArray(float mat[3][3]);
void MatrixConverter(float mat1[2][2], float result[3][3]);

// Module-level variables:
float zero_matrix[3][3] = {
    {},
    {},
    {}
};

// Following Matices ares used to test functionality
// for MatrixMath.c

float testA[3][3] = {
    {4.0, 5.0, 6.0},
    {1.0, 2.0, 3.0},
    {7.0, 8.0, 9.0}
};

float testB[3][3] = {
    {0.6, 5.0, 1.4},
    {2.6, 3.0, 4.9},
    {9.7, 5.9, 6.7}
};

float testC[3][3] = {
    {1.0, 2.3, 5.6},
    {8.9, 2.4, 8.2},
    {4.5, 6.36, 3.68}
};

float testD[3][3] = {
    {4.0, 5.0, 6.0},
    {1.0, 2.0, 3.0},
    {7.0, 8.0, 9.0}
};

// Following Matrices store the results
float result_1[3][3] = {
    {},
    {},
    {}
};
float result_2[3][3] = {
    {},
    {},
    {}
};
float result_3[3][3] = {
    {},
    {},
    {}
};

int main() {
    BOARD_Init();

    printf("\nBeginning rtchavez's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);

    printf("\nDemonstrating MatrixPrint():\n");
    MatrixPrint(zero_matrix);

    // Add more tests here!

    float points = 0;
    int sol = 0;

    //test 1 Equality Test

    // Use MatrixEqual() to compare if Matrixes are equal, otherwise test fails
    if (MatrixEquals(testA, testD) && !MatrixEquals(testA, testB)) {
        printf("PASSED (2/2): MatrixEquals()\n");
        points += 2.0;
        sol++;
    } else {
        printf("FAILED : MatrixEquals()\n");
    }

    //test 2 Addition

    // Results for MatixAdded saved here
    float add_result[3][3] = {
        {5, 7.3, 11.6},
        {9.9, 4.4, 11.2},
        {11.5, 14.36, 12.68}
    };

    // Run MatrixAdd()
    MatrixAdd(testA, testC, result_1);
    MatrixAdd(testC, testA, result_2);

    // Use MatrixEqual() to compare results are equal, otherwise test fails
    if (MatrixEquals(result_1, add_result) && MatrixEquals(result_2, add_result)) {
        printf("PASSED (2/2): MatrixAdd()\n");
        points += 1.0;
        sol++;
    } else {
        printf("FAILED : MatrixAdd()\n");
    }

    // Zero Out arrays 
    ZeroArray(result_1);
    ZeroArray(result_2);

    //Rinse and repeat process for other test, fairly different for
    //MatrixSubMatrix(), MatrixTrace() and MatrixDeterminant() tested similarly

    //test 3 Scalar Addition

    float sa_result_1[3][3] = {
        {6, 7, 8},
        {3, 4, 5},
        {9, 10, 11}
    };
    float sa_result_2[3][3] = {
        {3, 4.3, 7.6},
        {10.9, 4.4, 10.2},
        {6.5, 8.36, 5.68}
    };
    float sa_result_3[3][3] = {
        {2.6, 7, 3.4},
        {4.6, 5, 6.9},
        {11.7, 7.9, 8.7}
    };

    MatrixScalarAdd(2.0, testA, result_1);
    MatrixScalarAdd(2.0, testC, result_2);
    MatrixScalarAdd(2.0, testB, result_3);

    if (MatrixEquals(result_1, sa_result_1)
            && MatrixEquals(result_2, sa_result_2)
            && MatrixEquals(result_3, sa_result_3)) {
        printf("PASSED (3/3): MatrixScalarAdd()\n");
        points += 0.5;
        sol++;

    } else {
        printf("FAILED : MatrixScalarAdd()\n");
    }


    ZeroArray(result_1);
    ZeroArray(result_2);
    ZeroArray(result_3);

    //test 4 Scalar Multiplication

    float ms_result_1[3][3] = {
        {8.0, 10.0, 12.0},
        {2.0, 4.0, 6.0},
        {14.0, 16.0, 18.0}
    };
    float ms_result_2[3][3] = {
        {2, 4.6, 11.2},
        {17.8, 4.8, 16.4},
        {9, 12.72, 7.36}
    };
    float ms_result_3[3][3] = {
        {1.2, 10, 2.8},
        {5.2, 6, 9.8},
        {19.4, 11.8, 13.4}
    };

    MatrixScalarMultiply(2.0, testA, result_1);
    MatrixScalarMultiply(2.0, testC, result_2);
    MatrixScalarMultiply(2.0, testB, result_3);

    if (MatrixEquals(result_1, ms_result_1)
            && MatrixEquals(result_2, ms_result_2)
            && MatrixEquals(result_3, ms_result_3)) {
        printf("PASSED (3/3): MatrixScalarMultiply\n");
        points += 0.5;
        sol++;

    } else {
        printf("FAILED: MatrixScalarMultiply\n");
    }

    ZeroArray(result_1);
    ZeroArray(result_2);
    ZeroArray(result_3);

    //test 5 Multiplication

    MatrixMultiply(testA, testC, result_1);
    MatrixMultiply(testC, testA, result_2);

    float mul_result_1[3][3] = {
        {75.5, 59.36, 85.48},
        {32.3, 26.18, 33.04},
        {118.7, 92.54, 137.92}
    };
    float mul_result_2[3][3] = {
        {45.5, 54.4, 63.3},
        {95.4, 114.9, 134.4},
        {50.12, 64.66, 79.2}
    };

    if (MatrixEquals(result_1, mul_result_1)
            && MatrixEquals(result_2, mul_result_2)
            && !MatrixEquals(mul_result_1, mul_result_2)) {
        printf("PASSED (3/3): MatrixMultiply()\n");
        points += 1.0;
        sol++;
    } else {
        printf("FAILED: MatrixMultiply()\n");
    }

    ZeroArray(result_1);
    ZeroArray(result_2);

    //test 6 Trace

    // Store Trace Results
    float trace_result_1 = 15;
    float trace_result_2 = 7.08;
    float trace_result_3 = 10.3;

    // Calculate if difference between results and MatrixTrace() is precisely equal, 
    // otherwise test fails 

    if (fabsf(MatrixTrace(testA) - trace_result_1) < FP_DELTA
            && fabsf(MatrixTrace(testC) - trace_result_2) < FP_DELTA
            && fabsf(MatrixTrace(testB) - trace_result_3) < FP_DELTA) {
        printf("PASSED (3/3): MatrixTrace()\n");
        points += 1.0;
        sol++;
    } else {
        printf(" FAILED MatrixTrace\n");
    }

    // Zero Out Arrays
    ZeroArray(result_1);
    ZeroArray(result_2);
    ZeroArray(result_3);

    //test 7 Transpose

    float transpose_result_1[3][3] = {
        {4, 1, 7},
        {5, 2, 8},
        {6, 3, 9}
    };
    float transpose_result_2[3][3] = {
        {1, 8.9, 4.5},
        {2.3, 2.4, 6.36},
        {5.6, 8.2, 3.68}
    };
    float transpose_result_3[3][3] = {
        {0.6, 2.6, 9.7},
        {5, 3, 5.9},
        {1.4, 4.9, 6.7}
    };

    MatrixTranspose(testA, result_1);
    MatrixTranspose(testC, result_2);
    MatrixTranspose(testB, result_3);

    if (MatrixEquals(result_1, transpose_result_1)
            && MatrixEquals(result_2, transpose_result_2)
            && MatrixEquals(result_3, transpose_result_3)) {
        printf("PASSED (3/3): MatrixTranspose()\n");
        points += 1.0;
        sol++;

    } else {
        printf("FAILED : MatrixTranspose()\n");
    }

    ZeroArray(result_1);
    ZeroArray(result_2);
    ZeroArray(result_3);

    //test 8 SubMatrix

    //initialize 2x2 matrices to store results
    float sub_mat_result_1[2][2] = {
        {},
        {}
    };
    float sub_mat_result_2[2][2] = {
        {},
        {}
    };
    float sub_mat_result_3[2][2] = {
        {},
        {}
    };

    // expected results for matrix A
    float sub_mat_expected_1[3][3] = {
        {2, 3},
        {8, 9}
    };
    float sub_mat_expected_2[3][3] = {
        {4, 6},
        {7, 9}
    };
    float sub_mat_expected_3[3][3] = {
        {4, 5},
        {1, 2}
    };

    // Find SubMatrix at Specified points
    MatrixSubmatrix(0, 0, testA, sub_mat_result_1);
    MatrixSubmatrix(1, 1, testA, sub_mat_result_2);
    MatrixSubmatrix(2, 2, testA, sub_mat_result_3);

    // converts 2x2 to 3x3
    MatrixConverter(sub_mat_result_1, result_1);
    MatrixConverter(sub_mat_result_2, result_2);
    MatrixConverter(sub_mat_result_3, result_3);

    // compare expected results with results from MatrixSubMatrix()
    if (MatrixEquals(result_1, sub_mat_expected_1)
            && MatrixEquals(result_2, sub_mat_expected_2)
            && MatrixEquals(result_3, sub_mat_expected_3)) {
        printf("PASSED (3/3): SubMatraix()\n");
        points += 1.0;
        sol++;
    } else {
        printf("FAILED : SubMatraix()\n");
    }

    // Zero Out result Arrays
    ZeroArray(result_1);
    ZeroArray(result_2);
    ZeroArray(result_3);

    //test 9 Determinant

    float deter_expected_1 = 0, deter_expected_2 = 222.7228, deter_expected_3 = 126;

    if (fabsf(MatrixDeterminant(testA) - deter_expected_1) < FP_DELTA
            && fabsf(MatrixDeterminant(testC) - deter_expected_2) < FP_DELTA
            && fabsf(MatrixDeterminant(testB) - deter_expected_3)) {
        printf("PASSED (3/3) : MatrixDeterminant()\n");

        points += 0.5;
        sol++;

    } else {

        printf("FAILED: MatrixDeterminant()\n");
    }

    //test 10 Inverse

    float inverse_expected_1[3][3] = {
        {-108300.0 / 556807.0, 67880.0 / 556807.0, 13550.0 / 556807.0},
        {10370.0 / 556807.0, -53800.0 / 556807.0, 104100.0 / 556807.0},
        {114510.0 / 556807.0, 9975.0 / 556807.0, -45175.0 / 556807.0}
    };

    float inverse_expected_2[3][3] = {
        {-881.0 / 12600.0, -631.0 / 3150.0, 29.0 / 180},
        {3011.0 / 12600.0, -239.0 / 3150.0, 1.0 / 180.0},
        {-172.0 / 1575.0, 562.0 / 1575.0, -4.0 / 45.0}
    };

    MatrixInverse(testC, result_1);
    MatrixInverse(testB, result_2);

    if (MatrixEquals(result_1, inverse_expected_1) && MatrixEquals(result_2, inverse_expected_2)) {
        printf("PASSED (3/3): MatrixInverse()\n");
        points += 0.5;
        sol++;
    } else {
        printf("Failed : MatrixInverse()\n");
    }

    ZeroArray(result_1);
    ZeroArray(result_2);

    printf("________________________\n");
    printf("%d of 10 Solutions Passed,(%.2f)\n", sol, (points / 9.0)*100.0);

    //Prints test A
    printf("Printing Matrix A\n");
    MatrixPrint(testA);

    //Prints test B
    printf("Printing Matrix B\n");
    MatrixPrint(testB);

    //Prints test C
    printf("Printing Matrix C\n");
    MatrixPrint(testC);

    BOARD_End();
    while (1);
}

/*
 * Function : Clears 3x3 Matrix
 * @param: mat, pointer to a summand of a 3x3 matrix
 * @return: none 
 * 
 * Main Use so decrease error in tests
 */
void ZeroArray(float mat[3][3]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            mat[i][j] = 0;
        }
    }
    return;
}

void MatrixConverter(float mat1[2][2], float result[3][3]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = mat1[i][j];
        }
    }

    return;
}