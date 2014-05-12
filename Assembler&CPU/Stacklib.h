//{===========================================================
//! @file Stacklib.c
//============================================================}
#ifndef STACKLIB_H_INCLUDED
#define STACKLIB_H_INCLUDED

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define MAX_SIZE 1000
//#define COOL_PRINT
//#define VERY_COOL_PRINT

struct Stack_str
{
    int my_max_size;
    int numb;
    double* data;
};

typedef struct Stack_str Stackt;

int Stack_construct ( Stackt* my_stack, int my_size );

int Stack_ok ( Stackt* my_stack );

int Stack_push ( Stackt* my_stack, double new_data );

double Stack_pop ( Stackt* my_stack );

int Stack_full ( Stackt* my_stack );

int Stack_empty ( Stackt* my_stack );

int Stack_dump ( Stackt* my_stack );

int Stack_destruct ( Stackt* my_stack );

#endif // STACKLIB_H_INCLUDED
