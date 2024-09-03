#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "obj.h"
#include "functions.h"
#define BUFFERLENGTH 400
#define ALPLENGTH 25

struct Queue* postfix_notation(char* buffer);
void calculator(struct Queue* q, char* operands, char values[][BUFFERSIZE], int per_amt);
int check_operands(char* operands, char* buffer);

//Converts an expression in infix notation to postfix one using Dijkstra's algorithm.
struct Queue* postfix_notation(char* buffer)
{
    struct Stack Tehas;
    initializeStack(&Tehas);
    struct Queue California;
    initializeQueue(&California);
    char tempstr[BUFFERSIZE];
    Clear(tempstr, BUFFERSIZE);
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if (isalpha(buffer[i]))
        {
            int j = 0;
            while (isalpha(buffer[i])) tempstr[j++] = buffer[i++];
            i--;
            if (strlen(tempstr) == 1) //if variables put in queue
            {
                put(&California, tempstr);
            }
            else goto operationslogic;//if functions
            Clear(tempstr, BUFFERSIZE);
        }
        else if (isdigit(buffer[i]))
        {
            int j = 0;
            while (isdigit(buffer[i]) || buffer[i] == '.') tempstr[j++] = buffer[i++];
            i--;
            put(&California, tempstr);
            Clear(tempstr, BUFFERSIZE);
        }
        else if (buffer[i] == '(')
        {
            tempstr[0] = buffer[i];
            tempstr[1] = '\0';
            push(&Tehas, tempstr);
            Clear(tempstr, BUFFERSIZE);
        }
        else if (buffer[i] == ')')
        {
            char r[BUFFERSIZE];
            while (!isEmptyS(&Tehas) && Tehas.top->data[0] != '(') {
                char result[BUFFERSIZE] = { 0 };
                pop(&Tehas, result);
                put(&California, result);
            }
            if (!isEmptyS(&Tehas)) pop(&Tehas, r);
        }
        else if (buffer[i] != ' ') //operations like + - * etc.
        {
            tempstr[0] = buffer[i];
            tempstr[1] = '\0';
        operationslogic://!!! here functions like sqrt sin cos and etc. are added.
            while (!isEmptyS(&Tehas) && operation_priority(Tehas.top->data) >= operation_priority(tempstr)) {
                char result[BUFFERSIZE] = { 0 };
                pop(&Tehas, result);
                put(&California, result);
            }
            push(&Tehas, tempstr);
            Clear(tempstr, BUFFERSIZE);
        }
    }
    while (!isEmptyS(&Tehas)) {
        char result[BUFFERSIZE] = { 0 };
        pop(&Tehas, result);
        put(&California, result);
    }
    return &California;
}

//Doing some operations in postfix notatin in queue with stack
void calculator(struct Queue* q, char* operands, char values[][BUFFERSIZE], int per_amt)
{
    struct list* current = q->first;
    struct Stack stack;
    initializeStack(&stack);
    char res[BUFFERSIZE] = { 0 };
    while (current != NULL)
    {
        Clear(res, BUFFERSIZE);
        get(q, res);
        int flag = demarcation(res);
        switch (flag)
        {
        case 1:
            push(&stack, res);
            break;
        case 2:
        {
            int ind = massivesearch(operands, res[0], per_amt);
            if (ind != (-1)) push(&stack, values[ind]);
            break;}
        case 3:
            calculation(&res, &stack);
            break;
        default:
            break;
        }
        current = current->pnextList;
    }
    printf("\nRESULT:%s", stack.top->data);
}

//Add variable names from buffer in operands massive.
//Return variebles amount
int check_operands(char* operands, char* buffer)
{
    int kol = 0;
    int flag = 0;
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        flag = 0;
        if (isalpha(buffer[i]))
        {
            if ((i == 0 && !isalpha(buffer[i + 1])) || (i > 0 && buffer[i + 1] != '\0' && !isalpha(buffer[i + 1]) && !isalpha(buffer[i - 1])) || (i > 0 && buffer[i + 1] == '\0' && !isalpha(buffer[i - 1])))
            {
                flag = 1;
            }
            if (flag == 1)
            {
                if (massivesearch(operands, buffer[i], kol) == (-1)) {
                    operands[kol++] = buffer[i];
                }
            }
        }
    }
    return kol;
}


int main(void)
{
    char buffer[BUFFERLENGTH] = { 0 };
    char operands[ALPLENGTH] = { 0 };
    printf("Enter expression>>>> ");
    fflush(stdin);
    fgets(buffer, 400, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    int per_amt = check_operands(operands, buffer);
    char values[ALPLENGTH][BUFFERSIZE];

    for (int i = 0; i < per_amt; i++)
    {
        printf("Enter value of variable %c >>>", operands[i]);
        fflush(stdin);
        fgets(&values[i], BUFFERSIZE, stdin);
        values[i][strlen(values[i]) - 1] = '\0';
    }

    struct Queue* q = postfix_notation(buffer);
    printf("Expression in postfix notation: ");
    printQueue(q);
    printf("\n");

    calculator(q, operands, values, per_amt);
}