#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Fast inverse sqrt
// Code taken from https://en.wikipedia.org/wiki/Fast_inverse_square_root
#ifdef CUSTOM
__attribute__((noinline))
#endif
float Q_rsqrt( float number )
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y  = number;
  i  = * ( long * ) &y;                       // evil floating point bit level hacking
  i  = 0x5f3759df - ( i >> 1 );               // what the [...]?
  y  = * ( float * ) &i;
  y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
  return y;
}


double invmag(double* __restrict__ A, int n) {
  double sumsq = 0;
  for (int i=0; i<n; i++) {
    sumsq += A[i] * A[i];
  }
  return Q_rsqrt(sumsq);
}

#ifdef CUSTOM

void aug_rsqrt(float x) {
  // Nothing need to be done in augmented forward pass
}

float rev_rsqrt(float x, float grad_out) {
  // derivative of x^(-1/2) = -1/2 x^(-3/2)
  return -grad_out * Q_rsqrt(x) / (2 * x);
}

void* __enzyme_register_gradient_rsqrt[3] = { (void*)Q_rsqrt, (void*)aug_rsqrt, (void*)rev_rsqrt };

#endif


void __enzyme_autodiff(void*, ...);
int enzyme_const, enzyme_dup, enzyme_out;

int main(int argc, char *argv[]) {
  int n = 3;
  if (argc > 1) {
    n = atoi(argv[1]);
  }


  double *A = (double*)malloc(sizeof(double) * n);
  for(int i=0; i<n; i++)
   A[i] = (i+1);
  assert(A != 0);

  double *grad_A = (double*)malloc(sizeof(double) * n);
  assert(grad_A != 0);
  for(int i=0; i<n; i++)
   grad_A[i] = 0;

  __enzyme_autodiff((void*)invmag, A, grad_A, n);
  printf("Gradient invmag(A)[0] = %f\n", grad_A[0]);

  return 0;
}
