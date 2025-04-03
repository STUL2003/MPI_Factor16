#include "Process.h"
#include <iostream>

Process::Process(int rank, long long value)
    : rank(rank), value(value), recVal(0), step(1), rec2bVal(0) {}


void Process::send() {
    if (step == 1) {
        // на первом шаге всё просто и для четных кидаем сами себе и к соседям постарше
        // для нечетных сами себе
        if (rank % 2 == 0) {
            MPI_Sendrecv(&value, 1, MPI_LONG, rank, 0, &recVal, 1, MPI_LONG, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&value, 1, MPI_LONG, (rank + 1), 1, MPI_COMM_WORLD);
            if (rank == 2 || rank == 6) {
                MPI_Send( &value, 1, MPI_LONG, (rank - 1), 13, MPI_COMM_WORLD);
            }
            else if (rank == 4) {
                MPI_Send(&value, 1, MPI_LONG, 1, 14, MPI_COMM_WORLD);
            }
        }
        else {
            MPI_Sendrecv(&value, 1, MPI_LONG, rank, 0, &recVal, 1, MPI_LONG, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        step += 1;
    }

    else if (step == 2) {
        if (rank == 1 || rank == 5) {
            for (int i = 0; i < 4; i++) i != 1 ? MPI_Send(&value, 1, MPI_LONG, (rank + (i - 1)), 2, MPI_COMM_WORLD) : MPI_Sendrecv(&value, 1, MPI_LONG, rank, 0, &recVal, 1, MPI_LONG, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            if (rank == 5) {
                MPI_Send(&value, 1, MPI_LONG, 3, 24, MPI_COMM_WORLD);
            }

        }
        else if (rank == 2 || rank == 3 || rank == 6 || rank == 7) {
            MPI_Sendrecv(&value, 1, MPI_LONG, rank, 0, &recVal, 1, MPI_LONG, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        else if (rank == 4) {
            MPI_Send(&value, 1, MPI_LONG, 2, 24, MPI_COMM_WORLD);
        }

        step += 1;

    }

    else if (step == 3){
        if (rank == 3) {
            for (int i = 0; i < 8; i++) {
                i != 3 ? MPI_Send(&value, 1, MPI_LONG, i, 34, MPI_COMM_WORLD) : MPI_Sendrecv(&value, 1, MPI_LONG, i, 0, &recVal, 1, MPI_LONG, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
            }
        }
        if (rank > 3) MPI_Sendrecv(&value, 1, MPI_LONG, rank, 0, &recVal, 1, MPI_LONG, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        recVal = value;
        step += 1;
    }
}

void Process::recv() {
    if (step == 2) {
        if (rank % 2 == 1) {
            MPI_Recv(&recVal, 1, MPI_LONG, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    else if (step == 3) {
        if (rank < 4 && rank != 1) MPI_Recv(&recVal, 1, MPI_LONG, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        else if (rank > 3 && rank != 5)  MPI_Recv(&recVal, 1, MPI_LONG, 5, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        else if (rank == 1 || rank == 5) MPI_Recv(&rec2bVal, 1, MPI_LONG,(rank+1), 13, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else if (step == 4) {
        if (rank != 3) MPI_Recv(&value, 1, MPI_LONG, 3, 34, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        if (rank == 1) MPI_Recv(&rec2bVal, 1, MPI_LONG, 4, 14, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        if (rank == 2 || rank == 3) MPI_Recv(&rec2bVal, 1, MPI_LONG, (rank + 2), 24, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
    }


}


long long Process::getValue() const {
    return value;
}

void Process::setValue(long long newValue) {
    value = newValue;
}

long long Process::getRecVal() const {
    return recVal;
}

long long Process::getRec2bVal() const {
    return rec2bVal;
}