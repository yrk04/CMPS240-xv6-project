// reset.c
#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
  resetcallcount();
  printf(1, "System call counters have been reset.\n");
  exit();
}
