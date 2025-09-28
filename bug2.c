#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Tries to create file in root directory without permissions
    // You should not be root to imitate a problem
    int fd = open("/root/testfile", O_CREAT|O_WRONLY, 0644);
    if (fd < 0) return 1;  // Fails silently due to permission denied
    
    close(fd);
    printf("success\n");
    return 0;
}
