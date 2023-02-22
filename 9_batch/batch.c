#include <stdio.h>

struct Vector {
  double x1, x2, x3, x4;
};

extern Vector __enzyme_batch(...);

extern int enzyme_width;
extern int enzyme_vector;
extern int enzyme_scalar;

double square(double x) { return x * x; }

Vector vecsquare(double x1, double x2, double x3, double x4) {
  return __enzyme_batch(square, enzyme_width, 4, enzyme_vector, x1, x2, x3, x4);
}
int main() {
  double vals[] = {23.1, 10.0, 100.0, 3.14};
  double expected[] = {square(vals[0]), square(vals[1]), square(vals[2]),
                       square(vals[3])};
  Vector result = vecsquare(vals[0], vals[1], vals[2], vals[3]);
}