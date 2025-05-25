#include "Table.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_philosophers>" << std::endl;
        return 1;
    }
    
    int numPhilosophers = std::stoi(argv[1]);
    Table table(numPhilosophers);
    
    std::cout << "Starting dinner for " << numPhilosophers << " philosophers." << std::endl;
    table.startDinner();
    
    std::this_thread::sleep_for(std::chrono::seconds(30)); // Let philosophers run for 30 seconds
    
    return 0;
}
