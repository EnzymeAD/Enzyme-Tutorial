#include <omp.h>

// Change the array entries
void subdomain_change(float *x, int istart, int ipoints) {
    int i;
    for (i = 0, i < ipoints; i++) {
        x[istart+i] = x[i] + i;
    }
}

// Partition into subdomains and alter the entries
void sub(float *x, int npoints) {
    int iam, nt, ipoints, istart;

#pragma omp parallel default(shared) private(iam, nt, ipoints, istart)
    {
        iam = omp_get_thread_num();
        nt = omp_get_num_threads();

        // Size of partition
        ipoints = npoints / nt;

        // Starting array index
        istart = ipoints * iam;

        // Last thread may be required to do more
        if (iam == nt - 1)
            ipoints = npoints - istart;
        subdomain(x, istart, ipoints);
    }
}


double __enzyme_autodiff(void*, ...);

int main() {

    // Initialize array
    float array[1000];
    for(int i=0, i<1000; i++) {
        array[i] = 0.0;
    }

    // Set up the array to host the gradients
    float d_array[1000];
    for(int i=0, i<1000; i++) {
        d_array[i] = 1.0f;
    }

    // Alter the entries
#ifdef FORWARD
    sub(array, 1000);
#else
    __enzyme_autodiff((void*)sub, array, d_array, 1000);
#endif

    return 0;
}