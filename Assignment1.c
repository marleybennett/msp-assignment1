#include <stdlib.h>


int strmv(
    const long n,
    const long p,
    const double alpha,
    double **U,    /* two-dimensional array, row-major */
    double **W,    /* two-dimensional array, row-major */
    double *x,     /* one-dimensional array */
    double *ws     /* workspace (length p array) */
    ){

    if(U == NULL || W == NULL || x == NULL || ws == NULL)
        return EXIT_FAILURE;
    

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
}


int main(){
    const long n = 2;
    const long p = 2;
    const double alpha = 1;
    double **U = malloc_array2d(n, p);    /* two-dimensional array, row-major */
    double **W = malloc_array2d(n,p);    /* two-dimensional array, row-major */
    double *x = malloc_array1d(n);     /* one-dimensional array */
    double *ws = malloc_array1d(p);    /* workspace (length p array) */

    if(U == 0 || W == 0 || x == 0 || ws == 0)
        return EXIT_FAILURE;
    
    strmv(n, p, alpha, U, W, x, ws);

    free(U[0]);
    free(U);
    free(W[0]);
    free(W);
    free(x);
    free(ws);

    

}