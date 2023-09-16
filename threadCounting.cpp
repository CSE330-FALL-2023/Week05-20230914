#include<stdio.h>
#include<assert.h>
#include<pthread.h>

static volatile int counter = 0;

// mythread()
// Simply adds 1 to counter repeatedly, in a loop
// No, this is not how you would add 10,000,000 to
// a counter, but it shows the problem nicely.
void *mythread(void *arg){
    printf("%s: begin\n", (char *) arg);
    int i;
    for (i = 0; i < 1e7; i++) {
        counter = counter + 1;
    }
    printf("%s: done\n", (char*) arg);
    return NULL;
}


int
main(int argc, char *argv[]) {
    pthread_t p1, p2;
    int rc;
    printf("main: begin (counter = %d)\n", counter);
    char arg1[] = "A"; // Create a character array for thread argument
    rc = pthread_create(&p1, NULL, mythread, arg1);
    assert(rc == 0);

    char arg2[] = "B"; // Create a character array for thread argument
    rc = pthread_create(&p2, NULL, mythread, arg2);
    assert(rc == 0);
    // join waits for the threads to finish

    rc = pthread_join(p1, NULL);
    assert(rc == 0);
    rc = pthread_join(p2, NULL);
    assert(rc == 0);
    printf("main: end (counter = %d)\n", counter);
    return 0;
}

