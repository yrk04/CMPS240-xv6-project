#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf(1, "Usage: callcount <syscall_id>\n");
    exit();
  }

  int id = atoi(argv[1]);
  int count = syscallcount(id);

  if(count >= 0){
    printf(1, "System call %d was called %d times\n", id, count);
  } else {
    printf(1, "Invalid syscall ID\n");
  }

  exit();
}

