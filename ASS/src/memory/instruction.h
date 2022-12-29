#ifndef ins_guard
#define ins_guard

#pragma once
#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<memory/dram.h>
#include"cpu/mmu.h"
#include"cpu/register.h"
#define NUM_INSTRTYPE 30



typedef enum OP
{
    push,
    pop,
    mov_reg_reg,
    mov_reg_mm,
    mov_mm_reg,
    CALL,
    ret,
    add_REG_REG

}op_t;
/* ����������������ö��
*/
typedef enum OD_TYPE
{
    ENPTY,
    IMM,
    REG,
    MM_IMM,
    MM_REG,
    MM_IMM_REG,
    MM_REG1_REG2,
    MM_IMM_REG1_REG2,
    MM_REG2_S,
    MM_IMM_REG2_S,
    MM_REG1_REG2_S,
    MM_IMM_REG1_REG2_S,
}od_type_t;

/*�������������Լ��ṹ��*/
typedef struct OD{
    od_type_t type;
    int64_t imm;
    int64_t scal;
    //�������ָ�룬�ֱ�ָ����ǼĴ��
    //����ŵ��ǼĴ����ĵ�ַ�� 
    uint64_t *reg1;
    uint64_t *reg2;
   
}od_t;

/*ָ��Ľṹ��  ����ָ��������������*/
typedef struct INSTRUCT_STRUCT
{
    op_t op;
    od_t src;
    od_t dst;
    char code[100];
}inst_t;


void instruction_cycle();

//���庯��ָ������
//����ģ��ÿһ�ֲ������ľ������������������30��
//���� ö����ÿһ�����Ͷ����Կ�����һ������Ҳ���ǿ��Գ�Ϊindex
typedef void (*handler_t) (uint64_t,uint64_t);
handler_t handler_table[NUM_INSTRTYPE];
/*  push,
    pop,
    mov_reg_reg,
    mov_reg_mm,
    mov_mm_reg,
    CALL,
    ret,
    add_REG_REG*/
void init_handler_table();
void add_REG_REG_handler(uint64_t src,uint64_t dst);
void mov_reg_reg_handler(uint64_t src,uint64_t dst);
void call_handler(uint64_t src, uint64_t dst);
void push_handler(uint64_t src, uint64_t dst);
void mov_reg_mm_handler(uint64_t src, uint64_t dst);
void mov_mm_reg_handler(uint64_t src, uint64_t dst);
void pop_handler(uint64_t src, uint64_t dst);
void ret_handler(uint64_t src, uint64_t dst);

  #endif