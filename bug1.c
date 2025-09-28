#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Program tries to open non-existent file
    // To solve this problem, create file
    int fd = open("nonexistent-file.txt", O_RDONLY);
    if (fd < 0) return 1;  // Fails silently if file doesn't exist
    
    close(fd);
    printf("success\n");
    return 0;
}
