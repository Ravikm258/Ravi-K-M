#include<stdio.h>
#include<stdint.h>
uint8_t swap(uint8_t num,int s)
{
    uint8_t i,sn;
    sn=((num>>s)&0x0F);
    
    return sn;
}
int main()
{
    uint8_t f,s;
    uint64_t num=0x18F6000000000000;
    // f= swap(num,4);
    // s = swap(num,0);
    // s=s<<4;
    // printf("%x\n",f|s);


    uint64_t res=(num);
    printf("%x",res);
}