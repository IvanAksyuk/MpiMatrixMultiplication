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
     int M = 10000;
     int N = 1000;
     int K = 1000;

    Matrix A(1.0, M, N);
    Matrix B(1.0, N, K);
    
    int MK = M * K;
    

  
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
    //std::cout << ProcNum << "\n";
    if (ProcRank == 0) {
        // Действия, выполняемые только процессом с рангом 0
        Matrix C(M, K);

        
        for (int i = 0; i < MK / ProcNum+(MK%ProcNum); i++) {
            double C_ij = 0;
            int index_1 = i / K;
            int index_2 = i % K;
            //std::cout << i << "\n";
            for (int j = 0; j < N; j++) {
                C_ij += A.getAij(index_1, j) * B.getAij(j, index_2);
               
            }
            //std::cout << ProcRank << " ";
            //if((i+1)%K==0) std::cout <<"\n";
            C.setAij(C_ij, index_1, index_2);
        }

        for (int i = MK-MK%ProcNum; i < MK; i++) {
            double C_ij = 0;
            int index_1 = i / K;
            int index_2 = i % K;
            //std::cout << index_1<<" "<<index_2 << "\n";
            for (int j = 0; j < N; j++) {
                C_ij += A.getAij(index_1, j) * B.getAij(j, index_2);

            }
            //std::cout << ProcRank << " ";
            //if((i+1)%K==0) std::cout <<"\n";
            //std::cout << C_ij << "\n";
            C.setAij(C_ij, index_1, index_2);
        }
       
        
       for (int i = 1; i < ProcNum; i++) {
           double* C_ij = new double[MK/ProcNum];
           for (int j = 0; j < MK / ProcNum; j++) { C_ij[j] = 0; 
           //printf("%3f", C_ij[j]);
           }
           MPI_Recv(&RecvRank, 1, MPI_INT, MPI_ANY_SOURCE,  MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
           
           MPI_Recv(C_ij, (int)(MK/ProcNum), MPI_DOUBLE, MPI_ANY_SOURCE,
                    MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
           //std::cout << RecvRank << " ";
           //std::cout << C_ij[0] << "\n";
           for (int j = 0+ RecvRank * (MK / ProcNum),k=0; j < 0 + (RecvRank + 1) * (MK / ProcNum); j++,k++) {
               //std::cout << RecvRank << " ";
               //if ((j + 1) % K == 0) std::cout << "\n";
               //std::cout <<RecvRank<<" "<< j / K << " " << j % K << "\n";
               C.setAij(C_ij[k], j/K, j%K);
           }

           }
          
        
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

        std::cout << time_spent << ","<< std::endl;
        //C.info();
    }
    else {
        //std::cout << ProcRank << "\n";
        //std::cout << 123 << "\n";
        double* C_ij = new double[MK / ProcNum];
        for (int j = 0; j < MK / ProcNum; j++) {
            C_ij[j] = 0;
        }
        
        
        for (int i = 0+ProcRank * (MK / ProcNum),k=0; i < 0+ (ProcRank + 1) * (MK / ProcNum); i++,k++) {
            
            int index_1 = i / K;
            int index_2 = i % K;
            //std::cout << ProcRank << " " << index_1 << " " << index_2 << "\n";
            for (int j = 0; j < N; j++) {
                
                C_ij[k] += A.getAij(index_1, j) * B.getAij(j, index_2);
            }
            
            
            
        }
            
        MPI_Send(&ProcRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(C_ij, (int)(MK/ProcNum), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
          
       
        
    }
        MPI_Finalize();
   

   

    
    //

   

    

    // рассчитать прошедшее время, найдя разницу (end - begin) и
    // деление разницы на CLOCKS_PER_SEC для перевода в секунды
    /*
    int N = 200;
    Matrix A(1.0, N,N);
    A.info();
    Matrix B(1.0, N, N);
    B.info();
    Matrix C;
    
    
    C = A.dot(B);
  
   
    

    
    C.info();


  
    */
    
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
