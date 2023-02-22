#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

float tdiff(struct timeval *start, struct timeval *end) {
  return (end->tv_sec-start->tv_sec) + 1e-6*(end->tv_usec-start->tv_usec);
}

#ifndef NOALIAS

void squareCopy(double* in, double* out, int n) {
  double sumsq = 0;
  for (int i=0; i<n; i++) {
    sumsq += in[i] * in[i];
  }
  *out = sumsq;
}

#else

void squareCopy(double *__restrict__ in, double *__restrict__ out, int n) {
  double sumsq = 0;
  for (int i=0; i<n; i++) {
    sumsq += in[i] * in[i];
  }
  *out = sumsq;
}

#endif

void __enzyme_autodiff(void*, ...);
int enzyme_const, enzyme_dup, enzyme_out;

int main(int argc, char *argv[]) {
  struct timeval start, end;

  int n = 30000000;
  if (argc > 1) {
    n = atoi(argv[1]);
  }


  double *in = (double*)malloc(sizeof(double) * n);
  assert(in != 0);
  for(int i=0; i<n; i++)
   in[i] = (i+1);

  double *out = (double*)malloc(sizeof(double));
  assert(out != 0);

  double *grad_out = (double*)malloc(sizeof(double));
  assert(grad_out != 0);

  *grad_out = 1;

  double *grad_in = (double*)malloc(sizeof(double) * n);
  assert(grad_in != 0);
  for(int i=0; i<n; i++)
   grad_in[i] = 0;

  gettimeofday(&start, NULL);

  __enzyme_autodiff((void*)squareCopy, in, grad_in, out, grad_out, n);

  gettimeofday(&end, NULL);

  printf("Gradient time=%0.6f squareCopy(in)[0] = %f\n", tdiff(&start, &end), grad_in[0]);

  return 0;
}
