// MpiMatrixMultiplication.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <stdio.h>
#include "mpi.h"
#include <iostream>
#include "Matrix.h"
#include <chrono>
#include <time.h>      

int main(int argc, char** argv)
{   
     const int M = 10000;
     const int N = 1000;
     const int K = 1000;

    Matrix<M,N> A(0.1);
    Matrix<N,K> B(0.5);
    
    int MK = M * K;
    /*
    A.info(5);
    B.info(5);

    auto C = dot(A, B);
    std::cout << typeid(C).name() << "\n";
    C.info(5);
    */
    double time_spent = 0.0;
    //double start, end;
    int ProcNum, ProcRank, RecvRank;
    double Sum = 0;
    MPI_Status Status;

    clock_t begin = clock();
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    srand(time(NULL) + ProcRank);
    
  
    if (ProcRank == 0) {
      
        Matrix<M,K> C;

        
        for (int i = 0; i < MK / ProcNum; i++) {
            double C_ij = 0;
            int index_1 = i / K;
            int index_2 = i % K;
           
            for (int j = 0; j < N; j++) {
                C_ij += A(index_1, j) * B(j, index_2);
               
            }
          
            C(index_1, index_2)= C_ij;
        }

      
        
       for (int i = 1; i < ProcNum; i++) {
          
           MPI_Recv(&RecvRank, 1, MPI_INT, MPI_ANY_SOURCE,  MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
           bool T = ((MK % ProcNum) >= RecvRank);
           double* C_ij = new double[MK / ProcNum+T];

           for (int j = 0; j < MK / ProcNum+T; j++) {
               C_ij[j] = 0;
               
           }
           
           MPI_Recv(C_ij, (int)(MK/ProcNum+T), MPI_DOUBLE, MPI_ANY_SOURCE,
                    MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
           
             for (int j = T * (RecvRank - 1) + (!T) * (MK % ProcNum) + RecvRank * (MK / ProcNum),k=0; j < T * (RecvRank)+!T * (MK % ProcNum) + (RecvRank + 1) * (MK / ProcNum); j++,k++) {
              
               C(j/K, j%K)= C_ij[k];
           }

           }
          
        
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

        std::cout << time_spent << ","<< std::endl;
        C.info(10);
    }
    else {
       
        bool T = ((MK % ProcNum) >= ProcRank);

        //std::cout << T << "\n";
        double* C_ij = new double[MK / ProcNum+T];
        for (int j = 0; j < MK / ProcNum+T; j++) {
            C_ij[j] = 0;
        }
        
        
        for (int i = T*(ProcRank-1)+(!T)*(MK%ProcNum)+ProcRank * (MK / ProcNum),k=0; i < T * (ProcRank)+(!T)*(MK % ProcNum) + (ProcRank + 1) * (MK / ProcNum); i++,k++) {
            
            int index_1 = i / K;
            int index_2 = i % K;
            //std::cout << ProcRank << " " << index_1 << " " << index_2 << "\n";
            for (int j = 0; j < N; j++) {
                
                C_ij[k] += A(index_1, j) * B(j, index_2);
            }
            
            
            
        }
            
        MPI_Send(&ProcRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(C_ij, (int)(MK/ProcNum+T), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
          
       
        
    }
        MPI_Finalize();
     
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
