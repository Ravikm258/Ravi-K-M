#include <stdio.h>
#include<stdlib.h>
#include <stdint.h>

struct list
{
    int data;
    struct list *next;
};

typedef struct list node;

int count=0;

void reverse_list(node **head)
{
    node *prev= NULL,*new=NULL,*curr=(*head);
    if(head==NULL)
    {
        printf("list is empty\n");
    }
    else
    {
        while(curr != NULL)
        {
            new=curr->next;
            curr->next=prev;
            prev=curr;
            curr=new;
        }
        (*head)=prev;
    }
}

void delete_random(node **head,uint32_t loc)
{
    if((*head)==NULL)
    {
        printf("\nlist is empty");
    }
    else
    {
        node *temp=(*head),*temp1;
        uint32_t i;
        for(i=0;i<loc;i++)
        {
            temp1=temp;
            temp=temp->next;
        }    
        if(loc != 1)
        {
            temp1->next=temp->next;
            free(temp);
        }
        else
        {
            (*head)=temp->next;
            free(temp);
        }
    }
    count--;
}

void insertRandom(node **head,int pos,int val)
{
    node *new=(node*)malloc(sizeof(node));
    new->data=val;
    node *temp=(*head);
    int i;
    if(pos<1)
    {
        return;
    }
    if(count==0)
    {
        new->next=NULL;
        (*head)=new; 
        count++;
        return;
    }
    if(pos>count)
    {
        new->next=NULL;
        temp=(*head);
        while(temp->next!=NULL)
        {
          temp=temp->next;  
        }
        temp->next=new;
        count++;
        return;
    }
    else if(pos==1 && count != 0)
    {
        new->next=(*head);
        (*head)=new; 
        count++;
        return;   
    }
    else
    {
        for(i=0;i!=pos-2 && temp!=NULL;i++)
        {
            temp=temp->next;
        }
        new->next=temp->next;
        temp->next=new;
    }
    count++;
    
}
void display(node **head)
{
    node *temp=(*head);
    while(temp != NULL)
    {
        printf("%d\n",temp->data);
        temp=temp->next;
    }
}



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