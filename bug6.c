// bug6.c
// Problem: Attempts to open 1500 file descriptors
// Outputs "success" only if all opens succeed
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define TOTAL_FDS 1500  // Intentional overcommit

int main() {
    int fds[TOTAL_FDS];

    for (int i = 0; i < TOTAL_FDS; i++) {
        fds[i] = open("/dev/null", O_RDONLY);
        if (fds[i] == -1) {
            // Fail immediately if any open fails
            return 1;
        }
    }

    // Only reach here if all opens succeeded
    write(STDOUT_FILENO, "success\n", 8);
    
    // Intentional descriptor leak (no close)
    return 0;
}