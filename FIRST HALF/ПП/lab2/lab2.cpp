#include <iostream>
#include "mpi.h"
#include "matrix.h"




int main(int argc, char* argv[]) {

    Matrix a(argc, argv, "output.txt", 14, 6);
    a.scatterv();


    return 0;
}
