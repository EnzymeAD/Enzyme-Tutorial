#include <stdio.h>

void __device__ square_impl(double* x_in, double *x_out) {
    x_out[0] = x_in[0] * x_in[0];
}

typedef void (*f_ptr)(double*, double*);

extern void __device__ __enzyme_autodiff(f_ptr,
    int, double*, double*,
    int, double*, double*
);

void __global__ square(double* x_in, double *x_out) {
    square_impl(x_in, x_out);
}

int __device__ enzyme_dup;
int __device__ enzyme_out;
int __device__ enzyme_const;

void __global__ square_grad(double* x, double *d_x, double *y, double *d_y) {

    __enzyme_autodiff(square_impl,
        enzyme_dup, x, d_x,
        enzyme_dup, y, d_y);

}

int main() {

    // Device pointers
    double *x, *d_x, *y, *d_y;

    // Allocate GPU device memory
    cudaMalloc(&x, sizeof(*x));
    cudaMalloc(&d_x, sizeof(*d_x))
    cudaMalloc(&y, sizeof(*y));
    cudaMalloc(&d_y, sizeof(*d_y))

    // Initialize device values
    double host_x = 1.4;
    double host_d_x = 0.0;
    double host_y;
    double host_d_y = 1.0;

    // Copy data to device
    cudaMemcpy(x, &host_x, sizeof(*x), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, &host_d_x, sizeof(*d_x), cudaMemcpyHostToDevice);
    cudaMemcpy(y, &host_y, sizeof(*y), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, &host_d_y, sizeof(*d_y), cudaMemcpyHostToDevice);

#ifdef FORWARD
    // Forward pass only
    square<<<1, 1>>>(x, y);
#else
    // Forward and backward pass
    square_grad<<<1, 1>>>(x, d_x, y, d_y);  
#endif

    // Synchronize device memory
    cudaDeviceSynchronize();

    // Copy data from device to host
    cudaMemcpy(&host_x, x, sizeof(*x), cudaMemcpyDeviceToHost);
    cudaMemcpy(&host_d_x, d_x, sizeof(*d_x), cudaMemcpyDeviceToHost);
    cudaMemcpy(&host_y, y, sizeof(*y), cudaMemcpyDeviceToHost);
    cudaMemcpy(&host_d_y, d_y, sizeof(*d_y), cudaMemcpyDeviceToHost);

    // Print results
    printf("%f %f\n", host_x, host_y);
    printf("%f %f\n", host_d_x, host_d_y);
    
}