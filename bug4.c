#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>

int main() {
    // Attempt to load the shared library
    void* handle = dlopen("libnonexistent.so", RTLD_LAZY);
    
    if (!handle) {
        // Write debug message to fd=4 (visible in strace)
        const char* debug_msg = "You need to create this lib...\n";
        write(4, debug_msg, strlen(debug_msg));
        
        // Write error to stderr (fd=2)
        const char* error = dlerror();
        return 1;
    }
    
    // Library loaded successfully - close it
    dlclose(handle);
    
    // Print success message
    printf("success\n");
    return 0;
}