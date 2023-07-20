#include "types.h"
#include "user.h"
#include "syscall.h"
#include "memlayout.h"

void getResults(addr_t *va) {
    addr_t pa;  // Physicall address to store the final answer
    printf(1, "Virtual Address: 0x%x\n", va);
    int val = v2paddr(&pa, va);
    if(val == 0) {   // Success
        printf(1, "Physical Address: 0x%x\n", pa);
    }
    printf(1, "\n");
}

int thirdT = 99999;  // A test global variable

int main(int argc, char *argv[])
{
    //Test #1
    int firstT = 0;
    addr_t* va = (addr_t*)(&firstT);

    getResults(va);

    // Test #2
    addr_t* secondT = (void*)(KERNBASE + 0x555);
    va = secondT;
    getResults(va);

    // Test #3
    va = (addr_t*)(&thirdT);
    getResults(va);

    exit();
}