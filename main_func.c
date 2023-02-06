#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"header.h"



int main()
{
    node *head=NULL;
    insertRandom(&head,1,20);
    insertRandom(&head,2,40);
    insertRandom(&head,3,50);
    insertRandom(&head,1,25);
    insertRandom(&head,6,55);
    printf("before reverse\n");
    display(&head);
    reverse_list(&head);
    printf("after reverse\n");
    display(&head);
}