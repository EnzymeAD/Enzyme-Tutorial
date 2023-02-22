struct complex {
    double r;
    double i;
};

struct complex myblas_cdot(struct complex* x, struct complex *y, int n);

double myblas_cabs(struct complex x);
