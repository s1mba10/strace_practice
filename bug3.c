// bug3.c
// Problem: Infinite loop unless NO_LOOP environment variable is set
// ltrace will show getenv() call and different behavior based on env
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    // Check environment variable
    char* no_loop = getenv("NO_LOOP");
    
    if (no_loop != NULL) {
        printf("success\n");
        return 0;
    }

    // Original infinite loop behavior
    while (1) {
        sleep(1);
    }
    
    return 0;
}