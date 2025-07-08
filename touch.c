#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf(2, "Usage: touch file...\n");
    exit();
  }

  for(int i = 1; i < argc; i++){
    int fd = open(argv[i], O_WRONLY | O_CREATE);
    if(fd >= 0)
      close(fd);
    else
      printf(2, "touch: cannot open %s\n", argv[i]);
  }

  exit();
}

