#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#include "trace.h"
#include "syscall.h"



int current_trace_state = 0;

int system_call_count[TOT] = {0};


static char *syscall_name[] = {

[SYS_chdir]    "sys_chdir",
[SYS_close]    "sys_close",
[SYS_dup]      "sys_dup",
[SYS_exec]     "sys_exec",
[SYS_exit]     "sys_exit",
[SYS_fork]     "sys_fork",
[SYS_fstat]    "sys_fstat",
[SYS_getpid]   "sys_getpid",
[SYS_getyear]    "sys_getyear",
[SYS_kill]     "sys_kill",
[SYS_link]     "sys_link",
[SYS_mkdir]    "sys_mkdir",
[SYS_mknod]    "sys_mknod",
[SYS_open]     "sys_open",
[SYS_pipe]     "sys_pipe",
[SYS_print_count] "sys_print_count",
[SYS_read]     "sys_read",
[SYS_sbrk]     "sys_sbrk",
[SYS_sleep]    "sys_sleep",
[SYS_toggle]   "sys_toggle",
[SYS_unlink]   "sys_unlink",
[SYS_uptime]   "sys_uptime",
[SYS_wait]     "sys_wait",
[SYS_write]    "sys_write",
[SYS_ps]       "sys_ps",
[SYS_add]      "sys_add"
};


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

int 
sys_getyear(void) {
  return 2003;
}


int 
sys_toggle() {    
  if (current_trace_state == TRACE_ON) {
    current_trace_state = TRACE_OFF;
  } else {
    current_trace_state = TRACE_ON;
    for (int i = 0; i < TOT; i++) {
      system_call_count[i] = 0;
    } 
  }
  
  if (current_trace_state == TRACE_ON)
  cprintf("Toggle is ON \n");
  
  if (current_trace_state == TRACE_OFF)
  cprintf("Toggle is OFF \n");
  
  return 0;
}

int 
sys_print_count() {
  int z = 0;
  for (int i = 0; i < TOT; i++) {
    if (system_call_count[i] > 0) {
      cprintf("%s %d\n", syscall_name[i], system_call_count[i]);
      z += system_call_count[i];
    }
  }
  return z; // z is the count of all the system calls encountered
}

int 
sys_ps() {
  return ps();
}

int
sys_add(void) {
    int a, b;
    argint(0, &a);
    argint(1, &b);
    return a + b;
}





