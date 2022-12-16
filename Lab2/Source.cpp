#include <iostream>
#include <chrono>
#include <omp.h>


void Print_Matrix(int* Mat, int size)
{
    std::cout << "Multiplication: " << std::endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << Mat[i * size + j] << " ";
        }
        std::cout << std::endl;
    }
}


int main(int argc, char* argv[]) {
    clock_t start;
    if (argc != 2) {
        std::cout << "Program usage: " << std::endl << "./" << argv[0] << " <n>" << std::endl
            << "where <n> is the size of square matrix" << std::endl;
        return -1;
    }

    const int N = 500;
    int* A, * B, * C;
    A = new int[N * N];
    B = new int[N * N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (i + 2) * (j + 1);
            B[i * N + j] = (i + 1) + 2 * (j + 3);
        }
    }

    //Print_Matrix(A, N);
    //Print_Matrix(B, N);
    C = new int[N * N];

    start = clock();

    double wtime = omp_get_wtime();


    int threads;
    omp_set_num_threads(8);

#pragma omp parallel shared(threads)
    {
        threads = omp_get_num_threads();

#pragma for
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                C[i * N + j] = 0;
                for (int k = 0; k < N; k++)
                {
                    C[i * N + j] += A[i * N + k] * B[k * N + j];
                }
            }
    }


    wtime = omp_get_wtime() - wtime;
    std::cout << "Elapsed omp time: " << wtime << " seconds" << std::endl;
    std::cout << std::endl << "Num of threads: " << threads << std::endl << "Calculation time: " << double(clock() - start) / CLOCKS_PER_SEC << " seconds" << std::endl;


    //Print_Matrix(C, N);

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}