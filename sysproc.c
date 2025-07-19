#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "fs.h"
#include "stat.h"
#include "file.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
extern int syscall_counter[];

int sys_resetcallcount(void) {
  for (int i = 0; i < NSYSCALLS; i++) {
    syscall_counter[i] = 0;
  }
  return 0;
}

int sys_shutdown(void){
  outw(0xB004, 0x0|0x2000);
  outw(0x604, 0x0|0x2000);
  return 0;
}

int sys_getextents(void) {
  char *path;
  if (argstr(0, &path) < 0)
    return -1;

  struct inode *ip;
  begin_op();
  ip = namei(path); 
  if(ip == 0){
    end_op();
    return -1;
  }

  ilock(ip);
  if(ip->type != T_EXTENT){
    cprintf("Not an extent file\n");
    iunlockput(ip);
    end_op();
    return -1;
  }

  for(int i = 0; i < MAX_EXTENTS; i++){
    if(ip->extents[i].length == 0)
      break;
    cprintf("Extent %d: start=%d, len=%d\n", i, ip->extents[i].start, ip->extents[i].length);
  }

  iunlockput(ip);
  end_op();
  return 0;
}

