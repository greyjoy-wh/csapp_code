#include "memory/instruction.h"
#include "disk/code.h"
#include "memory/dram.h"
#include "cpu/register.h"
#include "disk/elf.h"
#include "cpu/mmu.h"
#include<stdio.h>

int main(){
    init_handler_table();
    regs.rax = 0x12340000;
    regs.rbx = 0x555555555190;
    regs.rcx = 0x555555555190;
    regs.rdx = 0xabcd;
    regs.rsi = 0x7fffffffe018;
    regs.rdi = 0x1;
    regs.rbp = 0x7fffffffdf20;
    regs.rsp = 0x7fffffffdf00;
    regs.rip = (uint64_t)&program[11];

    wirte64bits_dram(va2pa(0x7fffffffdf00),0x0);
    wirte64bits_dram(va2pa(0x7fffffffdf08),0x12340000);
    wirte64bits_dram(va2pa(0x7fffffffdf10),0xabcd);
    wirte64bits_dram(va2pa(0x7fffffffdf18),0x0);
    wirte64bits_dram(va2pa(0x7fffffffdf20),0x0);


    // uint64_t pa = va2pa(0x7fffffffdf08);
    // printf("%16lx\n", 
    //       *((uint64_t *)(&mm[pa])));
   
    //run
      print_reg();
        print_stack();
    for(int i = 0; i < 5; i++){
        instruction_cycle(); 
        print_reg();
        print_stack();
    }



    //verify
    int match = 1;

    match = match && (regs.rax == 0x1234abcd);
    match = match && (regs.rbx == 0x555555555190);
    match = match && (regs.rcx == 0x555555555190);
    match = match && (regs.rdx == 0x12340000);
    match = match && (regs.rsi == 0xabcd);
    match = match && (regs.rdi == 0x12340000);
    match = match && (regs.rbp == 0x7fffffffdf20);
    match = match && (regs.rsp == 0x7fffffffdf00);

    if(match)
    {
        printf("register is right\n");
    }else{
        printf("register is wrong\n");
    }

    match = match && (mm[va2pa(0x7fffffffdf00)] == 0x0);
    match = match && (mm[va2pa(0x7fffffffdf08)] == 0x12340000);
    match = match && (mm[va2pa(0x7fffffffdf10)] == 0xabcd);
    match = match && (mm[va2pa(0x7fffffffdf18)] == 0x1234abcd);
    match = match && (mm[va2pa(0x7fffffffdf20)] == 0x0);
    
    if(match)
    {
        printf("memory is right\n");
    }
    else
    {
        printf("memory is wrong\n");
    }

    return 0;
}
