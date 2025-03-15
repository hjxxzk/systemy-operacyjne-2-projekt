// Copyright 2025 Agnieszka

#include <pthread.h>
#include <iostream>

struct Philosopher {
    int id;
};

void* think(void *arg) {
    auto* philosopher = static_cast<Philosopher*>(arg);
    std::cout << "Philosopher " << philosopher->id
        << " - " << "thinking...\n" << std::endl;
    return nullptr;
}

int main(int argc, char* argv[]) {
    const int NUMBER_OF_PHILOSOPHERS = std::stoi(argv[1]);
    pthread_t threads[NUMBER_OF_PHILOSOPHERS];
    Philosopher philosophers[NUMBER_OF_PHILOSOPHERS];

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        philosophers[i].id = i + 1;
        pthread_create(&threads[i], nullptr, think, &philosophers[i]);
    }

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        pthread_join(threads[i], nullptr);
    }

    return 0;
}

