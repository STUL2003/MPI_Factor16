#ifndef PROCESS_H
#define PROCESS_H

#include "mpi.h"

class Process {
private:
    int rank; //ранг процесса
    long long value; // значение
    long long recVal; // временное хранилизе для полученого значения от прошлого процесса
    int step; // щаг
    long long rec2bVal;

public:
    Process(int rank, long long value);
    void send();
    void recv();

    // методы для доступа к данным
    long long getValue() const;
    void setValue(long long newValue);
    void setRecVal(long long newRecVal);
    long long getRecVal() const;
    long long getRec2bVal() const;
};

#endif