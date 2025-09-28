// bug7.c
// Problem: Attempts to connect to localhost:9999
// Shows different messages for success/failure
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
    // Create TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket creation failed");
        return 1;
    }

    // Set up connection parameters (localhost:9999)
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(9999),
        .sin_addr.s_addr = inet_addr("127.0.0.1")
    };

    // Attempt connection (fixed if condition syntax)
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        // Connection failed - specific nginx message
        fprintf(stderr, "Can not connect to nginx (error: %s)\n", strerror(errno));
        close(sock);
        return 1;
    }

    // Connection succeeded
    printf("success\n");
    
    close(sock);
    return 0;
}