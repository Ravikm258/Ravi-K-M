#include <stdio.h>
#include <string.h>
#include<stdint.h>
#include<stdlib.h>

uint8_t hex_to_byte(uint8_t *src,uint32_t src_start_pos,uint32_t src_len);
void data_decompression_bit_level(uint8_t *compressed_data,uint8_t snapshot_count,uint8_t bit_length,uint64_t *decompressed);

uint32_t lafm_utils_decode_from_hex(uint8_t * dst, uint32_t dst_len, uint32_t dst_start_pos, uint8_t * src,
    uint32_t src_len, uint32_t src_start_pos, uint32_t bytes_to_decode)
{
    if(src == NULL || src_len % 2 == 1)
    {
        return 0;
    }
    else
    {
        uint32_t result=0;
        if(dst_len>=bytes_to_decode)
        {
            if(src_len>=bytes_to_decode*2-1)
            {
                while ((src_start_pos<src_len))
                {
                    dst[dst_start_pos]= hex_to_byte(src,src_start_pos,src_len);
                    src_start_pos=src_start_pos + 2;
                    dst_start_pos+=1;
                    result++;
                }
                return result;
            }
        }
    }
}

uint8_t hex_to_byte(uint8_t *src,uint32_t src_start_pos,uint32_t src_len)
{
    uint8_t nib1=0,nib2=0;
    nib1=src[src_start_pos+0];
    nib2=src[src_start_pos+1];
    if(nib1 >= 'A' && nib1 <= 'F')
        nib1=(nib1-65)+10;

    if(nib2 >='A' && nib2 <='F')
        nib2=(nib2-65)+10;
    
    if(nib1 >= 'a' && nib1 <= 'f')
        nib1=(nib1-97)+10;

    if(nib2 >='a' && nib2 <= 'f')
        nib2=(nib2-97)+10;
    
    if(nib1 >= '0' && nib1 <= '9')
        nib1=nib1-48;

    if(nib2 >= '0' && nib2 <= '9')
        nib2=nib2-48;

    nib1 = (nib1<<4)|nib2;
    return nib1;      
        
}

int main()
{
    uint8_t *str="4C413569007B0CCF03010100CA0339578A2000000000203C432729AFCFBF64C2D8C0683741653303AC62AA16DA4AA148C2637CCD42543F20B90BE80300034007000000007514B275000000007614C875000000007614B875BA0BE8030003400799040000FD18A70F9B040000FD18A70F99040000FD189D0FBB0BE8030003400700000100F641283800000100F641283800000100F6412838BC0BE80300034007830B4C360000BB00830B4C360000BB00830B4C360000BB00BD0BE80300034007DB7FFB7F0680FF7FDC7FFC7F06800180DC7FFD7F07800080BE0BE80300034007FB7FFD7F0480FE7FFD7FFB7F0680FF7FFC7FFC7F08800080BF0BE80300034007028002800280048001800380048005800380038003800580C00BE80300034007038000800280008005800180048002800780018006800280C10BE803000340076C326C326C326C326C326C326C326C326C326C326C326C32C20BE803000340076C326C326C326C326C326C326C326C326C326C326C326C32C30BE80300034007793179317931793179317931793179317931793179317931C40BE80300034007793179317931793179317931793179317931793179317931C50BE80300034007BB00020021000000BB00020021000000BB00020021000000C60BE80300034007000000000000000000000000000000000000000000000000C70BE803000340079A18C800000064009A18C800000064009A18C80000006400C80BE80300034007651777042B02D80B661777042B02D80B691777042B02D80BC90BE80300034007DB7F06807B142B00DC7F06807B142A00DE7F09807B142B00CA0BE8030003400779316C320228000079316C320228000079316C3202280000CB0BE803000340070100040000FFFF000100440000FFFF000100400000FFFF00CC0BE80300034007000000000000000000000000000000000000000000000000CD0BE80300034000CE0BE80300034007E2173D0005000000E2173D0005000000E2173D0005000000CF0BE80300034007072607262476020007260726247602000726072624760200D00BE80300034007FD07000070175E170008000070176917FF07000070176517D10BE80300034007000800080008000800080008000800080008000800080008D20BE80300034007000800080008000800080008000800080008000800080008D30BE80300034007006000600060006000600060006000600060006000600060D40BE80300034007006000600060006000600060006000600060006000600060D50BE8030003400786380100F9FE010086380100F9FE010086380100F9FE0100D60BE80300034000D70BE80300034000D80BE803000340008B6B";
    uint32_t s_len=strlen(str);
    uint32_t size = s_len/2;
    uint8_t byte[size];
    //printf("%d\n",size);
    uint32_t decoded_bytes = lafm_utils_decode_from_hex(byte,size,0,str,s_len,0,size);
    if(decoded_bytes==0)
        exit(1);
    uint32_t i;
    for(i=0;i<decoded_bytes;i++)
    {
        printf("%02X ",byte[i]);
    } 
    printf("\n\n");
    uint32_t snap_size=24;
    uint8_t snapshot[snap_size];
    memcpy(snapshot,byte+64,snap_size);

    for(i=0;i<snap_size;i++)
    {
        if(i==8 || i== 16)
            printf(" ");
        printf("%02X",snapshot[i]);
    }
    // uint8_t snap[2]={0x09,0x0A};
    uint64_t result[3];
    data_decompression_bit_level(snapshot,2,64,result);
    printf("%016llX ",result[0]);
}


