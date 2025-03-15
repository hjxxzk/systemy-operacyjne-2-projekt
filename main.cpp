// Copyright 2025 Agnieszka

#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <vector>

pthread_mutex_t writeMutex = PTHREAD_MUTEX_INITIALIZER;
int NUMBER_OF_PHILOSOPHERS;
int INDEX_OF_FIRST_FORK = 0;
constexpr int TIME_OF_AN_ACTION = 6;
pthread_mutex_t *forks;

struct Philosopher {
    int id;
    int leftForkId;
    int rightForkId;
    bool isThinking;
};

void think(Philosopher *philosopher) {
    philosopher->isThinking = true;
    sleep(TIME_OF_AN_ACTION);
}

void pickUpTheForks(const Philosopher *philosopher) {
    pthread_mutex_lock(&forks[philosopher->leftForkId]);
    pthread_mutex_lock(&forks[philosopher->rightForkId]);
}

void eat(Philosopher *philosopher) {
    philosopher->isThinking = false;
    sleep(TIME_OF_AN_ACTION);
}

void putDownTheForks(const Philosopher *philosopher) {
    pthread_mutex_unlock(&forks[philosopher->rightForkId]);
    pthread_mutex_unlock(&forks[philosopher->leftForkId]);
}

void *feast(void *arg) {
    auto *philosopher = static_cast<Philosopher *>(arg);

    while (true) {
        think(philosopher);
        pickUpTheForks(philosopher);
        eat(philosopher);
        putDownTheForks(philosopher);
    }
}

int calculateRightForkId(int philosopherId) {
    int indexOfLastPhilosopher = NUMBER_OF_PHILOSOPHERS - 1;
    if (philosopherId == indexOfLastPhilosopher) {
        return INDEX_OF_FIRST_FORK;
    } else {
        return philosopherId + 1;
    }
}

void displayStatus(const std::vector<Philosopher> &philosophers) {
    for (const auto &philosopher : philosophers) {
        std::cout << "Philosopher " << philosopher.id + 1
                << " is " << (philosopher.isThinking ? "thinking" : "eating")
                << "..." << std::endl;
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    NUMBER_OF_PHILOSOPHERS = std::stoi(argv[1]);
    pthread_t threads[NUMBER_OF_PHILOSOPHERS];
    std::vector<Philosopher> philosophers(NUMBER_OF_PHILOSOPHERS);
    forks = new pthread_mutex_t[NUMBER_OF_PHILOSOPHERS];

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], nullptr);
    }

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        philosophers[i].id = i;
        philosophers[i].leftForkId = i;
        philosophers[i].rightForkId = calculateRightForkId(philosophers[i].id);
        pthread_create(&threads[i], nullptr, feast, &philosophers[i]);
    }

    while (true) {
        displayStatus(philosophers);
        sleep(TIME_OF_AN_ACTION);
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
