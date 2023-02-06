#include<stdio.h>
#include<stdint.h>
#include<string.h>
uint32_t lafm_utils_decode_from_hex(uint8_t * dst, uint32_t dst_len, uint32_t dst_start_pos, uint8_t * src,
    uint32_t src_len, uint32_t src_start_pos, uint32_t bytes_to_decode);
uint8_t hex_to_byte(uint8_t *src,uint32_t src_start_pos);
int main()
{
    uint8_t i;
    uint8_t string[]="4C4135690007008B00010400860018F6000000000000102B420332313038353033E12C6A29574B104D4643333941314C3241463752202020104C4146435F44454641554C545F485700294C4146435F43414E5F46575F56325F325F312C204E6F7620203720323032322C31333A33323A30350020AA2F3C01B746D205EE4AAEB3286486D17D2171D281407C72DC158F3467E3FE71D398";
    uint32_t size=strlen(string);
    uint8_t buffer[(size/2)];
    uint32_t decod_bytes = lafm_utils_decode_from_hex(buffer,size/2,0,string,size,0,size/2);
    printf("no of bytes decoded --- %d\n",decod_bytes);
    for(i=0;i<=(size/2)-1;i++)
    {
        printf("%02X",buffer[i]);
    }

}
uint32_t lafm_utils_decode_from_hex(uint8_t * dst, uint32_t dst_len, uint32_t dst_start_pos, uint8_t * src,
    uint32_t src_len, uint32_t src_start_pos, uint32_t bytes_to_decode)
{
    uint32_t result=0;
    if(dst_len>=bytes_to_decode)
    {
    if(src_len>=bytes_to_decode)
    {
        while ((src_start_pos<src_len))
        {
            dst[dst_start_pos]=hex_to_byte(src,src_start_pos);
            src_start_pos=src_start_pos + 2;
            dst_start_pos+=1;
            result++;
        }
        return result;
    }
}
}
uint8_t hex_to_byte(uint8_t *src,uint32_t src_start_pos)
{
    uint32_t i=0,j=0;
    uint8_t nib1=0,nib2=0;
    for(i=src_start_pos;i<src_start_pos+2;i+=2)
    {

            nib1=src[i];
            nib2=src[i+1];
            if(nib1 >= 'A' && nib1 <= 'F')
            {
                nib1=(nib1-65)+10;
            }

            if(nib2 >='A' && nib2 <='F')
            {
                nib2=(nib2-65)+10;
            }

            if(nib1 >= 'a' && nib1 <= 'f')
            {
                nib1=(nib1-97)+10;
            }
            if(nib2 >='a' && nib2 <= 'f')
            {
                nib2=(nib2-97)+10;
            }
            if(nib1 >= '0' && nib1 <= '9')
            {
                nib1=nib1-48;
            }
            if(nib2 >= '0' && nib2 <= '9')
            {
                nib2=nib2-48;
            }
            nib1 = (nib1<<4)|nib2;
            return nib1;      
        }

}


uint8_t get_uptime(uint8_t *byte,uint32_t size,uint32_t start_pos,uint32_t no_of_bytes,uint8_t *uptime_val)
{
    uint8_t i,j=0;
    while (j<no_of_bytes)
    {
        if(size>start_pos)
        {
            for(i=start_pos;i<start_pos+no_of_bytes;i++)
            {
                uptime_val[j++]=(byte[i]);
            }
        }
    }
}

int8_t *_16bit_val(uint8_t *byte,uint32_t size,uint32_t start_pos,uint32_t no_of_bytes,uint8_t *arr)
{
    uint8_t i,j=0;
    while (j<no_of_bytes)
    {
        if(size>start_pos)
        {
            for(i=start_pos;i<start_pos+no_of_bytes;i++)
            {
                arr[j++]=(byte[i]);
            }
        }
    }
    

   return arr;
}

int8_t get_FW_ver(uint8_t *byte,uint32_t size,uint32_t start_pos,uint32_t no_of_bytes,uint8_t *fw_ver)
{
    uint8_t i,j=0;
    for(i=start_pos;i<start_pos+no_of_bytes;i++)
    {
        fw_ver[j++]=(byte[i]);
    }
}//try without loop

uint8_t get_pl_sign(uint8_t *byte,uint32_t size,uint32_t start_pos,uint32_t no_of_bytes,uint8_t *pl_sign)
{
    uint8_t i,j=0;
    while(j<no_of_bytes)
    {
        if(size>start_pos)
        {
            for(i=start_pos;i<start_pos+no_of_bytes;i++)
            {
                pl_sign[j++]=(byte[i]);
            }
        }   
    }
}





            uint8_t arr[16];
            /*to get uptime*/
            uint8_t uptime_val[8];
            get_uptime(byte,size,st_pos+14,8,uptime_val);
            printf("Uptime ---      ");
            for(i=0;i<8;i++)
            {
                printf("%02X",uptime_val[i]);
            }
            printf("\n");
   
            /*to get device ID*/
            uint8_t *device_id = _16bit_val(byte,size,st_pos+23,16,arr);
            printf("device Id ---   ");
            for(i=0;i<16;i++)
            {
                printf("%02X",device_id[i]);
            }
            printf("\n");

            /*to get part no*/
            uint8_t *part_no = _16bit_val(byte,size,st_pos+40,16,arr);
            printf("Part number --- ");
            for(i=0;i<16;i++)
            {
                printf("%c",part_no[i]);
            }
            printf("\n");
            /*to get h/w version*/
            uint8_t *hw_ver = _16bit_val(byte,size,st_pos+57,16,arr);
            printf("H/W version --- ");
            for(i=0;i<16;i++)
            {
                printf("%c",hw_ver[i]);
            }
            printf("\n");

            /*to get f/w version*/
            uint8_t fw_ver[41];
            get_FW_ver(byte,size,st_pos+74,41,fw_ver);
        
            printf("F/W version --- ");
            for(i=0;i<41;i++)
            {
                printf("%c",fw_ver[i]);
            }
            printf("\n");
            

            uint8_t pl_sign[32];
            get_pl_sign(byte,size,st_pos+116,32,pl_sign);
            printf("Can setting PL sign --- ");
            for(i=0;i<32;i++)
            {
                printf("%02X",pl_sign[i]);
            }
            printf("\n");
    