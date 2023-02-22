#include <stdio.h>
#include <math.h>
#include <assert.h>


double __enzyme_autodiff(void*, ...);

double log1p_like_function(double a) {
  return 2*a;
}

double test(double a) {
  return log1p_like_function(a);
}

void* __enzyme_function_like[2] = {(void*)log1p_like_function, "log1p"}; 

int main(int argc, char** argv) {

  double grad_out = __enzyme_autodiff(test, 2.0);
  printf("Gradient of the log1p like function is %f", grad_out);

  return 0;
}