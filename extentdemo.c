#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main() {
    char fname[16];
    int fd, i, j;
    int blocks_per_file = 5;
    int num_files = 6;       // 6 files * 5 blocks = 30 blocks

    // Step 1: Create 6 files (a1.ext ... a6.ext), each 5 blocks
    for (i = 1; i <= num_files; i++) {
        fname[0] = 'a';
        fname[1] = '0' + i;
        strcpy(fname+2, ".ext");
        fd = open(fname, O_CREATE | O_RDWR | O_EXTENT);
        if (fd >= 0) {
            char buf[512];
            memset(buf, 'A'+i, sizeof(buf));
            for (j = 0; j < blocks_per_file; j++)
                write(fd, buf, sizeof(buf));
            close(fd);
        }
    }

    // Step 2: Delete every other file (a2.ext, a4.ext, a6.ext)
    for (i = 2; i <= num_files; i += 2) {
        fname[0] = 'a';
        fname[1] = '0' + i;
        strcpy(fname+2, ".ext");
        unlink(fname);
    }

    // Step 3: Create "big.ext" to fill 3 holes of 5 blocks (total 15 blocks)
    fd = open("big.ext", O_CREATE | O_RDWR | O_EXTENT);
    if (fd >= 0) {
        char buf[512];
        memset(buf, 'Z', sizeof(buf));
        for (i = 0; i < 15; i++)
            write(fd, buf, sizeof(buf));
        close(fd);
    }

    // Step 4: Print extents for "big.ext"
    getextents("big.ext");

    exit();
}

