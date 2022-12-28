#include <stdlib.h>
#include "memory/instruction.h"
#include "cpu/register.h"
#include "disk/elf.h"


// inst_t program[INST_LEN] = {
//     {
//         MOV,
//         { REG, 0, 0,(uint64_t)&regs.rax,NULL},
//         { REG, 0, 0,(uint64_t)&regs.rbx,NULL},
//         "mov rax rbx"
//     }

// };

inst_t program[INST_LEN] = 
{
    { push, 
    {REG, 0, 0, &regs.rbp, NULL}, 
    {ENPTY, 0, 0, NULL, NULL},
    "push  \%rbp"
     },

    { mov_reg_reg, 
    {REG, 0, 0, &regs.rsp, NULL}, 
    {REG, 0, 0, &regs.rbp, NULL},
    "mov \%rsp, \%rbp"
    },

    { mov_reg_mm, 
    {REG, 0, 0, &regs.rdi, NULL}, 
    {MM_IMM_REG, -0x18, 0, &regs.rbp, NULL},
    "mov \%rdi, -0x18(\%rbp)"
    },

    { mov_reg_mm, 
    {REG, 0, 0, &regs.rsi, NULL}, 
    {MM_IMM_REG, -0x20, 0, &regs.rbp, NULL},
    "mov \%rsi, -0x20(\%rbp)"
    },

    { mov_mm_reg, 
    {MM_IMM_REG, -0x18, 0, &regs.rbp, NULL},
    {REG, 0, 0, &regs.rdx, NULL}, 
    "mov -0x18(\%rbp) \%rdx"
    },

    { mov_mm_reg, 
    { MM_IMM_REG, -0x20, 0, &regs.rbp, NULL},
    { REG, 0, 0, &regs.rax, NULL}, 
    "mov -0x20(\%rbp) \%rax"
    },
    
    { add_REG_REG,
    {REG, 0, 0, &regs.rdx, NULL},
    {REG, 0, 0, &regs.rax, NULL},
    "add \%rdx, \%rax"
    },

     { mov_reg_mm, 
    {REG, 0, 0, &regs.rax, NULL}, 
    {MM_IMM_REG, -0x8, 0, &regs.rbp, NULL},
    "mov \%rax, -0x8(\%rbp)"
    },

     { mov_mm_reg, 
    { MM_IMM_REG, -0x8, 0, &regs.rbp, NULL},
    { REG, 0, 0, &regs.rax, NULL}, 
    "mov -0x8(\%rbp) \%rax"
    },

    {pop, 
    {REG, 0, 0, &regs.rbp,NULL},
    {ENPTY, 0, 0, NULL, NULL},
    "pop \%rbp"
    },

     {ret,
    {ENPTY, 0, 0, NULL, NULL},
    {ENPTY, 0, 0, NULL, NULL},
    "ret"
    },

     { mov_reg_reg, 
    {REG, 0, 0, &regs.rdx, NULL}, 
    {REG, 0, 0, &regs.rsi, NULL},
    "mov \%rdx, \%rsi"
    },

     { mov_reg_reg, 
    {REG, 0, 0, &regs.rax, NULL}, 
    {REG, 0, 0, &regs.rdi, NULL},
    "mov \%rax, \%rdi"
    },

     {CALL, 
    {IMM, (uint64_t)(&program[0]), 0, NULL, NULL}, 
    {ENPTY, 0, 0, NULL, NULL},
    "call <add>"
    },

     { mov_reg_mm, 
    {REG, 0, 0, &regs.rax, NULL}, 
    {MM_IMM_REG, -0x8, 0, &regs.rbp, NULL},
    "mov \%rax, -0x8(\%rbp)"
    }
};
