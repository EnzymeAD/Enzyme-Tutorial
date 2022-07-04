#include "myblas.h"

struct complex myblas_cdot(struct complex* x, struct complex *y, int n) {
  struct complex sum = { 0, 0 };
  for (int i=0; i<n; i++) {
    sum.r += x[i].r * y[i].r - x[i].i * y[i].i;
    sum.i += x[i].r * y[i].i + x[i].i * y[i].r;
  }
  return sum;
}

double myblas_cabs(struct complex x) {
    return x.r * x.r + x.i * x.i;
}
