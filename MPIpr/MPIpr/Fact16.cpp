#include "Fact16.h"
#include "Process.h"
#include <iostream>
#include "mpi.h"

Fact16::Fact16() {
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
}

void Fact16::processing(Process* process) {
    process->send();
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

    //1-2ой шаг
    if (process) {
        processing(process);
        if (rank % 2 == 0) process->setValue(process->getValue() * (rank * 2 + 3));
        else process->setValue(process->getValue() * process->getRecVal());

    }

    // 2-3-й шаг
    if (process) {
        processing(process);
        if (rank == 0 || rank == 4) process->setValue(process->getRecVal() * (2 * rank + 5));
        else if (rank == 1 || rank == 5) process->setValue(process->getRecVal() * process->getRec2bVal());
        else process->setValue(process->getValue() * process->getRecVal());
    }
    
    //3-4й шаг
    if (process) {
        processing(process);
        if (rank == 0) process->setValue(process->getValue() * 9);
        else if (rank == 1 || rank == 2) process->setValue(process->getValue() * process->getRec2bVal());
        else if (rank == 3) process->setValue(process->getRecVal() * process->getRec2bVal());
        else process->setValue(process->getRecVal() * process->getValue());
    }
    

    if (process) {
        std::cout << "proc " << rank << " res: " << process->getValue() << std::endl;
        delete process;
    }
}