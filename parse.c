#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>


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
 uint16_t b_t(uint8_t *byte,uint32_t size, uint32_t pos)
 {
    uint32_t i,j=0, hex[2];
    uint16_t val=0;
    if(size>pos)
    {
        for(i = pos;i < pos+2;i+=2)
        {
            hex[0] = byte[i++];
            hex[1]=byte[i];
        }
        val=hex[1]<<8|hex[0];
        return val;
    }
    else return -1;
 }

uint16_t payload_len(uint8_t *byte,uint32_t size, uint32_t start_pos)
{
    uint32_t i,j=0,hex[2];
    uint16_t pyl_size=0;
    if(size>start_pos)
    {
        for(i = start_pos;i < start_pos+2;i+=2)
        {
            hex[0] = byte[i++];
            hex[1]=byte[i];

        }
        pyl_size=hex[1]<<8|hex[0];
        return pyl_size;
    }
    else return -1;
}
 uint8_t *pyl(uint8_t *byte,uint32_t size,uint32_t start_pos,uint32_t end_pos,uint8_t *py_buffer)
 {
    uint32_t i,j=0;
    if(size>start_pos)
    {
        for(i = start_pos;i < start_pos+end_pos;i++)
        {
            py_buffer[j]=byte[i];
            j++;
        }
        return py_buffer;
    }
 }

uint16_t get_crc(uint8_t *byte,uint32_t size,uint32_t start_pos)
{
    uint32_t i;
    uint16_t crc_val=0;
    uint8_t hex[2];
    if(size>start_pos)
    {
        for(i = start_pos;i < size ;i+=2)
        {
            hex[0]=byte[i];
            hex[1]=byte[i+1];
        }
        crc_val=hex[1]<<8|hex[0];

        return crc_val;
    }
}



uint16_t lafc_crc16_compute(uint8_t const * p_data, uint16_t size, uint16_t const * p_crc)
{
    uint16_t crc = (p_crc == NULL) ? 0xFFFF : *p_crc;

    for (uint16_t i = 0; i < size; i++)
    {
        crc = (uint16_t)(crc >> 8) | (uint16_t)(crc << 8);
        crc = (uint16_t)(crc ^ p_data[i]);
        crc ^= (uint16_t)((crc & (uint16_t)0xFF) >> 4);
        crc ^= (uint16_t)((crc << 8) << 4);
        crc = (uint16_t)(crc ^ (((crc & 0xFF) << 4) << 1));
    }
    return crc;
}

int main()
{
   // uint8_t byte[] = {0x4C,0x41,0x35, 0x6A,0x00, 0x0A,0x00, 0x09,0x00, 0x01,0x02,0x00,0x04,0x00,0x03,0x10,0x27,0x00, 0x12,0x79};
    
    uint8_t byte[]={0x4C,0x41,0x35 ,0x69, 0x00, 0x07, 0x00, 0x8B, 0x00, 0x01, 0x04, 0x00, 0x86 ,0x00, 0x18, 0xF6, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x10, 0x2B, 0x42, 0x03, 0x32, 0x31 ,0x30, 0x38, 0x35, 0x30, 0x33, 0xE1, 0x2C, 0x6A, 0x29 ,0x57,
    0x4B, 0x10, 0x4D, 0x46, 0x43, 0x33, 0x39 ,0x41, 0x31, 0x4C, 0x32, 0x41, 0x46, 0x37, 0x52, 0x20, 0x20, 0x20, 0x10, 0x4C, 
    0x41, 0x46, 0x43, 0x5F, 0x44, 0x45, 0x46, 0x41, 0x55, 0x4C, 0x54, 0x5F, 0x48, 0x57, 0x00, 0x29, 0x4C ,0x41, 0x46, 0x43, 
    0x5F ,0x43, 0x41, 0x4E, 0x5F, 0x46, 0x57, 0x5F, 0x56,0x32, 0x5F, 0x32, 0x5F, 0x31, 0x2C, 0x20, 0x4E, 0x6F, 0x76, 0x20,
    0x20, 0x37, 0x20, 0x32, 0x30, 0x32, 0x32, 0x2C, 0x31, 0x33, 0x3A, 0x33, 0x32, 0x3A, 0x30, 0x35, 0x00, 0x20, 0xAA, 0x2F,
    0x3C, 0x01, 0xB7, 0x46, 0xD2, 0x05, 0xEE, 0x4A, 0xAE, 0xB3, 0x28, 0x64, 0x86, 0xD1, 0x7D, 0x21, 0x71, 0xD2, 0x81, 0x40,
    0x7C, 0x72, 0xDC, 0x15, 0x8F, 0x34, 0x67, 0xE3, 0xFE, 0x71,0xD3,0x98};
    

    uint32_t size = sizeof(byte)/sizeof(byte[0]);
    unsigned char *ch="LA5";
    uint32_t len= strlen(ch);
    uint32_t res= check_header(byte,size,ch,len);
    printf("start_pos = %d \n",res);

    uint16_t btyp=b_t(byte,size,res+3);
    printf("B.T = 0x%04X \n",btyp);

    uint16_t py_len=payload_len(byte,size,res+7);
    printf("payload length = 0x%04X \n",py_len);

    // uint8_t buffer_size = (size-res-py_len);
    // printf("%d\n ",buffer_size);

    uint8_t *py_buffer=(uint8_t*)malloc(py_len*sizeof(uint8_t));
    uint8_t *pylod=pyl(byte,size,res+9,9,py_buffer);
    //uint8_t i;
    // for(i=0;i<py_len;i++)
    // {
    //     printf("0x%02X ",pylod[i]);
    // }
    int a=0x20;
   uint16_t crc_data = get_crc(byte,size,(res+9+py_len));
   printf("0x%04X \n",crc_data);

    
    uint16_t calc_crc = lafc_crc16_compute(byte,size-2,NULL);
    printf("0x%04X ",calc_crc);

    if(crc_data==calc_crc)
    {
        printf("\nprocess\n");

    }

    else
    {
        printf("do not process\n");
    }
    free(py_buffer);
}