#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265358979323846

double factorial(double n);
void calculation(char* operation, struct Stack* s);
int massivesearch(char massive[], char data, int n);
int operation_priority(char* operation);
int demarcation(char* str);


double factorial(double n) {
    if (n < 0) {
        printf("Error: negative value\n");
        return -1.0;
    }
    double result = 1.0;
    for (int i = 1; i <= (int)n; i++) {
        result *= i;
    }

    return result;
}
void calculation(char* operation, struct Stack* s) {
    char operations[15][5] = { "cos" , "sin" , "tg" , "ctg" , "asin", "acos" , "atg", "actg", "sqrt", "!", "^", "/", "*", "+", "-" };
    char value1[BUFFERSIZE] = { 0 }, value2[BUFFERSIZE] = { 0 };

    if (strcmp(operations[0], operation) == 0) {
        pop(s, value1);
        double result = cos(atof(value1));
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[1], operation) == 0) {
        pop(s, value1);
        double result = sin(atof(value1));
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[2], operation) == 0) {
        pop(s, value1);
        double result = tan(atof(value1));
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[3], operation) == 0) {
        pop(s, value1);
        double result = tan(M_PI / 2 - atof(value1));
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[4], operation) == 0) {
        pop(s, value1);
        double result = acos(atof(value1));
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[5], operation) == 0) {
        pop(s, value1);
        double result = asin(atof(value1));
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[6], operation) == 0) {
        pop(s, value1);
        double result = atan(atof(value1));
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[7], operation) == 0) {
        pop(s, value1);
        double result = M_PI / 2 - atan(atof(value1));
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[8], operation) == 0) {
        pop(s, value1);
        if (atof(value1) < 0) printf("\nERROR: value in sqrt is negative");
        double result = sqrt(atof(value1));
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[9], operation) == 0) {
        pop(s, value1);
        if (atof(value1) < 0) printf("\nERROR: value in factorial is negative");
        double result = factorial(atof(value1));
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[10], operation) == 0) {
        pop(s, value2);
        pop(s, value1);
        double result = pow(atof(value1), atof(value2));
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[11], operation) == 0) {
        pop(s, value2);
        pop(s, value1);
        double result = atof(value1) / atof(value2);
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[12], operation) == 0) {
        pop(s, value2);
        pop(s, value1);
        double result = atof(value1) * atof(value2);
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[13], operation) == 0) {
        pop(s, value2);
        pop(s, value1);
        double result = atof(value1) + atof(value2);
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
    else if (strcmp(operations[14], operation) == 0) {
        pop(s, value2);
        pop(s, value1);
        double result = atof(value1) - atof(value2);
        char resultStr[BUFFERSIZE];
        snprintf(resultStr, BUFFERSIZE, "%f", result);
        push(s, resultStr);
    }
}


int massivesearch(char massive[], char data, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (massive[i] == data) return i;
    }
    return -1;
}

//Get operation priority
int operation_priority(char* operation)
{
    if (strlen(operation) == 1)
    {
        if (operation[0] == '^' || operation[0] == '!') return 3;
        if (operation[0] == '/' || operation[0] == '*') return 2;
        if (operation[0] == '+' || operation[0] == '-') return 1;
        if (operation[0] == '(') return 0;
    }
    else if (strlen(operation) > 1)
    {
        return 4;//functions sin cos etc.
    }
    else return -1;//unknown operation
}
//return 1 if digit
//return 2 if variable 
//return 3 if operation or function
int demarcation(char* str)
{
    if (isdigit(str[0])) return 1;
    else if (isalpha(str[0]) && strlen(str) == 1) return 2;
    else if (strlen(str) == 0) return -1; //some trash
    else return 3;//operations and functions
}