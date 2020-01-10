#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EMPTY_TOS -1
#define MIN_STACK_SIZE 20

struct stack_record_char
{
    unsigned int stack_size;
    int top_of_stack;
    char *stack_array;
};

struct stack_record_num
{
    unsigned int stack_size;
    int top_of_stack;
    long *stack_array;
};

typedef struct stack_record_char *STACK_C;
typedef struct stack_record_num *STACK_N;

STACK_C CreateStack_C(unsigned int max_elements)
{
    STACK_C S;
    if (max_elements < MIN_STACK_SIZE)
    {
        printf("\nThe size is too small");
        return NULL;
    }
    S = (STACK_C)malloc(sizeof(struct stack_record_char));
    if (S == NULL)
    {
        printf("\nOut of space");
        return NULL;
    }
    S->stack_array = (char *)malloc(sizeof(char) * max_elements);
    if (S->stack_array == NULL)
    {
        printf("\nOut of space");
        return NULL;
    }
    S->stack_size = max_elements;
    S->top_of_stack = EMPTY_TOS;
    return S;
}

STACK_N CreateStack_N(unsigned int max_elements)
{
    STACK_N S;
    if (max_elements < MIN_STACK_SIZE)
    {
        printf("\nThe size is too small");
        return NULL;
    }
    S = (STACK_N)malloc(sizeof(struct stack_record_num));
    if (S == NULL)
    {
        printf("NULL");
        return NULL;
    }
    S->stack_array = (long *)malloc(sizeof(long) * max_elements);
    if (S->stack_array == NULL)
    {
        printf("NULL");
        return NULL;
    }
    S->stack_size = max_elements;
    S->top_of_stack = EMPTY_TOS;
    return S;
}

int is_valid(char *exp)
{
    int count = 0;
    char c;
    if (exp == NULL)
    {
        printf("\nNull Error");
        return 0;
    }
    c = *exp;
    while (c != 0)
    {
        if ((c > 57 || c < 48) && (c < 40 || c > 43) && c != 45 && c != 47)
        {
            printf("\ninvalid");
            return 0;
        }
        c = *(exp + ++count);
    }
    return 1;
}

long char2long(char c)
{
    if (c > 57 || c < 48)
        return -1;
    else
        return (long)(c - 48);
}

int is_empty_C(STACK_C S)
{
    if (S == NULL)
    {
        printf("NULL");
        exit(0);
    }
    if (S->top_of_stack == EMPTY_TOS)
        return 1;
    else
        return 0;
}

int is_empty_N(STACK_N S)
{
    if (S == NULL)
    {
        printf("NULL");
        exit(0);
    }
    if (S->top_of_stack == EMPTY_TOS)
        return 1;
    else
        return 0;
}

int is_full_C(STACK_C S)
{
    if (S != NULL)
    {
        if (S->top_of_stack == S->stack_size - 1)
            return 1;
        else
            return 0;
    }
}

int is_full_N(STACK_N S)
{
    if (S != NULL)
    {
        if (S->top_of_stack == S->stack_size - 1)
            return 1;
        else
            return 0;
    }
}

void PushStack_C(char x, STACK_C S)
{
    if (is_full_C(S) == 1)
    {
        printf("NULL");
        exit(0);
    }
    S->stack_array[++S->top_of_stack] = x;
}

void PushStack_N(long x, STACK_N S)
{
    if (is_full_N(S) == 1)
    {
        printf("NULL");
        exit(0);
    }
    S->stack_array[++S->top_of_stack] = x;
}

char PopStack_C(STACK_C S)
{
    if (is_empty_C(S) == 1)
    {
        printf("NULL");
        exit(0);
    }
    return S->stack_array[S->top_of_stack--];
}

long PopStack_N(STACK_N S)
{
    if (is_empty_N(S) == 1)
    {
        printf("NULL");
        exit(0);
    }
    return S->stack_array[S->top_of_stack--];
}

char TopStack_C(STACK_C S)
{
    if (is_empty_C(S) == 1)
    {
        printf("NULL");
        exit(0);
    }
    return S->stack_array[S->top_of_stack];
}