void data_decompression_bit_level(uint8_t *compressed_data,uint8_t snapshot_count,uint8_t bit_length,uint64_t *decompressed)
{
    uint8_t j = 0;
    while(snapshot_count)
    {
        uint8_t i = 0 ; 
        uint8_t bit_count = bit_length ;
            while(bit_count >= 8)
            {
                *decompressed = *decompressed | (uint64_t)(compressed_data[j]) << i*8 ;
                i++;
                j++;
                bit_count-=8;
            }
            uint8_t rem_bits = bit_count;
            if(bit_count > 0)
            {
                *decompressed = *decompressed | (uint64_t)(compressed_data[j]) << i*8 ;
                bit_count-=rem_bits;
            }
            snapshot_count--;
            decompressed++;
    }

}














































































//     uint64_t time1=0;
//     uint64_t time2=0;
//     uint64_t num =  0x18F6A01234567897;
//     uint8_t i;     

//     time1 |= (num & 0xff00000000000000) >> 56 ;
//     time1 |= (num & 0x00ff000000000000) >> 40 ; 
//     time1 |= (num & 0x0000ff0000000000) >> 24 ;
//     time1 |= (num & 0x000000ff00000000) >> 8 ;

//     time1 |= (num & 0x00000000ff000000)  << 8;
//     time1 |= (num & 0x0000000000ff0000) << 24 ;
//     time1 |= (num & 0x000000000000ff00) << 40 ;
//     time1 |= (num & 0x00000000000000ff) << 56 ;
    
//     printf("0x%016llX\n",time1);
    
// }


// uint64_t get(uint8_t *array)
// {
//     uint8_t i;
//     uint64_t num=0;
//     for(i=0;i<8;i++)
//     {
//         num |= ((uint64_t) array[i]<<i*8);
//     }
//     return num;
// }
// int main()
// {
//     uint8_t array[8]={0x18,0xF6,0x00,0x00,0x00,0x00,0x00,0x00};
//     uint64_t up = get(array);



//     // | ((uint64_t)array[1]<<8)| ((uint64_t)array[2]<<16)| ((uint64_t)array[3]<<24)|
//     //         ((uint64_t)array[4]<<32)| ((uint64_t)array[5]<<40)| ((uint64_t)array[6]<<48)| ((uint64_t)array[7]<<56);

//             printf("%ld",up);
//     uint8_t validity_flag=22,i;
//     uint8_t valid_data = 0;
//     for(i=0;i<8;i++)
//     {
//         if((validity_flag>>i)& 0x01)
//             valid_data++;
//     }
//     printf("\n%d", valid_data);

//     uint8_t byte[10]={0x18,0xF6,0x0A,0x12,0x45,0x06,0x76,0x54};
//     uint32_t PID_number = ((uint32_t)((byte[1])<<16) | ((uint32_t)(byte[2])<<8) | (uint32_t)((byte[3])));
//     printf("\nPID Number is --- %d\n",PID_number);

            
// }





















































// struct payload
// {
//     uint16_t beacon_type;
//     uint16_t seq_id;
//     uint16_t payload_length;
// };
// typedef struct payload payload;

// uint8_t hex_to_byte(uint8_t *src,uint32_t src_start_pos,uint32_t src_len);


// uint32_t lafm_utils_decode_from_hex(uint8_t * dst, uint32_t dst_len, uint32_t dst_start_pos, uint8_t * src,
//     uint32_t src_len, uint32_t src_start_pos, uint32_t bytes_to_decode)
// {
//     if(src != NULL)
//     {
//         uint32_t result=0;
//         if(dst_len>=bytes_to_decode)
//         {
//             if(src_len>=bytes_to_decode*2-1)
//             {
//                 while ((src_start_pos<src_len))
//                 {
//                     dst[dst_start_pos]= hex_to_byte(src,src_start_pos,src_len);
//                     src_start_pos=src_start_pos + 2;
//                     dst_start_pos+=1;
//                     result++;
//                 }
//                 return result;
//             }
//         }
//     }
// }

