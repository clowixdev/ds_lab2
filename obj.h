#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#define BUFFERSIZE 20

void Clear(char* str, int strlen);

struct list;
struct Stack;
struct Queue;

//stack:
void initializeStack(struct Stack* s);
int isEmptyS(struct Stack* s);
void printStack(struct Stack* s);
void push(struct Stack* s, char* data);
void pop(struct Stack* s, char* result);

//queue:
void initializeQueue(struct Queue* q);
int isEmptyQ(struct Queue* q);
void put(struct Queue* q, char* data);
void get(struct Queue* q, char* result);
void freeQueue(struct Queue* q);
void printQueue(struct Queue* q);


void Clear(char* str, int strlen) {
    for (int i = 0; i < strlen; i++) {
        str[i] = 0;
    }
}

struct list
{
    struct list* pnextList;
    char data[BUFFERSIZE];
};


struct Stack{
    struct list *top;
};

void initializeStack(struct Stack *s) {
    s->top = NULL;
}

int isEmptyS(struct Stack *s) {
    return (s->top == NULL);
}

void printStack(struct Stack *s) {
    if (isEmptyS(s)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack contents:");
    struct list *current = s->top;
    while (current != NULL) {
        printf("!%s! ", current->data);
        current = current->pnextList;
    }
    printf("\n");
}

void push(struct Stack* s, char* data) {
    struct list* newlist = (struct list*)malloc(sizeof(struct list));
    if (newlist == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    Clear(newlist->data, BUFFERSIZE);
    newlist->pnextList = s->top;
    s->top = newlist;

    strncpy(newlist->data, data, BUFFERSIZE - 1);
    newlist->data[BUFFERSIZE - 1] = '\0'; // Гарантируем нуль-терминацию
}

void pop(struct Stack* s, char* result) {
    if (isEmptyS(s)) {
        printf("Error: Stack is empty\n");
        return;
    }
    struct list* temp = s->top;
    s->top = temp->pnextList;

    if (result != NULL && temp->data != NULL) {
        strcpy(result, temp->data);
    }
    free(temp);
}

struct Queue{
    struct list* first;
    struct list* last;
};

void initializeQueue(struct Queue *q) {
    q->first = NULL;
    q->last = NULL;
}

int isEmptyQ(struct Queue *q) {
    return (q->first == NULL);
}

void put(struct Queue *q,char* data) {
    struct list *newlist = (struct list *)malloc(sizeof(struct list));
    if (newlist == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    strcpy(newlist->data,data);
    newlist->pnextList = NULL;

    // If the queue is empty, the new node becomes the start and end of the queue
    if (isEmptyQ(q)) {
        q->first = newlist;
        q->last = newlist;
    } else {
        q->last->pnextList  = newlist;
        q->last = newlist;
    }
}
//first el of queue
void get(struct Queue* q, char* result) {
    if (isEmptyQ(q)) {
        printf("Queue is empty. Unable to get.\n");  
        return;
    }

    struct list* temp = q->first;
    if (temp->data != NULL && result != NULL) {
        strcpy(result, temp->data);
 //       printf("copied %s\n",result);
    }
    else {
        printf("Error: Invalid pointers detected.\n");
        return;
    }
    if (q->first == NULL) {
        q->last = NULL;
    }
    q->first = q->first->pnextList;
    //free(temp);
}

// Освобождение памяти, выделенной под элементы очереди
void freeQueue(struct Queue *q) {
    while (!isEmptyQ(q)) {
        get(q,NULL);
    }
}

void printQueue(struct Queue *q) {
    if (isEmptyQ(q)) {
        printf("Queue is empty.\n");
        return;
    }

  //  printf("Queue contents: ");
    struct list *current = q->first;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->pnextList;
    }
}