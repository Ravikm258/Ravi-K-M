#ifndef HEADER_H
#define HEADER_H

#include<stdint.h>
struct list
{
    int data;
    struct list *next;
};

typedef struct list node;

void reverse_list(node **head);
void delete_random(node **head,uint32_t loc);
void insertRandom(node **head,int pos,int val);
void display(node **head);

#endif