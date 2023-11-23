#include <iostream>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t condition_variable;

void* worker(void* arg) {
    int *i = (int *) arg;

    pthread_mutex_lock(&mutex);

    pthread_cond_wait(&condition_variable, &mutex);

    std::cout<<"Value: "<<++(*i)<<" in Thread(pid): "<<getpid()<<std::endl;

    pthread_cond_signal(&condition_variable);

    pthread_mutex_unlock(&mutex);

    pthread_exit(nullptr);
}

int main() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&condition_variable, nullptr);

    pthread_t thread1, thread2, thread3;

    int par = 0;

    pthread_create(&thread1, nullptr, worker, &par);
    pthread_create(&thread2, nullptr, worker, &par);
    pthread_create(&thread3, nullptr, worker, &par);

    sleep(1);
    pthread_cond_signal(&condition_variable);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);
    pthread_join(thread3, nullptr);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition_variable);
    
    sleep(2);
    return 0;
}