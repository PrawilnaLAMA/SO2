#ifndef TABLE_H
#define TABLE_H

#include "Philosopher.h"
#include <vector>

class Table {
private:
    int numPhilosophers;
    std::vector<std::mutex> forks;
    std::vector<std::thread> philosophers;

public:
    Table(int num);
    ~Table();
    void startDinner();
};

#endif
