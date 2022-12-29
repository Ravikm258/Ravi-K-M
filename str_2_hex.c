#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>

// uint32_t lafm_utils_decode_from_hex(uint8_t * dst, uint32_t dst_len, uint32_t dst_start_pos, uint8_t * src,
//     uint32_t src_len, uint32_t src_start_pos, uint32_t bytes_to_decode)


uint32_t lafm_utils_decode_from_hex(uint8_t * dst, uint32_t dst_len, uint32_t dst_start_pos, uint8_t * src,
    uint32_t src_len, uint32_t src_start_pos, uint32_t bytes_to_decode)
 {
    uint32_t i=0,j=0;
    uint8_t val=0,val2=0,val3=0;
    int m=dst_start_pos;
    for(i=src_start_pos;i<src_len-1;i+=2)
    {

            val=src[i];
            val2=src[i+1];
            if(val >= 'A' && val <= 'F')
            {
                val=(val-65)+10;
            }

            if(val2 >='A' && val2 <='F')
            {
                val2=(val2-65)+10;
            }

            if(val >= 'a' && val <= 'f')
            {
                val=(val-97)+10;
            }
            if(val2 >='a' && val2 <= 'f')
            {
                val2=(val2-97)+10;
            }
            if(val >= '0' && val <= '9')
            {
                val=val-48;
            }
            if(val2 >= '0' && val2 <= '9')
            {
    
                val2=val2-48;
            }

            val = (val<<4)|val2;
            dst[m++]=val;      
    }
    printf("\n");
    for(i=0;i<bytes_to_decode;i++)
    {
        printf("%X ",dst[i]);
    }
    // printf("%d ",sizeof(dst));
 }


int main()
{
    unsigned char *str="4C4135690007008B00010400860018F6000000000000102B420332313038353033E12C6A29574B104D4643333941314C3241463752202020104C4146435F44454641554C545F485700294C4146435F43414E5F46575F56325F325F312C204E6F7620203720323032322C31333A33323A30350020AA2F3C01B746D205EE4AAEB3286486D17D2171D281407C72DC158F3467E3FE71D398";
    uint32_t s_len=strlen(str);
    printf("%d\n",s_len);
    unsigned char *arr=(char*)malloc((s_len/2)*sizeof(char));
    uint32_t d_len=strlen(arr);
    lafm_utils_decode_from_hex(arr,d_len,0,str,s_len,0,s_len/2);
// printf("\n%02x\n",arr[4]);
    free(arr);    


}