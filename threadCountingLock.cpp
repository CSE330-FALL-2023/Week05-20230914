#include <stdio.h>
#include <assert.h>
#include <pthread.h>

static volatile int counter = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *mythread(void *arg) {
    printf("%s: begin\n", (char *)arg);
    int i;
    for (i = 0; i < 1e7; i++) {
        // Lock the mutex before updating the counter
        pthread_mutex_lock(&counter_mutex);
        counter = counter + 1;
        // Unlock the mutex after updating the counter
        pthread_mutex_unlock(&counter_mutex);
    }
    printf("%s: done\n", (char *)arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    int rc;
    printf("main: begin (counter = %d)\n", counter);
    char arg1[] = "A";
    rc = pthread_create(&p1, NULL, mythread, arg1);
    assert(rc == 0);

    char arg2[] = "B";
    rc = pthread_create(&p2, NULL, mythread, arg2);
    assert(rc == 0);

    rc = pthread_join(p1, NULL);
    assert(rc == 0);
    rc = pthread_join(p2, NULL);
    assert(rc == 0);
    
    // Destroy the mutex
    pthread_mutex_destroy(&counter_mutex);

    printf("main: end (counter = %d)\n", counter);
    return 0;
}
