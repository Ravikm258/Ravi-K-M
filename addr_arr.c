#include <stdio.h>
#include <stdint.h>

int main()
{
    int a[3][5] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15}};
    int *rp = a[1];
    for(uint32_t i = 0 ; i < 10 ; i++)
        printf("%d ",*(rp+i));

    return 0;
}