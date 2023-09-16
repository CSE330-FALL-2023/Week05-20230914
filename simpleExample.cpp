#include <stdio.h>
#include <pthread.h>
#include <assert.h>

void *mythread(void *arg) {
    printf("%s\n", (char *)arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    int rc;
    printf("main: begin\n");
    
    char arg1[] = "A"; // Create a character array for thread argument
    rc = pthread_create(&p1, NULL, mythread, arg1);
    assert(rc == 0);
    
    char arg2[] = "B"; // Create a character array for thread argument
    rc = pthread_create(&p2, NULL, mythread, arg2);
    assert(rc == 0);
    
    // Join waits for the threads to finish
    rc = pthread_join(p1, NULL);
    assert(rc == 0);
    rc = pthread_join(p2, NULL);
    assert(rc == 0);
    
    printf("main: end\n");
    return 0;
}
