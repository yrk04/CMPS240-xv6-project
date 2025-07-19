#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main() {
  int fd = open("myfile.txt", O_CREATE | O_RDWR);
  char buf[512];
  for (int i = 0; i < sizeof(buf); i++)
    buf[i] = 'X';

  for (int i = 0; i < 10; i++) 
    write(fd, buf, sizeof(buf));

  close(fd);
  printf(1, "Calling getextents:\n");
  getextents("myfile.txt");
  exit();
}

