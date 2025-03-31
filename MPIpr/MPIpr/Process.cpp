#include "Process.h"
#include <iostream>

Process::Process(int rank, long value)
    : rank(rank), value(value), recVal(0), step(1), rec2bVal(0) {}


void Process::send() {
    if (step == 1) {
        // на первом шаге всё просто и для четных кидаем сами себе и к соседям постарше
        // для нечетных сами себе
        if (rank % 2 == 0) {
            MPI_Sendrecv(&value, 1, MPI_INT, rank, 0, &recVal, 1, MPI_INT, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&value, 1, MPI_INT, (rank + 1), 1, MPI_COMM_WORLD);
            if (rank == 2 || rank == 6) {
                MPI_Send( &value, 1, MPI_INT, (rank - 1), 0, MPI_COMM_WORLD);
            }
        }
        else {
            MPI_Sendrecv(&value, 1, MPI_INT, rank, 0, &recVal, 1, MPI_INT, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        step += 1;
    }

    else if (step == 2) {
        if (rank == 1 || rank == 5) {
            for (int i = 0; i < 4; i++) i != 1 ? MPI_Send(&value, 1, MPI_INT, (rank + (i - 1)), 1, MPI_COMM_WORLD) : MPI_Sendrecv(&value, 1, MPI_INT, rank, 0, &recVal, 1, MPI_INT, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        else if ( rank == 2 || rank == 3 || rank == 6 || rank == 7) {
            MPI_Sendrecv(&value, 1, MPI_INT, rank, 0, &recVal, 1, MPI_INT, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        step += 1;

    }
}

void Process::recv() {
    if (step == 2) {
        if (rank % 2 == 1) {
            MPI_Recv(&recVal, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    else if (step == 3) {
        if (rank < 4 && rank != 1) MPI_Recv(&recVal, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        else if (rank > 3 && rank != 5)  MPI_Recv(&recVal, 1, MPI_INT, 5, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        else if (rank == 1 || rank == 5) MPI_Recv(&rec2bVal, 1, MPI_INT,(rank+1), 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

}


long Process::getValue() const {
    return value;
}

void Process::setValue(long newValue) {
    value = newValue;
}

void Process::setRecVal(long newRecVal) {
    recVal = newRecVal;
}

long Process::getRecVal() const {
    return recVal;
}

long Process::getRec2bVal() const {
    return rec2bVal;
}