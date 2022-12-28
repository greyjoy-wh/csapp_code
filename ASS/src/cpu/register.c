#include"register.h"


int main(){
 
 
 
    regs.rax =   0x1234abcd5678aaff;
    printf("eax: %08x\n", cpu.eax);
    printf("al: %02x\n", cpu.al);
    printf("ah: %02x\n", cpu.ah);



    return 0; 
}