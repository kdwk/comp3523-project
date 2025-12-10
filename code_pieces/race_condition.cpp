#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

std::shared_ptr<int> counter = 0;

void incrementCounter(int times) {
    for (int i = 0; i < times; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        counter++;
    }
}

int main() {
    const int numThreads = 10;
    const int incrementsPerThread = 1000;

    std::vector<std::thread> threads;

    // Create threads
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(incrementCounter, incrementsPerThread));
    }

    // Join threads
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
