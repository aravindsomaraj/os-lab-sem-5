#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
int sys_v2paddr(void)
{
  //Returns the physical address corresponding to a valid virtual address
  unsigned long int *va; unsigned long int *pa;

  if(argptr(1, (void*) &va, sizeof(*va)) < 0) {
        cprintf("Invalid virtual address pointer received to be read.\n");
        return -1;  // If the virtual address pointer don't lie withing the process address space
    }

  if(argptr(0, (void*) &pa, sizeof(*pa)) < 0) {
        cprintf("Invalid physical address pointer received to store to.\n");
        return -1;  // If the physical address pointer (where user wants to store the final answer) don't lie withing the process address space
  }
  argptr(1, (void *)&pa, sizeof(pa));

  if (*va > KERNBASE)
  {
    cprintf("ERROR : Can't access address in Kernel space!!!\n");
    return -1;
  }
  pte_t *pte;
  pde_t *pde;
  pde_t *pgtab;
  pde = &myproc()->pgdir[PDX(*va)];
  if (*pde & PTE_P)
  {
    pgtab = (pte_t *)P2V(PTE_ADDR(*pde));
  }
  else
  {
    cprintf("ERROR : Page table not found!!\n");
    return -1;
  }
  pte = &pgtab[PTX(*va)];
  if (*pte & PTE_P)
  {
    *pa = PTE_ADDR(*pte);
  }
  else
  {
    cprintf("ERROR : Page not found!!\n");
    return -1;
  }
  //Adding first 20 bits of pa and last 12 bits of va(which is obtained by & with 4095)
  *pa = *pa >> 12;
  *pa = *pa << 12;
  *pa = PTE_ADDR(*pte) | PTE_FLAGS(va);
  return 1;
}


