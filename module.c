// CAN Data Beacon
// Beacon Type - 105
// Module Code - 01

// Module Structure
// <Coproc Uptime: 8 Bytes> <Size of PL Sign: 1> <PL Sign: x Bytes> <No Of PID: 1> 
// <PID Number: 2> <Save Interval: 3> <Snapshots: 1> <Bit Length: 1> <Validity Flag: x Bytes(size Depending on Snapshot Count)>
// <Snapshots: x>


#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>

void call_module_1(uint8_t  *byte,uint32_t pos);
uint8_t hex_to_byte(uint8_t *src,uint32_t src_start_pos,uint32_t src_len);


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

/*check for header and return start position*/
uint32_t check_header(uint8_t *byte,uint32_t size,uint8_t *ch,uint32_t len)
{
    uint32_t index=0;
    uint8_t *res=strstr(byte,ch);
    index=res-byte;
    if(index>=0)
        return index;
    else
        return -1;
}

/* actual crc*/
uint16_t get_crc(uint8_t *byte,uint32_t size,uint32_t start_pos)
{
    uint8_t hex[2];
    hex[0]=byte[start_pos];
    hex[1]=byte[start_pos+1]; 
    uint16_t crc_val=hex[1]<<8|hex[0];
    return crc_val;
}



/*calculated crc*/
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






uint64_t get_uptime(uint8_t *byte,uint32_t start_pos,uint32_t no_of_bytes)
{
    uint64_t num=0;
    uint8_t i;
    for(i=0;i<no_of_bytes;i++)
    {
        num |= ((uint64_t) byte[start_pos]<<(i*8));
        start_pos++;
    }
    return num;
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

    unsigned char *header="LA5";
    uint32_t len= strlen(header);
    uint32_t st_pos=0;
    if(decoded_bytes>len)
    {
        st_pos= check_header(byte,size,header,len);
        printf("\n\nstart_pos = %d \n",st_pos);
    }
    if(st_pos<0 || st_pos>decoded_bytes)
        exit(1);
    else
    {
        uint16_t payload_length=((uint16_t)((byte[st_pos+7])<<0) | ((uint16_t)(byte[st_pos+8])<<8));
        printf("payload length is ---- %d\n",payload_length);
        printf("%02X  %02X", byte[7],byte[8]);

        uint32_t buffer=(decoded_bytes - payload_length);

        
        if(buffer>=11)
        {
            uint16_t crc_data = get_crc(byte,size,(st_pos+9+payload_length));
            printf("actual crc --- 0x%04X \n",crc_data);

                
                uint16_t calc_crc = lafc_crc16_compute(byte,size-2,NULL);
                printf("calculated crc --- 0x%04X ",calc_crc);

                if(crc_data==calc_crc)
                {
                    printf("\nprocess\n");
                    uint8_t mod_count=byte[st_pos+9];
                    printf("module count --- %d\n",mod_count);

                    uint16_t mod_code=((uint16_t)((byte[st_pos+10])<<0) | ((uint16_t)(byte[st_pos+11])<<8));
                    printf("\n module code ---  %d\n",mod_code);
                    st_pos=st_pos+11;
                    if(mod_code==1)
                    {
                        call_module_1(byte,st_pos);
                    }

                }
                else
                    printf("\ndo not process\n");
        }
    }  
}
    

void call_module_1(uint8_t  *byte,uint32_t pos)
{
    pos=12;
    uint16_t mod_size = ((uint16_t)((byte[pos])<<0) | ((uint16_t)(byte[pos+1])<<8));
    printf("\nmodule size is ---- %d\n",mod_size);
    pos+=2;
    uint64_t uptime=get_uptime(byte,pos,8);
    printf(" uptime is %d mili seconds \n",uptime);
    printf("\n\n");
    pos+=8;
    uint8_t i;
    uint32_t plsign_size=byte[pos];
    printf("PL sign size is ---- %d\n",plsign_size);
    uint8_t pl_sign[plsign_size];
    memcpy(pl_sign,byte+(pos+1),plsign_size);
    printf("PL SIGN ---- ");
    for(i=0;i<plsign_size;i++)
    {
        printf("%02X",pl_sign[i]);
    }

    pos=pos+plsign_size+1;

    uint8_t no_of_PID=byte[pos];
    printf("\nNo. of PID ----  %d\n",no_of_PID);

     pos=pos+1;

    uint16_t PID_number = ((uint16_t)((byte[pos])<<0) | ((uint16_t)(byte[pos+1])<<8));
    printf("PID Number is --- %d\n",PID_number);


    pos = pos+2;
    uint32_t save_intrvl = 0;
    save_intrvl = ((uint32_t)((byte[pos])) | ((uint32_t)((byte[pos+1])<<8)) | ((uint32_t)(byte[pos+2])<<16)) ;
    printf("Save Interval --- %d ms\n",save_intrvl);
    
    pos+=3;
    
    uint8_t snapshot_count = byte[pos];
    printf(" snapshot count --- %d \n",snapshot_count);

    pos+=1;

    uint8_t bit_length = byte[pos];
    printf("Bit length ----- %d bits\n",bit_length);

    pos+=1;

    uint8_t validity_flag=0;
    if(snapshot_count<8)
    {
        validity_flag = byte[pos];
    }
    pos=pos+1;
    /* to get no of valid data*/
    uint8_t valid_data = 0;
    for(i=0;i<snapshot_count;i++)
    {
        if((validity_flag>>i)& 0x01)
            valid_data++;
    }
    printf("Valid data ---   %d\n",valid_data);
    uint8_t snap_size= (((bit_length*valid_data)+7)/8);
    printf("Snapshot size is ---  %d bytes",snap_size);

    printf("\n\n");
    uint8_t snapshot[snap_size];
    memcpy(snapshot,byte+pos,snap_size);
    for(i=0;i<snap_size;i++)
    {
        if(i==8 || i== 16)
            printf(" ");
        printf("%02X",snapshot[i]);
    }
    
    


}
