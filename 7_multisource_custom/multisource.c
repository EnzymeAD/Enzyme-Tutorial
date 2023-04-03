#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "myblas.h"

void __enzyme_double(void*, size_t);

double dotabs(struct complex* alpha, struct complex* beta, int n) {
  struct complex prod = myblas_cdot(alpha, beta, n);
  __enzyme_double(&prod, sizeof(struct complex));
  return myblas_cabs(prod);
}

void __enzyme_autodiff(void*, ...);

int main(int argc, char *argv[]) {
  int n = 3;
  if (argc > 1) {
    n = atoi(argv[1]);
  }


  struct complex *A = (struct complex*)malloc(sizeof(struct complex) * n);
  assert(A != 0);
  for(int i=0; i<n; i++)
   A[i] = (struct complex){(i+1), (i+2)};

  struct complex *grad_A = (struct complex*)malloc(sizeof(struct complex) * n);
  assert(grad_A != 0);
  for(int i=0; i<n; i++)
   grad_A[i] = (struct complex){0,0};



  struct complex *B = (struct complex*)malloc(sizeof(struct complex) * n);
  assert(B != 0);
  for(int i=0; i<n; i++)
   B[i] = (struct complex){-3-i, 2*i};

  struct complex *grad_B = (struct complex*)malloc(sizeof(struct complex) * n);
  assert(grad_B != 0);
  for(int i=0; i<n; i++)
   grad_B[i] = (struct complex){0,0};

  __enzyme_autodiff((void*)dotabs, A, grad_A, B, grad_B, n);
  printf("Gradient dotabs(A)[0] = %f\n", grad_A[0].r);

  return 0;
}
