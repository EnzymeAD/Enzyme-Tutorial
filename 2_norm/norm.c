#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

float tdiff(struct timeval *start, struct timeval *end) {
  return (end->tv_sec-start->tv_sec) + 1e-6*(end->tv_usec-start->tv_usec);
}

__attribute__((const,noinline))
double mag(const double *A, int n) {
  double amt = 0;
  for(int i=0; i<n; i++) amt += A[i];
  return amt;
}

void normalize(double *__restrict__ out, const double *__restrict__ in, int n) {
 for(int i = 0; i < n; ++i)
    out[i] = in[i] / mag(in, n);
}

void __enzyme_autodiff(void*, ...);
int enzyme_const, enzyme_dup, enzyme_out;

int main(int argc, char *argv[]) {
  struct timeval start, end;
  int n = 1000000;
  int x = 20;
  if (argc > 1) {
    n = atoi(argv[1]);
    if (argc > 2) {
      x = atoi(argv[2]);
    }
  }

  double *A = (double*)malloc(sizeof(double) * n);
  assert(A != 0);

  double *B = (double*)malloc(sizeof(double) * n);
  assert(B != 0);
  for(int i=0; i<n; i++)
   B[i] = x; 


  double *grad_A = (double*)malloc(sizeof(double) * n);
  assert(grad_A != 0);
  for(int i = 0; i < n; i++)
      grad_A[i] = 1.0;

  double *grad_B = (double*)malloc(sizeof(double) * n);
  assert(grad_B != 0);
  for(int i = 0; i < n; i++)
      grad_B[i] = 0.0;


  gettimeofday(&start, NULL);

  normalize(A, B, n);

  gettimeofday(&end, NULL);
  printf("Serial Normalize %0.6f %f\n", tdiff(&start, &end), A[n-1]);

  gettimeofday(&start, NULL);

  __enzyme_autodiff((void*)normalize,
                    enzyme_dup, A, grad_A,
                    enzyme_dup, B, grad_B,
                    enzyme_const, n);

  gettimeofday(&end, NULL);
  printf("Gradient Normalize %0.6f %f %f\n", tdiff(&start, &end), A[n-1], grad_B[0]);

  free(A);
  free(B);
  return 0;
}
