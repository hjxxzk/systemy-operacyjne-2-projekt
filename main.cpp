// Copyright 2025 Agnieszka

#include <pthread.h>
#include <iostream>

pthread_mutex_t writeMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t* forks;

struct Philosopher {
    int id;
};

void* think(void *arg) {
    auto* philosopher = static_cast<Philosopher*>(arg);

    pthread_mutex_lock(&writeMutex);
    std::cout << "Philosopher " << philosopher->id
        << " - " << "thinking..." << std::endl;
    pthread_mutex_unlock(&writeMutex);
    return nullptr;
}

int main(int argc, char* argv[]) {
    const int NUMBER_OF_PHILOSOPHERS = std::stoi(argv[1]);
    pthread_t threads[NUMBER_OF_PHILOSOPHERS];
    Philosopher philosophers[NUMBER_OF_PHILOSOPHERS];
    forks = new pthread_mutex_t[NUMBER_OF_PHILOSOPHERS];

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], nullptr);
    }

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        philosophers[i].id = i + 1;
        pthread_create(&threads[i], nullptr, think, &philosophers[i]);
    }

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        pthread_join(threads[i], nullptr);
    }

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
        pthread_mutex_destroy(&forks[i]);
    }

    pthread_mutex_destroy(&writeMutex);
    delete[] forks;
    return 0;
}
