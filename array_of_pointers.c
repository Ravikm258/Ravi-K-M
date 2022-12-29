#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>

int main()
{
    uint8_t buffer_0[64];
    uint8_t buffer_1[64];
    uint8_t buffer_2[64];
    uint8_t buffer_3[64];
    uint8_t *ap[4] = {buffer_0,buffer_1,buffer_2,buffer_3};
    ap[0] = "abcdgrtgtrgtrrrexwerectrcgtrhtrnnytnytntnyty";
    ap[1] = "lj2bnknkv4pbntkvnwltkng4o5ojt2549h5o4hihvibvvivjo5hjihvpoihg";
    scanf("%s",ap[2]);
    printf("%u ",*(&ap[0])+0);
    printf("%u ",*(&ap[0])+1);
    printf("%u ",*(&ap[0])+2);
    printf("%u ",*(&ap[0])+3);
    printf("\n%s ",ap[1]);
    printf("\n%s ",ap[2]);
    //printf("\n%p ",&(ap[2]));




}