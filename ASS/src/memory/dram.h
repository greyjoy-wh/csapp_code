#ifndef dra_guard
#define dra_guard
#include<stdint.h>
#include<stdio.h>
#include "cpu/register.h"
#include "cpu/mmu.h"
#define MM_LEN 1000
uint8_t mm[MM_LEN];

uint64_t read64bits_dram(uint64_t paddr);
void wirte64bits_dram(uint64_t paddr, uint64_t data);
//virtual address
//physical address
void print_reg();
void print_stack();
#endif 