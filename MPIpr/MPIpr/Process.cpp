#include "Process.h"
#include <iostream>

Process::Process(int rank, int value)
    : rank(rank), value(value), recVal(0), step(1) {}


void Process::send() {
    if (step == 1) {
        // на первом шаге всё просто и для четных кидаем сами себе и к соседям постарше
        // для нечетных сами себе

        if (rank % 2 == 0) {
            MPI_Sendrecv(&value, 1, MPI_INT, rank, 0, &recVal, 1, MPI_INT, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // для одновременного приема и передачи данных
            MPI_Send(&value, 1, MPI_INT, (rank+1), 1, MPI_COMM_WORLD);
        }
        else {
            MPI_Sendrecv(&value, 1, MPI_INT, rank, 0, &recVal, 1, MPI_INT, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        step += 1;
    }
}

void Process::recv() {
    if (step == 2) {
        if (rank  % 2== 1) {
            MPI_Recv(&recVal, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

}

int Process::getValue() const {
    return value;
}

void Process::setValue(int newValue) {
    value = newValue;
}

void Process::setRecVal(int newRecVal) {
    recVal = newRecVal;
}

int Process::getRecVal() const {
    return recVal;
}