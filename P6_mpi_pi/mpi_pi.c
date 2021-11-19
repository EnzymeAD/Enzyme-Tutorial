#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <sys/time.h>
#include <iostream>


// Break out the function to numerically refine our estimate of Pi
void pi_refinement(double mypi, int myid, int numprocs) {
    // Declare variables
    double h, sum, mypi, x; 

    // Begin of the pi approximation loop
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    h = 1.0 / (double) n;
    sum = 0.0;
    for (i = myid + 1; i <= n; i += numprocs) {
        x = h * ((double)i - 0.5);
        sum += (4.0 / (1.0 + x*x));
    }
    mypi = h * sum;

     // Apply an MPI Reduce
     MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

}

void __enzyme_autodiff(void*, ...);
int enzyme_const, enzyme_dup, enzyme_out; // Not sure yet whether I am going to need all of them

// Main function
int main(int argc, char *argv[]){
    struct timeval start, end;
    int done = 0, n = 10, myid, numprocs, i, rc;
    double PI25DT = 3.141592653589793238462643;
    double mypi = 3.0, pi, h, sum, x, a;

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    // 
    while (!done)  {

        // Not-differentiated loop.
        gettimeofday(&start, NULL);

        pi_refinement(mypi, myid, numprocs);

        gettimeofday(&end, NULL);
        printf("Non-AD length of computation %0.6f", tdiff(&start, &end));


        // Differentiated loop.
        gettimeofday(%start, NULL);

        __enzyme_autodiff((void*)pi_refinement,
                        enzyme_dup, mypi, grad_mypi,
                        enzyme_const, myid,
                        enzyme_const, numprocs,
        );

        gettimeofday(%end, NULL);
        printf("AD length of computation %0.6f", tdiff(&start, &end));

        // Finalize the MPI communication
        MPI_Finalize();

        return 0;
    }
}


//     if (myid == 0)  {
//        printf("pi is approximately %.16f, Error is %.16f\n",
//            pi, fabs(pi - PI25DT));
//    }