long TopStack_N(STACK_N S)
{
    if (is_empty_N(S) == 1)
    {
        printf("NULL");
        exit(0);
    }
    return S->stack_array[S->top_of_stack];
}

void D_Cal(STACK_N OPD, char c)
{
    long num_1, num_2;
    if (c == '+')
    {
        num_1 = PopStack_N(OPD);
        num_2 = PopStack_N(OPD);
        PushStack_N(num_1 + num_2, OPD);
    }
    else if (c == '*')
    {
        num_1 = PopStack_N(OPD);
        num_2 = PopStack_N(OPD);
        PushStack_N(num_1 * num_2, OPD);
    }
    else if (c == '/')
    {
        num_1 = PopStack_N(OPD);
        num_2 = PopStack_N(OPD);
        if (num_1 == 0)
        {
            printf("NULL");
            exit(0);
        }
        PushStack_N(num_2 / num_1, OPD);
    }
    else if (c == '^')
    {
        num_1 = PopStack_N(OPD);
        num_2 = PopStack_N(OPD);
        if (num_1 <= 0 && num_2 == 0)
        {
            printf("NULL");
            exit(0);
        }
        PushStack_N((long)pow(num_2, num_1), OPD);
    }
    else if (c == '-')
    {
        num_1 = PopStack_N(OPD);
        num_2 = PopStack_N(OPD);
        PushStack_N(num_2 - num_1, OPD);
    }
    else
    {
        printf("NULL");
        exit(0);
    }
}

void main()
{
    STACK_C OPR;
    STACK_N OPD;
    char c, exp[210];
    int count = 0;
    long num = 0;
    OPR = CreateStack_C(200);
    OPD = CreateStack_N(200);
    gets(exp);
    c = *exp;
    while (c != 0)
    {
        if (c > 47 && c < 58) //数字0到9
        {
            num = char2long(c);
            c = *(exp + ++count);
            while (c > 47 && c < 58)
            {
                num = num * 10 + char2long(c);
                c = *(exp + ++count);
                ;
            }
            PushStack_N(num, OPD);
            count--;
        }
        else if (c == 'a') //abs() 用[]标记
        {
            if (*(exp + ++count) == 'b' && *(exp + ++count) == 's' && *(exp + ++count) == '(')
                PushStack_C('[', OPR);
            else
            {
                printf("NULL");
                return;
            }
        }
        else if (c == '(')
            PushStack_C(c, OPR);
        else if (c == '-' || c == '+') //使用之前的 + -
        {
            if (count == 0 || *(exp + count - 1) == '(')
                PushStack_N(0, OPD);
            while (!is_empty_C(OPR) && (TopStack_C(OPR) == '-' || TopStack_C(OPR) == '+'))
                D_Cal(OPD, PopStack_C(OPR));
            PushStack_C(c, OPR);
        }
        else if (c == '*' || c == '/')
        {
            while (!is_empty_C(OPR) && TopStack_C(OPR) != '(' && TopStack_C(OPR) != '[' && TopStack_C(OPR) != '^')
                D_Cal(OPD, PopStack_C(OPR));
            PushStack_C(c, OPR);
        }
        else if (c == '^')
        {
            while (!is_empty_C(OPR) && TopStack_C(OPR) != '(' && TopStack_C(OPR) != '[')
                D_Cal(OPD, PopStack_C(OPR));
            PushStack_C(c, OPR);
        }
        else if (c == ')')
        {
            while (!is_empty_C(OPR) && TopStack_C(OPR) != '(' && TopStack_C(OPR) != '[')
                D_Cal(OPD, PopStack_C(OPR));
            if (TopStack_C(OPR) == '(')
                PopStack_C(OPR);
            else if (TopStack_C(OPR) == '[')
            {
                PushStack_N(abs(PopStack_N(OPD)), OPD);
                PopStack_C(OPR);
            }
            else
            {
                printf("NULL");
                return;
            }
        }
        c = *(exp + ++count);
    }
    while (!is_empty_C(OPR))
        D_Cal(OPD, PopStack_C(OPR));
    num = PopStack_N(OPD);
    if (!is_empty_N(OPD))
    {
        printf("NULL");
        return;
    }
    else
    {
        printf("%ld", num);
        return;
    }
}