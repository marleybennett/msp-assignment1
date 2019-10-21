#include <stdlib.h>
#include <stdio.h> //Remove before submitting!


int strmv(
    const long n,
    const long p,
    const char trans,
    double **U,    /* two-dimensional array, row-major */
    double **W,    /* two-dimensional array, row-major */
    double *b,     /* one-dimensional array */
    double *ws     /* workspace (length p array) */
    ){

    if(U == NULL || W == NULL || b == NULL || ws == NULL) {
        return EXIT_FAILURE;
    }
    
    *ws = 0.0;

    if(trans == 'N') {
        for(int i = 0; i < n; i++){
            double vproduct1 = 0.0;
            double vproduct2 = 0.0;
            for(int j = 0; j < p; j++){
                vproduct1 += U[i][j] * ws[j];
                vproduct2 += U[i][j] * W[i][j];
                printf("vproduct1 = %f\n", vproduct1);
                printf("vproduct2 = %f\n", vproduct2);
            }
            b[i] = (b[i] - vproduct1)/vproduct2;
            for(int j = 0; j < p; j++) {
                ws[j] += W[i][j] * b[i];
            }
        }
    } else if(trans == 'T') {
        for(int i = 0; i < n; i++){
            double vproduct1 = 0.0;
            double vproduct2 = 0.0;
            for(int j = 0; j < p; j++){
                vproduct1 += W[i][j] * ws[j];
                vproduct2 += U[i][j] * W[i][j];
            }
            b[i] = (b[i] - vproduct1)/vproduct2;
            for(int j = 0; j < p; j++) {
                ws[j] += U[i][j] * b[i];
            }
        }
    } else {
        printf("Invalid value for variable trans.\n");
        return 0;
    }

    printf("result of equation: \n");

    for(int i = 0; i < n; i++) {
        printf("%f\n", b[i]);
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
    const long p = 2;
    const char trans = 'N';
    double **U = malloc_array2d(n, p);    /* two-dimensional array, row-major */
    double **W = malloc_array2d(n,p);    /* two-dimensional array, row-major */
    double *b = malloc_array1d(n);     /* one-dimensional array */
    double *ws = malloc_array1d(p);    /* workspace (length p array) */

    if(U == 0 || W == 0 || b == 0 || ws == 0)
        return EXIT_FAILURE;


    U[0][0] = 1;
    U[0][1] = 2;
    U[1][0] = 3;
    U[1][1] = 4;

    W[0][0] = 5;
    W[0][1] = 6;
    W[1][0] = 7;
    W[1][1] = 8;
  
    b[0] = 17;
    b[1] = 145;
  
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


    printf("b: \n");

    for(int i = 0; i < n; i++)
        printf("%f \n", b[i]);

    printf("\n \n");


    strmv(n, p, trans, U, W, b, ws);

    free(U[0]);
    free(U);
    free(W[0]);
    free(W);
    free(b);
    free(ws);
}