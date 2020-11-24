#include <stdio.h>
#include <stdlib.h>

struct node
{
    char data;
    struct node* nextPtr;
};


struct Node 
{ 
    int data; 
    struct Node *next; 
}; 


void initializeNode (struct node ** head, char val)
{
    struct node*  initial_node = malloc(sizeof(struct node));
    initial_node -> data = val;
    initial_node -> nextPtr = NULL;
    *head = initial_node; 
}

void insertAtBegining (struct node ** head, char val)
{
    struct node*  initial_node = malloc(sizeof(struct node));
    initial_node -> data = val;
    initial_node -> nextPtr = *head;
    *head = initial_node; 
}

void insertAtEnd(struct node ** head, char val)
{
    struct node * current = *head;
    if(current!= NULL)
    {
        while (current->nextPtr != NULL)
        {
            current= current ->nextPtr;
        }
        current->nextPtr = malloc (sizeof(struct node));
        current->nextPtr->data = val;
        current->nextPtr->nextPtr = NULL;
    }
    else 
    {
        current = malloc (sizeof(struct node));
        current -> data = val;
        current ->nextPtr = NULL;
    }
}

void printfList(struct node* currentPtr)
{
    while(currentPtr != NULL)
    {
        printf("the head -> data is  %c\n", currentPtr-> data);
        currentPtr = currentPtr->nextPtr;
    }
}


void doublePtrFancyFunction(int **p)
{
    int * b = (int *)malloc(sizeof(int*));
    *b =5;
    *p  = b;
}

void arrayChange(int *b)
{
    *b =5;
}

int main(int argc, char* argv[])
{ 
    struct node* head = NULL;  // be aware that this is pointer
    initializeNode(&head, 'B');
    insertAtBegining(&head, 'A');
    //insertAtEnd(&head, 'P');
    insertAtBegining(&head, 'D');
    printfList(head);

    return 0;
}

