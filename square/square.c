#include <stdio.h>
#include <stdlib.h>
double square(double x) {
  return x * x;
}

double __enzyme_autodiff(void*, ...);
int enzyme_const, enzyme_dup, enzyme_out;

int main(int argc, char *argv[]) {
  double x = 20;
  if (argc > 1) {
    x = atof(argv[1]);
  }

  double grad_x = __enzyme_autodiff((void*)square, x);
  printf("Gradient square(%f) = %f\n", x, grad_x);

  return 0;
}
