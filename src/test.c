#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include "matrix.h"
#include "image.h"
#include "test.h"
#include "args.h"

double what_time_is_it_now()
{
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

// This function returns 1 if A[][] and B[][] are identical 
// otherwise returns 0 
int areSame(matrix A, matrix B) 
{ 
    int i, j; 
    for (i = 0; i < A.rows; i++) 
        for (j = 0; j < A.cols; j++) 
            if (A.data[i*A.cols + j] != B.data[i*B.cols + j]) 
                return 0; 
    return 1; 
}

void test_matrix_speed()
{
    int i;
    int n = 128;
    matrix a = random_matrix(512, 512, 1);
    matrix b = random_matrix(512, 512, 1);
    double start = what_time_is_it_now();
    for(i = 0; i < n; ++i){
        matrix d = matmul(a,b);
        free_matrix(d);
    }
    printf("Matmul elapsed %lf sec\n", what_time_is_it_now() - start);
    start = what_time_is_it_now();
    for(i = 0; i < n; ++i){
        matrix at = transpose_matrix(a);
        free_matrix(at);
    }
    printf("Transpose elapsed %lf sec\n", what_time_is_it_now() - start);
}

void test_matrix_copy()
{
    matrix a = random_matrix(512, 512, 1);
    matrix b = copy_matrix(a);
    
    // Test for same shape
    if ((a.rows == b.rows) && (a.cols == b.cols))
        printf("Matrices have same shape\n");
    else
        printf("Matrices do NOT have same shape\n");

    // Test for same data
    if (areSame(a, b)) 
        printf("Matrices are identical\n");
    else
        printf("Matrices are not identical\n"); 
}

void test_matrix_transpose()
{
    matrix a = random_matrix(3, 3, 1);
    matrix b = transpose_matrix(a);
    
    // Test for shape
    printf("a.shape = (%d, %d)\n", a.rows, a.cols);
    printf("b.shape = (%d, %d)\n", b.rows, b.cols);
    if ((a.rows == b.cols) && (a.cols == b.rows))
        printf("Transpose shape correct\n");
    else
        printf("Transpose shape incorrect\n");

    // Test for same data
    matrix bt = transpose_matrix(b);
    if (areSame(a, bt))
        printf("Matrices are identical\n");
    else
        printf("Matrices are not identical\n");

    // Show matrices
    print_matrix(a);
    print_matrix(b);
    print_matrix(bt);
}

void run_tests()
{
    test_matrix_speed();
    test_matrix_copy();
    test_matrix_transpose();
    //printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);
}

