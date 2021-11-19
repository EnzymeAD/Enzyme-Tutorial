#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>

float tdiff(struct timeval *start, struct timeval *end) {
  return (end->tv_sec-start->tv_sec) + 1e-6*(end->tv_usec-start->tv_usec);
}

double dot(double* __restrict__ A, double* __restrict__ B, double C, int n) {
  double sum = 0;
  for (int i=0; i<n; i++) {
    sum += A[i] * B[i];
  }
  return C + sum;
}

double __enzyme_autodiff(void*, ...);
int enzyme_const, enzyme_dup, enzyme_out;

int main(int argc, char *argv[]) {
  struct timeval start, end;
  int n = 20000000;
  int x = 20;
  if (argc > 1) {
    n = atoi(argv[1]);
    if (argc > 2) {
      x = atoi(argv[2]);
    }
  }

  double *A = (double*)malloc(sizeof(double) * n);
  for(int i=0; i<n; i++)
   A[i] = x / (i+1);
  assert(A != 0);

  double *B = (double*)malloc(sizeof(double) * n);
  assert(B != 0);
  for(int i=0; i<n; i++)
   B[i] = x + i;


  double *grad_A = (double*)malloc(sizeof(double) * n);
  assert(grad_A != 0);
  for(int i = 0; i < n; i++)
      grad_A[i] = 0.0;

  double *grad_B = (double*)malloc(sizeof(double) * n);
  assert(grad_B != 0);
  for(int i = 0; i < n; i++)
      grad_B[i] = 0.0;

  double C = 1/x;

  gettimeofday(&start, NULL);

  double grad_C = __enzyme_autodiff((void*)dot,
                    A, grad_A,
                    B, grad_B,
                    C,
                    n);

  gettimeofday(&end, NULL);
  printf("Grad Normalize time=%0.6f A'[0]=%f B'[0]=%f C'=%f\n", tdiff(&start, &end), grad_A[0], grad_B[0], grad_C);

  for(int i = 0; i < n; i++)
      grad_A[i] = 0.0;
  for(int i = 0; i < n; i++)
      grad_B[i] = 0.0;

  gettimeofday(&start, NULL);

  grad_C =__enzyme_autodiff((void*)dot,
                    enzyme_const, A,
                    enzyme_dup, B, grad_B,
                    enzyme_out, C,
                    enzyme_const, n);

  gettimeofday(&end, NULL);
  printf("Constant A time=%0.6f A'[0]=%f B'[0]=%f C'=%f\n", tdiff(&start, &end), grad_A[0], grad_B[0], grad_C);

  return 0;
}
