#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf(2, "Usage: mkextent filename [text]\n");
        exit();
    }
    
    int fd = open(argv[1], O_CREATE | O_RDWR | O_EXTENT);
    if(fd < 0) {
        printf(2, "Failed to create extent file %s\n", argv[1]);
        exit();
    }
    
    if(argc > 2) {
        // Write the provided text
        write(fd, argv[2], strlen(argv[2]));
        write(fd, "\n", 1);
    }
    
    close(fd);
    printf(1, "Created extent file: %s\n", argv[1]);
    getextents(argv[1]);
    exit();
}
