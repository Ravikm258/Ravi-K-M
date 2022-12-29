#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>


void packed_data_bits(uint64_t *unpacked,uint8_t snapshot_count,uint8_t bit_len,uint32_t *packed_data)
{
    uint8_t bits = 0 ;
    
    while(snapshot_count)
    {
        uint8_t ext_bits = 0;

        while (ext_bits != bit_len)
        {
            *packed_data = *packed_data | ((*unpacked & 0x01) << bits);
            *unpacked = *unpacked >> 1;
            ext_bits++;
            bits++;

        }
        snapshot_count--;
        unpacked++;
    }

}
int main()
{
    uint8_t snapshot_count = 2 ;
    uint8_t bit_len = 10 ;
    // uint64_t unpacked[3] = { 0x0D, 0x0F,0x13  } ;
    // printf("%016llX \n%016llX\n%016llX",unpacked[0],unpacked[1],unpacked[2]);
    // uint16_t packed_data = 0;
    // packed_data_bits(unpacked,snapshot_count,bit_len,&packed_data);
    // printf("\n%04X ",packed_data);
    // printf("\n\n");

    //uint64_t decom[5] = {0x1A,0x11,0x1E,0x04,0x1B};
    // uint32_t packed_data1 = 0 ;
    // packed_data_bits(decom,snapshot_count,bit_len, &packed_data1);
    // printf("\n%08X ",packed_data1);

    uint64_t decom[2]={0x287,0x32B};
    uint32_t packed_data1 = 0 ;
    packed_data_bits(decom,snapshot_count,bit_len, &packed_data1);
    printf("\n%08X ",packed_data1);






}