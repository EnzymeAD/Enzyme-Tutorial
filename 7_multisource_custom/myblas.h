extern int enzyme_const, enzyme_dup, enzyme_out;
extern int enzyme_byref;

struct complex {
    double r;
    double i;
};

struct complex myblas_cdot(struct complex* x, struct complex *y, int n);

double myblas_cabs(struct complex x);

struct TapeAndComplex {
    void* tape;
    struct complex res;
};

struct TapeAndComplex myblas_cdot_fwd(struct complex* x, struct complex* dx, struct complex *y, struct complex* dy, int n, int dn);
void myblas_cdot_rev(struct complex* x, struct complex* dx, struct complex *y, struct complex* dy, int n, int dn, struct complex* diffret, void* tape);

struct TapeAndDouble {
    void* tape;
    double res;
};

struct TapeAndDouble myblas_cabs_fwd(struct complex x);
struct complex myblas_cabs_rev(struct complex x, double diffret, void* tape);
void* __enzyme_register_gradient1[] = { (void*)myblas_cdot, (void*)myblas_cdot_fwd, (void*)myblas_cdot_rev, "byref_6" };
void* __enzyme_register_gradient2[] = { (void*)myblas_cabs, (void*)myblas_cabs_fwd, (void*)myblas_cabs_rev };
