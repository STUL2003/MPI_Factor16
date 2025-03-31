#ifndef PROCESS_H
#define PROCESS_H

#include "mpi.h"

class Process {
private:
    int rank; //ранг процесса
    long value; // значение
    long recVal; // временное хранилизе для полученого значения от прошлого процесса
    int step; // щаг
    long rec2bVal;

public:
    Process(int rank, long value);
    void send();
    void recv();

    // методы для доступа к данным
    long getValue() const;
    void setValue(long newValue);
    void setRecVal(long newRecVal);
    long getRecVal() const;
    long getRec2bVal() const;
};

#endif