#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

uint8_t check_header(uint8_t *byte,uint32_t size,uint8_t *ch,uint32_t len)
{
    uint32_t i,j;
    for(i = 0;i < size-len;i++)
    {
        for(j = 0;j < len;j++)
        {
            if(ch[j] != byte[j+i])
                break;
            if(j==(len-1))
                return i;
        }
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
    while (j<no_of_bytes)
    {
        if(size>start_pos)
        {
            for(i=start_pos;i<start_pos+no_of_bytes;i++)
            {
                fw_ver[j++]=(byte[i]);
            }
        }
    }
    

}

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

uint8_t hex_to_str(uint8_t *byte,uint32_t size)
{
    
}


int main()
{
    uint8_t byte[]={0x4C,0x41,0x35 ,0x69, 0x00, 0x07, 0x00, 0x8B, 0x00,0x01,0x04, 0x00, 0x86 ,0x00, 0x18, 0xF6, 0x00,0x00, 
    0x00, 0x00, 0x00, 0x00, 0x10, 0x2B, 0x42, 0x03, 0x32, 0x31 ,0x30, 0x38, 0x35, 0x30, 0x33, 0xE1, 0x2C, 0x6A, 0x29 ,0x57,
    0x4B, 0x10, 0x4D, 0x46, 0x43, 0x33, 0x39 ,0x41, 0x31, 0x4C, 0x32, 0x41, 0x46, 0x37, 0x52, 0x20, 0x20, 0x20, 0x10, 0x4C, 
    0x41, 0x46, 0x43, 0x5F, 0x44, 0x45, 0x46, 0x41, 0x55, 0x4C, 0x54, 0x5F, 0x48, 0x57, 0x00, 0x29, 0x4C ,0x41, 0x46, 0x43, 
    0x5F ,0x43, 0x41, 0x4E, 0x5F, 0x46, 0x57, 0x5F, 0x56,0x32,  0x5F, 0x32, 0x5F, 0x31, 0x2C, 0x20, 0x4E, 0x6F, 0x76, 0x20,
    0x20, 0x37, 0x20, 0x32, 0x30, 0x32, 0x32, 0x2C, 0x31, 0x33, 0x3A, 0x33, 0x32, 0x3A, 0x30, 0x35, 0x00, 0x20, 0xAA, 0x2F,
    0x3C, 0x01, 0xB7, 0x46, 0xD2, 0x05, 0xEE, 0x4A, 0xAE, 0xB3, 0x28, 0x64, 0x86, 0xD1, 0x7D, 0x21, 0x71, 0xD2, 0x81, 0x40,
    0x7C, 0x72, 0xDC, 0x15, 0x8F, 0x34, 0x67, 0xE3, 0xFE, 0x71 ,0xD3, 0x98};
    uint8_t i,size=150;
    uint8_t arr[16];
    uint8_t st_pos=0;

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
        printf("%02X",part_no[i]);
    }
    printf("\n");
    /*to get h/w version*/
    uint8_t *hw_ver = _16bit_val(byte,size,st_pos+57,16,arr);
    printf("H/W version --- ");
    for(i=0;i<16;i++)
    {
        printf("%02X",hw_ver[i]);
    }
    printf("\n");
    uint8_t fw_ver[41];
    /*to get f/w version*/
    get_FW_ver(byte,size,st_pos+74,41,fw_ver);
    printf("F/W version --- ");
    for(i=0;i<41;i++)
    {
        printf("%02X",fw_ver[i]);
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

}