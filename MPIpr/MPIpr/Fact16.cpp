#include "Fact16.h"
#include "Process.h"
#include <iostream>
#include "mpi.h"

Fact16::Fact16() {
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
}

void Fact16::processing(Process* process) {
    process->send();
    MPI_Barrier(MPI_COMM_WORLD);
    process->recv();
}

void Fact16::calc() {
    Process* process;

    switch (rank)
    {
    case 0: process = new Process(rank, 1 * 2); break;
    case 1: process = new Process(rank, 3 * 4); break;
    case 2: process = new Process(rank, 5 * 6); break;
    case 3: process = new Process(rank, 7 * 8); break;
    case 4: process = new Process(rank, 9 * 10); break;
    case 5: process = new Process(rank, 11 * 12); break;
    case 6: process = new Process(rank, 13 * 14); break;
    case 7: process = new Process(rank, 15 * 16); break;
    default:
        process = nullptr;
        break;
    }

    //1-ый шаг
    if (process) {
        processing(process);
        if (rank % 2 == 0) process->setValue(process->getValue() * (rank * 2 + 3));
        else process->setValue(process->getValue() * process->getRecVal());

    }

    if (process) {
        std::cout << "proc " << rank << " res: " << process->getValue() << std::endl;
        delete process;
    }
}