// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = { "sh", 0 };

void newlinekiller(char *s){
  int i = 0;
  while(s[i] != '\0'){
    if(s[i] == '\n'){
      s[i] = '\0';
    }
    i++;
  }
  return;
}

void login(){
  char username[32];
  char password[32];
for(int i = 0; i < 3 ; i++){
  if(i > 0){
    printf(1, "Retry login \n");
  }
  printf(1, "Username: ");
  gets(username, sizeof(username));
  newlinekiller(username);
  printf(1, "Password: ");
  gets(password, sizeof(password));
  newlinekiller(password);
  
  if(strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0){
    printf(1, "Welcome!\n");
    return;
  } else {
    printf(1, "Invalid credentials.\n");
  }
 }
  
  printf(1, "Too many failed attempts.");
  shutdown();
}

int
main(void)
{
  int pid, wpid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr
  
  login();
  for(;;){
    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
