
#include"dram.h"
#define SRAM_CACHE_SETTING 0


uint64_t read64bits_dram(uint64_t paddr)
{
    if(SRAM_CACHE_SETTING == 1)
    {
        return 0x0;
    }
    uint64_t res = 0x0;
    for(int i = 0; i<8; i++){

    res += ((uint64_t)mm[paddr + i]) <<  i * 8;
        
    }


    return res;
}

void wirte64bits_dram(uint64_t paddr, uint64_t data)
{
    if(SRAM_CACHE_SETTING == 1)
    {
        return;
    }
    for(int i = 0; i<8; i++)
    {
        mm[paddr + i ] = (data >> (i *8)) & 0xff;
    }
    // mm[paddr] = 0x1;
    //&  && 的区别
    // mm[paddr + 0] = (data >> 0) & 0xff;
    // mm[paddr + 1] = (data >> 8) & 0xff;
    // mm[paddr + 2] = (data >> 16) & 0xff;
    // mm[paddr + 3] = (data >> 24) & 0xff;
    // mm[paddr + 4] = (data >> 32) & 0xff;
    // mm[paddr + 5] = (data >> 40) & 0xff;
    // mm[paddr + 6] = (data >> 48) & 0xff;
    // mm[paddr + 7] = (data >> 56) & 0xff;

}


void print_reg()
{
    printf("rax = %16lx\trbx = %16lx\trcx = %16lx\trdx = %16lx\n",
        regs.rax, regs.rbx, regs.rcx, regs.rdx);
    printf("rsi = %16lx\trdi = %16lx\trbp = %16lx\trsp = %16lx\n",
        regs.rsi, regs.rdi, regs.rbp, regs.rsp);
    printf("rip = %16lx\n", regs.rip);

}

//把rsp前面十个后面 十个内存中的数全部打印出来；
void print_stack()
{
           int n = 10;
           uint64_t * mm_ptr  = (uint64_t *)&mm[va2pa(regs.rsp)];
           mm_ptr -= 10;
           uint64_t start_stack = regs.rsp - 8 * 10;
           for(int i = 0; i < 2 * n ; ++i)
           {
            printf("0x%lx \t 0x%lx\t\t ", start_stack + i*8, *mm_ptr);
            mm_ptr += 1;
            
            if(start_stack+ i*8 == regs.rsp)
            {
            printf("<==");
            }
            printf("\n");

           }

}