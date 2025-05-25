#include "Table.h"

Table::Table(int num) : numPhilosophers(num), forks(num) {
    for (int i = 0; i < numPhilosophers; i++) {
        philosophers.emplace_back([this, i]() {
            Philosopher p(i, forks[i], forks[(i + 1) % numPhilosophers]);
            p.philosopherLife();
        });        
    }
}

Table::~Table() {
    for (auto &philosopher : philosophers) {
        if (philosopher.joinable()) {
            philosopher.join();
        }
    }
}

void Table::startDinner() {
    for (auto &philosopher : philosophers) {
        philosopher.detach();
    }
}
