#include <iostream>
#include "integral.h"


int main(int argc, char* argv[]) {
    /*int r, n;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &n);

    printf("Rank: %i\tProsses: %i\n", r, n);

    MPI_Finalize();*/

    Integral a(argc, argv);
    a.calculate_integral();
    a.sum_results_process();
    std::cout << a << std::endl;


    return 0;
}

// mpiexex -n ... file
