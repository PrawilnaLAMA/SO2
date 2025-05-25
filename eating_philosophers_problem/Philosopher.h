#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Philosopher {
private:
    int id;
    std::mutex &leftFork;
    std::mutex &rightFork;

public:
    Philosopher(int id, std::mutex &left, std::mutex &right);
    void philosopherLife();
};

#endif
