#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

// Converts integer i (0..99) to decimal string and writes into buf.
// Returns pointer to the end of the string (so you can append).
char* itoa(char *buf, int i) {
    if(i >= 10) {
        *buf++ = '0' + (i / 10);
        *buf++ = '0' + (i % 10);
    } else {
        *buf++ = '0' + i;
    }
    *buf = '\0';
    return buf;
}

int main() {
    char fname[16];
    int fd;
    // Create 20 small files
    for (int i = 1; i <= 20; i++) {
        fname[0] = 'a';
        char *p = itoa(fname+1, i); // fname = "aXX"
        strcpy(p, ".ext");          // append ".ext"
        fd = open(fname, O_CREATE | O_RDWR | O_EXTENT);
        if (fd >= 0) {
            write(fd, fname, strlen(fname));
            close(fd);
        }
    }
    // Delete every other file
    for (int i = 2; i <= 20; i += 2) {
        fname[0] = 'a';
        char *p = itoa(fname+1, i);
        strcpy(p, ".ext");
        unlink(fname);
    }
    // Create big.ext and so on...
    // ...
    exit();
}

