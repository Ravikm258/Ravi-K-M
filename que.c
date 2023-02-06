#include<stdio.h>
#include<stdint.h>

#define size 5

uint32_t front = -1;
uint32_t rear = -1;
uint32_t qu[size];

uint32_t isEmpty()
{
  return ( (front == -1) ? 1 : 0); 
}
void enqueue(uint32_t ele)
{
    if((rear+1)%size == front)
    {
      printf(" queue is full\n");
      return;
    }
    else 
    {
        if (front == -1 && rear == -1)
        {
          front = 0;
          rear=0;
          qu[rear] = ele;
        }
        else
        {
          rear = (rear + 1) % size;
          qu[rear] = ele;
        }

  }
   
}

void dequeue()
{
    if(isEmpty())
    {
        printf("\n queue is empty\n");
        return;
    }
    if (front == rear) 
    {
      printf("\n Deleted element is : %d",qu[front]);
      front = -1;
      rear = -1;
    }
    else
    { 
    printf("\n Deleted element is : %d",qu[front]);
    front = (front + 1) % size;
    }
  } 


void display()
{
    uint32_t i=0;
    if(front == -1 && rear == -1)
    {
        printf("\n empty queue\n\n");
    }
    else
    {
    printf("\n front : %d ", front);
    printf("\n elements are : ");

    for (i=front; i!=rear; i=(i+1) % size)
    {
      printf("%d ", qu[i]);
    }
    printf("%d ", qu[i]);
    printf("\n rear : %d \n", rear);

  }
}

int main()
{
   uint32_t i;
  //  for(i=0;i<size;i++)
  //  {
  //   enqueue(i+5);
  //  }
    // display();
    enqueue(10);
    //dequeue();
    //dequeue();
    //dequeue();
    //dequeue();
    //dequeue();
    enqueue(50);
    enqueue(20);
    enqueue(30);
    enqueue(40);
   
    enqueue(90);
    dequeue();
    enqueue(100);
    display();

    printf("SIZE OF QUEUE IS : %d",sizeof(qu));
}


