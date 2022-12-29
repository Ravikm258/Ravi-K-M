#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>

/* source is array of packed data and dest will be array of unpacked data */

void data_decompression_bit_level(uint8_t *source,uint8_t snapshot_count,uint8_t bit_len,uint64_t *dest)
{
    uint8_t bit_count = 0, bits = bit_len;
    uint8_t extd_bits = 0;
    uint8_t rem_bits = 8;
    uint8_t req_bits = 8 ;

    while(snapshot_count)
    {
        while(bits >= 8 && (rem_bits >= req_bits))
        {
            *dest = *dest | ((uint64_t)(*source) & 0xFF) << extd_bits;
            extd_bits += 8 ;
            source++ ;
            bits -= 8 ; 
        }

        while(bits)
        {
            *dest = *dest | ((uint64_t)(*source) & 0x01) << extd_bits;
            *source = *source >> 1 ;
            extd_bits++ ;
            rem_bits -- ;
            req_bits--;
            bit_count++ ;
            bits--;
        }
            if(extd_bits == bit_len)
            {
            dest++ ;
            extd_bits = 0 ;
            snapshot_count-- ;
            bits = bit_len;
            }
            if(bit_count == 8)
            {
            bit_count = 0 ;
            source ++ ;
            }
        }
}


/*source is array of unpacked data and dest will array of packed data*/

void packed_data_bits(uint64_t *source,uint8_t snapshot_count,uint8_t bit_len,uint8_t *dest)
{
    
    uint8_t bits = 0 ;
    
    while(snapshot_count)
    {
        uint8_t ext_bits = 0;

        while (ext_bits != bit_len)
        {
            *dest = *dest | ((*source & 0x01) << bits);
            *source = *source >> 1;
            ext_bits++;
            bits++;
            if(bits == 8)
            {
                dest++;
                bits = 0;
            }

        }
        snapshot_count--;
        source++;
    }

}
int main()
{
    uint8_t i;
    // uint8_t snapshot_count = 3 ;
    // uint8_t bit_len = 5 ;
    // uint64_t unpacked[3] = { 0x000000000000000D, 0x000000000000000F,0x0000000000000013  } ;
    // uint8_t size = ((snapshot_count * bit_len)+7) / 8 ;
    // uint8_t packed_data[size];
    // memset(packed_data,0,sizeof(packed_data));
    // packed_data_bits(unpacked,snapshot_count,bit_len,packed_data);
    // for(i = 0 ;i < size ; i++ )
    // {
    //     printf("%02X",packed_data[i]);
    // }


    // uint8_t snapshot_count = 5 ;
    // uint8_t bit_len = 5 ;
    // uint64_t decom[5] = {0x000000000000001A,0x0000000000000011,0x000000000000001E,0x0000000000000004,0x000000000000001B};
    // uint8_t size = ((snapshot_count * bit_len)+7) / 8 ;
    // uint8_t packed_data[size];  
    // memset(packed_data,0,sizeof(packed_data));
    // packed_data_bits(decom,snapshot_count,bit_len, packed_data);
    // for(i = 0 ;i < size ; i++ )
    // {
    //     printf("%02X",packed_data[i]);
    // }


    // uint8_t snapshot_count = 2 ;
    // uint8_t bit_len = 10 ;

    // uint64_t unpacked[2]={0x0000000000000287,0x000000000000032B};
    // uint8_t size = ((snapshot_count * bit_len)+7) / 8 ;
    // uint8_t packed_data[size];
    // memset(packed_data,0,sizeof(packed_data));
    // packed_data_bits(unpacked,snapshot_count,bit_len, packed_data);
    // printf("PACKED DATA :\n");
    // for(i = 0 ;i < size ; i++ )
    // {
    //     printf("%02X",packed_data[i]);
    // }




    // uint8_t snapshot_count = 3 ;
    // uint8_t bit_len =55 ;
    // uint64_t decom[3] = {0x0071040041E9B5D6 ,0x0048760050838822,0x005034003145A459};
    // uint8_t size = ((snapshot_count * bit_len)+7) / 8 ;
    // uint8_t packed_data[size];  
    // memset(packed_data,0,sizeof(packed_data));
    // packed_data_bits(decom,snapshot_count,bit_len, packed_data);
    // printf("PACKED DATA :\n");
    // for(i = 0 ;i < size ; i++ )
    // {
    //     printf("0x%02X ",packed_data[i]);
    // }

    // uint8_t snapshot_count = 3 ;
    // uint8_t bit_len = 28 ;

    // uint64_t decom[3]={0x0000000008987645,0x000000000AE29937,0x000000000B3D17E2};

    // uint8_t size = ((snapshot_count * bit_len)+7) / 8 ;
    // uint8_t packed_data[size];  
    // memset(packed_data,0,sizeof(packed_data));
    // packed_data_bits(decom,snapshot_count,bit_len, packed_data);
    // printf("PACKED DATA :\n");
    // for(i = 0 ;i < size ; i++ )
    // {
    //     printf("%02X",packed_data[i]);
    // }


    uint8_t snapshot_count = 4;
    uint8_t bit_len = 34;
    uint64_t decom[5] = {0x1234567890ABCDEF ,0X1234567890ABCDEF,0x1234567890ABCDEF,
                        0x1234567890ABCDEF ,0X1234567890ABCDEF};
    uint8_t size = ((snapshot_count * bit_len)+7) / 8 ;
    uint8_t packed_data[size];  
    memset(packed_data,0,sizeof(packed_data));
    packed_data_bits(decom,snapshot_count,bit_len, packed_data);
    printf("PACKED DATA :\n");
    for(i = 0 ;i < size ; i++ )
    {
        printf("%X ",packed_data[i]);
    }


    printf("\n");
    uint64_t unpacked_data[snapshot_count];
    memset(unpacked_data,0,sizeof(unpacked_data));
    data_decompression_bit_level(packed_data,snapshot_count,bit_len,unpacked_data);
    printf("\nUNPACKED DATA : ");
    for(i = 0 ;i < snapshot_count ; i++ )
    {
        printf("\n");
        printf("%llX",unpacked_data[i]);
    }
}