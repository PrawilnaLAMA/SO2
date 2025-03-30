#include "Philosopher.h"
#include <chrono>
#include <random>

Philosopher::Philosopher(int id, std::mutex &left, std::mutex &right)
    : id(id), leftFork(left), rightFork(right) {}

void Philosopher::philosopherLife() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> duration(1000, 3000);

    while (true) {
        std::cout << "Philosopher " << id << " is thinking..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(duration(gen)));

        std::lock(leftFork, rightFork);
        std::lock_guard<std::mutex> leftLock(leftFork, std::adopt_lock);
        std::lock_guard<std::mutex> rightLock(rightFork, std::adopt_lock);

        std::cout << "Philosopher " << id << " is eating..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(duration(gen)));

        std::cout << "Philosopher " << id << " has finished eating." << std::endl;
    }
}
