#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

typedef struct node
{
    uint8_t *addr;
    struct node *next;   
}node;
node *head = NULL,*tail = NULL ;
uint8_t rx_buffer_1[10U] ;
uint8_t rx_buffer_2[10U];
uint8_t rx_buffer_3[10U];
uint8_t rx_buffer_4[10U];
uint8_t rx_buffer_5[10U];



void add(uint8_t *addr)
{
    node *new =(node*)malloc(sizeof(node));
    new->addr = addr;
    if(head == NULL)
    {
        new->next = NULL ;
        head = tail = new ;
    }
    else
    {
        tail->next = new ; 
        new->next = NULL ;
        tail = new ;
    }
}

int main()
{
    add(rx_buffer_1);
    add(rx_buffer_2);
    add(rx_buffer_3);
    add(rx_buffer_4);
    add(rx_buffer_5);
    printf("%u ",head->addr);
    printf("%u ",head->next->addr);
    printf("%u ",tail->addr);
    printf("%u ",&rx_buffer_1);
    //printf("%u ",&rx[1]);
   // printf("%u ",&rx_buffer_2);
    //printf("%u ",&rx_buffer_3);
    //printf("%d ",sizeof(head->addr));
    //printf("%d ",sizeof(head->next->addr));
    uint8_t *rx = head->addr ;
    rx[0] = 'A';
    //printf("%u ",&rx);
    printf("%u ",rx[0]);
    printf("%u ",&rx[5]);
    printf("%u ",&rx_buffer_1[5]);
    printf("tail : %u ",tail->addr);
    printf("%u ",&rx_buffer_5);
}

