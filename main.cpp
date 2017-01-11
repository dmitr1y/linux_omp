#include <iostream>
#include <iomanip>
#include <sys/times.h>
#include <cmath>
#include <omp.h>
#include <unistd.h>
#include <cstdlib>
/*
 * g++ main.cpp -march=bdver1 -mtune=bdver1 -fopenmp -O0
 * sudo nice -n -20 ./a.out
 *
 */

#define ITERATIONS_NUMBER 1000000000
#define STEPPING_NUMBER 430801

int main(int argc, char **argv) {
    double PI25DT = 3.141592653589793238462643;
omp_set_num_threads(1024);
#pragma omp parallel
    {
#pragma omp master
        {
            int cntThreads = omp_get_num_threads();
            std::cout << "OpenMP. number of threads = " << cntThreads << std::endl;
        }
    }
    clock_t clockStart, clockStop;
    tms tmsStart, tmsStop;
    clockStart = times(&tmsStart);
    long double PI = 0;
    //num_threads(THREADS_NUMBER)
#pragma omp parallel for schedule(dynamic, STEPPING_NUMBER) reduction(+:PI)
    for (long int i = 0; i < ITERATIONS_NUMBER; i++) {
        PI += 4 / (1 + pow((i + 0.5) / ITERATIONS_NUMBER, 2));
    }


    clockStop = times(&tmsStop);
    std::cout << "The value of PI is " << PI << " Error is " << fabs(PI - PI25DT) << std::endl;
    std::cout << "The time to calculate PI was ";
    double secs = (clockStop - clockStart) / static_cast<double>(sysconf(_SC_CLK_TCK));
    std::cout << secs << " seconds\n" << std::endl;
    exit(0);
}
