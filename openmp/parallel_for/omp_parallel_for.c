#include <omp.h>


// Do parallel for 
void omp(float *x, int npoints) {

#pragma omp parallel for
    for (int i = 0; i < npoints; i++) {
        x[i] *= x[i];
    }
}


double __enzyme_autodiff(void*, ...);

int main() {

    // Initialize array
    float array[1000];
    for(int i=0; i<1000; i++) {
        array[i] = i + 0.5;
    }

    // Set up the array to host the gradients
    float d_array[1000];
    for(int i=0; i<1000; i++) {
        d_array[i] = 1.0f;
    }

    // Alter the entries
#ifdef FORWARD
    sub(array, 1000);
#else
    __enzyme_autodiff((void*)omp, array, d_array, 1000);
#endif

    return 0;
}
