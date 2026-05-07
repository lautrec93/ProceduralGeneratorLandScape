#include <execution>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
#include <omp.h>

int main() {
    std::vector<int> v(1000000);
    std::iota(v.begin(), v.end(), 0);
    std::sort(std::execution::par, v.begin(), v.end());

    #pragma omp parallel
    {
        #pragma omp single
        std::cout << "OpenMP threads: " << omp_get_num_threads() << "\n";
    }
    std::cout << "Parallel STL works!\n";
}
