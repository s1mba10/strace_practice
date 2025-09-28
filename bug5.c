// bug5_fixed.c
// Create a file without read permission; reading should fail until read permission is added.
// On successful read, print "success".

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(void) {
    const char *path = "/tmp/secret";

    // Create/overwrite the file with write-only permission (----w---- = 0200)
    int fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0200);
    if (fd == -1) {
        return 1;
    }

    const char msg[] = "success";
    ssize_t written = write(fd, msg, sizeof(msg) - 1);
    close(fd);
    if (written != (ssize_t)(sizeof(msg) - 1)) {
        return 1;
    }

    // Try to open the file for reading — will fail with EACCES until read permission is added
    fd = open(path, O_RDONLY);
    if (fd == -1) {
        // Expected: Permission denied (strace will show open() = -1 EACCES)
        return 1;
    }

    // If we could open it for reading, read and print "success"
    char buf[sizeof(msg) - 1];
    ssize_t n = read(fd, buf, sizeof(buf));
    close(fd);
    if (n <= 0) {
        return 1;
    }

    if (write(STDOUT_FILENO, buf, n) != n) {
        return 1;
    }

    return 0;
}
