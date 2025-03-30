#include <cstdio>
#include "mpi.h"
#include <iostream>
#include <string.h>
#include "Fact16.h"

//=================================getting up to speed======================================================
void task_1(int argc, char** argv) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::cout << rank << std::endl;
}

void task_2(int argc, char** argv) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        std::string s = "Mesage from 0";

        /*
        * c_str() в C++ — это функция, которая переводит строку в массив из символов
        */
        MPI_Send(s.c_str(), s.size() + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD); // 0 - тег сообщения, чтобы различать
    }
    else if (rank == 1) {
        char s[100];
        MPI_Recv(s, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << s << std::endl;
    }

}

void task_3(int argc, char** argv) {

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {

        const int a = 2;

        MPI_Send(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        int a_;
        MPI_Recv(&a_, 1, MPI_INT, 4, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "From rank 4: " << a_ << std::endl;
    }
    else if (rank == 1) {
        int a;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "From rank 0 " << a << std::endl;
        a *= 2;
        MPI_Send(&a, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);

    }
    else if (rank == 2) {
        int a;
        MPI_Recv(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "From rank 1 " << a << std::endl;
        a *= 2;
        MPI_Send(&a, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);

    }
    else if (rank == 3) {
        int a;
        MPI_Recv(&a, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "From rank 2 " << a << std::endl;
        a *= 2;
        MPI_Send(&a, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
    }

    else if (rank == 4) {
        int a;
        MPI_Recv(&a, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "From rank 3 " << a << std::endl;
        a *= 2;
        MPI_Send(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
}
//=================================finishing======================================================



int main(int argc, char** argv) {

    auto getarg = [argc, argv]() -> std::string {
        std::string s = "";
        for (int i = 0; i < strlen(argv[1]); i++) s += argv[1][i];
        return s;
        };

    std::string task = getarg();

    MPI_Init(&argc, &argv);

    if (task == "task1") task_1(argc, argv);

    else if (task == "task2") task_2(argc, argv);

    else if (task == "task3") task_3(argc, argv);
    
    else if (task == "Fact16") {
        Fact16* fact16 = new Fact16();
        fact16->calc();
    }

    else std::cout << task;

    MPI_Finalize();

    return 0;
}