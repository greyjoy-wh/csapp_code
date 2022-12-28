#include"instruction.h"
#include"cpu/mmu.h"
#include"cpu/register.h"

static uint64_t decode_od(od_t od)
{
    if (od.type == IMM)
    {
        //返回立即数
        return *((uint64_t*)&od.imm);
    }
    else if ( od.type == REG )
    {   
        //返回的是寄存器的地址，即指针的值
        return (uint64_t)od.reg1;
    }
    else
    {
        //mm
        uint64_t vaddr = 0;
        
        if(od.type == MM_IMM)
        {
            //返回立即数
            vaddr = od.imm;
        }
        else if (od.type == MM_REG)
        {
            //返回的是指针指向的寄存器中包含指向内存的值
            vaddr =  *(od.reg1);
        }
        else if (od.type == MM_IMM_REG)
        {
           
            vaddr =  *(od.reg1) + od.imm;
        }
        else if (od.type == MM_REG1_REG2)
        {
            
            vaddr =  *(od.reg1) + *(od.reg2);
        }
        else if (od.type == MM_IMM_REG1_REG2)
        {
           
            vaddr =  od.imm + *(od.reg1) + *(od.reg2) ;
        }
        else if (od.type == MM_REG2_S)
        {
            
            vaddr =  (*(od.reg2))* od.scal;
        }
         else if (od.type == MM_IMM_REG2_S)
        {
            
            vaddr =  od.imm + (*(od.reg2))* od.scal;
        }
        else if (od.type == MM_REG1_REG2_S)
        {
           
            vaddr =  *(od.reg1) + (*(od.reg2))* od.scal;
        }
         else if (od.type == MM_IMM_REG1_REG2_S)
        {
            
            vaddr = od.imm + *(od.reg1) + (*(od.reg2))* od.scal;
        }
        //返回的是物理地址 
        return vaddr;
    }
}


void instruction_cycle()
{
    inst_t *instr = (inst_t*)regs.rip;
    uint64_t src = decode_od(instr->src);
    uint64_t dst = decode_od(instr->dst);
    
    handler_t handler = handler_table[instr->op];
    handler(src,dst);
    printf("     %s\n", instr-> code);
}


//参数是寄存器的地址。
void add_REG_REG_handler(uint64_t src,uint64_t dst)
{
    *(uint64_t*)dst = *(uint64_t*)dst + *(uint64_t*)src; 
    regs.rip = regs.rip + sizeof(inst_t);
    return;
}

void mov_reg_reg_handler(uint64_t src,uint64_t dst)
{
     *(uint64_t*)dst =*(uint64_t*)src; 
     regs.rip = regs.rip + sizeof(inst_t);
}
void push_handler(uint64_t src, uint64_t dst)
{
    //push的功能是 将寄存器器储存的值写入内存中。
    regs.rsp -=0x8;
    wirte64bits_dram(va2pa(regs.rsp),*(uint64_t*)src);
    regs.rip = regs.rip + sizeof(inst_t);
}

void mov_reg_mm_handler(uint64_t src, uint64_t dst)
{
    //将寄存器中的值写入内存
    wirte64bits_dram(va2pa(dst),*(uint64_t*)src);
    regs.rip = regs.rip + sizeof(inst_t);
    

}
void mov_mm_reg_handler(uint64_t src, uint64_t dst)
{
    //将内存中的值写入寄存器
    wirte64bits_dram(dst,read64bits_dram(va2pa(src)));
    regs.rip = regs.rip + sizeof(inst_t);


}


//call指令的实现：rip 中存放的是指令的地址，rsp中存放的是栈顶的地址

//先让栈顶减小8个字节，放入的是下call下一个指令的地址，然后将rip的值改变成
//目标函数的开始指令地址,当运行到目标函数的ret 指令时，返回栈顶，此时rip存放的是栈顶中存放的地址，
//call下一个的函数。
void call_handler(uint64_t src, uint64_t dst)
{
    regs.rsp -= 8;

    wirte64bits_dram(va2pa(regs.rsp),regs.rip + sizeof(inst_t));

    regs.rip = src;
}

void init_handler_table(){
    handler_table[add_REG_REG] = &add_REG_REG_handler;
    handler_table[mov_reg_reg] = &mov_reg_reg_handler;
    handler_table[mov_reg_mm] = &mov_reg_mm_handler;
    handler_table[mov_mm_reg] = &mov_mm_reg_handler;
    handler_table[CALL] = &call_handler;
    handler_table[push] = &push_handler;

}



