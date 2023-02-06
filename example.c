#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>
int main()
{
    char *str = "sfdp" ;
    char ptr[16] = "\0\0\0\0sfdpldsofof";
    int res = strstr(str,ptr);
    printf("%lu ",res) ;
    return 0 ;
}