#pragma once
#include "mpi.h"
#include "Process.h"

class Fact16 {//класс факториала
private:
    int rank;//ранги процессов
    void processing(Process* process); //обработка процессов
public:
    Fact16();
    void calc();
};