#ifndef PROCESS_H
#define PROCESS_H

#include "mpi.h"

class Process {
private:
    int rank; //ранг процесса
    int value; // значение
    int recVal; // временное хранилизе для полученого значения от прошлого процесса
    int step; // щаг

public:
    Process(int rank, int value);
    void send();
    void recv();

    // методы для доступа к данным
    int getValue() const;
    void setValue(int newValue);
    void setRecVal(int newRecVal);
    int getRecVal() const;
};

#endif