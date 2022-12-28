#include"instruction.h"
#include"cpu/mmu.h"
#include"cpu/register.h"

static uint64_t decode_od(od_t od)
{
    if (od.type == IMM)
    {
        //����������
        return *((uint64_t*)&od.imm);
    }
    else if ( od.type == REG )
    {   
        //���ص��ǼĴ����ĵ�ַ����ָ���ֵ
        return (uint64_t)od.reg1;
    }
    else
    {
        //mm
        uint64_t vaddr = 0;
        
        if(od.type == MM_IMM)
        {
            //����������
            vaddr = od.imm;
        }
        else if (od.type == MM_REG)
        {
            //���ص���ָ��ָ��ļĴ����а���ָ���ڴ��ֵ
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
        //���ص��������ַ 
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


//�����ǼĴ����ĵ�ַ��
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
    //push�Ĺ����� ���Ĵ����������ֵд���ڴ��С�
    regs.rsp -=0x8;
    wirte64bits_dram(va2pa(regs.rsp),*(uint64_t*)src);
    regs.rip = regs.rip + sizeof(inst_t);
}

void mov_reg_mm_handler(uint64_t src, uint64_t dst)
{
    //���Ĵ����е�ֵд���ڴ�
    wirte64bits_dram(va2pa(dst),*(uint64_t*)src);
    regs.rip = regs.rip + sizeof(inst_t);
    

}
void mov_mm_reg_handler(uint64_t src, uint64_t dst)
{
    //���ڴ��е�ֵд��Ĵ���
    wirte64bits_dram(dst,read64bits_dram(va2pa(src)));
    regs.rip = regs.rip + sizeof(inst_t);


}


//callָ���ʵ�֣�rip �д�ŵ���ָ��ĵ�ַ��rsp�д�ŵ���ջ���ĵ�ַ

//����ջ����С8���ֽڣ����������call��һ��ָ��ĵ�ַ��Ȼ��rip��ֵ�ı��
//Ŀ�꺯���Ŀ�ʼָ���ַ,�����е�Ŀ�꺯����ret ָ��ʱ������ջ������ʱrip��ŵ���ջ���д�ŵĵ�ַ��
//call��һ���ĺ�����
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



