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

struct TapeAndComplex __enzyme_augmentfwd(void*, ...);
struct TapeAndDouble __enzyme_augmentfwd2(void*, ...);
void __enzyme_reverse(void*, ...);
struct complex __enzyme_reverse2(void*, ...);
struct TapeAndComplex myblas_cdot_fwd(struct complex* x, struct complex *dx, struct complex *y, struct complex* dy, int n, int dn) {
   return __enzyme_augmentfwd((void*)myblas_cdot, x, dx, y, dy, n);
}

void myblas_cdot_rev(struct complex* x, struct complex* dx, struct complex *y, struct complex* dy, int n, int dn, struct complex* diffret, void* tape) {
   return __enzyme_reverse((void*)myblas_cdot, x, dx, y, dy, enzyme_dup, n, dn, enzyme_byref, sizeof(struct complex), diffret, tape);
}

struct TapeAndDouble myblas_cabs_fwd(struct complex x) {
   return __enzyme_augmentfwd2((void*)myblas_cabs, x);
}
struct complex myblas_cabs_rev(struct complex x, double diffret, void* tape) {
   return __enzyme_reverse2((void*)myblas_cabs, x, diffret, tape);
}
