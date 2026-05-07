#include <iostream>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        #pragma omp single
        std::cout << "OpenMP threads: " << omp_get_num_threads() << "\n";
    }
}
