#include <stdlib.h>
#include <stdio.h> //Remove before submitting!


int strmv(
    const long n,
    const long p,
    const char alpha,
    double **U,    /* two-dimensional array, row-major */
    double **W,    /* two-dimensional array, row-major */
    double *x,     /* one-dimensional array */
    double *ws     /* workspace (length p array) */
    ){

    if(U == NULL || W == NULL || x == NULL || ws == NULL) {
        return EXIT_FAILURE;
    }
    
    *ws = 0.0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < p; j++){
            printf("i is %d\n", i);
            printf("j is %d\n", j);
            printf("ws[j] is %f\n", ws[j]);
            printf("W[i][j] is %f\n", W[i][j]);
            printf("x[i] is %f\n", x[i]);
            ws[j] += W[i][j] * x[i];
            printf("ws[j] is %f\n", ws[j]);
        }
        x[i] = 0.0;
        for(int j = 0; j < p; j++) {
            printf("x[i] is %f\n", x[i]);
            x[i] += U[i][j] * ws[j] * alpha;
            printf("x[i] is %f\n", x[i]);
        }
    }

    printf("result of matrix-vector-scalar multiplication: \n");

    for(int i = 0; i < n; i++) {
        printf("%f\n", x[i]);
    } 

    return 0;
}

double **malloc_array2d(size_t m, size_t n) {

    if (m == 0 || n == 0)
        return NULL;

    double **B = malloc(m * sizeof(*B));
        if (B == NULL)
        return NULL;

    B[0] = malloc(m * n * sizeof(double));
    if (B[0] == NULL) {
        free(B);
        return NULL;
    }

    for (size_t i = 1; i < m; i++) //setting pointers
        B[i] = B[0] + i * n;

    return B;
}

double *malloc_array1d(size_t n){
    if(n==0)
        return NULL;
   
    double *A = malloc(n * sizeof(double));

    if(A == NULL)
        return NULL; 
    
    return A;
}


int main(){
    const long n = 2;
    const long p = 3;
    const double alpha = 2;
    double **U = malloc_array2d(n, p);    /* two-dimensional array, row-major */
    double **W = malloc_array2d(n,p);    /* two-dimensional array, row-major */
    double *x = malloc_array1d(n);     /* one-dimensional array */
    double *ws = malloc_array1d(p);    /* workspace (length p array) */

    if(U == 0 || W == 0 || x == 0 || ws == 0)
        return EXIT_FAILURE;


    U[0][0] = 1;
    U[0][1] = 2;
    U[0][2] = 2;
    U[1][0] = 3;
    U[1][1] = 4;
    U[1][2] = 4;

    W[0][0] = 5;
    W[0][1] = 6;
    W[0][2] = 6;
    W[1][0] = 7;
    W[1][1] = 8;
    W[1][2] = 8;
  
    x[0] = 1;
    x[1] = 2;
  
    printf("U: \n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < p; j++)
            printf("%f    ", U[i][j]);
        printf("\n");
    }
    
    printf("W: \n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < p; j++) {
            printf("%f    ", W[i][j]);
        }
        printf("\n");
    }


    printf("x: \n");

    for(int i = 0; i < n; i++)
        printf("%f \n", x[i]);

    printf("\n \n");


    strmv(n, p, alpha, U, W, x, ws);

    free(U[0]);
    free(U);
    free(W[0]);
    free(W);
    free(x);
    free(ws);
}