// Copyright 2025 Agnieszka

#include <pthread.h>
#include <iostream>

pthread_mutex_t writeMutex = PTHREAD_MUTEX_INITIALIZER;
int NUMBER_OF_PHILOSOPHERS;
int INDEX_OF_FIRST_FORK = 0;
pthread_mutex_t* forks;

struct Philosopher {
    int id;
    int leftForkId;
    int rightForkId;
};

void* think(void *arg) {
    auto* philosopher = static_cast<Philosopher*>(arg);

    pthread_mutex_lock(&writeMutex);
    std::cout << "Philosopher " << philosopher->id + 1
        << " - " << "thinking... - left fork id: " << philosopher->leftForkId
        << " right fork id: "<< philosopher->rightForkId << std::endl;
    pthread_mutex_unlock(&writeMutex);
    return nullptr;
}

int calculateRightForkId(int philosopherId) {
    int indexOfLastPhilosopher = NUMBER_OF_PHILOSOPHERS - 1;
    if (philosopherId == indexOfLastPhilosopher) {
        return INDEX_OF_FIRST_FORK;
    } else {
        return philosopherId + 1;
    }
}

int main(int argc, char* argv[]) {
    NUMBER_OF_PHILOSOPHERS = std::stoi(argv[1]);
    pthread_t threads[NUMBER_OF_PHILOSOPHERS];
    Philosopher philosophers[NUMBER_OF_PHILOSOPHERS];
    forks = new pthread_mutex_t[NUMBER_OF_PHILOSOPHERS];

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], nullptr);
    }

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        philosophers[i].id = i;
        philosophers[i].leftForkId = i;
        philosophers[i].rightForkId = calculateRightForkId(philosophers[i].id);
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
