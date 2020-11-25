#include <stdio.h>
#include <stdlib.h>

struct node
{
    char data;
    struct node* nextPtr;
};

char deleteSpecificNode(struct node ** head, char value)
{
    struct node* tempPtr;
    struct node* previousPtr;
    struct node* currentPtr;

    if(value == (*head)->data)
    {
        tempPtr = * head;
        *head =(*head)->nextPtr;
        free(tempPtr);
        return value;
    }
    else 
    {
        previousPtr = *head;
        currentPtr = (*head)->nextPtr;

        while(currentPtr != NULL && currentPtr ->data != value)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }
        
        if((currentPtr != NULL) && (currentPtr ->data == value))
        {
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
            return value;
        }
    }

}
void deleteAtBeginning(struct node ** head)
{
    struct node* tempPtr = NULL;
    if(head != NULL)
    {
        // store the node that want to remove 
        tempPtr = *head;
        //move head node to subsequent node
        *head = (*head)-> nextPtr;
        //free the head node
        free(tempPtr);
    }
}

void insertInOrder(struct node ** head, char val)
{
    struct node* newPtr;
    struct node* previousPtr;
    struct node* currentPtr;

    newPtr = malloc(sizeof(struct node));

    if(newPtr != NULL)
    {
        newPtr->data = val;
        newPtr->nextPtr =NULL;
        
        previousPtr = NULL;
        currentPtr = *head;

        while(currentPtr != NULL && val > currentPtr->data)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if(previousPtr == NULL)
        {
            /*insert new node at beginning*/
            newPtr ->nextPtr = * head;
            *head = newPtr;
        }
        else 
        {
            /*insert new node between previous Otr and currentPtr*/
            previousPtr ->nextPtr = newPtr;
            newPtr ->nextPtr = currentPtr;
        }
    }

}

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
        printf("%c --> ", currentPtr-> data);
        currentPtr = currentPtr->nextPtr;
    }
    printf("NULL\n\n");
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
    initializeNode(&head, 'f');
    insertAtBegining(&head, 'd');
    insertAtBegining(&head, 'e');
    insertAtBegining(&head, 'x');
    insertAtEnd(&head, 'p');
    insertAtBegining(&head, 'd');
    insertInOrder(&head, 'z');
    //deleteSpecificNode(&head, 'c');
    printfList(head);

    return 0;
}