// uint8_t hex_to_byte(uint8_t *src,uint32_t src_start_pos,uint32_t src_len)
// {
//     uint8_t nib1=0,nib2=0;
//     nib1=src[src_start_pos+0];
//     nib2=src[src_start_pos+1];
//     if(nib1 >= 'A' && nib1 <= 'F')
//         nib1=(nib1-65)+10;

//     if(nib2 >='A' && nib2 <='F')
//         nib2=(nib2-65)+10;
    
//     if(nib1 >= 'a' && nib1 <= 'f')
//         nib1=(nib1-97)+10;

//     if(nib2 >='a' && nib2 <= 'f')
//         nib2=(nib2-97)+10;
    
//     if(nib1 >= '0' && nib1 <= '9')
//         nib1=nib1-48;

//     if(nib2 >= '0' && nib2 <= '9')
//         nib2=nib2-48;

//     if(src_start_pos+1 == src_len)
//         nib1 = (nib2<<4)|nib1;
//     else
//         nib1 = (nib1<<4)|nib2;
//     return nib1;      
        
// }

// payload get_data(uint8_t *byte,uint32_t start_pos)
// {
//     payload v;
//     uint8_t hex[6];
//     hex[0]=byte[start_pos];
//     hex[1]=byte[start_pos+1];
//     v.beacon_type=hex[1]<<8|hex[0];
    
//     hex[2]=byte[start_pos+2];
//     hex[3]=byte[start_pos+3];
//     v.seq_id=hex[3]<<8|hex[2];

//     hex[4]=byte[start_pos+4];
//     hex[5]=byte[start_pos+5];
//     v.payload_length=hex[5]<<8|hex[4];

//     return v;
// }

// uint32_t check_header(uint8_t *byte,uint32_t size,uint8_t *ch,uint32_t len)
// {
//     uint32_t index;
//     uint8_t *res=strstr(byte,ch);
//     index=byte-res;
//     if(index>=0)
//         return index;
//     else
//         return -1;
// }

// int main()
// {
//     uint8_t *str="4C4135690007008B00010400860018F6000000000000102B420332313038353033E12C6A29574B104D4643333941314C3241463752202020104C4146435F44454641554C545F485700294C4146435F43414E5F46575F56325F325F312C204E6F7620203720323032322C31333A33323A30350020AA2F3C01B746D205EE4AAEB3286486D17D2171D281407C72DC158F3467E3FE71D398";
//     uint32_t s_len=strlen(str);
//     uint32_t size = (s_len%2==0)?s_len/2:(s_len/2)+1;
//     uint8_t byte[size];
//     //printf("%d\n",size);
//     uint32_t decoded_bytes = lafm_utils_decode_from_hex(byte,size,0,str,s_len,0,size);
//     //printf("%d \n",decoded_bytes);
//     uint32_t i;
//     payload res;
//     res = get_data(byte,3);
//     uint8_t choice,option;
//     do{
//     printf("1.Print Byte array\n2.Header start position\n3.Beacon Type,Sequence Id,Payload Length\n4.Get payload details\n");
//     printf("enter the option");
//     scanf("%d",&option);
//     switch (option)
//     {
//     case 1:    
//             for(i=0;i<decoded_bytes;i++)
//             {
//                 printf("%02X ",byte[i]);
//             }
//             break;
//     case 2:    
//             unsigned char *header="LA5";
//             uint32_t len= strlen(header);
//             uint32_t st_pos= check_header(byte,size,header,len);
//             printf("\nstart_pos = %d \n",st_pos);
//             break;
//     case 3:
//         printf("\nBeacon type --- %d \nSequence ID -----%d \nPayload length ---%d",res.beacon_type,res.seq_id,res.payload_length);
//         break;
//     default:printf("invalid");
//         break;
//     }
//     printf("\ndo u want to print again 1.yes or press any key\n");
//     scanf("%d",&choice);
//     }while(choice==1);

//     // do
//     // {
//     //     payload res;
//     //     res = get_data(byte,3);
//     //     printf("\nBeacon type --- %d \nSequence ID -----%d \nPayload length ---%d",res.beacon_type,res.seq_id,res.payload_length);
//     //     printf("\ndo u want to print again 1.yes or press any key\n");
//     //     scanf("%d",&choice);
//     // }while(choice==1);
// }